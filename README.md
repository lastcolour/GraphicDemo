# GraphicsDemo
This is project for different 3D Graphics and SW techniques practices.

## Build
For build project need:
- For Windows: Visual Studio 11 compiler
- For Linux: g++ and make
- Python 2.7.*
- Cmake 2.8 or higher

To perform build use script **project.py**, here is some examples:

    > project.py -build
    > project.py -build=debug
    > project.py -build=release -c

**-build=[build_type]** - build project. Avaible valid build's types:
- debug
- release

**-clean** - clean up project (not required)

**-p** - specify project file location (not required)
