#include "explpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace EXPL {

	EXPL::VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			EX_CORE_ASSERT(false, "None not support");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		EX_CORE_ASSERT(false, "API not support");
		return nullptr;
	}

}
