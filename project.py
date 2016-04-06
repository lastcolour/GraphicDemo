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
_DEF_PROJECT = "config/projects/DemoApp.json"
del selfPath


def parseArgs():
    from argparse import ArgumentParser
    argPrs = ArgumentParser(description="Helpful script for project managment")
    argPrs.add_argument("-p",     dest="proj",  nargs=1,   required=False, type=str,    default=_DEF_PROJECT,
                                  help="specifie custon project file")
    argPrs.add_argument("-build", dest="build", nargs="?", required=True,  type=str,    const="debug", choices=["Debug","debug" ,"Release", "release"],
                                  help="build project of specifig type (debug, release)")
    argPrs.add_argument("-clean", dest="clean", nargs="?", required=False, type=bool,   const=True, default=False,
                                  help="clean all generated files before build")
    return argPrs.parse_args()                                                                                                                                                                                                            


def main():
    args = parseArgs()
    try:
        proj = Project(args.proj)
    except:
        log.error("[Error] Unexpected error when loading project from: {0}".format(args.proj))
        log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
        return
    if args.clean:
        proj.cleanUp()
    proj.build(args.build.title())

if __name__ == "__main__":
    main()
