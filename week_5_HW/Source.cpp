#include <iostream>
#include<GL/glut.h>
#include<GL/GLU.h>


double cx = 0;
double cz = 0;
double r = 1;
double cxx = 0;
double czz = 0;
double ex = 0;
double ez = 0;
float angel = -1.55; 
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

void Timer_Call_Camera(int);
void SpecialKeyCamera(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void initWindow();
void resize(int, int);
void drawCoord();
void initGlut();
void draw();
void setLighting();
void drawGate();

//drawing
void drawAiuLogo();
void drawALetter();
void drawILetter();
void drawULetter();

GLUquadric* obj = gluNewQuadric();


bool enable = true;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	initWindow();
	initGlut();
	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	setLighting();
	glutTimerFunc(1000, Timer_Call_Camera,0);
	glutSpecialFunc(SpecialKeyCamera);
	glutKeyboardFunc(keyboard);
	glEnable(GL_LIGHTING);
	

	glutMainLoop();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(ex, 0, ez, cxx, 0, czz, 0, 1, 0);
	glTranslatef(0, 0, -30);
	
	glPushMatrix();
	drawAiuLogo();
	glPopMatrix();
	

	glTranslatef(0,0, -30);
	glPushMatrix();
	drawGate();
	glPopMatrix();

	drawCoord();
	glFlush();
}


void resize(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 600.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void drawCoord() {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);

	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);

	glVertex3f(0, -1000, 0);
	glVertex3f(0, 1000, 0);

	glVertex3f(0, 0, -1000);
	glVertex3f(0, 0, 1000);

	glEnd();
}


void initGlut() {
	glutInitDisplayMode(GLUT_SINGLE);
	glShadeModel(GLU_SMOOTH);
	glClearColor(0.68f, 0.85f, 0.9f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void initWindow() {
	int windowPostionX = (glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2;
	int windowPostionY = (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2;
	glutInitWindowPosition(windowPostionX, windowPostionY);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Home work");
}


void Timer_Call_Camera(int) {
	glutPostRedisplay();
	//without r
	/*cx=cos(Angel);
	cz=sin(Angel);*/
	//for r
	/*cxx=r*cos(Angel);
	czz=r*sin(Angel);
	*/
	//تحريك الكامرا وتدويرها
	//Angel=(Angel*3.1415)/180;
	cxx = ex + cos(angel);
	czz = ez + sin(angel);
	glutTimerFunc(1000 / 60, Timer_Call_Camera, 0);
};


void SpecialKeyCamera(int key, int x, int y) {
	switch (key) {
	case VK_ESCAPE: //Escape key //
		exit(0);
		break;
	case GLUT_KEY_LEFT:
		angel -= 0.05;
		/*ex+=cos(Angel);
		ez+=sin(Angel);*/
		break;
	case GLUT_KEY_RIGHT:
		angel += 0.05;
		/*ex-=cos(Angel);
		ez-=sin(Angel);*/
		break;
	case GLUT_KEY_UP:
		//r+=0.5;
		ez += sin(angel);
		ex += cos(angel);
		break;
	case GLUT_KEY_DOWN:
		//r-=0.5;
		ez -= sin(angel);
		ex -= cos(angel);
		break;


	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: //Escape key //
		exit(0);
		break;

	case'q':
		std::cout << "pressed\n";
		if (enable) {
			glEnable(GL_LIGHTING);
		}
		else {
			glDisable(GL_LIGHTING);
		}

		enable = !enable;
		break;

	default:
		break;
	}
}

void setLighting() {
	GLfloat lightposition[] = { 0.0f, 5.0f, 4.0f, 1.0f };
	GLfloat lighanbient[] = { 0.05f, 0.0f, 0.0f, 1.0f };
	GLfloat lightdiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat lightspecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat matanbient[] = { 0.05f, 0.0f, 0.0f, 1.0f };
	GLfloat matdiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat matspecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat matshaning[] = { 180.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, lightposition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lighanbient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightspecular);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matdiffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matanbient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matshaning);
	glEnable(GL_COLOR_MATERIAL);
}

void drawAiuLogo() {

	glPushMatrix();
	drawALetter();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 0);
	drawILetter();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.5, 0, 0);
	drawULetter();
	glPopMatrix();
}

void drawALetter() {
	// (/)
	glColor3f(0, 0, 1);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(35, 0, 1, 0);
	gluCylinder(obj, 0.5, 0.5, 3, 4, 4);
	glPopMatrix();

	//(\)
	glTranslatef(4, 0, 0);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(-35, 0, 1, 0);
	gluCylinder(obj, 0.5, 0.5, 3, 4, 4);
	glPopMatrix();

	//(-)
	glTranslatef(-1.5, 2.5, 0);
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	gluCylinder(obj, 0.5, 0.5, 1, 4, 4);
	glPopMatrix();


	//(_)
	glTranslatef(0.3, -1, 0);
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	gluCylinder(obj, 0.5, 0.5, 1.8, 4, 4);
	glPopMatrix();


}

void drawILetter() {


	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 0.5, 0.5, 3, 4, 4);

}

void drawULetter() {

	// (|)
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 0.5, 0.5, 3, 4, 4);
	glPopMatrix();
	

	// (_)
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(obj, 0.5, 0.5, 1.5, 4, 4);
	glPopMatrix();


	// (|)
	glPushMatrix();
	glTranslatef(1.5, 0.1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 0.5, 0.5, 3, 4, 4);
	glPopMatrix();

}

void drawGate() {
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glScalef(2, 1, 0.1);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70, 10, 0);
	glScalef(2, 1, 0.1);
	glutSolidCube(20);
	glPopMatrix();
}