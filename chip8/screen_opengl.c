#include <GL/glut.h>

#define HEIGHT 32
#define WIDTH 64

int matrix[WIDTH][HEIGHT];

void refreshScreen() {
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < WIDTH; i++)
		for(int j = 0; j < HEIGHT; j++)
			if (matrix[i][j] == 1)
				glVertex3f((float) (i - 32)/32.0, (float) (j - 16)/16.0, 0);
	glEnd();
	glFlush();
}
	

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(10.0f);
	glBegin(GL_POINTS);
		glVertex3f(-1.0, -1.0, 0.0); // left, down
		glVertex3f(1.0, 1.0, 0.0);   // right, up
		glVertex3f(1.0, -1.0, 0.0);  // right, down
		glVertex3f(-1.0, 1.0, 0.0);  // left, up
	glEnd();
	glFlush();
}



int main(int argc, char** argv)
{
	int i;

	/* Test */
	for(int i = 0; i < WIDTH; i+=2)
		matrix[i][0] = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Emulator screen");
	glutDisplayFunc(refreshScreen);
	glutMainLoop();
	return 0;
}
