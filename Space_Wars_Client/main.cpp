
#include "Client.h"
#if _WIN32
#include <Windows.h>
#define FREEGLUT_LIB_PRAGMAS 0
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#endif

// Entete OpenGL 
#define GLEW_STATIC 1

#include "Shader.h"
Shader basicShader;
//#include <gl/GL.h>
//#include "GL/glext.h"

// FreeGLUT
#include "GL/freeglut.h"

#include <cstdio>
#include <cmath>
int previousTime = 0;


PlayerGL* p;


/*
struct Camera
{

} g_Camera;*/

void Initialize()
{
	GLenum error = glewInit();
	if (error != GL_NO_ERROR) {
		// TODO
	}
	p = new  PlayerGL();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	previousTime = glutGet(GLUT_ELAPSED_TIME);
}

void Terminate()
{
	delete p;
}


void Render()
{
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glClearColor(1.f, 1.0f, 1.0f , 1.0f);
	glClearDepth(1.F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float w = (float)glutGet(GLUT_WINDOW_WIDTH);
	float h = (float)glutGet(GLUT_WINDOW_HEIGHT);
	float ratio = w / h;

	glm::mat4 proj = glm::perspective(45.f, w / h, 0.1f, 1000.f);
	glm::mat4 modelView;
	modelView = glm::mat4(1.0f);
	modelView = glm::translate(glm::vec3(0, 0, -7.0f));
	p->draw(proj, modelView);

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int delta = currentTime - previousTime;
	previousTime = currentTime;
	static float time = 1.f;
	time += delta / 1000.f;

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	//Client c = Client();
	//c.sendMessage("Z");
	//c.sendMessage("S");
	//c.sendMessage("D");
	int l;
	//std::cin >> l;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cube Basique");

#ifdef FREEGLUT
	// Note: glutSetOption n'est disponible qu'avec freeGLUT
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	Initialize();

	glutDisplayFunc(Render);

	glutMainLoop();

	Terminate();

	return 0;

	//recupère les donné du serveur et les traitent

	//fait avancer les vaisseaux dans le vecteur orientation

	//envoi les inputs
}
