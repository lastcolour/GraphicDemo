# author: Oleksii Zhogan (alexzhogan@gmail.com)

import os
import sys
import json
import platform

from logger import log

from utils import findAppsInENV
from utils import runCMD

from runner import Runner

from ConfigParser import SafeConfigParser

_CONFIG_FILE_NAME  = "toolchain.json"
_DEF_CONFIG_FILENAME = "local-config.ini"

_DEF_WIN_COMPILER = "MSVC"
_DEF_LIN_COMPILER = "MAKE"

class Initializer:
  def __init__(self, paths):
    Runner.setRootPath(paths["root"])
    self._repoPaths = paths
    self._validCompiler = None
    self._validCmake = None

  def getCmake(self):
    return self._validCmake

  def getCompiler(self):
    return self._validCompiler

  def initLocal(self):
    if os.path.exists(_DEF_CONFIG_FILENAME):
      self._config = self._loadLocalConfig(_DEF_CONFIG_FILENAME)
    else:
      self._config = self._createDefConfig(_DEF_CONFIG_FILENAME)
    return self._validateSW()

  def _getBinNames(self, swItem):
    # look in path only for Win OS
    if platform.system().lower() == "windows":
      tSWPathList = findAppsInENV(swItem["bin"])
      if len(tSWPathList) > 0:
        return [item + "/" for item in tSWPathList]
      else:
        log.error("[Error] Can't found: {0} in OS paths".format(swItem["bin"]))
        return []
    else:
      return [swItem["bin"]]

  def _doValidation(self, toolchain, swItemName):
      swItem = self._findToolItem(toolchain, swItemName)
      if swItem is None:
        log.error("[Error] Can't find in toolchain configs: {0}".format(swItemName))
        return None
      tSWPathList = self._getBinNames(swItem)
      tValidInfo = dict()
      hasValidVersion = False
      for item in tSWPathList:
        tFullBinName = "{0}{1}{2}".format(item, swItem["bin"],
                        ".exe" if ("." not in swItem["bin"] and platform.system().lower() == "windows") else "")
        log.info("[Info] Found {0}: {1}{2}".format(swItem["type"], swItemName,
                                                        " ({0})".format(swItem["full_name"]) if "full_name" in swItem else ""))
        log.info("[Info] > In: {0}".format(item))
        try:
          if self._checkToolVersion(tFullBinName, swItem["query"]):
            hasValidVersion = True
            log.info("[Info] > Supported!")
            tValidInfo["path"] = tFullBinName
            tValidInfo["name"] = swItemName
            break
          else:
            log.info("[Info] > Version: {0} -- Not supported".format(swItem["query"]["actual_ver"]))
        except:
          log.error("[Error] Can't get version of: {0}".format(swItemName))
          log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
      if hasValidVersion:
        return tValidInfo
      else:
         log.error("[Error] Required version of: {0} is: {1}".format(swItem["name"],
                                                                        swItem["query"]["match"]["value"]))

  def _makeVerEval(self, version, cmpOp, expVer):
      tEvalExpr = "{0} {1} {2}".format(int(version), cmpOp, expVer)
      try:
        tValue = eval(tEvalExpr)
      except:
        log.error("[Error] Can't compare versions: {0} <-> {1}, by {2}".format(version, expVer, cmpOp))
        log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
        return False
      else:
        return tValue

  def _isValidVersion(self, version, algoInfo):
    if not algoInfo["composite"]:
      return self._makeVerEval(version, algoInfo["type"], algoInfo["value"])
    tVerList = version.split(".")
    tCMPOp = algoInfo["type"].split(",")
    tExpcValue = algoInfo["value"].split(".")
    if len(tVerList) != len(tCMPOp) and len(tVerList) != len(tExpcValue):
      log.error("[Error] Invalid version compare op: {0} for {1} to {2}".format(version, algoInfo["type"], tExpcValue))
      return False
    resResults = True
    for currOp in xrange(0, len(tCMPOp)):
      if tCMPOp[currOp] != "?":
        resResults = resResults and self._makeVerEval(tVerList[currOp], tCMPOp[currOp], tExpcValue[currOp])
        if currOp == 0 and resResults and ">=" in tCMPOp[currOp] and "back_port" in algoInfo and algoInfo["back_port"]:
          if self._makeVerEval(tVerList[currOp], ">", tExpcValue[currOp]):
            return True
    return resResults

  def _checkToolVersion(self, binName, matchInfo):
    tCmdArgs = [binName, matchInfo["args"]]
    # Uncoment for easy debug
    return True
    tProcOut = runCMD(tCmdArgs, isShell=platform.system().lower() == "windows")
    return True
    if tProcOut["ret_code"] != 0:
      log.error("[Error] Can't get version of: {0}".format(binName))
      return False
    tLines = tProcOut["out"].split("\n")
    if len(tLines) < matchInfo["line"]:
       log.error("[Error] Invalid number of lines in output of: {0}".format(binName))
       log.error("[Error] Expected count of lines: {0}".format(matchInfo["line"]))
       return False
    tWords = tLines[matchInfo["line"]].split(" ")
    if len(tWords) < matchInfo["word"]:
      log.error("[Error] Invalid  count of word ({0} but need {1}): {2}"
                .format(len(tWords), matchInfo["word"], binName))
      return False
    tPhrase = tWords[matchInfo["word"]]
    matchInfo["actual_ver"] = tPhrase
    return self._isValidVersion(tPhrase, matchInfo["match"])

  def _findToolItem(self, toolchain, itemName):
    for swItem in toolchain:
      if type(toolchain[swItem]) is list:
        for swSubItem in toolchain[swItem]:
          if swSubItem["name"] == itemName:
            return swSubItem
      elif toolchain[swItem]["name"] == itemName:
        return toolchain[swItem]
    return None

  def _validateSW(self):
    log.info("[Info] Start checking needed SW...")
    tCHItem = self._loadToolChains()
    if tCHItem is None:
      log.error("[Error] Can't validate SW without configs")
      return False
    # Validate cmake
    tItem = self._config.get("generator", "name").lower()
    self._validCmake = self._doValidation(tCHItem, tItem)
    if self._validCmake is None:
      log.error("[Error] Can't found supported cmake")
      return False
    # Validate compiler
    tItem = self._config.get("compiler", "name").lower()
    self._validCompiler = self._doValidation(tCHItem, tItem)
    if self._validCompiler is None:
      log.error("[Error] Can't found supported compiler")
      return False
    return True

  def _loadToolChains(self):
    tConfigFile = self._repoPaths["toolchain"] + "/" + _CONFIG_FILE_NAME
    if not os.path.exists(tConfigFile):
       log.error("[Error] Toolchain config file doesn't exist: {0}".format(tConfigFile))
       return None
    try:
      with open(tConfigFile, "r") as tFile:
        tConfig = json.load(tFile)
    except:
      log.error("[Error] Can't parse config file: {0}".format(tConfigFile))
      return None
    if platform.system().lower() == "windows":
      toolChain = tConfig["win"]
    else:
      toolChain = tConfig["lin"]
    return toolChain

  def _createDefConfig(self, filename):
    tConfig = SafeConfigParser()
    # Default cmake values
    tConfig.add_section("generator")
    tConfig.set("generator", "name", "Cmake")
    tConfig.add_section("compiler")
    if platform.system().lower() == "windows":
      tConfig.set("compiler", "name", _DEF_WIN_COMPILER)
    else:
      tConfig.set("compiler", "name", _DEF_LIN_COMPILER)
    self._config = tConfig
    try:
      with open(filename, "w") as tFile:
        tConfig.write(tFile)
    except:
      log.error("[Error] Can't create local config file: {0}".format(_DEF_CONFIG_FILENAME))
      log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
      return None
    else:
      log.info("[Info] Created default config in: {0}".format(filename))
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

  def getConfigPath(self):
    return _DEF_CONFIG_FILENAME

  def getProjectPath(self):
    return self._repoPaths["projects"]