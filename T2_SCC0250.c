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
GLfloat rotX, rotY, rotZ;
GLfloat transX, transY, transZ;
GLfloat viewRadius;
GLfloat rotT; // torus rotation
GLint upX, upY, upZ;
float alpha, beta;


void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s);
//void drawCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat s);
//void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat s);

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

void initialization(){
	
	glEnable(GL_DEPTH_TEST);
	near = 10.0f;
	far = 300.0f;
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
	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	rotT = 0.0f;
}

void draw(){
	
	transformation();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	/*
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0,1, 0);
	glEnd();
	*/
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(rotT, 1, 0, 0);
	glTranslatef(50, 50, 0);
	glutWireTorus(8, 10, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	drawPiramide(xp, yp, zp, sp);
	glPopMatrix();
	
	glutWireSphere(50, 10, 10);

	glutSwapBuffers();
}

void drawPiramide(GLfloat x, GLfloat y, GLfloat z, GLfloat s){
	
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
		
		case 'w': //front
			transX -= 5;
			break;
		case 's': //back
			transX += 5;
			break;
		case 'a': //left
			transZ += 3;
			break;
		case 'd': //right
			transZ -= 3;
			break;

		case '1': //torus rotation
			rotT += 5;
			break;
	}

	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y){

	switch(key){
		case GLUT_KEY_UP:
			/*
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
*/
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
			//eyeY = viewRadius*sin(alpha);
			//eyeZ = viewRadius*cos(alpha);
			
			//eyeY += 5;

			rotZ += 5;
			break;
		case GLUT_KEY_DOWN:
			//eyeY -= 5;
			rotZ -= 5;
			break;
		case GLUT_KEY_LEFT:
			//eyeX += 200*PI/36;
			rotY += 5;
			break;
		case GLUT_KEY_RIGHT:
			rotY -= 5;
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

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	
	initialization();

	glutMainLoop();

	return 0;
}
