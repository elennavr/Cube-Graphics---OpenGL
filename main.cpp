#include <GL/glut.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


GLfloat rot = 0.75;
static short int flag = 1;
static short int flag_scale = 1;
GLfloat scale = 1.0;
static int id = 1;
static short int flag_id = 1;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (flag && flag_id) {
		glPushMatrix();
		glTranslatef(0.0, 0.0, -70.0);
		flag = 0;
	}else if (flag && !flag_id) {
		glPushMatrix();
		glTranslatef(0.0, 0.0, -56.0);
		glRotatef(rot, 1.0,2.0,2.0);
		glTranslatef(0.0,0.0,-14.0);
		flag = 0;
	}

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -2.0);
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(2.5f * scale, 2.5f * scale, 2.5f * scale);//a=5
	glRotatef(90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glCallList(1);
	glEnd();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void idle() {

	if (flag_scale) {
		scale += 0.1;
		if (scale >= 1.998) {
			flag_scale = 0;
		}
	}
	else {
		scale -= 0.1;
		if (scale <= 1.002) {
			flag_scale = 1;
		}
	}
	
	if (flag_id)
		glRotatef(rot, 1.0, 2.0, 2.0);//rotation
	else {
		glTranslatef(0.0, 0.0, 14.0);
		glRotatef(rot, 1.0,2.0,2.0);
		glTranslatef(0.0,0.0,-14.0);
	}
		

	Sleep(60);
	glutPostRedisplay();
}

void menu(int id) {
	switch (id){
	case 1:
		rot = 0.75;
		flag_id = 1;
		glPopMatrix();
		flag = 1;
		break;
	case 0:
		rot = 2.0;
		flag_id = 0;
		glPopMatrix();
		flag = 1;
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /* default, not needed */
	glutInitWindowSize(500, 500); /* 500 x 500 pixel window */
	glutInitWindowPosition(0, 0); /* place window top left on display */
	glutCreateWindow("Graphics 2"); /* window title */
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
	glMatrixMode(GL_PROJECTION);              // setup viewing projection
	glLoadIdentity();

	glNewList(1, GL_COMPILE);

	glVertex3f(-1.0, -1.0, 1.0);       // P1
	glVertex3f(-1.0, 1.0, 1.0);       // P2
	glVertex3f(1.0, 1.0, 1.0);       // P3
	glVertex3f(1.0, -1.0, 1.0);       // P4

	glEndList();

	glutCreateMenu(menu);

	glutAddMenuEntry("switch to a", 1);
	glutAddMenuEntry("switch to b", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// start with identity matrix
	glOrtho(-20.0, 20.0, -20.0, 20.0, -80.0, 80.0);   // setup a 10x10x2 viewing world
	glutDisplayFunc(display); /* display callback invoked when window opened */
	glutIdleFunc(idle);
	glutMainLoop(); /* enter event loop */

	return 0;
}
