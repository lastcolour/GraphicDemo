#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

class Application;

class Surface {
public:

	Surface(Application* app);
	virtual ~Surface();

	virtual void dispaly() = 0;

protected:

	Application *appListener;
};

#endif /* __SURFACE_HPP__ */
