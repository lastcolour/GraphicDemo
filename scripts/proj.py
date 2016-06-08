__all__ = ["Project"]

import os
import sys
import json

from logger import log

from utils import tryFormat
from utils import copyFiles

from cmake import CmakeRunner
from compile import CompileRunner

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


_OUT_DIR_NAME = "_out/" + Platform["name"]


class DependError(RuntimeError):
    def __init__(self, depErr):
        self._depErr = depErr
    def __str__(self):
        return  self._depErr


class Project:

    # TODO: Move model to other class
    # TODO: Add build dict as member of Project instance
    # TODO: Move project creation to ProjectBuilder class

    _CONFIG_ROOT = ""
    _REPO_ROOT = ""

    def __init__(self, projectName, parent=None):
        self._parent = parent
        self._installFlag = False
        self._cmakeOutDir = None
        self._cmakeGenerator = None
        self._depProjects = dict()
        self._fast = False
        self._loadModel(projectName)

    def setSkip3dParty(self, flag):
        self._fast = flag
        for depProjName in self._depProjects:
          tProjectNode = self._depProjects[depProjName]["project"]
          tProjectNode.setSkip3dParty(self._fast)

    def getName(self):
        return self._model["name"]

    def cleanUp(self):
        # TODO: Implement this method
        log.warning("[Warning] Project CleanUP not implemented")

    @staticmethod
    def intializePaths(pathInfo):
        Project._CONFIG_ROOT = pathInfo["config_root"]
        Project._REPO_ROOT = pathInfo["repo_root"]

    def _absPath(self, path):
       tPath = ""
       if path != "":
           tPath = "/" + path
       return os.path.abspath(self._CONFIG_ROOT + tPath)

    def is3dParty(self):
        return self._model["3dParty"]

    def build(self, buildType):
        self._targetBuildType = buildType
        log.info("[Info][{0}] Start build target: {0}".format(self.getName()))
        for depProjName in self._depProjects:
            tProjectNode = self._depProjects[depProjName]
            if tProjectNode["project"].is3dParty() and self._fast:
               log.info("[Info] Skip build of 3rd party project: {0}".format(depProjName))
               continue
            tBuildDict = {"OUT_DIR"   : self._getInstallRoot(),
                          "BUILD_TYPE": buildType,
                          "PLATFORM"  : Platform["name"]}
            if "install" in tProjectNode:
                tInstallPath = tryFormat(tProjectNode["install"]["path"], tBuildDict)
                tProjectNode["project"]._setCustomInstallPath(tInstallPath)
            if not tProjectNode["project"].build(self._getDepBuildType(tProjectNode["type"])):
                log.error("[Error][{0}] Can't build dep project: {1}".format(self.getName(), depProjName))
                return False
        return self._doBuild(buildType)

    def _getDepBuildType(self, depBuildType):
        try:
            return depBuildType.format(BUILD_TYPE=self._targetBuildType)
        except KeyError:
            return depBuildType

    def _setCustomInstallPath(self, path):
        for item in self._model["install"]["groups"]:
            item["to"] = path

    def _loadModel(self, projectName):
        if "json" in projectName.split("."):
            tPrefix = ""
        else:
            tPrefix = ".json"
        tConfigFile = "{0}/{1}".format(Project._CONFIG_ROOT, projectName) + tPrefix
        if not os.path.exists(tConfigFile):
            raise  RuntimeError("[Error] Can't find project config file: {0}".format(tConfigFile))
        try:
            with open(tConfigFile, "r") as tFile:
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
                raise DependError("Can't load dep project from file: {0}".format(tConfigFile))
            else:
                log.error("[Error] Unknown error when load project from: {0}".format(tConfigFile))
                raise
        else:
            log.info("[Info][{0}] Loaded -- OK".format(self.getName()))

    def _loadDepProject(self, depInfo):
        depInfo["project"] = Project(depInfo.pop("project"), parent=self)
        if "install" in depInfo:
            depInfo["project"]._setNeedInstall(True)
        self._depProjects[depInfo["project"].getName()] = depInfo

    def _setNeedInstall(self, flag):
        self._installFlag = flag

    def _setLinkType(self, linkType):
        self._linkType = linkType

    def setLocalConfig(self, config):
        self._cmakeGenerator = config.getCMAKEGenerator()

    def _doBuild(self, buildType):
        if not self._compileProject(buildType):
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
        return self._installFlag

    def _needCleanAfterBuild(self, buildType):
        return False

    def _doInstall(self, buildType):
        if not "install" in self._model or "groups" not in self._model["install"]:
            log.info("[Info][{0}] Can't find install config. Skip installing".format(self.getName()))
            return True
        inGroups = self._model["install"]["groups"]
        tBuildValues =  {"PLATFORM"     : Platform["name"],
                         "BUILD_TYPE"   : buildType if Platform["short_name"] is "win" else "",
                         "OUT_DIR"      : self._getInstallRoot(),
                         "CMAKE_OUT_DIR": self._cmakeOutDir}
        for inItem in inGroups:
            log.info("[Info][{0}] Install files: {1}".format(self.getName(), inItem["name"]))
            try:
                copyFiles(inItem["files"], tryFormat(inItem["from"], tBuildValues),
                                           tryFormat(inItem["to"], tBuildValues))
            except:
                log.error("[Error][{0}] Can't install files: {1}".format(self.getName(), inItem["files"]))
                log.error("[Error][{0}] Problem: {1}".format(self.getName(), sys.exc_info()[1]))
                return False
        return True

    def _doCleanAfterBuild(self, buildType):
        return False

    def _getInstallRoot(self):
        return Project._REPO_ROOT + "/" + "_out"

    def _getCmakeGen(self):
        if self._parent is not None:
            return self._parent._getCmakeGen()
        else:
            return self._cmakeGenerator

    def _compileProject(self, buildType):
        tCmakeRunner = CmakeRunner(self._model["cmake"])
        tCmakeRunner.setGenerator(self._getCmakeGen())
        tCmakeRunner.setRootPath(Project._REPO_ROOT)
        tCmakeInfo = tCmakeRunner.run(buildType)
        if tCmakeInfo is None:
            log.error("[Error][{0}] Can't generate project files by cmake".format(self.getName()))
            return False
        else:
            log.info("[Info][{0}] Cmake generation -- OK".format(self.getName()))
            self._cmakeOutDir = tCmakeInfo["CMAKE_OUT_DIR"] # TODO Remove this
        tCompileRunner = CompileRunner(tCmakeInfo)
        return tCompileRunner.run()