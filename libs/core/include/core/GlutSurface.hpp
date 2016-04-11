// author: Oleksii Zhogan

#ifndef __GLUT_SURFACE_HPP__
#define __GLUT_SURFACE_HPP__

#include <core/Surface.hpp>

#include <memory>

class GlutDataHandler;

class GlutSurface : public Surface {
public:
	GlutSurface(Application* app);
	virtual ~GlutSurface();

    bool initialize();
	void dispaly();
    void swapBuffers();

    void setBufferMode(SurfaceBufferMode mode);
    void setColorMode(SurfaceColorMode mode);

    void setTitle(const std::string& title);
    void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);


private:

    static void surfaceResizeFunc(int width, int height);
    static void surfaceDisplayFunc();
    static void surfaceIdleFunc();
    static void surfaceMouseFunc(int, int, int, int);
    static void surfaceKeybordFunc(unsigned char, int, int);

private:

    std::unique_ptr<GlutDataHandler> dataHandler;

};

#endif /* __GLUT_SURFACE_HPP__ */
