// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core/DEFS.hpp>
#include <core/Surface.hpp>
#include <core/ResouceManager.hpp>

#include <memory>

// TODO: Replace all uses of STL at public API to more portable
template class LIB_EXPORT_CONV std::unique_ptr<Surface>;
template class LIB_EXPORT_CONV std::unique_ptr<ResourceManager>;
template class LIB_EXPORT_CONV std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

class LIB_EXPORT_CONV Application {
public:

    Application(int argc, char* argv[]);
    virtual ~Application();

    static const Application* getInstance();

    ResourceManager* getResourceManager() const;
    Surface* getSurface();

    int run();

protected:

    virtual void onInitEvent();
    virtual void onDeinitEvent();
    virtual void onResizeEvent(unsigned int width, unsigned int height);
    virtual void onDrawEvent();

private:

    bool appDeinit();
    bool appInit();
    
    void mainLoop();

private:

    static Application* appInstance;

    std::unique_ptr<Surface> surfacePtr;
    std::unique_ptr<ResourceManager> resourcePtr;

private:

    friend class GLFWSurface;
};

#endif /* __APPLICATION_HPP__*/
