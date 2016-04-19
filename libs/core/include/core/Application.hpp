// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core/DEFS.hpp>
#include <core/Surface.hpp>
#include <core/ResouceManager.hpp>

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

    void finishApp(int errCode, const char* lastMessage=nullptr);

private:

    bool appDeinit();
    bool appInit();
    
    int getErrorCode() const;
    void setErrorCode(int errorCode);

    void mainLoop();

private:

    static Application* appInstance;

    int errCode;
    Surface* surfacePtr;
    ResourceManager* resourcePtr;

private:

    friend class GLFWSurface;
};

#endif /* __APPLICATION_HPP__*/
