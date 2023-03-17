#pragma once

#include <glm/glm.hpp>


namespace EXPL {

	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void Bind() const;
		void Unbind() const;

		void Delete() const;

		uint32_t GetUniformLocation(std::string name);

		void SetUniform1f(std::string name, float value);
		void SetUniform1i(std::string name, int value);
		void SetUniform3f(std::string name, float v0, float v1, float v2);
		void SetUniform4f(std::string name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(std::string name, const glm::mat4& matrix);

	private:
		static uint32_t CompileShader(uint32_t type, const std::string source);

	private:
		uint32_t m_RendererID;
		std::unordered_map<std::string, uint32_t> m_UniformLocationCache;
	};

}

