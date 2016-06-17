# author: Oleksii Zhogan

import os
import sys

from scripts.loader import ProjectLoader
from scripts.initter import Initializer
from scripts.logger import log


selfPath = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")
SELF_NAME = os.path.basename(__file__)
_REPO_PATHS = {
    "projects"  : selfPath + "/config/projects",
    "toolchain" : selfPath + "/config/toolchains"
}
del selfPath


def parseArgs():
    from argparse import ArgumentParser

    argPrs = ArgumentParser(description= "Helpful script for project management",
                            epilog="Developed by Oleksii Zhogan (alexzhogan@gmail.com)")

    argPrs.add_argument("-proj", dest="proj", nargs="?", required=True, type=str, default=None,
                                 help="specifie custon project file")
    tGroup = argPrs.add_mutually_exclusive_group()
    tGroup.add_argument("-build", dest="build", nargs="?", required=False, type=str, const="debug",
                                  choices=["Debug","debug" ,"Release", "release"],
                                  help="build project of specifig type (debug, release)")
    tGroup.add_argument("-init-local", dest="init local config", required=False, type=bool, const=True, default=False,
                                       nargs="?", help="init local configuration")
    tGroup.add_argument("-clean", dest="clean", nargs="?", required=False, type=bool, const=True, default=False,
                                  help="clean all generated files before build")
    tGroup.add_argument("-list", dest="list", nargs="?", required=False,  type=bool, const=True, default=False,
                                 help="show all projects")
    argPrs.add_argument("-fast", dest="fast", required=False, action="store_const", const=True,
                                 help="skip build of 3d parties depedecies")
    return argPrs.parse_args()


def main():
    args = parseArgs()
    tInit = Initializer(_REPO_PATHS)
    if not tInit.initLocal():
      log.error("[Error] Can't initialize local config of repo.")
      return
    try:
        proj = ProjectLoader(tInit).load(args.proj)
        if args.fast is not None:
          proj.setSkip3dParty(True)
    except:
        log.error("[Error] Unexpected error when loading project from: {0}".format(args.proj))
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