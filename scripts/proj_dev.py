import os
import sys
import json

from logger import log

from utils import runCMD

_ROOT = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")
_CONFIG_ROOT = _ROOT + "/config/projects"

_CMAKE_LOG_FILE = "lastCmakeRun.log"

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


class DependError(RuntimeError):
    def __init__(self, depErr):
        self._depErr = depErr
    def __str__(self):
        return  self._depErr


class Project:
    def __init__(self, configFile, parent=None):
        self._parent = parent
        self._depList = []
        self._model = self._loadModel(configFile)

    def getName(self):
        return self._model["name"]

    def build(self, buildType):
        log.info("[Info][{0}] Start build target: {0}".format(self.getName()))
        for depProj in self._depList:
            if not depProj.build(buildType):
                log.error("[Error][{0}] Can't build dep project: {1}".format(self.getName(), depProj.getName()))
                return False
        return self._doBuild(buildType)

    def _setBuildType(self, buildType):
        pass

    def _setLinkType(self, linkType):
        pass

    def _loadModel(self, filename):
        try:
            with open(filename, "r") as tFile:
              tModel =  json.load(tFile)
              self._model = tModel # TODO: Remove deps from model
              if "deps" in tModel:
                  for depItem in tModel["deps"]:
                      self._depList.append(self._loadDepProject(depItem))
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
            if self._parent is not None:
                log.info("[Info][{0}] Loaded project: {1}".format(self._parent.getName(), self.getName()))
            else:
                log.info("[Info][{0}] Loaded -- OK".format(self.getName()))
            return tModel

    def _loadDepProject(self, depInfo):
       tDepProj = Project(depInfo["project"], parent=self)
       tDepProj._setBuildType(depInfo["type"])
       tDepProj._setLinkType(depInfo["link"])
       return tDepProj

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
        tCmakeCmd = "cmake -H." + cmakeConfig["defs"]
        tCmakeLogFile = cmakeConfig["run_dir"] + "/" + _CMAKE_LOG_FILE
        try:
            with open(tCmakeLogFile, "w+") as tFile:
               cmakeOut = runCMD(tCmakeCmd, workDir=cmakeConfig["work_dir"], pipe=tFile, isShell=Platform["shell"])
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
        return False

    def _doInstall(self, buildType):
        return False

    def _doCleanAfterBuild(self, buildType):
        return False
    def _getCmakeRunDir(self):
        return ""

    def _getCmakeDefs(self, buildType):
        return None

    def _getCmakeEnvs(self, buildType):
        return None

    def _getCmakeOutDir(self, buildType):
        return None

    def _getCompileRunDir(self):
        pass

    def _genCmakeProject(self, buildType):
        cmakeConfig = dict()
        cmakeConfig["build_type"] = buildType
        cmakeConfig["run_dir"] = self._getCmakeRunDir()
        cmakeConfig["out_dir"] = self._getCmakeOutDir(buildType)
        cmakeConfig["defs"] = self._getCmakeDefs(buildType)
        cmakeConfig["envs"] = self._getCmakeEnvs(buildType)
        return self._runCmake(cmakeConfig)

    def _createBins(self, buildType):
        compileConfig = dict()
        compileConfig["build_type"] = buildType
        compileConfig["run_dir"] = self._getCompileRunDir()
        return self._runCompiler(compileConfig)


def main():
    proj = Project("DemoApp.json")
    proj.build("debug")


if __name__ == "__main__":
    main()