#ifndef __GLEW_MANAGER_HPP__
#define __GLEW_MANAGER_HPP__

class GLEWManager {
public:

    static bool initialize();
    static bool deinitialize();

private:

    GLEWManager();
    GLEWManager(GLEWManager&);
    GLEWManager& operator=(const GLEWManager&);
};

#endif /* __GLEW_MANAGER_HPP__ */