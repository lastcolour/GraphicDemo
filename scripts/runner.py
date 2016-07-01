from logger import log

class Runner:
  def __init__(self):
    self._binPath = None

  def _printNiceLog(self, logMsg):
     pass

  def _getLogPath(self):
      return None

  def setBinPath(self, path):
      self._binPath = path

  def run(self, project, buildType):
    pass


class CmakeRunner(Runner):
    """Generate project files"""
    def __init__(self):
        Runner.__init__(self)
        self._runDir = None
        self._outDir = None
        self._runConfig = {}

    def addRunConfig(self, runType, config):
        self._runConfig[runType.lower()] = config

    def setRunDir(self, dirPath):
        self._runDir = dirPath

    def setOutDir(self, dirPath):
        self._outDir = dirPath

    def _doApplyConfig(self, project, buildType, config):
        pass

    def _applyConfig(self, project, buildType):
        tNeedApply = ["common", buildType.lower()]
        for item in tNeedApply:
            if item in self._runConfig:
                self._doApplyConfig(project, buildType, self._runConfig[item])
            else:
                log.debug("[Debug] Absent cmake run config: {0}".format(item))

    def run(self, project, buildType):
        self._applyConfig(project, buildType)


class CompilerRunner(Runner):
    """Build project"""
    def __init__(self):
        Runner.__init__(self)

    def run(self, project, buildType):
        pass