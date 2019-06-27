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

// coordinate dei control point della curva
float controlPoints[MAX_NUM_PTS][3];
// numero di control point presenti
int currentControlPoints = 0;

// Window size in pixels
int WindowHeight;
int WindowWidth;
int overPointIndex = -1;
bool dragging = false;
int breakCurveCounter = 0;

/* Prototypes */ 
void addNewPoint(float x, float y);
void removeFirstPoint();
void removeLastPoint();
void deCasteljau(float param, float* result);
void subdivision(float threshold, float controlPoints[][3], int numberOfControls); 
void passive(int x, int y);
void active(int x, int y);
float pointFromLineSquared(float px, float py, float lx1, float ly1, float lx2, float ly2);
void divideCurve(float controlPoints[][3], int numberOfControls, float leftCurve[][3], float rightCurve[][3]);

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
		
		float xPos = ((float)x)/((float)(WindowWidth-1));
		float yPos = ((float)y)/((float)(WindowHeight-1));


		

		yPos = 1.0f-yPos;			// Flip value since y position is from top row.

		cout << "Press" << overPointIndex << "\n";
		if (overPointIndex >= 0) {
			dragging = true;
		}
		else {
			addNewPoint(xPos, yPos);
		}
		glutPostRedisplay();
	}


	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		cout << "Release";
		dragging = false;
	}

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
	if ( currentControlPoints>=MAX_NUM_PTS ) {
		removeFirstPoint();
	}
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
	
	// Draw the line segments
	
	if ( currentControlPoints>1 ) {
		glColor3f(0.0f, 0.5f, 0.8f);			// Reddish/purple lines
		glBegin( GL_LINE_STRIP );
		for ( i=0; i<currentControlPoints; i++ ) {
				glVertex2f( controlPoints[i][0], controlPoints[i][1] ); // collego due punti
		}
		glEnd();
	}

	/*
	if (NumPts > 1) {
		glColor3f(0.2f, 0.5f, 0.2f);
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, NumPts, &PointArray[0][0]);
		// disegno della curva di bezier
		glBegin(GL_LINE_STRIP);
		// valuto la curva in 100 punti e la collego con delle linee
		
		float deCastResult[3];
		
		for (i = 0; i < 100; i++) {

			// valutazione e rendering della curva tramite opengl
			//glEvalCoord1f((GLfloat)i / 100.0);

			// valutazione tramite decasteljau alternativa a quella di opengl
			deCasteljau((float)i / 100.0, deCastResult);
			// rendering delle valutazioni
			glVertex3f(deCastResult[0], deCastResult[1], 0.0);

		}
		glEnd();
	}*/

	glColor3f(0.2f, 0.5f, 0.2f);
	glBegin(GL_LINE_STRIP);
	if (currentControlPoints > 2) {
		breakCurveCounter = 0;
		subdivision(0.000001, controlPoints, currentControlPoints);
		cout << "Numero di suddivisioni " << breakCurveCounter << "\n";
	}
	glEnd();
	   	  
	// Draw the interpolated points second.
	glColor3f( 0.0f, 0.0f, 0.0f);			// Draw points in black
	glBegin( GL_POINTS );

	for ( i=0; i<currentControlPoints; i++ ) {
		if (i == overPointIndex) {
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		glVertex2f( controlPoints[i][0], controlPoints[i][1] );
		if (i == overPointIndex) {
			glColor3f(0.0f, 0.0f, 0.0f);
		}
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
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// per la curva di bezier
	glEnable(GL_MAP1_VERTEX_3);
}

void subdivision(float threshold, float controlPoints[][3], int numberOfControls) {
	
	float x, y, z, distance;
	bool noSubdivision = false;
	breakCurveCounter++;
	   
	for (int i = 1; i < numberOfControls - 1 && noSubdivision == false; i++) {
		x = controlPoints[i][0];
		y = controlPoints[i][1];
		z = controlPoints[i][2];
		distance = pointFromLineSquared(x, y, controlPoints[0][0], controlPoints[0][1], controlPoints[numberOfControls - 1][0], controlPoints[numberOfControls - 1][1]);
		if (distance > threshold) {
			noSubdivision = true;
			// break curve
			float leftCurve[MAX_NUM_PTS][3];
			float rightCurve[MAX_NUM_PTS][3];
			divideCurve(controlPoints, numberOfControls, leftCurve, rightCurve);
			subdivision(threshold, leftCurve, numberOfControls);
			subdivision(threshold, rightCurve, numberOfControls);
		}
	}

	if (noSubdivision == false) {
		glVertex2f(controlPoints[0][0], controlPoints[0][1]);
		glVertex2f(controlPoints[numberOfControls - 1][0], controlPoints[numberOfControls - 1][1]);
	}
}

float pointFromLineSquared(float px, float py, float lx1, float ly1, float lx2, float ly2){
	float m = (ly2 - ly1) / (lx2 - lx1);
	float q = ly2 - m * lx2;
	float squareDistance = pow(-m * px + py - q, 2) / (m * m + 1);
	return squareDistance;
}

void divideCurve(float controlPoints[][3], int numberOfControls, float leftCurve[][3], float rightCurve[][3] ) {
	float _leftCurve[MAX_NUM_PTS][3];
	float _reverseRightCurve[MAX_NUM_PTS][3];
	float tempPoints[MAX_NUM_PTS][3];
	int i = 0;
	int j = 0;
	int iteration = 0;
	int tempNPoints = currentControlPoints;

	for (i = 0; i < currentControlPoints; i++) {
		tempPoints[i][0] = controlPoints[i][0];
		tempPoints[i][1] = controlPoints[i][1];
		tempPoints[i][2] = controlPoints[i][2];
	}

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
			//tempPoints[i][2] = (1 - param) * tempPoint[i][2] + param * tempPoint[i + 1][2]
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
	// copio i punti
	float tempPoints[MAX_NUM_PTS][3];
	int i = 0;
	int j = 0;
	int tempNPoints = currentControlPoints;
		
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
			//tempPoints[i][2] = (1 - param) * tempPoint[i][2] + param * tempPoint[i + 1][2]
		}
		tempNPoints--;
	}

	result[0] = tempPoints[0][0];
	result[1] = tempPoints[0][1];
}

void active(int x, int y) {


	float xPos = ((float)x) / ((float)(WindowWidth - 1));
	float yPos = ((float)y) / ((float)(WindowHeight - 1));

	yPos = 1.0f - yPos;			// Flip value since y position is from top row.
	
	if (dragging && overPointIndex >= 0) {
		controlPoints[overPointIndex][0] = xPos;
		controlPoints[overPointIndex][1] = yPos;
		glutPostRedisplay();
	}
}

void passive(int x, int y) {
	// converto le coordinate da pixel a scena
	float xPos = ((float)x) / ((float)(WindowWidth - 1));
	float yPos = ((float)y) / ((float)(WindowHeight - 1));

	yPos = 1.0f - yPos;			// Flip value since y position is from top row.

	overPointIndex = -1;
	
	for (int i = 0; i < currentControlPoints; i++) {
		float distance = sqrt(pow(xPos - controlPoints[i][0], 2.0) + pow(yPos - controlPoints[i][1], 2.0));
		if (distance < DISTANCE_THRESHOLD) {
			cout << "over" << i << "\n";
			overPointIndex = i;
			break;
		}
	}
	
	glutPostRedisplay();
}

void resizeWindow(int w, int h)
{
	WindowHeight = (h>1) ? h : 2;
	WindowWidth = (w>1) ? w : 2;
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

	return 0;					// This line is never reached
}
