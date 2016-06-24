Here is little description about project structure:

   ROOT
    |_ app     -- target app of TA
    |_ extern  -- extern libs
    |_ physics -- traget lib of TA (shader)
    
To compile project you need:
  - MSVC 2015 (path to devenv.com has to setto window PATH varible)
  - opengl32  (should support 3.3 core version)

1. In folder 
    "app" - loaceted SRCs and shader for target APP in TA
    
2. In folder 
    "physics" - located SRCs for stand alone dynamic library with physics simulation (as require TA)
    
3. In folder
    "extern" - loaceted bins and header for two external libraries:
    
     3.1 GLFW - allow create GL contex and manage surface (Windwos manager)
                Purpose : due to lack of knowlage about WinAPI I suggest to use this library window managment  
                Version : 
                Site    : 
                Licence : 
                
     3.2 GLEW - help initialize all GL call for given GL version
                Purpose : standart way to initialize all GL calls in GL driver
                Version : 
                Site    : 
                Licence : LGPL
                
     Each external lib has next structure:
         - lib_name
           |_ include    -- include files
           |_ bins       -- compiled release binaries with MSVC 14 
              |_x64      -- for x64 platform 
              |_x32      -- ....     
              
Also I had add to folders "_build", "_out". In this folder you'll find MSVC 14 projects files and pre-compiled binaries respectavly
If you know how cmake work you can delete and manually re-genared this folders by next commands:
 // in folder where this readme.txt located:
 
  // Debug build
  > cmake -Happ -B_build/Debug -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug
  
  // Release build
  > cmake -Happ -B_build/Release -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release
  