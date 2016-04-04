__all__ = ["Project"]

import os
import sys
import json

from logger import log

from utils import runCMD
from utils import setUpEnv
from utils import tryFormat

_DEF_WIN_GENERATOR = "Visual Studio 11"
_DEF_LIN_GENERATOR = "Ecplise CDT4 - Makefile Unix"

_CMAKE_LOG_FILE = "lastCmakeRun.log"
_COMPILE_LOG_FILE = "lastCompileRun.log"


def _getPlatformInfo():
  import platform
  tPlatform = dict()
  tPlatform["name"] = platform.system()
  if tPlatform["name"] == "Windows":
     tPlatform["shell"] = False
     tPlatform["app_ext"] = ".exe"
     tPlatform["short_name"] = "win"
  else:
    tPlatform["shell"] = True
    tPlatform["app_ext"] = ""
    tPlatform["short_name"] = "lin"
  return tPlatform
Platform = _getPlatformInfo()
del _getPlatformInfo


def formatCompileCmd(config):
    if Platform["name"] == "Windows":
        tCompCmd = "devenv.com  ALL_BUILD.vcxproj /Build {0}".format(config["build_type"])
    else:
        tCompCmd = "make"
    return tCompCmd

class DependError(RuntimeError):
    def __init__(self, depErr):
        self._depErr = depErr
    def __str__(self):
        return  self._depErr


