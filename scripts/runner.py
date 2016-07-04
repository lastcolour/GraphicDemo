import os
import sys

from logger import log
from utils import runCMD

class Runner:

    _ROOT_PATH = None

    def __init__(self):
        self._binPath = None
        self._outDir = None
        self._logName = None
        self._runDir = None

    def _printNiceLog(self, logMsg):
        pass

    @staticmethod
    def setRootPath(path):
        Runner._ROOT_PATH = path
        if not os.path.exists(path):
            raise Exception("Can't find root path: {0}".format(path))

    def _getAbsPath(self, somePath):
         return os.path.abspath(Runner._ROOT_PATH + "/" + somePath)

    def setRunDir(self, dirPath):
        self._runDir = self._getAbsPath(dirPath)

    def setOutDir(self, dirPath):
        self._outDir = self._getAbsPath(dirPath)

    def setBinPath(self, path):
        self._binPath = path

    def run(self, project, buildType):
         pass


class CmakeRunner(Runner):
    """Generate project files"""
    def __init__(self):
        Runner.__init__(self)
        self._runConfig = {}

    def addRunConfig(self, runType, config):
        self._runConfig[runType.lower()] = config

    def _doApplyConfig(self, project, buildType, config):
        pass

    def _applyConfig(self, project):
        pass

    def _doRun(self):
        pass

    def run(self, project):
        self._applyConfig(project)


class CompilerRunner(Runner):
    """Build project"""
    def __init__(self):
        Runner.__init__(self)

    def run(self, project):
        pass