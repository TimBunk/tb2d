#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// save the paths for later use
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
	// create the shader program
	CreateProgram(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(this->program);
}

void Shader::Use()
{
	glUseProgram(this->program);
}

void Shader::ReloadShaders()
{
	CreateProgram(this->vertexPath, this->fragmentPath);
}

void Shader::SetBool(const std::string & name, bool value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1i(uniformLoc, value);
	}
}

void Shader::SetInt(const std::string & name, int value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1i(uniformLoc, value);
	}
}

void Shader::SetIntArray(const std::string & name, int * value, int count)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1iv(uniformLoc, count, value);
	}
}

void Shader::SetUnsignedInt(const std::string & name, unsigned int value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1ui(uniformLoc, value);
	}
}

void Shader::SetUnsignedIntArray(const std::string & name, unsigned int * value, int count)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1uiv(uniformLoc, count, value);
	}
}

void Shader::SetFloat(const std::string & name, float value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1f(uniformLoc, value);
	}
}

void Shader::SetFloatArray(const std::string & name, float * value, int count)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform1fv(uniformLoc, count, value);
	}
}

void Shader::SetVec2Float(const std::string & name, glm::vec2 value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform2f(uniformLoc, value.x, value.y);
	}
}

void Shader::SetVec3Float(const std::string & name, glm::vec3 value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform3f(uniformLoc, value.x, value.y, value.z);
	}
}

void Shader::SetVec4Float(const std::string & name, glm::vec4 value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniform4f(uniformLoc, value.x, value.y, value.z, value.w);
	}
}

void Shader::SetMatrix4(const std::string & name, glm::mat4 value)
{
	GLint uniformLoc = GetUniformLocation(name);
	if (uniformLoc != -1) {
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
	}
}

GLint Shader::GetUniformLocation(const std::string & name)
{
	GLint uniformLocation = glGetUniformLocation(this->program, name.c_str());
	if (uniformLocation == -1) {
		// if this error appears there could be 2 possible things wrong you miss typed the uniform name or the uniform is not being used
		std::cout << "The uniform " << "'" << name << "'" << " could not be found or is not being used"<< std::endl;
	}
	return uniformLocation;
}

void Shader::CreateProgram(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// read the shader files
	std::string _vShaderCode = ReadShader(vertexPath);
	std::string _fShaderCode = ReadShader(fragmentPath);
	const GLchar* vShaderCode = _vShaderCode.c_str();
	const GLchar* fShaderCode = _fShaderCode.c_str();;
	// compile shaders
	GLuint vertex, fragment;
	int succes;
	char infolog[512];
	// create the vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		std::cout << "Error in vertex compilation" << infolog << std::endl;
	}
	// create the fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes) {
		glGetShaderInfoLog(fragment, 512, NULL, infolog);
		std::cout << "Error in fragment compilation" << infolog << std::endl;
	}
	// link the shaders to the program
	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);
	// check for linking errors
	glGetProgramiv(this->program, GL_LINK_STATUS, &succes);
	if (!succes) {
		glGetProgramInfoLog(this->program, 512, NULL, infolog);
		std::cout << "Error in linking of the shaders " << infolog << std::endl;
	}
	// clear the allocated memory that is no longer necessarily
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::ReadShader(const GLchar * shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open the files
		shaderFile.open(shaderPath, std::ios::in);
		if (shaderFile.fail()) {
			std::cout << "File not found: " << shaderPath << std::endl;
		}
		std::stringstream shaderStream;
		// read file and buffer it into the stream
		shaderStream << shaderFile.rdbuf();
		// close the file
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error shader file was not read correctly" << std::endl;
	}
	return shaderCode;
}
