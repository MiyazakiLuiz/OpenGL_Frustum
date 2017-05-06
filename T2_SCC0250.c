#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415

int WIN_W = 800;
int WIN_H = 680;

GLfloat xp, yp, zp, sp; //center and size of piramide base
GLfloat xc, yx, zc, sc; //center and size of cylinder base
GLfloat xs, ys, zs, ss; //center and size of sphere
GLfloat near, far;
GLfloat eyeX, eyeY, eyeZ; 
GLfloat centerX, centerY, centerZ;
GLfloat viewRadius;
GLint upX, upY, upZ;
float alpha, beta;


void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s);
void drawCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat s);
void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat s);

void initialization(){
	
	glEnable(GL_DEPTH_TEST);
	near = 10.0f;
	far = 300.0f;
	viewRadius = 200.0f;
	alpha = 0;
	beta = 0;
	eyeX = 0.0f;
	eyeY = 0.0f;
	eyeZ = 200.0f;
	centerX = 0.0f;
	centerY = 0.0f;
	centerZ = 0.0f;
	xp = yp = zp = 0.0f;
	sp = 30.0f;
	upY = 1;
	upZ = 0;
	upX = 0;
}

void visualization(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

}

void draw(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
	visualization();
	
	/*
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0,1, 0);
	glEnd();
	*/

	glColor3f(1.0f, 1.0f, 0.0f);
	//glutWireSphere(50, 10, 10);
	glTranslatef(50, 50, 0);
	//glutWireCone(20, 40, 10, 10);
	glutWireTorus(8, 10, 16, 16);
	glTranslatef(-50, -50, 0);
//	glLoadIdentity();
	drawPiramide(xp, yp, zp, sp);

	glFlush();
	glutSwapBuffers();
}

void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s){
	
	glColor3f(0.0f, 1.0f, 0.0f);
	
	//draw base
	glBegin(GL_POLYGON);
	glVertex3f(x, y-s/3, z+2*s/3);
	glVertex3f(x-s/2, y-s/3, z-s/3);
	glVertex3f(x+s/2, y-s/3, z-s/3);
	glEnd();
	
	glColor3f(1.0f, 0.0f, 0.0f);
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

	//draw edges
	glColor3f(0.5f, 0.5f, 0.5f);
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

void keyboard(unsigned char key, int x, int y){
	
	switch(key){
		case 27:
			exit(0);
		
		case 'z':
			upZ = 1;
			upY = 0;
			break;
		case 'x':
			upX = 1;
			upY = 0;
			break;

	}

	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y){

	switch(key){
		case GLUT_KEY_UP:
			alpha += PI/36;
		
			if(alpha >= 2*PI){
				alpha = 0;
			}
			else if(alpha >= 3*PI/2){
				if(upY == -1){
					alpha += PI/36;
					upY = 1;
				}
			}
			else if(upY == 1 && alpha >= PI/2){
				alpha += PI/36;
				upY = -1;
			}

		 	/*
			if(alpha > 12.1*PI/36 && alpha < 14*PI/36){
				upZ = -1;
				upY = 0;
			}
			else if(alpha > PI/2){
				upZ = 0;
				upY = -1;
			}
			*/
			eyeY = viewRadius*sin(alpha);
			eyeZ = viewRadius*cos(alpha);
			
			//eyeY += 5;
			break;
		case GLUT_KEY_DOWN:
			eyeY -= 5;
			break;
		case GLUT_KEY_LEFT:
			//eyeX += 200*PI/36;
			eyeX += 5;
			break;
		case GLUT_KEY_RIGHT:
			eyeX -= 5;
			break;
	}

	glutPostRedisplay();
}

void mouse(int click, int state, int x, int y){

}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIN_W)/2, (glutGet(GLUT_SCREEN_HEIGHT) - WIN_H)/2);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("T2_SCC0250");

	initialization();

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0;
}
