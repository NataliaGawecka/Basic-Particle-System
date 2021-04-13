#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<iostream>
#include <windows.h>
#include <time.h>

#define MAX_PARTICLES 10000
#define MAX_AGE 10000


struct PARTICLE
{   
	float r, g, b, a;
	float x, y;
	float sx, sy;
	float tx, ty;
	bool Active; 
	int Age; 
	int MaxAge; 
} particles[MAX_PARTICLES];

void init() {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-40, 40, -40, 40);
}

void InitParticles()
{
	srand(0);
	for (unsigned int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].Active = false;
		particles[i].tx = 0.0f;
		particles[i].ty = 0.1f;
	

	}
}
void Activate()
{
	for (unsigned int i = 0; i < MAX_PARTICLES; i++)
	{
		if (!particles[i].Active)
		{
			particles[i].x = 0.0f;
			particles[i].y = 0.0f;
			
			particles[i].sx = ((((rand() % 100) + 1)) / 1000.0f) - 0.05f;
			particles[i].sy = (((rand() % 100) + 50) / 500.0f);
	
			particles[i].r = 0.0f;
			particles[i].g = 0.0f;
			particles[i].b = 0.0f;
			particles[i].a = 1.0f;

            particles[i].Active = true;
			
			particles[i].Age = 0;
			
			particles[i].MaxAge = MAX_AGE;
			return;
			
		}
	}
}
void ChangePosition()
{
	for (unsigned int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].sx += (particles[i].tx - particles[i].sx) / 100.0f;
		particles[i].sy += (particles[i].ty - particles[i].sy) / 100.0f;

		particles[i].x += particles[i].sx;
		particles[i].y += particles[i].sy;

		particles[i].a -= 0.005;

		particles[i].Age++;
		
		if (particles[i].Age > particles[i].MaxAge)
		{
			particles[i].Active = false;
		}
	}
}

void Display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Activate();
	ChangePosition();
	glPointSize(20.5);
    glBegin(GL_POINTS);
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (particles[i].Active)
		{
			
			glColor4f(particles[i].r, particles[i].g, particles[i].b, particles[i].a);
			glVertex2f(particles[i].x, particles[i].y);

			
		}
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void timer(int extra)
{
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("dym");
	init();
	InitParticles();
	glutDisplayFunc(Display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}
