#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ios>

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void Use();
	void ReloadShaders();
	void SetBool(const std::string &name, bool value);
	void SetInt(const std::string &name, int value);
	void SetUnsignedInt(const std::string &name, unsigned int value);
	void SetFloat(const std::string &name, float value);
	void SetVec2Float(const std::string &name, glm::vec2 value);
	void SetVec3Float(const std::string &name, glm::vec3 value);
	void SetVec4Float(const std::string &name, glm::vec4 value);
	void SetMatrix4(const std::string &name, glm::mat4 value);
	
private:
	const GLchar* vertexPath;
	const GLchar* fragmentPath;
	GLuint program;
	
	GLint GetUniformLocation(const std::string &name);
	void CreateProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	std::string ReadShader(const GLchar* shaderPath);
};
#endif // !SHADER_H
