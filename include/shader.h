#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <fstream>
#include <sstream>

class Shader
{
public:
	static Shader fromFile(const std::string& vertexPath, const std::string& fragmentPath);
	static Shader fromSource(const std::string& vertexSource, const std::string& fragmentSource);

	void use();

	GLuint getProgramId();

	void setInt(const std::string& name, GLint value);
	void setMat4(const std::string& name, const GLfloat* value);

private:
	Shader() = default;
	Shader(const GLchar* vertexSource, const GLchar* fragmentSource);

	GLuint _programId = 0;
};

Shader Shader::fromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();
		vertexSource = vertexStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "Read shader file fail: " << e.what() << std::endl;
		return Shader();
	}

	return Shader(vertexSource.data(), fragmentSource.data());
}

inline Shader Shader::fromSource(const std::string& vertexSource, const std::string& fragmentSource)
{
	return Shader(vertexSource.data(), fragmentSource.data());
}

inline void Shader::use()
{
	glUseProgram(_programId);
}

inline GLuint Shader::getProgramId()
{
	return _programId;
}

inline void Shader::setInt(const std::string& name, GLint value)
{
	GLint location = glGetUniformLocation(_programId, name.data());
	glUniform1i(location, value);
}

inline void Shader::setMat4(const std::string& name, const GLfloat* value)
{
	GLint location = glGetUniformLocation(_programId, name.data());
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

inline Shader::Shader(const GLchar* vertexSource, const GLchar* fragmentSource)
{
	GLint success;
	GLchar infoLog[512];

	// VertexShader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "Compile vertex shader fail: " << infoLog << std::endl;
		return;
	}

	// FragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "Compile fragment shader fail: " << infoLog << std::endl;
		return;
	}

	// ShaderProgram
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "Link shader program fail: " << infoLog << std::endl;
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	_programId = shaderProgram;
}

#endif // !SHADER_HPP
