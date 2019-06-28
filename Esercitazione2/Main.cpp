#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include "Game.h"
#include "TestGameLogic.h"

int INITIAL_WIDTH = 640;
int INITIAL_HEIGHT = 320;
const int WORLD_UPDATE_TIME = 16;
const int DISPLAY_UPDATE_TIME = 16;
GameManager* game;

void updateWorld(int value) {
	clock_t startTime = clock();
	game -> worldUpdate();
	clock_t endTime = clock();
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC * 1000);
	int nextUpdate = (difference >= 16) ? 0 : WORLD_UPDATE_TIME - difference;
	glutTimerFunc(nextUpdate, updateWorld, 0);
}

void updateDisplay(int value) {
	/* CHIEDERE ULTERIORI INFO SUL CLEAR*/
	glClear(GL_COLOR_BUFFER_BIT);
	clock_t startTime = clock();
	game -> displayUpdate();
	glutSwapBuffers();
	//glutPostRedisplay();
	clock_t endTime = clock();
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC * 1000);
	int nextUpdate = (difference >= 16) ? 0 : DISPLAY_UPDATE_TIME - difference;
	if(value != -1)
		glutTimerFunc(nextUpdate, updateDisplay, 0);
}

void display(void) {
	//clock_t startTime = clock();
	game->displayUpdate();
	//glutSwapBuffers();
	//glutPostRedisplay();
	//clock_t endTime = clock();
	//double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC * 1000);
	//int nextUpdate = (difference >= 16) ? 0 : DISPLAY_UPDATE_TIME - difference;
	//glutSwapBuffers();
}

void resize(int width, int height) {
	std::cout << "Resinzing " << width << " " << height;
	glutReshapeWindow(INITIAL_WIDTH, INITIAL_HEIGHT);
	glViewport(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, INITIAL_WIDTH, INITIAL_HEIGHT, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void clean(void) {
	delete game;
}

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutCreateWindow("Esercitazione 2");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();

	game = new GameManager(&TestGameLogic());
	glutTimerFunc(WORLD_UPDATE_TIME, updateWorld, 0);
	glutTimerFunc(DISPLAY_UPDATE_TIME, updateDisplay, 0);
	glutCloseFunc(clean);
	glutMainLoop();
}
