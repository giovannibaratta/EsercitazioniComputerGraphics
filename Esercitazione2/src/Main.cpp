
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include <sstream>
#include "../include/GameManager.h"

using namespace std;

int FIXED_WIDTH = 640;
int FIXED_HEIGHT = 320;
// Aggiornamento ogni 16 MS
const int WORLD_UPDATE_TIME = 16;
const int DISPLAY_UPDATE_TIME = 16;
GameManager* game;

/* Gestione dello stato */ 
void updateWorld(int value) {
	clock_t startTime = clock();
	game -> worldUpdate();
	clock_t endTime = clock();
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC / 1000);
	int nextUpdate = (difference >= WORLD_UPDATE_TIME)
								? 0
								: WORLD_UPDATE_TIME - difference;
	glutTimerFunc(nextUpdate, updateWorld, 0);
}

/* Gestione della grafica */
void updateDisplay(int value) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	clock_t startTime = clock();
	game -> displayUpdate();
	glutSwapBuffers();
	clock_t endTime = clock();
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC / 1000);
	int nextUpdate = (difference >= DISPLAY_UPDATE_TIME)
								? 0
								: DISPLAY_UPDATE_TIME - difference;
	glutTimerFunc(nextUpdate, updateDisplay, 0);
}

void display(void) {
	//cout << "Display ";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game->displayUpdate();
	glutSwapBuffers();
}

void resize(int width, int height) {
	//cout << "Resinzing " << width << " " << height;
	if(width != FIXED_WIDTH || height != FIXED_HEIGHT)
		glutReshapeWindow(FIXED_WIDTH, FIXED_HEIGHT);
	glViewport(0, 0, FIXED_WIDTH, FIXED_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, FIXED_WIDTH, 0.0, FIXED_HEIGHT, -1.0, 1.0);
	gluLookAt(0, 0, 1, 0, 0, -1.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void clean(void) {
	delete game;
}

void arrowHandler(int key, int x, int y) {
	switch (key)
	{
		case GLUT_KEY_LEFT:
			game->keyPressed(GameManager::LEFT);
			break;
		case GLUT_KEY_RIGHT:
			game->keyPressed(GameManager::RIGHT);
			break;
	}
}

/*
void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}*/

#pragma region OpenGL version
// https://www.badprog.com/c-opengl-checking-the-freeglut-glew-and-opengl-version
string makeMeString(GLint versionRaw) {
	stringstream ss;
	string str = "\0";

	ss << versionRaw;    // transfers versionRaw value into "ss"
	str = ss.str();        // sets the "str" string as the "ss" value
	return str;
}

// https://www.badprog.com/c-opengl-checking-the-freeglut-glew-and-opengl-version
void formatMe(string* text) {
	string dot = ".";

	text->insert(1, dot); // transforms 30000 into 3.0000
	text->insert(4, dot); // transforms 3.0000 into 3.00.00
}

// https://www.badprog.com/c-opengl-checking-the-freeglut-glew-and-opengl-version
void printVersion() {
	char* versionGL;
	GLint versionFreeGlutInt = 0;

	versionGL = (char*)(glGetString(GL_VERSION));
	versionFreeGlutInt = (glutGet(GLUT_VERSION));

	string versionFreeGlutString = makeMeString(versionFreeGlutInt);
	formatMe(&versionFreeGlutString);

	cout << endl;
	cout << "OpenGL version: " << versionGL << endl;
	cout << "FreeGLUT version: " << versionFreeGlutString << endl;
	cout << "GLEW version: " <<
		GLEW_VERSION << "." << GLEW_VERSION_MAJOR << "." <<
		GLEW_VERSION_MINOR << "." << GLEW_VERSION_MICRO << endl << endl;
}
#pragma endregion

#pragma region print opengl debug messages
// https://learnopengl.com/In-Practice/Debugging
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}
#pragma endregion

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(FIXED_WIDTH, FIXED_HEIGHT);
	glutCreateWindow("Esercitazione 2");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutSpecialFunc(arrowHandler);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();
	printVersion();
   glDebugMessageCallback(glDebugOutput, 0);
	game = new GameManager(FIXED_WIDTH, FIXED_HEIGHT);
	
	glutTimerFunc(WORLD_UPDATE_TIME, updateWorld, 0);
	glutTimerFunc(DISPLAY_UPDATE_TIME, updateDisplay, 0);
	glutCloseFunc(clean);
	glutMainLoop();
}
