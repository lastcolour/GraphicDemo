#include <core/Surface.hpp>

class GlutSurface : public Surface {
public:
	GlutSurface(Application* app);
	virtual ~GlutSurface();

	void dispaly();
}
