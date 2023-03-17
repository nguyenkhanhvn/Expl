#include "explpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

EXPL::OpenGLContext::OpenGLContext(int width, int height, const char* title)
{
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	EX_CORE_ASSERT(m_Window, "Window is null!");
}

void EXPL::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGL();
	EX_CORE_ASSERT(status, "Failed to initialize Glad!");

	EX_CORE_INFO("OpenGL Info:");
	EX_CORE_INFO("	Vendor:		{0}", (const char*)glGetString(GL_VENDOR));
	EX_CORE_INFO("	Renderer:	{0}", (const char*)glGetString(GL_RENDERER));
	EX_CORE_INFO("	Version:	{0}", (const char*)glGetString(GL_VERSION));
}

void EXPL::OpenGLContext::SwapBuffers()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}
