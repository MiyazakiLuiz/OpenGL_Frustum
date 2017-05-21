#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415
#define TIMING 1

int WIN_W = 800; //window width
int WIN_H = 680; //window height

GLfloat xp, yp, zp, sp; //center and size of piramide base
GLfloat xc, yx, zc, sc; //center and size of cylinder base
GLfloat xs, ys, zs, ss; //center and size of sphere
GLfloat near, far; //used in frustum
GLfloat eyeX, eyeY, eyeZ; //eye of  lookAt
GLfloat centerX, centerY, centerZ; //center of  lookAt
GLfloat rotX, rotY, rotZ; //used for rotation of the scene
GLfloat transX, transY, transZ; //used for translation of the scene
GLfloat viewRadius; 
GLfloat rotT; //torus rotation
GLfloat scaP; //piramide scale
GLfloat transSX, transSY, transSZ; //sphere translation
GLint upX, upY, upZ; //orientation of lookAt
float alpha, beta;
int updT; //flag used for know if torus is rotating
int updP; //flag used for know if piramide is scaling
int scaPD; //flag used for determinter direction of the piramide scale

/**
 * Draw a piramide with center in (x, y, z) and size s
 */
void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s);

/**
 * Realize transformations on the scene
 */
void transformation(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0f, 10.0f, -10.0f, 10.0f, near, far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glTranslatef(transX, transY, transZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
}

/**
 * Set up initial variables, optionally reset pressing the r key
 */
void initialization(){
	
	glEnable(GL_DEPTH_TEST);
	near = 10.0f;
	far = 1000.0f;
	viewRadius = 200.0f;
	alpha = 0;
	beta = 0;
	eyeX = 0.0f;
	eyeY = 0.0f;
	eyeZ = 0.0f;
	centerX = 1.0f;
	centerY = 0.0f;
	centerZ = 0.0f;
	xp = yp = zp = 0.0f;
	sp = 30.0f;
	upY = 1.0f;
	upZ = 0.0f;
	upX = 0.0f;
	transX = 150.0f;
	transY = 0.0f;
	transZ = 0.0f;
	rotX = -45.0f;
	rotY = 45.0f;
	rotZ = 45.0f;
	rotT = 0.0f;
	scaP = 1.0f;
	transSX = 0.0f;
	transSY = 0.0f;
	transSZ = 0.0f;
	updT = -1;
	updP = -1;
	scaPD = 1;
}

/**
 * Draw a grid on the plan xz and the axes x, y, z
 */
void drawGrid(){

	glColor3f(0.7f, 0.7f, 0.7f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	
	//X axis
	glVertex3f(-200.0f, 0.0f, 0.0f);
	glVertex3f(200.0f, 0.0f, 0.0f);
	
	//Y axis
	glVertex3f(0.0f, -200.0f, 0.0f);
	glVertex3f(0.0f, 200.0f, 0.0f);

	//Z axis
	glVertex3f(0.0f, 0.0f, -200.0f);
	glVertex3f(0.0f, 0.0f, 200.0f);
	glEnd();


	glLineWidth(0.7f);
	glBegin(GL_LINES);
	int i;
	for(i = -200; i<200; i+=5){
		//paint lines below or above the sphere
		if(i > transSX-50 && i < transSX-10)	glColor3f(0.3f, 0.3f, 1.0f);
		else glColor3f(0.3f, 0.3f, 0.3f);
		glVertex3f(i, 0.0f, -200.0f);
		glVertex3f(i, 0.0f, 200.0f);
	}
	for(i = -200; i<200; i+=5){
		//paint lines below or above the sphere
		if(i > transSZ-60 && i < transSZ-20)	glColor3f(0.3f, 0.3f, 1.0f);
		else glColor3f(0.3f, 0.3f, 0.3f);
		glVertex3f(-200.0f, 0.0f, i);
		glVertex3f(200.0f, 0.0f, i);
	}
	glEnd();

}

/**
 * Draw objects
 */
void draw(){
	
	transformation();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawGrid();

	//torus
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(50, 50, 0);
	glRotatef(rotT, 1, 0, 0);
	glutWireTorus(8, 10, 16, 16);
	glColor3f(0.3f, 0.3f, 0.0f);
	glutSolidTorus(7.9, 10, 16, 16);
	glPopMatrix();

	//piramide
	glPushMatrix();
	glColor3f(0.8f, 0.0f, 0.0f);
	glTranslatef(-50, 20, 50);
	glScalef(scaP, scaP, scaP);
	drawPiramide(xp, yp, zp, sp);
	glPopMatrix();
	
	//sphere
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(transSX, transSY, transSZ);
	glTranslatef(-30, 20, -40);
	glutWireSphere(15, 15, 15);
	glColor3f(0.1f, 0.1f, 0.5f);
	glutSolidSphere(15, 15, 15);
	glPopMatrix();

	glutSwapBuffers();
}

/**
 * Draw a piramide with center in (x, y, z) and size s
 */
void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s){
	
	//draw face 1
	glBegin(GL_POLYGON);
	glVertex3f(x, y+2*s/3, z);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glEnd();

	//draw face 2
	glBegin(GL_POLYGON);
	glVertex3f(x, y+2*s/3, z);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glEnd();
	
	//draw face 3
	glBegin(GL_POLYGON);
	glVertex3f(x, y+2*s/3, z);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glEnd();

	glColor3f(0.0f, 0.8f, 0.0f);
	//draw base
	glBegin(GL_POLYGON);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glEnd();
	
	//draw edges
	glColor3f(0.7f, 0.7f, 0.7f);
	glLineWidth(s/10);
	glBegin(GL_LINE_STRIP);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x, y+2*s/3, z);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glVertex3f(x, y+2*s/3, z);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glEnd();
}

