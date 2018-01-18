/**
* @file shader.h
*
* @brief The Shader header file.
*/

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

/**
* @brief The Shader class
*/
class Shader {
public:
	/// @brief Constructor of the Shader
	/// @param vertexPath is the path to a vertext shader for example: "shaders\\basic.vs"
	/// @param fragmentPath is the path to a fragment shader for example: "shaders\\basic.fs"
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	/// @brief Destructor of the Shader
	virtual ~Shader();

	/// @brief Use call this to use the shaderProgram
	/// @return void
	void Use();
	/// @brief SetBool sets a bool by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetBool(const std::string &name, bool value);
	/// @brief SetInt sets a int by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetInt(const std::string &name, int value);
	/// @brief SetIntArray sets a array of ints by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @param count is the amount of ints inside the array
	/// @return void
	void SetIntArray(const std::string &name, int* value, int count);
	/// @brief SetUnsignedInt sets a unsigned int by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetUnsignedInt(const std::string &name, unsigned int value);
	/// @brief SetUnsingedIntArray sets a unsigned int array by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @param count is the amount of unsigned ints in the array
	/// @return void
	void SetUnsignedIntArray(const std::string &name, unsigned int* value, int count);
	/// @brief SetFloat sets a float by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetFloat(const std::string &name, float value);
	/// @brief SetFloatArray sets a array of floats by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @param count is the amount of floats inside the array
	/// @return void
	void SetFloatArray(const std::string &name, float* value, int count);
	/// @brief SetVec2Float sets a vec2 by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetVec2Float(const std::string &name, glm::vec2 value);
	/// @brief SetVec3Float sets a vec3 by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetVec3Float(const std::string &name, glm::vec3 value);
	/// @brief SetVec4Float sets a vec4 by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetVec4Float(const std::string &name, glm::vec4 value);
	/// @brief SetMatrix sets a mat4 by the shaders uniforms name
	/// @param name name of the uniform
	/// @param value is the value you want to set to that uniform
	/// @return void
	void SetMatrix4(const std::string &name, glm::mat4 value);
	
private:
	/// @brief GetUniformLocation return the location of a uniform. If that uniform does not exist it will retun -1
	/// @param name is the name of the uniform
	/// @return GLint
	GLint GetUniformLocation(const std::string &name);
	/// @brief CreateProgram creates a shader program from the specified vertext and fragmentPath
	/// @param vertexPath is the path to a vertext shader for example: "shaders\\basic.vs"
	/// @param fragmentPath is the path to a fragment shader for example: "shaders\\basic.fs"
	void CreateProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	/// @brief ReadShader reads the shader into a string and the returns it
	/// @param shaderPath is the path to the shader that has to be read
	/// @return std::string
	std::string ReadShader(const GLchar* shaderPath);

	GLuint program; ///< @brief program is a shader program
};
#endif // !SHADER_H
