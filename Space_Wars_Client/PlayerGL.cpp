#include "PlayerGL.h"


PlayerGL::PlayerGL()
{
	pos.x = 0.f;
	pos.y = 0.f;
	pos.z = 5.f;
	orientation = -pos;
	glm::normalize(orientation);
	rotation = glm::mat4(1.0f);
	m_shader = Shader("basic.vs", "basic.fs");
	m_shader.charger();
	load();
}

void PlayerGL::load()
{

	if (glIsVertexArray(m_vaoID) == GL_TRUE)
		glDeleteVertexArrays(1, &m_vaoID);
	// Destruction d'un éventuel ancien VBO
	if (glIsBuffer(m_vboID) == GL_TRUE)
		glDeleteBuffers(1, &m_vboID);
	if (glIsBuffer(m_eboID) == GL_TRUE)
		glDeleteBuffers(1, &m_eboID);

	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_vboID);
	glGenBuffers(1, &m_eboID);

	glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 15, g_pyramydeVertices, GL_STATIC_DRAW);

	GLint positionLocation = glGetAttribLocation(m_shader.getProgramID(), "a_position");
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionLocation);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* 18, g_pyramideIndices, GL_STATIC_DRAW);




	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


PlayerGL::~PlayerGL()
{
	glDeleteBuffers(1, &m_vboID);
	glDeleteBuffers(1, &m_eboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void PlayerGL::draw(glm::mat4& projection, glm::mat4& modelView)
{
	//std::cout << " x -> " << pos.x << " y -> " << pos.y << " z -> " << pos.z << std::endl;
	glUseProgram(m_shader.getProgramID());

	glBindVertexArray(m_vaoID);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_modelView"), 1, GL_FALSE, glm::value_ptr(modelView));

	glm::mat4 worldTransform = glm::mat4(1.0);
	worldTransform = glm::translate(pos);
	//glm::rotate(worldTransform, 90.f, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_worldMatrix"), 1, GL_FALSE, glm::value_ptr(worldTransform));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Déverrouillage du VAO
	glBindVertexArray(0);

	// Désactivation du shader
	glUseProgram(0);
}

void PlayerGL::draw(float * projection, float * modelView)
{
	//std::cout << " x -> " << pos.x << " y -> " << pos.y << " z -> " << pos.z << std::endl;
	glUseProgram(m_shader.getProgramID());

	glBindVertexArray(m_vaoID);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_projection"), 1, GL_FALSE, projection);
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_modelView"), 1, GL_FALSE, modelView);

	/*glm::mat4 worldTransform = glm::mat4(1.0);
	worldTransform = glm::translate(pos);
	glm::rotate(worldTransform, -90.f, glm::vec3(0, 1, 0));*/
	//glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_worldMatrix"), 1, GL_FALSE, glm::value_ptr(worldTransform));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Déverrouillage du VAO
	glBindVertexArray(0);

	// Désactivation du shader
	glUseProgram(0);
}
