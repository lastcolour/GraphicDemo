# author: Oleksii Zhogan

import os
import sys

from scripts.proj import Project

from scripts.logger import log


selfPath = os.path.dirname(os.path.abspath(__file__)).replace("\\", "/")
Project.intializePaths({
    "config_root": selfPath + "/" + "config/projects",
    "project_root": selfPath
})
_DEF_PROJECT = "config/projects/LightingApp.json"
del selfPath


def parseArgs():
    from argparse import ArgumentParser

    argPrs = ArgumentParser(description= "Helpful script for project managment",
                            epilog="Developed by Oleksii Zhogan (alexzhogan@gmail.com)")

    argPrs.add_argument("-proj",  dest="proj",  nargs=1,   required=False, type=str,    default=_DEF_PROJECT,
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
    try:
        if args.proj is None:
            log.error("[Info] Project not loaded")
            return
        proj = Project(args.proj)
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