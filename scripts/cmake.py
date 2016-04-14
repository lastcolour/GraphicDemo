__all__ = ["CmakeRunner"]

import os
import sys
import platform

from utils import runCMD
from utils import setUpEnv
from utils import tryFormat

from logger import log


_CMAKE_LOG_FILE = "lastCmakeRun.log"


class CmakeRunner:

    def __init__(self, cmakeConfig):
        self._config = cmakeConfig
        self._currBuild = None
        self._rootPath = None
        self._buildDict = None
        self._buildPath = None
        self._generator = None

    def setGenerator(self, genName):
        self._generator = genName

    def setRootPath(self, path):
        self._rootPath = path

    def run(self, buildType):
        assert self._rootPath is not None # check that root path specified
        self._setUpBuildInfo(buildType)
        cmakeCMD = "cmake -H." + self._getBuildDirCMD() + self._getGenCMD() + self._getDefsCMD()
        with open(self._getLogFile(), "w+") as tFile:
            setUpEnv(self._getEnvVars())
            try:
                tProcessOut = runCMD(cmakeCMD, workDir=self._getRunDir(), pipe=tFile,
                                     isShell=platform.system() is not "Windows")
            except:
                log.error("[Error] Can't run cmake: {0} ".format(sys.exc_info()[1]))
                return None
            else:
                log.info("[Info] Cmake log saved to: {0}".format(self._getLogFile()))
                if tProcessOut["ret_code"] != 0:
                    self._printNiceFailLog(tProcessOut["out"])
                    return None
                else:
                    return self._buildDict

    def _printNiceFailLog(self, processOut):
        pass

    def _getRunDir(self):
        return self._rootPath + "/" + self._config["run_dir"]

    def _getLogFile(self):
        return self._buildPath + "/" + _CMAKE_LOG_FILE

    def _getBuildDirCMD(self):
        self._buildPath = self._rootPath + "/" + tryFormat(self._config["out_dir"], self._buildDict)
        self._buildDict["CMAKE_OUT_DIR"] = self._buildPath
        if not os.path.exists(self._buildPath):
            try:
                os.makedirs(self._buildPath)
            except:
                log.error("[Error] Can't create cmake out dir: {0}".format(self._buildPath))
                log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
                raise
        return  " -B{0}".format(self._buildPath)

    def _getGenCMD(self):
        self._buildDict["COMPILER"] = self._extractCompilerFromGenerator(self._generator)
        if self._generator is not None:
            return " -G\"{0}\"".format(self._generator)
        return ""

    def _extractCompilerFromGenerator(self, generator):
        if generator is None:
            raise Exception("Generator for cmake not specified")
        else:
            tGenStr = generator.lower().split()
            if "studio" in tGenStr:
                return "MSVC"
            else:
                return "MAKE"

    def _getDefsCMD(self):
        defsItems = []
        if "defs" in self._config["common"] and len(self._config["common"]["defs"]) > 0:
            defsItems.extend(self._config["common"]["defs"])
        tCurrBuild = self._currBuild.lower()
        if "defs" in self._config[tCurrBuild] and len(self._config[tCurrBuild]["defs"]) > 0:
            defsItems.extend(self._config[tCurrBuild]["defs"])
        if len(defsItems) == 0:
            return ""
        resultDefsStr = ""
        for defGroup in defsItems:
            tTypeStr = ""
            if "type" in defGroup:
                tTypeStr = ":{0}".format(defGroup.pop("type"))
            for elem in defGroup:
                resultDefsStr += " -D{0}{1}={2}".format(elem, tTypeStr, defGroup[elem])
        return resultDefsStr

    def _getEnvVars(self):
        return None

    def _setUpBuildInfo(self, buildType):
        self._currBuild = buildType.lower().title()
        tBuildDict = dict()
        tBuildDict["BUILD_TYPE"] = self._currBuild
        tBuildDict["PLATFORM"] = platform.system()
        self._buildDict = tBuildDict


