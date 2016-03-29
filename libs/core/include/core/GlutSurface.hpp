#ifndef __GLUT_SURFACE_HPP__
#define __GLUT_SURFACE_HPP__

#include <core/Surface.hpp>

class GlutSurface : public Surface {
public:
	GlutSurface(Application* app);
	virtual ~GlutSurface();

	void dispaly();
};

#endif /* __GLUT_SURFACE_HPP__ */