/**
 * Function used for make the piramide and torus animation
 */
void update(int x){
	
	if(updT == 1 || updP == 1){
		if(updT == 1){
			rotT += 1;
		}
		if(updP == 1){
			scaP += 0.025*scaPD;
			if(scaPD == 1 && scaP >= 1.5) scaPD *= -1;
			else if(scaPD == -1 && scaP <= 0.1) scaPD *= -1;
		}
		
		glutTimerFunc(TIMING, update, 0);
	}
	else{
		return;
	}

 	glutPostRedisplay();
}

/**
 * Recieve keys and make actions
 */
void keyboard(unsigned char key, int x, int y){

	switch(key){
		//esc
		case 27: 
			exit(0);

		//rotations of the scene
		case 'w':
			rotZ += 5;
			break;
		case 's':
			rotZ -= 5;
			break;
		case 'a':
			rotY += 5;
			break;
		case 'd':
			rotY -= 5;
			break;
		case 'q':
			rotX += 5;
			break;
		case 'e':
			rotX -= 5;
			break;

		case '1': //torus rotation
			updT *= -1;
			if(updT == 1 && updP == -1) update(0);
			break;

		case '2': //piramide scale
			updP *= -1;
			if(updT == -1 && updP == 1) update(0);
			break;

		//sphere translation
		case 'u':
			transSX += 2;
			break;
		case 'h': 
			transSZ -= 2;
			break;
		case 'j': 
			transSX -= 2;
			break;
		case 'k': 
			transSZ += 2;
			break;
		case 'n': 
			transSY -= 2;
			break;
		case 'm': 
			transSY += 2;
			break;

		//reset
		case 'r':
			initialization();
			break;
	}

	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y){

	switch(key){

		case GLUT_KEY_UP: //front (zoom in)
			transX -= 5;
			break;
		case GLUT_KEY_DOWN: //back (zoom out)
			transX += 5;
			break;
		case GLUT_KEY_LEFT: //left
			transZ += 5;
			break;
		case GLUT_KEY_RIGHT: //right
			transZ -= 5;
			break;
	}

	glutPostRedisplay();
}

/**
 * Called when the window size is changed
 */
void reshape(GLint width, GLint height){
	glViewport(0, 0, width, height);
	transformation();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIN_W)/2, (glutGet(GLUT_SCREEN_HEIGHT) - WIN_H)/2); //centralize windows
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("T2_SCC0250");

	printf("\n\nCommands:\n\n\
Up: Zoom in\n\
Down: Zoom out\n\
Left, Right: Move scene\n\n\
w, a, s, d, q, e: Rotations\n\n\
1: Turn on/off Torus Spin\n\
2: Turn on/off Piramide Resize\n\
u, h, j, k, n, m: Sphere Translations\n\n\
r: Reset\n\n\
esc: Exit\n\n\
Developers:\n\
Danilo Francoso Tedeschi\n\
Douglas Amorim de Oliveira\n\
Luiz Massao Miyazaki\n\
Rafael Kenji Nissi\n\n\
");

	//callbacks
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(reshape);

	//set up variables
	initialization();

	glutMainLoop();

	return 0;
}
