# author: Oleksii Zhogan

import sys

from scripts.proj import Project
from scripts.logger import log
import os

_DEF_PROJECT = "config/projects/demo.json"
_ROOT = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")

def parseArgs():
  from argparse import ArgumentParser
  argPrs = ArgumentParser(description="Helpful script for project managment")
  argPrs.add_argument("-p",       dest="proj",  nargs=1,   required=False, type=str,  default=_DEF_PROJECT,
                                  help="specifie custon project file")
  argPrs.add_argument("-build",   dest="build", nargs="?", required=True,  type=str,  const="debug", choices=["debug", "release", "relwithdebinfo"],
                                  help="build project of specifig type (debug, release, relwithdebinfo, etc.)")
  argPrs.add_argument("-clean",   dest="clean", nargs="?", required=False, type=bool, const=True, default=False,
                                  help="clean all generated files before build")
  return argPrs.parse_args()                                                                                                      


def main():
  args = parseArgs()
  try:
    proj = Project(args.proj)
    proj.setRoot(_ROOT)
  except:
    log.error("[Error] Can't load project from: {0}".format(args.proj))
    log.debug("[Error] Problem: {0}".format(sys.exc_info()[1]))
    return
  log.info("[Info] Loaded project: {0}".format(proj.getName()))
  if args.clean:
    log.info("[Info] Remove all generated files")
    proj.cleanUp()
  proj.build(args.build)

if __name__ == "__main__":
  main()
