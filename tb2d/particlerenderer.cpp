#include "particlerenderer.h"

ParticleRenderer::ParticleRenderer(Shader* shader) : Renderer::Renderer(shader)
{
	// Generate and bind the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind the VBO
	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);
	GLfloat vertices[]{
		-0.5f, -0.5f, 0.0f, 0.0f,// lower left
		0.5f, -0.5f, 1.0f, 0.0f,// lower right
		0.5f, 0.5f, 1.0f, 1.0f,// upper right
		-0.5f, 0.5f, 0.0f, 1.0f // upper left
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Generate and bind the VBO
	glGenBuffers(1, &EBO_position);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_position);
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Generate and bind the VBO
	glGenBuffers(1, &VBO_particleData);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particleData);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(1);// TextureID
	glEnableVertexAttribArray(2);// Color
	glEnableVertexAttribArray(3);// matrix part1
	glEnableVertexAttribArray(4);// matrix part2
	glEnableVertexAttribArray(5);// matrix part3
	glEnableVertexAttribArray(6);// matrix part4

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::textureID)));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::color)));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::model) + (0 * sizeof(glm::vec4))));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::model) + (1 * sizeof(glm::vec4))));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::model) + (2 * sizeof(glm::vec4))));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (GLvoid*)(offsetof(ParticleData, ParticleData::model) + (3 * sizeof(glm::vec4))));

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	for (int i = 0; i < 32; i++) {
		activeTextureArray[i] = i;
	}
}

ParticleRenderer::~ParticleRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &EBO_position);
	glDeleteBuffers(1, &VBO_particleData);
}

void ParticleRenderer::Submit(Particle particle)
{
	// Set particle texture ID
	int id = 0;
	if (particle.textureID > 0) {
		bool found = false;
		for (; id < textureSlots.size(); id++) {
			if (particle.textureID == textureSlots[id]) {
				found = true;
				break;
			}
		}
		if (found == false) {
			if (textureSlots.size() == 32) {
				// TODO: Make a fix so that there can be more than 32 textures
				std::cout << "above 32 textures! " << std::endl;
			}
			textureSlots.push_back(particle.textureID);
		}
	}
	else {
		id = -1;
	}
	// Create the model matrix of the particle
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(particle.position.x, particle.position.y, 0.0f));
	model = glm::rotate(model, particle.angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(particle.width, particle.height, 0.0f));
	// Set the particle data
	ParticleData pd;
	pd.textureID = (GLfloat(id) + 1.0f);
	pd.color = particle.color;
	pd.model = model;
	particleData.push_back(pd);
}

void ParticleRenderer::Render(Camera * camera)
{
	// If there is nothing to draw
	if (particleData.size() == 0) { return; };

	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetIntArray("textures", activeTextureArray, 32);

	// Bind the VAO
	glBindVertexArray(VAO);

	for (int i = 0; i < textureSlots.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
	}

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_particleData);
	glBufferData(GL_ARRAY_BUFFER, particleData.size() * sizeof(ParticleData), &particleData[0], GL_DYNAMIC_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// draw elements
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleData.size());

	// Unbind the VAO and texture
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Clear all of the data
	particleData.clear();
	textureSlots.clear();
}
