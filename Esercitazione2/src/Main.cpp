#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include "../include/GameManager.h"

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
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC * 1000);
	int nextUpdate = (difference >= WORLD_UPDATE_TIME)
								? 0
								: WORLD_UPDATE_TIME - difference;
	glutTimerFunc(nextUpdate, updateWorld, 0);
}

/* Gestione della grafica */
void updateDisplay(int value) {
	std::cout << "Update ";
	glClear(GL_COLOR_BUFFER_BIT);
	clock_t startTime = clock();
	game -> displayUpdate();
	glutSwapBuffers();
	clock_t endTime = clock();
	double difference = ((float)endTime - startTime) / (CLOCKS_PER_SEC * 1000);
	int nextUpdate = (difference >= DISPLAY_UPDATE_TIME)
								? 0
								: DISPLAY_UPDATE_TIME - difference;
	// TODO("Verificare il value == -1)
	if(value != -1)
		glutTimerFunc(nextUpdate, updateDisplay, 0);
}

void display(void) {
	std::cout << "Display ";
	game->displayUpdate();
	glutSwapBuffers();
}

void resize(int width, int height) {
	std::cout << "Resinzing " << width << " " << height;
	if(width != FIXED_WIDTH || height != FIXED_HEIGHT)
		glutReshapeWindow(FIXED_WIDTH, FIXED_HEIGHT);
	glViewport(0, 0, FIXED_WIDTH, FIXED_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, FIXED_WIDTH, FIXED_HEIGHT, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void clean(void) {
	delete game;
}

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(FIXED_WIDTH, FIXED_HEIGHT);
	glutCreateWindow("Esercitazione 2");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glewInit();
	
	game = new GameManager(FIXED_WIDTH, FIXED_HEIGHT);
	glutTimerFunc(WORLD_UPDATE_TIME, updateWorld, 0);
	glutTimerFunc(DISPLAY_UPDATE_TIME, updateDisplay, 0);
	glutCloseFunc(clean);
	glutMainLoop();
}
