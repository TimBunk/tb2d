/**
* @file debugRenderer.h
*
* @brief The DebugRenderer header file.
*/

#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#define _USE_MATH_DEFINES

#include <math.h>

#include "camera.h"
#include "resourceManager.h"

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

class B2Entity;

/**
* @brief The DebugRenderer class
*/
class  DebugRenderer
{
public:
	/// @brief Initialize creates a instance of the debugRenderer as a singleton
	/// @return void
	static void Initialize();
	/// @brief Destroy delete the singleton instance of the debugRenderer
	/// @return void
	static void Destroy();
	
	/// @brief Submit submit a b2entity to debug render the body
	/// @param b2entity a b2entity thats needs to have a body otherwise nothing will be rendered
	/// @return void
	static void Submit(B2Entity* b2entity);
	/// @brief Render renders all of the submitted data
	/// @param camera a camera is needed because the shaders for the rendering require a projectionmatrix and sometimes a viewmatrix as well and the camera can provide that
	/// @return void
	static void Render(Camera* camera);
	/// @brief Line renders a single line from one points to another
	/// @param point1 begin point of the line
	/// @param point2 end point of the line
	/// @param color is the color of the line
	static void Line(glm::vec2 point1, glm::vec2 point2, glm::vec3 color);

	/// @brief SetActive can be used for if you want debugRendering to render yes or no
	/// @param active specifies if the DebugRenderer should render or not
	/// @return void
	static void SetActive(bool active);

private:
	/// @brief Constructor of the DebugRenderer
	DebugRenderer();
	/// @brief Destructor of the DebugRenderer
	virtual ~DebugRenderer();

	/// @brief AddBox if the submited b2entiy has a box collider add it to the box vector
	/// @param b2entity a b2entiy with a box collider
	/// @return void
	void AddBox(B2Entity* b2entity);
	/// @brief AddCircle if the submitted b2entity has a circle collider add it to the circle vector
	/// @param b2entity a b2entity with a circle collider
	/// @return void
	void AddCircle(B2Entity* b2entity);

	/// @brief DrawBoxes draws all of the submitted boxes and after that clears all of the box data
	/// @return void
	void DrawBoxes();
	/// @brief DrawCircle draws all of the submitted circle and after that clears all of the circle data
	/// @return void
	void DrawCircles();
	/// @brief DrawLines draws all of the lines that were submitted and after that clear of the line data
	/// @param camera a camera is needed to set some uniforms of a shader that is used for rendering the lines
	/// @return void
	void DrawLines(Camera* camera);

	static DebugRenderer* debugRenderer; ///< @brief debugRenderer is a singleton instance of this class
	bool active; ///< @brief active specifies if the DebugRenderer should render or not
	Shader* shader; ///< @brief shader is the shader that is used for drawing the boxes and the circle
	Shader* shaderLine; ///< @brief shaderLine is the shader that is used for drawing the lines

	GLuint VBO_position; ///< @brief VBO_position is a buffer that is being used for rendering both the boxes and the lines
	GLuint VBO_color; ///< @brief VBO_color is a buffer for the color that is being used for rendering both the boxes and the lines
	// box
	GLuint VAO_box; ///< @brief VAO_box is the VAO for the boxex
	GLuint VBO_boxModel; ///< @brief VBO_boxmodel is a buffer for the boxes modelmatrix
	std::vector<glm::vec2> boxesPosition; ///< @brief boxesPosition keeps track of all of the differnt box positions
	std::vector<glm::vec3> boxesColor; ///< @brief boxesColor keeps track of all of the different box colors
	std::vector<glm::mat4> boxesModel; ///< @brief boxesModel keeps track of all of the different box models
	int boxesCount; ///< @brief boxesCount is the amount of boxes that have to be drawn
	// circle
	GLuint VAO_circle; ///< @brief VAO_circle is the VAO for the circles
	GLuint VBO_circlePosition; ///< @brief VBO_circlePosition is a buffer that is being used for rendering the circle at the correct positons
	GLuint EBO_circlePosition; ///< @brief EBO_circlePosition is a buffer that indexes the VBO_circlePosition
	GLuint VBO_circleColor; ///< @brief VBO_circleColor is a buffer for all of the differnt circle colors
	GLuint VBO_circleModel; ///< @brief VBO_circleModel is a buffer for all of the different circle models
	std::vector<glm::vec3> circlesColor; ///< @brief circlesColor a vector that keeps track of all of the different circleColors
	std::vector<glm::mat4> circlesModel; ///< @brief circlesModel a vector that keeps track of all of the differnt model matrices of the circles
	int circlesCount; ///< @brief circlesCount is the amount of circle that have to be drawn
	// line
	GLuint VAO_line; ///< @brief VAO_line is the VAO for the lines
	std::vector<glm::vec2> linesPosition; ///< @brief linesPosition is a vector that keeps track of all of the differnt linePositions
	std::vector<glm::vec3> linesColor; ///< @brief lineColor is a vector that keeps track of all of the differnt colors
	int linesCount; ///< @brief linesCount is the amount of lines that need to be drawn
};

#endif // !DEBUGRENDERER_H
