#include<GL/glut.h>

double radio = 2;
double moZ = 0;
double movZ = 0;


void iniciar()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //fondo negro
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 17);
    gluLookAt(6, 5, 5, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
}

void tecladoEspecial(int key, int x, int y)
{

    if (key == GLUT_KEY_UP)
        movZ += 0.5;
    else if (key == GLUT_KEY_DOWN)
        movZ -= 0.5;
    else if (key == GLUT_KEY_F1)
        moZ += 0.18;
    else if (key == GLUT_KEY_F2)
        moZ -= 0.18;
    glutPostRedisplay();
}

void dibujarPlano() {
    glBegin(GL_LINES);
    glVertex3f(5, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 5);
    glVertex3f(0, 0, 0);
    glEnd();

}



void dibujarCabeza() {
    glRotatef(movZ, 0, 0, 0);
    glPushMatrix();
    glutSolidSphere(radio, 50, 50);
    glPopMatrix();


}
void dibujarCuello() {
    glTranslated(0, 0, 1);
    GLUquadricObj* objetoQ;
    objetoQ = gluNewQuadric();
    gluCylinder(objetoQ, 1, 1, 1.5, 50, 50);

}

void dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(90, 1, 0, 0);
    dibujarPlano();
    dibujarCabeza();
    dibujarCuello();
    glFlush();
}

void luces() {
    glEnable(GL_LIGHT0);

    float light0_position[] = { 1,1,1,0 };
    float light0_diffuso_color[] = { 0.980 , 0.647 , 0.447 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuso_color);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("JAEL");
    iniciar();
    glutDisplayFunc(dibujar);
    glEnable(GL_LIGHTING);
    luces();
    glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop();
}
