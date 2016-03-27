# author: Oleksii Zhogan

__all__ = ["Project"]

import os
import sys
import json

from logger import log

from utils import runCMD
from utils import setUpEnv

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


class Project:

  def __init__(self, filename):
    self._model = dict()
    self._rootPath = ""
    self._loadModel(filename)

  def setRoot(self, rootPath):
    self._rootPath = rootPath

  def _loadModel(self, filename):
    with open(filename, "r") as tFile:
      tModel = json.load(tFile)
    self._model["name"] = tModel["name"]
    self._model["location"] = tModel["location"]
    if Platform["short_name"] != "win":
      self._model["cmake"] = tModel["cmake"]["unix"]
    else:
      self._model["cmake"] = tModel["cmake"]["win"]
    self._model["cmake_log"] = tModel["cmake"]["cmake_log"]

  def getName(self):
    return self._model["name"]

  def cleanUp(self):
    # TODO: Implement this
    pass

  def _getGenerator(self):
    return " -G\"{0}\"".format(self._model["cmake"]["gen"])

  def _getBuildDir(self, forCmake=False):
    tDirPath = self._rootPath + "/" + self._model["cmake"]["build_dir"] + "/" + self._model["name"]
    if not os.path.exists(tDirPath):
      os.makedirs(tDirPath)
    if forCmake:
      return " -B{0}".format(tDirPath)
    return tDirPath

  def _setUpCmake(self):
    enVars = self._model["cmake"]["ENVs"]
    for item in enVars:
      if "path" in item and item["path"] and self._rootPath != "":
        for elem in [x for x in item if x != "path"]:
          item[elem] = self._rootPath + "/" + item[elem]
    resDict = dict()
    for item in enVars:
      for elem in item:
        if elem != "path":
           resDict[elem] = item[elem]
    setUpEnv(resDict)

  def _getDefs(self):
    tStr = " "
    for item in self._model["cmake"]["defs"]:
      tStr += "-D{0}".format(item)
    return tStr

  def _runCmake(self):
    if not self._setUpCmake():
      pass
    tCMD = "cmake -H." + self._getGenerator() + self._getBuildDir(forCmake=True) + self._getDefs()
    tWorkDir = self._rootPath + "/" + self._model["location"]
    tProcLog = self._getBuildDir() + "/" + self._model["cmake_log"]
    with open(tProcLog, "w+") as tFile:
      tProcData = runCMD(tCMD, pipe=tFile, isShell=Platform["shell"], workDir=tWorkDir)
    if tProcData["ret_code"] == 0:
      return True
    if tProcData["ret_code"] is None:
      log.error("[Error] Invalid cmd data sent to cmake")
    elif tProcData["ret_code"] != 0:
      log.error("[Error] Invalid cmake files. See log for more info")
    return False

  def build(self, buildType):
    if not self._runCmake():
      log.error("[Error] Cmake generation failed")
    else:
      log.info("[Info] Cmake generation successful")


