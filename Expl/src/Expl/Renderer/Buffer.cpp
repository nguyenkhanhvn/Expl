#include "explpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace EXPL {

	EXPL::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			EX_CORE_ASSERT(false, "None not support");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		EX_CORE_ASSERT(false, "API not support");
		return nullptr;
	}

	EXPL::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			EX_CORE_ASSERT(false, "None not support");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		EX_CORE_ASSERT(false, "API not support");
		return nullptr;
	}

}

