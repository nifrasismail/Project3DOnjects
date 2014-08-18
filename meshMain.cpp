
//The mesh class is used to read a mesh from a file and draw it.

#include "mesh.h"

int spinx = 0, spiny = 0;      //rotating angles
int H = 1;

//This is the display function.  Each time it draws a barn,
//it is rotated by the angles spinx and spiny.
void display(void)
{
	//set the background to black and clear the buffers
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	//create a mesh for the barn
	Mesh mymesh;

	mymesh.generatemesh("../BaseFile.txt","../3DMesh.txt", H);
	//mymesh.generatemesh("../BaseFile.txt","../3DMesh.txt", H);

	//read the mesh from the file
	//mymesh.readmesh("../3DMesh.txt");
	mymesh.readmesh("../3DMesh.txt");
	//rotate the barn by spin degrees
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(spinx, 1.0, 0.0, 0.0);
	glRotatef(spiny, 0.0, 1.0, 0.0);

	//draw the mesh
	mymesh.draw();
 
	//make it appear on the screen
	glFlush();
}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: spiny = (spiny - 10) % 360; glutPostRedisplay(); break;
	case GLUT_KEY_RIGHT: spiny = (spiny + 10) % 360; glutPostRedisplay(); break;
	case GLUT_KEY_UP: spinx = (spinx + 10) % 360; glutPostRedisplay(); break;
	case GLUT_KEY_DOWN: spinx = (spinx - 10) % 360; glutPostRedisplay(); break;
	default: return;
	}
}

//This is the reshape callback.
void myReshape(int w, int h)
{
	//set the viewport to the entire window
	glViewport(0, 0, w, h);

	//use an orthographic view volume of a cube
	//centered about the origin
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-3.0, 3.0, -3.0*(GLfloat)h/(GLfloat)w, 
		         3.0*(GLfloat)h/(GLfloat)w, -3.0, 3.0);
	else
		glOrtho(-3.0*(GLfloat)w/(GLfloat)h, 
		         3.0*(GLfloat)w/(GLfloat)h, -3.0, 3.0, -3.0, 3.0);

}

int main(int argc, char** argv)
{
	//create the window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 600); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);

	//set up callbacks
	glutReshapeFunc (myReshape);
	glutSpecialFunc(special);
	glutDisplayFunc(display);

	//start the main loop
	glutMainLoop();
	return 0;             
}
