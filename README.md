# GraphicsDemo
This is project for different 3D Graphics and SW techniques practices.

## Build
For build project need:
- For Windows: Visual Studio 14 compiler or relevant
- For Linux: g++ and make
- Python 2.7.*
- Cmake 2.8 or higher

To perform build use script **project.py**, here is some examples:

    > project.py -proj=DemoApp -build=Debug // make debug build of DemoApp 
    > project.py -build=Debug               // build default project (see local-config.ini) 
    > project.py -build=Release             // build default project in release

When first time run **project.py** will be generated file **local-config.ini** where you can specify
your default configs for this repo. 
    
## Project:
### DemoApp

Based on @www.learnopengl.com tutorial "Getting started" and contain fully implemented example
 
### LightigApp

Based on @www.learnopengl.com tutorial "Lighting" 
