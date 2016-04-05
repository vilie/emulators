#include <GL/glut.h>
#include <stdio.h>

#define HEIGHT 32
#define WIDTH 64

extern uint8_t screen_surface[WIDTH][HEIGHT];

void refreshScreen() {
	/* printf("Am intrat in refresh \n"); */
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < WIDTH; i++)
		for(int j = 0; j < HEIGHT; j++)
			if (screen_surface[i][j] == 1) {
				/* printf("IJ %d %d\n", i, j); */
				glVertex3f((float) (i - 31.5)/31.5,
						(float) - (j - 15.5)/15.5, 0);
			}
	glEnd();
	glFlush();
}
	

void displayMe(void) {
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(10.0f);
	glBegin(GL_POINTS);
		glVertex3f(-1.0, -1.0, 0.0); /* left, down */
		glVertex3f(1.0, 1.0, 0.0);   /* right, up */
		glVertex3f(1.0, -1.0, 0.0);  /* right, down */
		glVertex3f(-1.0, 1.0, 0.0);  /* left, up */
	glEnd();
	glFlush();
}



int update_screen(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Emulator screen");
	glutDisplayFunc(refreshScreen);
	glutMainLoopEvent();
	return 0;
}
