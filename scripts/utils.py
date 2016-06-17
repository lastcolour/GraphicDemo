# author: Oleksii Zhogan

__all__ = ["runCMD", "setUpEnv", "tryFormat", "copyFiles", "findAppInENV"]

import platform
import shutil
import glob
import sys
import os

from subprocess import Popen
from logger import log

_TMP_FILE = "data.temp"


def findAppsInENV(appName):
    if "." not in appName:
       tAppName = appName + ".exe" if platform.system().lower() == "windows" else ""
    else:
       tAppName = appName
    def _scanPath(path, appName):
        if not os.path.exists(path) or not os.path.isdir(path):
           return False
        for item in os.listdir(path):
            if os.path.basename(item) == tAppName:
                return True
        return False
    tPossiblePath = []
    for item in os.environ:
        tElem =  os.environ[item]
        tPathList = tElem.split(";")
        if len(tPathList) > 1:
          for tPath in tPathList:
             if _scanPath(tPath, appName):
                 tPossiblePath.append(tPath.replace("\\", "/"))
        elif _scanPath(tElem, appName):
          tPossiblePath.append(tElem.replace("\\", "/"))
    return tPossiblePath


def copyFiles(fileMasks, fromPath, toPath):
    log.debug("[Info] Source location: {0}".format(fromPath))
    log.debug("[Info] Target location: {0}".format(toPath))
    if not os.path.exists(toPath):
        try:
            os.makedirs(toPath)
        except:
            log.debug("[Debug] Can't create target path for COPY: {0}".format(toPath))
            log.debug("[Debug] Problem: {0}".format(sys.exc_info()[1]))
            return
    for maskItem in fileMasks:
      pathSplicer = "/"
      if fromPath[-1] == "/" or fromPath[-1] == "\\":
          pathSplicer = ""
      for item in glob.iglob(fromPath + pathSplicer + maskItem):
        tBaseName = os.path.basename(item)
        log.debug("[Info] Copy file: {0}".format(os.path.basename(tBaseName)))
        try:
            shutil.copy(item, toPath + "/" + tBaseName)
        except:
            log.debug("[Debug] Can't copy file: {0}".format(tBaseName))
            log.debug("[Debug] Problem: {0}".format(sys.exc_info()[1]))

def tryFormat(rawStr, dictValues):
    tOutStr = rawStr
    try:
        tOutStr = tOutStr.format(**dictValues)
    except KeyError:
        log.debug("[Error] Unknown key when format str: {0}".format(rawStr))
        log.debug("[Error] Key: {0}".format(sys.exc_info()[1]))
    return tOutStr

def setUpEnv(envVars):
  if envVars is None:
      return
  for item in envVars:
    if item in os.environ:
      log.warning("[Warning] Override ENV variable: {0}: {1} -> {2}".format(
        item, envVars[item], os.environ[item]))
    else:
      log.info("[Info] Setup ENV var: {0} = {1}".format(item, envVars[item]))
    os.environ[item] = envVars[item]

def runCMD(cmd, workDir=None, pipe=None, isShell=False):
  tProcData = dict()
  usedTmp = False
  if pipe is None:
     pipeFile = open(_TMP_FILE, "w+")
     usedTmp = True
  else:
    pipeFile = pipe
  try:
    #log.debug("[Debug] Start process: {0}".format(cmd if type(cmd) != list else " ".join(cmd)))
    tProc = Popen(cmd, cwd=workDir, shell=isShell, stdout=pipeFile, stderr=pipeFile)
    tProc.wait()
  except:
    log.error("[Error] Can't run process: {0}".format(cmd))
    log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
    tProcData["ret_code"] = None
  else:
    tProcData["ret_code"] = tProc.returncode
  finally:
    pipeFile.tell()
    pipeFile.seek(0)
    tProcData["out"] = pipeFile.read()
    pipeFile.close()
    if usedTmp:
      os.remove(_TMP_FILE)
    return tProcData
