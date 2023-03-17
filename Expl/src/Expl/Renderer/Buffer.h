#pragma once

#include "glad/glad.h"

namespace EXPL {

	enum class ShaderDataType
	{
		None	= 0,
		Bool,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
	};

	inline uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case EXPL::ShaderDataType::Bool:	return 1;
		case EXPL::ShaderDataType::Int:		return 4 * 1;
		case EXPL::ShaderDataType::Int2:	return 4 * 2;
		case EXPL::ShaderDataType::Int3:	return 4 * 3;
		case EXPL::ShaderDataType::Int4:	return 4 * 4;
		case EXPL::ShaderDataType::Float:	return 4 * 1;
		case EXPL::ShaderDataType::Float2:	return 4 * 2;
		case EXPL::ShaderDataType::Float3:	return 4 * 3;
		case EXPL::ShaderDataType::Float4:	return 4 * 4;
		case EXPL::ShaderDataType::Mat3:	return 4 * 3 * 3;
		case EXPL::ShaderDataType::Mat4:	return 4 * 4 * 4;
		}

		EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	inline GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case EXPL::ShaderDataType::Bool:	return GL_BOOL;
		case EXPL::ShaderDataType::Int:		return GL_INT;
		case EXPL::ShaderDataType::Int2:	return GL_INT;
		case EXPL::ShaderDataType::Int3:	return GL_INT;
		case EXPL::ShaderDataType::Int4:	return GL_INT;
		case EXPL::ShaderDataType::Float:	return GL_FLOAT;
		case EXPL::ShaderDataType::Float2:	return GL_FLOAT;
		case EXPL::ShaderDataType::Float3:	return GL_FLOAT;
		case EXPL::ShaderDataType::Float4:	return GL_FLOAT;
		case EXPL::ShaderDataType::Mat3:	return GL_FLOAT;
		case EXPL::ShaderDataType::Mat4:	return GL_FLOAT;
		}

		EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferLayoutElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferLayoutElement(ShaderDataType type, std::string name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		inline uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case EXPL::ShaderDataType::Bool:	return 1;
			case EXPL::ShaderDataType::Int:		return 1;
			case EXPL::ShaderDataType::Int2:	return 2;
			case EXPL::ShaderDataType::Int3:	return 3;
			case EXPL::ShaderDataType::Int4:	return 4;
			case EXPL::ShaderDataType::Float:	return 1;
			case EXPL::ShaderDataType::Float2:	return 2;
			case EXPL::ShaderDataType::Float3:	return 3;
			case EXPL::ShaderDataType::Float4:	return 4;
			case EXPL::ShaderDataType::Mat3:	return 3 * 3;
			case EXPL::ShaderDataType::Mat4:	return 4 * 4;
			}

			EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			: m_Elements(elements)
		{
			CaculateOffsetAndStride();
		}

		inline const std::vector<BufferLayoutElement>& GetElement() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return m_Elements.end(); }		
		std::vector<BufferLayoutElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CaculateOffsetAndStride()
		{
			uint32_t offset = 0;
			for (BufferLayoutElement& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride = 0;

	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}

