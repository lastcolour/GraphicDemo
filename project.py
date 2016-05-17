# author: Oleksii Zhogan

import os
import sys

from scripts.proj import Project
from scripts.initter import Initializer
from scripts.logger import log


selfPath = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")
SELF_NAME = os.path.basename(__file__)
Project.intializePaths({
    "config_root": selfPath + "/" + "config/projects",
    "repo_root": selfPath
})
del selfPath


def parseArgs():
    from argparse import ArgumentParser

    argPrs = ArgumentParser(description= "Helpful script for project managment",
                            epilog="Developed by Oleksii Zhogan (alexzhogan@gmail.com)")

    argPrs.add_argument("-proj",  dest="proj",  nargs="?",   required=False, type=str,    default=None,
                                  help="specifie custon project file")
    tGroup = argPrs.add_mutually_exclusive_group()
    tGroup.add_argument("-build", dest="build", nargs="?", required=False,  type=str,    const="debug", choices=["Debug","debug" ,"Release", "release"],
                                  help="build project of specifig type (debug, release)")
    tGroup.add_argument("-init-local", dest="init local config", required=False, type=bool, const=True, default=False,
                                       nargs="?", help="init local configuration")
    tGroup.add_argument("-clean", dest="clean", nargs="?", required=False, type=bool,   const=True, default=False,
                                  help="clean all generated files before build")
    tGroup.add_argument("-list",  dest="list", nargs="?", required=False,  type=bool,    const=True, default=False,
                                  help="show all projects")
    return argPrs.parse_args()


def main():
    args = parseArgs()
    tInit = Initializer()
    if not tInit.initLocal():
      log.error("[Error] Can't initialize local config for repository.")
      return
    tProjectName = args.proj # Try get project from cmd, if not specified, then use default
    if args.proj is None:
       tProjectName = tInit.getDefProject()
    if tProjectName is None:
      log.error("[Error] Default project not specified in local config: {0}".format(tInit.getConfigPath()))
      log.error("[Error] Please add cmd args: \n\n\t> {0} -proj=PROJECT_NAME ...\n\n".format(SELF_NAME))
      log.error("[Error] or query avaible project use: \n\n\t> {0} -list\n\n".format(SELF_NAME))
      return
    try:
        proj = Project(tProjectName)
        proj.setLocalConfig(tInit)
    except:
        log.error("[Error] Unexpected error when loading project from: {0}".format(tProjectName))
        log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
        return
    if args.clean:
        proj.cleanUp()
    if args.build is None:
        log.info("[Info] Build config not specified. Skipping!")
        return
    proj.build(args.build.title())

if __name__ == "__main__":
    main()