# GraphicsDemo
This is project for different 3D Graphics and SW techniques practices.

# Build
For build project need:
- Python 2.7
- Cmake 2.8

To perform build use script **project.py**, here is some examples:
'''
  project.py -b=debug
  project.py -b=release -clean
'''
**-b=<build_type>** -- type of build. Valid values is:
- debug
- release
- or None, than will be perfomed debug build
**-clean** -- perform clean build. (All generated files will be removed)

