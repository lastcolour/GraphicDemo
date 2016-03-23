# author: Oleksii Zhogan

import os
import sys
import json
import shutil

from subprocess import Popen

_DEF_PROJECT = "config/projects/demo.json"
_TMP_FILE = "data.temp"
_PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")

def _getPlatformInfo():
  import platform
  tPlatform = dict()
  tPlatform["name"] = platform.system()
  if tPlatform["name"] == "Windows":
     tPlatform["app_ext"] = ".exe"
     tPlatform["short_name"] = "win"
  else:
    tPlatform["app_ext"] = ""
    tPlatform["short_name"] = "lin"
  return tPlatform
  
def _createLogger():
  import logging
  logger = logging.getLogger("__main__")
  logger.setLevel(logging.DEBUG)
  logger.addHandler(logging.StreamHandler(sys.stderr))
  return logger

_PLATFORM = _getPlatformInfo()
logger = _createLogger()
del _createLogger
del _getPlatformInfo

def findAppAtPath(appName):
  checkDir = set()
  if "PATH" in os.environ:
    checkDir = checkDir.union(os.environ["PATH"].split(";"))
  if "Path" in os.environ:
    checkDir = checkDir.union(os.environ["Path"].split(";"))
  for dirPath in checkDir:
    for fileName in os.listdir(dirPath):
      if fileName == appName + _PLATFORM["app_ext"]:
        return dirPath + "\\" + fileName
  return None

def runCmd(cmdLine):
  tProcessOut = dict()
  # Create pipe file
  try:
    pipeFile = open(_TMP_FILE, "w+")
  except:
    logger.error("[Error] Can't create file: {0}".format(_TMP_FILE))
    logger.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
    pipeFile = None
  # Start process
  try:
    tProcess = Popen(cmdLine, stdout=pipeFile, stderr=pipeFile)
    tProcess.wait()
    tProcessOut["ret_code"] = tProcess.returncode
  except:
    logger.error("[Error] Can't run process: {0}".format(cmdLine))
    logger.error("[Error] Problem: {0}".sys.exc_info()[1])
    tProcessOut["ret_code"] = None
  finally:
    if pipeFile is None:
      tProcessOut["out"] = None
    else:
      pipeFile.tell()
      pipeFile.seek(0)
      tProcessOut["out"] = pipeFile.read()
      pipeFile.close()
      try:
        os.remove(_TMP_FILE)
      except:
        pass
    return tProcessOut

    
class Project:

  def __init__(self, projFile):
    self._model = dict()
    self._loadModel(projFile)
    
  def name(self):
    return self._model["name"]

  def cleanUp(self):
    # TODO: Implement this
    pass
    
  def generatorLog(self):
    # TODO: Implement this
    return ""
    
  def generate(self, buildType):
    # TODO: Implement this
    return True
    
  def _loadModel(self, projFile):
    with open(projFile, "r") as tFile:
      self._model = json.load(tFile)["project"]
 

def parseArgs():
  from argparse import ArgumentParser
  argPrs = ArgumentParser(description="Helpful script for project managment")
  argPrs.add_argument("-p",     dest="proj",  nargs=1,   required=False, type=str,  default=_DEF_PROJECT, 
                                help="specifie custon project file")
  argPrs.add_argument("-b",     dest="build", nargs="?", required=True,  type=str,  const="debug", choices=["debug", "release", "relwithdebinfo"], 
                                help="build project of specifig type (debug, release, relwithdebinfo, etc.)")
  argPrs.add_argument("-clean", dest="clean", nargs="?", required=False, type=bool, const=True, default=False,
                                help="clean all generated files before build")                                                      
  return argPrs.parse_args()                                                                                                      


def main():
  args = parseArgs()
  try:
    proj = Project(args.proj)
  except:
    logger.error("[Error] Can't load project from: {0}".format(args.proj))
    logger.debug("[Error] Problem: {0}".format(sys.exc_info()[1]))
    return
  logger.info("[Info] Loaded project: {0}".format(proj.name()))
  if args.clean:
    logger.info("[Info] Remove all generated files")
    proj.cleanUp()
  if not proj.generate(args.build):
     logger.error("[Error] Can't generate project")
     logger.error("[Error] For more info see log at: {0}".format(proj.generatorLog()))
     return
  logger.info("[Info] Project file created")
  # TODO: Implement project build  
  
   
if __name__ == "__main__":
  main()