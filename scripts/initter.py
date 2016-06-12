import os
import sys
import platform

from logger import log

from ConfigParser import SafeConfigParser


_DEF_CONFIG_FILENAME = "local-config.ini"

_DEF_PROJECT = "LightingApp"
_DEF_WIN_GENERATOR = "Visual Studio 14 Win64"
_DEF_LIN_GENERATOR = "Eclipse CDT4 - Unix Makefiles"

class Initializer:
  def __init__(self):
    self._config = None

  def initLocal(self):
    if os.path.exists(_DEF_CONFIG_FILENAME):
      self._config = self._loadLocalConfig(_DEF_CONFIG_FILENAME)
    else:
      self._config = self._createDefConfig(_DEF_CONFIG_FILENAME)
    return self._config is not None

  def _createDefConfig(self, filename):
    tConfig = SafeConfigParser()
    # Default project values
    tConfig.add_section("project")
    tConfig.set("project", "default", _DEF_PROJECT)
    # Default cmake values
    tConfig.add_section("cmake")
    if platform.system().lower() == "windows":
      tConfig.set("cmake", "generator", _DEF_WIN_GENERATOR)
    else:
      tConfig.set("cmake", "generator", _DEF_LIN_GENERATOR)
    self._config = tConfig
    try:
      with open(filename, "w") as tFile:
        tConfig.write(tFile)
    except:
      log.error("[Error] Can't create local config file: {0}".format(_DEF_CONFIG_FILENAME))
      log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
      return None
    else:
      log.info("[Warning] Created default config in: {0}".format(filename))
      return tConfig

  def _loadLocalConfig(self, filename):
    try:
      tConfig = SafeConfigParser()
      tConfig.read(filename)
      log.info("[Info] Loaded config from: {0}".format(filename))
      return tConfig
    except:
      log.error("[Error] Can't load local config from: {0}".format(filename))
      log.debug("[Error] Problem: {0}".format(sys.exc_info()[1]))
      return None

  def getCMAKEGenerator(self):
    if self._config is None:
      return None
    return self._config.get("cmake", "generator")

  def getConfigPath(self):
    return _DEF_CONFIG_FILENAME

  def getDefProject(self):
    if self._config is None:
      return None
    return self._config.get("project", "default")
