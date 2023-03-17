#pragma once
#include "Expl/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace EXPL {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(int width, int height, const char* title);

		virtual void Init() override;
		virtual void SwapBuffers() override;
        GLFWwindow* GetWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;

    };

}

