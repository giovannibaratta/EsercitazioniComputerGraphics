/**********************************
 *	BARATTA GIOVANNI 0000853633   *
 **********************************/

/*
 * Lab-01-1819_students.c
 *
 *     This program draws straight lines connecting dots placed with mouse clicks.
 *
 * Usage:  
 *   Left click to place a control point.  
 *		Maximum number of control points allowed is currently set at 64.
 *	 Press "f" to remove the first control point
 *	 Press "l" to remove the last control point.
 *	 Press escape to exit.
 */

#include <stdlib.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

#define MAX_NUM_PTS 64
// distanza minima dal control point per renderlo clickabile
#define DISTANCE_THRESHOLD 0.015 

enum CURVE_EVALUATION_METHOD
{
	OPENGL,
	DE_CASTELJAU,
	SUBDIVISION
};

CURVE_EVALUATION_METHOD eval_method = SUBDIVISION;

// coordinate dei control point della curva
float controlPoints[MAX_NUM_PTS][3];
// numero di control point presenti
int currentControlPoints = 0;

// Window size in pixels
int windowHeight;
int windowWidth;

/* gestione spostamento control point */
// indice del control point sulla quale mi trovo. -1 se non sono su un control point
int mouseOverPointIndex = -1;
// true se sto trasciando un control point
bool dragging = false;
int breakCurveCounter = 0;

/* Prototypes */ 
void addNewPoint(float x, float y);
void removeFirstPoint();
void removeLastPoint();
void deCasteljau(float param, float* result);
int subdivision(float threshold, float controlPoints[][3], int numberOfControls); 
void passive(int x, int y);
void active(int x, int y);
float pointLineDistanceSquared(float px, float py, float lx1, float ly1, float lx2, float ly2);
void divideCurve(float controlPoints[][3], int numberOfControls, float leftCurve[][3], float rightCurve[][3]);

/* Gestione interazione tramite tastiera*/
void myKeyboardFunc (unsigned char key, int x, int y)
{
	switch (key) {
	case 'f':
		removeFirstPoint();
		glutPostRedisplay();
		break;
	case 'l':
		removeLastPoint();
		glutPostRedisplay();
		break;
	case 27:			// Escape key
		exit(0);
		break;
	}
}

void removeFirstPoint() {
	int i;
	if ( currentControlPoints>0 ) {
		// Remove the first point, slide the rest down
		currentControlPoints--;
		for ( i=0; i<currentControlPoints; i++ ) {
			controlPoints[i][0] = controlPoints[i+1][0];
			controlPoints[i][1] = controlPoints[i+1][1];
			controlPoints[i][2] = 0;
		}
	}
}

// Left button presses place a control point.
void myMouseFunc( int button, int state, int x, int y ) {
	
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) 
	{
		
		float xPos = ((float)x)/((float)(windowWidth-1));
		float yPos = ((float)y)/((float)(windowHeight-1));

		// Flip value since y position is from top row.
		yPos = 1.0f-yPos;			

		// se sono sopra un altro punto, invece di aggiungerne un 
		// altro, sposto quello già presente. La gestione del movimento
		// avviene nella funzione passive.
		if (mouseOverPointIndex >= 0)
			dragging = true;
		else
			addNewPoint(xPos, yPos);

		glutPostRedisplay();
	}

	// quando rilascio il mouse sinistra termino il trascinamento
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		dragging = false;

}

// Add a new point to the end of the list.  
// Remove the first point in the list if too many points.
void removeLastPoint() {
	if ( currentControlPoints>0 ) {
		currentControlPoints--;
	}
}

// Add a new point to the end of the list.  
// Remove the first point in the list if too many points.
void addNewPoint( float x, float y ) {
	
	if ( currentControlPoints>=MAX_NUM_PTS )
		removeFirstPoint();
	
	controlPoints[currentControlPoints][0] = x;
	controlPoints[currentControlPoints][1] = y;
	controlPoints[currentControlPoints][2] = 0;
	currentControlPoints++;
	
}