class Project:

    _CONFIG_ROOT = ""
    _PROJECTS_ROOT = ""
    
    def __init__(self, configFile, parent=None):
        self._parent = parent
        self._cmakeOutDir = None
        self._depProjects = dict()
        self._loadModel(configFile)

    def getName(self):
        return self._model["name"]

    def cleanUp(self):
        # TODO: Implement this method
        pass
        
    @staticmethod
    def intializePaths(pathInfo):
        Project._CONFIG_ROOT = pathInfo["config_root"]
        Project._PROJECTS_ROOT = pathInfo["project_root"]
        
    def _absPath(self, path):
       tPath = ""
       if path != "":
           tPath = "/" + path
       return os.path.abspath(self._CONFIG_ROOT + tPath)

    def build(self, buildType):
        self._targetBuildType = buildType
        log.info("[Info][{0}] Start build target: {0}".format(self.getName()))
        for depProjName in self._depProjects:
            tProjectNode = self._depProjects[depProjName]
            if not tProjectNode["project"].build(self._getDepBuildType(tProjectNode["type"])):
                log.error("[Error][{0}] Can't build dep project: {1}".format(self.getName(), depProjName))
                return False
        return self._doBuild(buildType)

    def _getDepBuildType(self, depBuildType):
        try:
            return depBuildType.format(BUILD_TYPE=self._targetBuildType)
        except KeyError:
            return depBuildType

    def _loadModel(self, filename):
        try:
            with open(filename, "r") as tFile:
              self._model =  json.load(tFile)
              if "deps" in self._model:
                  for depItem in self._model.pop("deps"):
                      self._loadDepProject(depItem)
        except DependError as depEX:
            if self._parent is not None:
                log.error("[Error][{0}] Problem: {1}".format(self.getName(), depEX))
                raise DependError("Incomplete project: {0}".format(self.getName()))
            else:
               # can't format error suffix here, model not loaded
               log.error("[Error][{0}] Problem: {1}".format(self._model["name"], depEX))
               raise
        except:
            if self._parent is not None:
                raise DependError("Can't load dep project from file: {0}".format(filename))
            else:
                log.error("[Error] Unknown error when load project from: {0}".format(filename))
                raise
        else:
            log.info("[Info][{0}] Loaded -- OK".format(self.getName()))

    def _loadDepProject(self, depInfo):
        depInfo["project"] = Project(self._findProjectFile(depInfo.pop("project")))
        self._depProjects[depInfo["project"].getName()] = depInfo

    def _setLinkType(self, linkType):
        self._linkType = linkType

    def _doBuild(self, buildType):
        if not self._genCmakeProject(buildType):
            log.error("[Error][{0}] Can't generate project by cmake. See log for more info".format(self.getName()))
            return False
        log.info("[Info][{0}] Cmake generation -- OK".format(self.getName()))
        if not self._createBins(buildType):
            log.info("[Error][{0}] Can't compile project. See log for more info".format(self.getName()))
            return False
        log.info("[Info][{0}] Compiled -- OK".format(self.getName()))
        # Optional steps
        if self._needInstall():
            if not self._doInstall(buildType):
                log.error("[Error][{0}] Can't install produced binaries. See log for more info".format(self.getName()))
                return False
            log.info("[Info][{0}] Install -- OK".format(self.getName()))
        if self._needCleanAfterBuild(buildType):
            if not self._doCleanAfterBuild(buildType):
                log.error("[Error][{0}] Can't clean up after build".format(self.getName()))
                return False
            log.info("[Info][{0}] Clean up after build -- OK".format(self.getName()))
        # All steps success
        return True

    def _needInstall(self):
        return False

    def _needCleanAfterBuild(self, buildType):
        return False

    def _runCmake(self, cmakeConfig):
        tCmakeCmd = "cmake -H." + cmakeConfig["defs"] + " -B{0}".format(cmakeConfig["out_dir"])\
                    + " -G\"{0}\"".format(cmakeConfig["generator"])
        tCmakeLogFile = cmakeConfig["out_dir"] + "/" + _CMAKE_LOG_FILE
        if not os.path.exists(cmakeConfig["out_dir"]):
            try:
                os.makedirs(cmakeConfig["out_dir"])
            except:
                log.error("[Error] Can't create cmake out dir: {0}".format(cmakeConfig["out_dir"]))
                log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
                return False
        try:
            setUpEnv(cmakeConfig["envs"])
            with open(tCmakeLogFile, "w+") as tFile:
               cmakeOut = runCMD(tCmakeCmd, workDir=cmakeConfig["run_dir"], pipe=tFile, isShell=Platform["shell"])
        except:
            log.error("[Error][{0}] Can't run cmake: {1} ".format(self.getName(), sys.exc_info()[1]))
            return False
        else:
            log.info("[Info][{0}] Cmake log saved to: {1}".format(self.getName(), tCmakeLogFile))
            if cmakeOut["ret_code"] != 0:
                return False
            else:
                return True

    def _runCompiler(self, compileConfig):
        tCompCmd = formatCompileCmd(compileConfig)
        tCompileLog = compileConfig["run_dir"] + "/" + _COMPILE_LOG_FILE
        try:
            with open(tCompileLog, "w+") as tFile:
                compileOut = runCMD(tCompCmd, workDir=compileConfig["run_dir"], pipe=tFile, isShell=Platform["shell"])
        except:
            log.error("[Error][{0}] Can't compile project: {0}".format(self.getName(), sys.exc_info()[1]))
            return False
        else:
            log.info("[Info][{0}] Compile log saved to: {1}".format(self.getName(), tCompileLog))
            if compileOut["ret_code"] != 0:
                return False
            else:
                return True

    def _doInstall(self, buildType):
        return False

    def _doCleanAfterBuild(self, buildType):
        return False

    def _getCmakeRunDir(self):
        return self._model["cmake"]["run_dir"]

    def _getCmakeDefs(self, buildType):
        tBuildType = buildType.lower()
        defsItems = []
        tCmakeNode = self._model["cmake"]
        if "defs" in tCmakeNode["common"] and len(tCmakeNode["common"]["defs"]) > 0:
            defsItems.extend(tCmakeNode["common"]["defs"])
        if "defs" in tCmakeNode[tBuildType] and len(tCmakeNode[tBuildType]["defs"]) > 0:
            defsItems.extend(tCmakeNode[tBuildType]["defs"])
        if len(defsItems) == 0:
            return ""
        resultDefsStr = ""
        for defGroup in defsItems:
            for elem in defGroup:
                resultDefsStr += " -D{0}={1}".format(elem, defGroup[elem])
        return resultDefsStr

    def _getCmakeEnvs(self, buildType):
        return None

    def _getCmakeGenerator(self):
        if Platform["name"] == "Windows":
            # TODO: Move generator to some config
            tGenStr = _DEF_WIN_GENERATOR
        else:
            tGenStr = _DEF_LIN_GENERATOR
        return tGenStr

    def _getCmakeOutDir(self, buildType):
        tBuildValues =  {"PLATFORM"  : Platform["name"],
                         "BUILD_TYPE": buildType}
        self._cmakeOutDir = tryFormat(self._model["cmake"]["out_dir"], tBuildValues)
        return  self._cmakeOutDir

    def _getCompileRunDir(self):
        return self._cmakeOutDir

    def _genCmakeProject(self, buildType):
        cmakeConfig = dict()
        cmakeConfig["build_type"] = buildType
        cmakeConfig["run_dir"] = Project._PROJECTS_ROOT + "/" + self._getCmakeRunDir()
        cmakeConfig["out_dir"] = Project._PROJECTS_ROOT + "/" + self._getCmakeOutDir(buildType)
        cmakeConfig["generator"] = self._getCmakeGenerator()
        cmakeConfig["defs"] = self._getCmakeDefs(buildType)
        cmakeConfig["envs"] = self._getCmakeEnvs(buildType)
        return self._runCmake(cmakeConfig)

    def _createBins(self, buildType):
        compileConfig = dict()
        compileConfig["build_type"] = buildType
        compileConfig["run_dir"] = self._getCompileRunDir()
        return self._runCompiler(compileConfig)
        
    def _findProjectFile(self, projectFile):
        tPath = Project._CONFIG_ROOT + "/" + projectFile
        if not os.path.exists(tPath):
            raise DependError("Can't find project file: {0}".format(tPath))
        return tPath