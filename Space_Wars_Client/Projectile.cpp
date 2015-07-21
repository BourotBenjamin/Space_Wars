#include "Projectile.h"


ProjectileGL::ProjectileGL(std::string vs, std::string fs)
{
	m_shader = Shader(vs, fs);
	m_shader.charger();

	for (int i = 0; i < 24; i++)
	{
		m_toVBOPoints.push_back(g_projectileVertices[i]);
	}
	vbosize = m_toVBOPoints.size() * sizeof(float);
	for (int i = 0; i < 36; i++)
	{
		m_indicesTriangle.push_back(g_projectileIndices[i]);
	}
	ebosize = m_indicesTriangle.size() * sizeof(GLushort);
}


ProjectileGL::~ProjectileGL()
{
	glDeleteBuffers(1, &m_vboID);
	glDeleteBuffers(1, &m_triangleEBO);
	glDeleteVertexArrays(1, &m_vaoID);
}

void ProjectileGL::load()
{

	// Génération de l'identifiant des VAO, VBO et EBO
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_vboID);
	glGenBuffers(1, &m_triangleEBO);

	// Verrouillage du VAO
	glBindVertexArray(m_vaoID);

	// Verrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// Allocation de la mémoire vidéo
	glBufferData(GL_ARRAY_BUFFER, vbosize, 0, GL_STATIC_DRAW);

	// Transfert des données
	glBufferSubData(GL_ARRAY_BUFFER, 0, vbosize, m_toVBOPoints.data());

	// Déverrouillage de l'objet
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebosize, m_indicesTriangle.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Accès aux vertices dans la mémoire vidéo
	GLint positionLocation = glGetAttribLocation(m_shader.getProgramID(), "a_position");
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionLocation);

	// Déverrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Déverrouillage du VAO
	glBindVertexArray(0);
}

void ProjectileGL::draw(Mat4x4 projection, Mat4x4 modelView, Mat4x4 world, Point2 color, Point2 camPos, Point2 camDir)
{
	// Activation du shader
	glUseProgram(m_shader.getProgramID());

	// Verrouillage du VAO
	glBindVertexArray(m_vaoID);

	// Envoi des matrices
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_projection"), 1, GL_FALSE, projection.getMatrix());
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_modelView"), 1, GL_FALSE, modelView.getMatrix());
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "u_world"), 1, GL_FALSE, world.getMatrix());
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "u_camPos"), camPos.Getx(), camPos.Gety(), camPos.Getz());
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "u_camPos"), camDir.Getx(), camDir.Gety(), camDir.Getz());
	glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "u_color"), color.Getx(), color.Gety(), color.Getz());


	// Rendu
	glDrawElements(GL_TRIANGLES, m_indicesTriangle.size(), GL_UNSIGNED_SHORT, 0);

	// Déverrouillage du VAO
	glBindVertexArray(0);

	// Désactivation du shader
	glUseProgram(0);
}