void display(void)
{
	int i;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	
	if ( currentControlPoints > 1 ) {
		glColor3f(0.0f, 0.5f, 0.8f);
		glBegin( GL_LINE_STRIP );
		for ( i=0; i < currentControlPoints; i++ ) {
			// collego i punti 2 a 2 con un segmento
			glVertex2f( controlPoints[i][0], controlPoints[i][1] );
		}
		glEnd();
	}

	/* DISEGNO DELLA CURVA TRAMITE OPENGL*/
	if (eval_method == OPENGL && currentControlPoints > 1){

		glColor3f(0.2f, 0.5f, 0.2f);
		// direttiva ad opengl per la valutazione dei punti di controllo
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, currentControlPoints, &controlPoints[0][0]);
		glBegin(GL_LINE_STRIP);
		// valuto la curva in 100 punti e la collego con delle linee
		for (i = 0; i < 100; i++)
			// valutazione e rendering della curva tramite opengl
			glEvalCoord1f((GLfloat)i / 100.0);

		glEnd();
	}

	/* DISEGNO DELLA CURVA TRAMITE DECASTELJAU */
	if (eval_method == DE_CASTELJAU && currentControlPoints > 1) {

		glColor3f(0.2f, 0.5f, 0.2f);
		// direttiva ad opengl per la valutazione dei punti di controllo
		glBegin(GL_LINE_STRIP);
		// valuto la curva in 100 punti e la collego con delle linee
		float deCastResult[3];
		for (i = 0; i < 100; i++) {

			deCasteljau((float)i / 100.0, deCastResult);
			// rendering delle valutazioni
			glVertex3f(deCastResult[0], deCastResult[1], 0.0);

		}
		glEnd();
	}

	/* DISEGNO DELLA CURVA TRAMITE SUBDIVISION */
	if (eval_method == SUBDIVISION && currentControlPoints > 2) {
		glColor3f(0.2f, 0.5f, 0.2f);
		glBegin(GL_LINE_STRIP);
		int subCount = subdivision(0.000001, controlPoints, currentControlPoints);
		glEnd();

		cout << "Numero di suddivisioni " << subCount << "\n";
	}

	// Draw the interpolated points second.
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);

	for (i = 0; i < currentControlPoints; i++) {
		if (i == mouseOverPointIndex)
			// cambio colore
			glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(controlPoints[i][0], controlPoints[i][1]);
		if (i == mouseOverPointIndex)
			// ripristno il nero
			glColor3f(0.0f, 0.0f, 0.0f);
	}

	glEnd();
	glFlush();
}

void initRendering() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// Make big points and wide lines.  (This may be commented out if desired.)
	glPointSize(8);
	
	// The following commands should induce OpenGL to create round points and 
	//	antialias points and lines.  (This is implementation dependent unfortunately, and
	//  may slow down rendering considerably.)
	//  You may comment these out if you wish.
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(eval_method == OPENGL)
		glEnable(GL_MAP1_VERTEX_3);
}

/* disegna la curva tramite metodo di subdivision*/
int subdivision(float threshold, float controlPoints[][3], int numberOfControls) {
	
	float x, y, z, distance;
	bool noSubdivision = false;
	int subdivisionCount = 0;
	
	float lineStartX = controlPoints[0][0];
	float lineStartY = controlPoints[0][1];
	float lineEndX = controlPoints[numberOfControls - 1][0];
	float lineEndY = controlPoints[numberOfControls - 1][1];

	for (int i = 1; i < numberOfControls - 1 && noSubdivision == false; i++) {
		x = controlPoints[i][0];
		y = controlPoints[i][1];
		z = controlPoints[i][2];
		distance = pointLineDistanceSquared(x, y, lineStartX, lineStartY, lineEndX, lineEndY);
		// se la distanza è maggiore della soglia spezzo la curva in due parti e procedo ricorsivamente.
		if (distance > threshold) {
			noSubdivision = true;
			float leftCurve[MAX_NUM_PTS][3];
			float rightCurve[MAX_NUM_PTS][3];
			divideCurve(controlPoints, numberOfControls, leftCurve, rightCurve);
			subdivisionCount += subdivision(threshold, leftCurve, numberOfControls) 
								+ subdivision(threshold, rightCurve, numberOfControls) 
								+ 2;
		}
	}

	if (noSubdivision == false) {
		glVertex2f(lineStartX, lineStartY);
		glVertex2f(lineEndX, lineEndY);
	}
	return subdivisionCount;
}

// distanza tra punto e retta al quadrato
float pointLineDistanceSquared(float px, float py, float lx1, float ly1, float lx2, float ly2){
	float m = (ly2 - ly1) / (lx2 - lx1);
	float q = ly2 - m * lx2;
	return pow(-m * px + py - q, 2) / (m * m + 1);
}

