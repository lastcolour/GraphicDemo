# author: Oleksii Zhogan

__all__ = ["runCMD", "setUpEnv", "tryFormat"]

import sys
import os

from subprocess import Popen
from logger import log

_TMP_FILE = "data.temp"


def tryFormat(rawStr, dictValues):
    tOutStr = rawStr
    try:
        tOutStr = tOutStr.format(**dictValues)
    except KeyError:
        pass
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
    log.debug("[Debug] Start process: {0}".format(cmd))
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
