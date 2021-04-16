#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


GLfloat colors[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,0.0,0.0} };
GLfloat vertices[][3] = { {0.0, 50.0, 0.0},{-50.0, 0.0, 0.0}, { 0.0, -100.0, 0}, {100.0, 0.0, 0.0} };
GLfloat normal[][3] = { {0.0 , 50.0, 0.0},{-50.0, 0.0, 0.0}, {0.0, -100.0, 0.0}, {100.0, 0.0, 0.0} };

void LineDDA(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat color1[3], GLfloat color2[3])
{
   
    GLfloat dm = 0;
    if (fabs(x2 - x1) >= fabs(y2 - y1))
    {
        dm = fabs(x2 - x1);              
    }
    else
    {
        dm = fabs(y2 - y1);             
    }
    GLfloat dx = (x2 - x1) / dm;  
    GLfloat dy = (y2 - y1) / dm;   
  
    GLfloat x = x1;
    GLfloat y = y1;
    GLfloat c1[3] = {0,0,0};
 
    for (int i = 0; i < dm; ++i)
    {
       
        c1[0] = (i / dm * color2[0])+ ((dm - i) / dm * color1[0]);
        c1[1] =( i / dm * color2[1]) + ((dm - i) / dm * color1[1]);
        c1[2] = (i / dm * color2[2]) + ((dm - i) / dm * color1[2]); 
        //cout << "a " << c1[0] << " b " << c1[1] << " c " << c1[2] << endl;
        glColor3fv(c1);
        glBegin(GL_POINTS);
        glVertex3f(x, y, 0);
        glEnd(); 
        x += dx;
        y += dy;

    }

}
void FindPoint()
{
    
    GLfloat ax[500],ay[500], bx[500], by[500], c1[500][3], c2[500][3];
    GLfloat x0 = vertices[0][0]; GLfloat y0 = vertices[0][1];
    GLfloat x1 = vertices[1][0]; GLfloat y1 = vertices[1][1];
    GLfloat x2 = vertices[2][0]; GLfloat y2 = vertices[2][1];
    GLfloat x3 = vertices[3][0]; GLfloat y3 = vertices[3][1];



    GLfloat dm = 0;
    if (fabs(x2 - x1) >= fabs(y2 - y1))
    {
        dm = fabs(x2 - x1);
    }
    else
    {
        dm = fabs(y2 - y1);
    }
    GLfloat dx = (x2 - x1) / dm;
    GLfloat dy = (y2 - y1) / dm;
    
    GLfloat x = x1;
    GLfloat y = y1;
    for (int i = 0; i <= dm; ++i)
    {
        ax[i] = x;
        ay[i] = y;
        x += dx;
        y += dy;
        c1[i][0] = (i / dm * colors[2][0]) + ((dm - i) / dm * colors[1][0]);
        c1[i][1] = (i / dm * colors[2][1]) + ((dm - i) / dm * colors[1][1]);
        c1[i][2] = (i / dm * colors[2][2]) + ((dm - i) / dm * colors[1][2]);
        //cout << "ax " << ax[i] << " ay " << ay[i] <<  endl;
    }


    if (fabs(x3 - x0) >= fabs(y3 - y0))
    {
        dm = fabs(x3 - x0);
    }
    else
    {
        dm = fabs(y3 - y0);
    }
     dx = (x3 - x0) / dm;
     dy = (y3 - y0) / dm;

     x = x0;
    y = y0;
    for (int i = 0; i <= dm; ++i)
    {
        bx[i] = x;
        by[i] = y;
        x += dx;
        y += dy;

        c2[i][0] = (i / dm * colors[3][0]) + ((dm - i) / dm * colors[0][0]);
        c2[i][1] = (i / dm * colors[3][1]) + ((dm - i) / dm * colors[0][1]);
        c2[i][2] = (i / dm * colors[3][2]) + ((dm - i) / dm * colors[0][2]);
        //cout << "bx " << bx[i] << " by " << by[i] << endl;
    }
    //if (vertices[3][1] == 0)
        for (int i = 0; i <= dm; ++i)
        {
            LineDDA(ax[i], ay[i], bx[i], by[i], c1[i], c2[i]);
        }
   
   



}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    FindPoint();

    glFlush();
    glutSwapBuffers();
}



void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-200.0f, 200.0f, -200.0f * h / w, 200.0f * h / w, 1.0, -1.0);
    else
        glOrtho(-200.0f * w / h, 200.0f * w / h, -200.0f, 200.0f, 1.0, -1.0);
   
    glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    //cout << "b1 " << b1 << " " << k1 << endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("fill");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