// spezza la curva in ingresso in due parti
void divideCurve(float controlPoints[][3], int numberOfControls, float leftCurve[][3], float rightCurve[][3] ) {
	float _leftCurve[MAX_NUM_PTS][3];
	float _reverseRightCurve[MAX_NUM_PTS][3];
	float tempPoints[MAX_NUM_PTS][3];
	int i = 0;
	int j = 0;
	int iteration = 0;
	int tempNPoints = currentControlPoints;

	// copio tutti i punti della curva
	for (i = 0; i < currentControlPoints; i++) {
		tempPoints[i][0] = controlPoints[i][0];
		tempPoints[i][1] = controlPoints[i][1];
		tempPoints[i][2] = controlPoints[i][2];
	}

	// copio i punti esterni nelle rispettive curve
	_leftCurve[0][0] = tempPoints[0][0];
	_leftCurve[0][1] = tempPoints[0][1];
	_reverseRightCurve[0][0] = tempPoints[tempNPoints - 1][0];
	_reverseRightCurve[0][1] = tempPoints[tempNPoints - 1][1];


	// le interpolazioni devono essere fatte fino ad ottenere un unico punto
	while (tempNPoints > 1) {
		// faccio le interpolazioni sui segmenti
		for (i = 0; i < currentControlPoints - 1; i++) {
			tempPoints[i][0] = 0.5 * tempPoints[i][0] + 0.5 * tempPoints[i + 1][0];
			tempPoints[i][1] = 0.5 * tempPoints[i][1] + 0.5 * tempPoints[i + 1][1];
		}
		tempNPoints--;
		iteration++;
		_leftCurve[iteration][0] = tempPoints[0][0];
		_leftCurve[iteration][1] = tempPoints[0][1];
		_reverseRightCurve[iteration][0] = tempPoints[tempNPoints - 1][0];
		_reverseRightCurve[iteration][1] = tempPoints[tempNPoints - 1][1];
	}

	for (int i = 0; i < iteration + 1; i++) {
		leftCurve[i][0] = _leftCurve[i][0];
		leftCurve[i][1] = _leftCurve[i][1];
		rightCurve[i][0] = _reverseRightCurve[iteration - i][0];
		rightCurve[i][1] = _reverseRightCurve[iteration - i][1];
	}

}

void deCasteljau(float param, float* result) {
	
	float tempPoints[MAX_NUM_PTS][3];
	int i = 0;
	int j = 0;
	int tempNPoints = currentControlPoints;
	// copio i punti
	for (i = 0; i < currentControlPoints; i++) {
		tempPoints[i][0] = controlPoints[i][0];
		tempPoints[i][1] = controlPoints[i][1];
		tempPoints[i][2] = controlPoints[i][2];
	}
	
	// le interpolazioni devono essere fatte fino ad ottenere un unico punto
	while (tempNPoints > 1) {
		// faccio le interpolazioni sui segmenti
		for (i = 0; i < currentControlPoints - 1; i++) {
			tempPoints[i][0] = (1 - param) * tempPoints[i][0] + param * tempPoints[i + 1][0];
			tempPoints[i][1] = (1 - param) * tempPoints[i][1] + param * tempPoints[i + 1][1];
		}
		tempNPoints--;
	}

	result[0] = tempPoints[0][0];
	result[1] = tempPoints[0][1];
}

void active(int x, int y) {

	float xPos = ((float)x) / ((float)(windowWidth - 1));
	float yPos = ((float)y) / ((float)(windowHeight - 1));

	yPos = 1.0f - yPos;			// Flip value since y position is from top row.
	
	if (dragging && mouseOverPointIndex >= 0) {
		// sposto il punto 
		controlPoints[mouseOverPointIndex][0] = xPos;
		controlPoints[mouseOverPointIndex][1] = yPos;
		glutPostRedisplay();
	}
}

void passive(int x, int y) {
	// converto le coordinate da pixel a scena
	float xPos = ((float)x) / ((float)(windowWidth - 1));
	float yPos = ((float)y) / ((float)(windowHeight - 1));

	yPos = 1.0f - yPos;			// Flip value since y position is from top row.

	mouseOverPointIndex = -1;
	
	for (int i = 0; i < currentControlPoints; i++) {
		float distance = sqrt(pow(xPos - controlPoints[i][0], 2.0) + pow(yPos - controlPoints[i][1], 2.0));
		if (distance < DISTANCE_THRESHOLD) {
			mouseOverPointIndex = i;
			break;
		}
	}
	
	glutPostRedisplay();
}

void resizeWindow(int w, int h)
{
	windowHeight = (h>1) ? h : 2;
	windowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv); // apre connessione con il server per creare una finestra
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); 
	glutInitWindowSize(500, 500); // orgine in alto a dx
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	initRendering();
	
	// associo le callback
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(myMouseFunc);
	glutPassiveMotionFunc(passive);
	glutMotionFunc(active);
	glutMainLoop();

	return 0; // This line is never reached
}
