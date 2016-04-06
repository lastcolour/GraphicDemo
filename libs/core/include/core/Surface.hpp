// author: Oleksii Zhogan

#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

class Application;


class Surface {
public:

	Surface(Application* app);
	virtual ~Surface();

	virtual void dispaly() = 0;

protected:

    static Application* getApp();

private:

	static Application *appListener;
};


// Inline methods implementation

inline
Application* Surface::getApp() { return appListener; }

#endif /* __SURFACE_HPP__ */
