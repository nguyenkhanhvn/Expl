#include "explpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

EXPL::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

EXPL::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void EXPL::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void EXPL::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////     INDEX BUFFER     //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

EXPL::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

EXPL::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{

}

void EXPL::OpenGLIndexBuffer::Bind() const
{

}

void EXPL::OpenGLIndexBuffer::Unbind() const
{

}

