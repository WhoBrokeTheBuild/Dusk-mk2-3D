#ifndef DUSK_GRAPHICS_CONTEXT_H
#define DUSK_GRAPHICS_CONTEXT_H

#include <Tracking/TrackedObject.h>
#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Graphics
{

class Window;

class GraphicsContext :
	public Tracking::TrackedObject
{

	friend class Window;

public:

	virtual inline string GetClassName(void) const { return "Graphics Context"; }

	bool Bind(void);
	void SwapBuffers(void);

private:

	inline GraphicsContext(GLFWwindow* pGLFWWindow) :
		mp_GLFWWindow(pGLFWWindow)
	{ }

	GLFWwindow*     mp_GLFWWindow;

}; // GraphicsContext

} // Graphics

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_H
