#include "explpch.h"

#include "Shader.h"
#include "Expl/Utils.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace EXPL {

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) :
		m_RendererID(0)
	{
		std::string vertSrc = get_file_contents(vertexShaderPath);
		std::string fragSrc = get_file_contents(fragmentShaderPath);
		uint32_t vs = Shader::CompileShader(GL_VERTEX_SHADER, vertSrc);
		uint32_t fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragSrc);

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vs);
		glAttachShader(m_RendererID, fs);

		glLinkProgram(m_RendererID);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::Delete() const
	{
		glDeleteProgram(m_RendererID);
	}

	uint32_t Shader::GetUniformLocation(std::string name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) EX_CORE_WARN("Warning: uniform {0} doesn't exist!", name);

		m_UniformLocationCache[name] = location;
		return location;
	}

	void Shader::SetUniform1f(std::string name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1i(std::string name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform3f(std::string name, float v0, float v1, float v2)
	{
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}

	void Shader::SetUniform4f(std::string name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4f(std::string name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string source)
	{
		GLuint id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			char message[1024];
			glGetShaderInfoLog(id, 1024, nullptr, message);
			EX_CORE_ERROR("Fail to compile {0} shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
			EX_CORE_ERROR(message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

}

