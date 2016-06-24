import json
import sys
import os

from logger import log

from cmake import CmakeRunner
from compile import CompileRunner

class Project:
    def __init__(self, name):
        self._name = name
        self._parent = None
        self._external = False
        self._cmakeRunner = None
        self._compilerRunner = None
        self._context = dict()
        self._buildTypes = []
        self._depProject = []

    def getContext(self):
        return self._context

    def __str__(self):
        return self._name

    def getName(self):
        return self._name

    def _doBuild(self):
        pass

    def setInstall(self, value):
        pass

    def setParent(self, parent):
        self._parent = parent

    def build(self, buildType):
        for depItem in self._depProject:
           depItem.build(buildType)
        self._doBuild()

    def setCmakeRunner(self, runner):
        self._cmakeRunner = runner

    def setCompilerRunner(self, runner):
        self._compilerRunner = runner

    def addDepProject(self, proj):
        proj.setParent(self)
        self._depProject.append(proj)

    def setBuildTypes(self, buildTypes):
        self._buildTypes = buildTypes

    def set3dParty(self, flag):
        self._external = flag


class DependError(RuntimeError):
    def __init__(self, depErr):
        self._depErr = depErr
    def __str__(self):
        return  self._depErr


class ProjectLoader:
    def __init__(self, initializer):
        self._initer = initializer
        self._tree  = dict()

    def _processProjNode(self, jsonNode):
        tProj = Project(jsonNode["name"])
        tProj.set3dParty(self._is3dParty(jsonNode))
        tProj.setBuildTypes(self._processBuildTypes(jsonNode))
        tProj.setCmakeRunner(self._processCmakeConfig(jsonNode))
        tProj.setCompilerRunner(self._processCompilerConfig(jsonNode))
        self._processDepProjNode(jsonNode, tProj)
        return tProj

    def _processCompilerConfig(self, jsonNode):
        tRunner = CompileRunner(jsonNode)
        tRunner.setBinPath(self._initer.getCompiler()["path"])
        return tRunner

    def _processCmakeConfig(self, jsonNode):
        tRunner = CmakeRunner(jsonNode)
        tRunner.setBinPath(self._initer.getCmake()["path"])
        return tRunner

    def _processBuildTypes(self, jsonNode):
        typesList = []
        if "build_types" in jsonNode:
            for item in jsonNode["build_types"]:
                typesList.append(item)
        return typesList

    def _processDepProjNode(self, jsonNode, root):
        if "deps" not in jsonNode:
            return
        for depItem in jsonNode["deps"]:
            log.info("[Info] {0} -> Process embedded project: {1}".format(root.getName(), depItem["project"]))
            tProj = self._loadProject(depItem["project"])

            if tProj is None:
                errStr = "[{0}] Can't load project from {1}".format(root.getName(), depItem["project"])
                raise DependError(errStr)
            else:
                root.addDepProject(tProj)

    def _removeDupes(self, project):
        #TODO: Implement this
        return project

    def _is3dParty(self, jsonNode):
        if "3dParty" in jsonNode:
            return jsonNode["3dParty"]
        return False

    def _loadProject(self, filename):
        tAbsFilePath = self._getAbsPath(filename)
        try:
          with open(tAbsFilePath, "r") as tFile:
            tProjModel = json.load(tFile)
        except:
            log.error("[Error] Can't parse file: {0}".format(tAbsFilePath))
            log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
            return None
        else:
            return self._processProjNode(tProjModel)

    def _getAbsPath(self, filename):
        tPath = os.path.abspath("{0}/{1}".format(self._initer.getProjectPath(), filename))
        if not os.path.exists(tPath):
            log.warning("[Warning] Path doesn't exits: {0}".format(tPath))
        return tPath

    def _preFormatName(self, projectName):
        if ".json" not in projectName:
            return projectName + ".json"
        return projectName

    def load(self, projectName):
        tProjName = self._preFormatName(projectName)
        try:
            log.info("[Info] Process project: {0}".format(tProjName))
            tProj = self._loadProject(tProjName)
        except DependError as ex:
            log.error("[Error] Dependency error: {0}".format(ex))
            return None
        except:
            log.error("[Error] Can't load project from: {0}".format(projectName))
            log.error("[Error] Problem: {0}".format(sys.exc_info()[1]))
            return None
        else:
            return self._removeDupes(tProj)