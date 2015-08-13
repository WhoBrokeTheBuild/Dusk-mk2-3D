#ifndef DUSK_GRAPHICS_H
#define DUSK_GRAPHICS_H

#include <Utility/Platform.h>

#if defined(DUSK_OS_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#undef GetClassName

#endif // DUSK_OS_WINDOWS

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

namespace Dusk
{

namespace Graphics
{

typedef GLuint GLShader;
typedef GLuint GLProgram;
typedef GLuint GLUniformLocation;
typedef GLuint GLTexture;
typedef GLuint GLAttribute;
typedef GLuint GLBuffer;
typedef GLuint GLVertexArray;
typedef GLenum GLPrimitiveType;

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_GRAPHICS_H
