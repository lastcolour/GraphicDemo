// author: Oleksii Zhogan

#ifndef __GLUT_SURFACE_HPP__
#define __GLUT_SURFACE_HPP__

#include <core/Surface.hpp>

class GlutSurface : public Surface {
public:
	GlutSurface(Application* app);
	virtual ~GlutSurface();

	void dispaly();

private:

    static void surfaceDisplayFunc();
    static void surfaceIdleFunc();
    static void surfaceMouseFunc(int, int, int, int);
    static void surfaceKeybordFunc(unsigned char, int, int);
};

#endif /* __GLUT_SURFACE_HPP__ */
