__all__ = ["CompileRunner"]

import sys
import platform

from utils import runCMD

from logger import log

_COMPILE_LOG_FILE = "lastCompileRun.log"


class CompileRunner:

    def __init__(self, cmakeRunInfo):
        self._config = cmakeRunInfo

    def run(self):
        tCompCmd = self._formatCompileCMD()
        try:
            tCompileLog = self._getLogFileName()
            with open(tCompileLog, "w+") as tFile:
                compileOut = runCMD(tCompCmd, workDir=self._getRunDir(), pipe=tFile,
                                    isShell=platform.system() is not "Windows")
        except:
            log.error("[Error] Can't compile project: {0}".format(sys.exc_info()[1]))
            return False
        else:
            log.info("[Info] Compile log saved to: {0}".format(tCompileLog))
            if compileOut["ret_code"] != 0:
                log.error("[Error] {0} Compiler log {1}".format("=" * 20, "=" * 20))
                self._printNiceFailLog(compileOut["out"])
                log.error("[Error] {0}".format("-" * 51))
                return False
            else:
                return True

    def _printNiceFailLog(self, processOutStr):
        tLineDecoration = "|"
        for line in processOutStr.split("\n"):
           log.warning("{0} {1}".format(tLineDecoration, line))

    def _formatCompileCMD(self):
        if self._config["COMPILER"] is "MSVC":
            return self._formatStudioCMD()
        elif self._config["COMPILER"] is "MAKE":
            return self._formatMakeCMD()
        else:
            raise Exception("Unsupported compiler: {0}".format(self._config["COMPILER"]))

    def _getLogFileName(self):
        return self._config["CMAKE_OUT_DIR"] + "/" + _COMPILE_LOG_FILE

    def _getRunDir(self):
        return self._config["CMAKE_OUT_DIR"]

    def _formatStudioCMD(self):
        return "devenv.com ALL_BUILD.vcxproj /Build {0}".format(self._config["BUILD_TYPE"])

    def _formatMakeCMD(self):
        return "make"