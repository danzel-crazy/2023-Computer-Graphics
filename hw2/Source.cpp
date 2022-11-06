
#include <iostream>
#include <windows.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

static int r_shoulderAngle = 0, r_elbowAngle = 0;
static int l_shoulderAngle = 0, l_elbowAngle = 0;
static int r_legAngle = 0, r_kneeAngle = 0;
static int l_legAngle = 0, l_kneeAngle = 0;
static int headAngle = 0;
static int bodyAngle = 0;

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'd': 
            if (l_shoulderAngle == 75 ) l_shoulderAngle = l_shoulderAngle;
            else (l_shoulderAngle += 5) %= 360;
            cout << l_shoulderAngle << endl;
            break;
        case 'a': 
            if (l_shoulderAngle == -75) l_shoulderAngle = l_shoulderAngle;
            else (l_shoulderAngle -= 5) %= 360; 
            cout << l_shoulderAngle << endl;
            break;
        case 'w': 
            if (l_elbowAngle == 75) l_elbowAngle = l_elbowAngle;
            else (l_elbowAngle += 5) %= 360; 
            break;
        case 's': 
            if (l_elbowAngle == -75) l_elbowAngle = l_elbowAngle;
            else (l_elbowAngle -= 5) %= 360;
            break;
        case 'f': (l_legAngle -= 5) %= 360; break;
        case 'h': (l_legAngle += 5) %= 360; break;
        case 't': (l_kneeAngle -= 5) %= 360; break;
        case 'g': (l_kneeAngle += 5) %= 360; break;

        case 'j': (r_legAngle -= 5) %= 360; break;
        case 'l': (r_legAngle += 5) %= 360; break;
        case 'i': (r_kneeAngle -= 5) %= 360; break;
        case 'k': (r_kneeAngle += 5) %= 360; break;

        case '1': (headAngle += 5) %= 360; break;
        case '2': (headAngle -= 5) %= 360; break;
        case '3': (bodyAngle += 5) %= 360; break;
        case '4': (bodyAngle -= 5) %= 360; break;
        default: return;
    }
    glutPostRedisplay();
}

void special(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT: 
            if (r_shoulderAngle == 75) r_shoulderAngle = r_shoulderAngle;
            else (r_shoulderAngle += 5) %= 360; 
            break;
        case GLUT_KEY_RIGHT: 
            if (r_shoulderAngle == -75) r_shoulderAngle = r_shoulderAngle;
            else (r_shoulderAngle -= 5) %= 360; 
            break;
        case GLUT_KEY_UP: 
            if (r_elbowAngle == 75) r_elbowAngle = r_elbowAngle;
            else (r_elbowAngle += 5) %= 360; 
            break;
        case GLUT_KEY_DOWN: 
            if (r_elbowAngle == -75) r_elbowAngle = r_elbowAngle;
            else (r_elbowAngle -= 5) %= 360;
            break;
        default: return;
    }
    glutPostRedisplay();
}

void wireBox(GLdouble width, GLdouble height, GLdouble depth) {

    glPushMatrix();
    glScalef(width, height, depth);
    glutWireCube(1.0);
    glPopMatrix();
}

void right_arm() {
    glPushMatrix();
    glTranslatef(1.0, 1.0, 0.0);

    glRotatef((GLfloat)r_shoulderAngle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 1.0);

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)r_elbowAngle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 1.0);

    glPopMatrix();
}

void left_arm() {
    glPushMatrix();
    glTranslatef(-1.0, 1.0, 0.0);
    glRotatef((GLfloat)l_shoulderAngle, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 1.0);

    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)l_elbowAngle, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 1.0);

    glPopMatrix();
}

void left_leg() {
    glPushMatrix();
    glTranslatef(-0.8, -2.0, 0.0);
    glRotatef((GLfloat)l_legAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    wireBox(0.4, 2.0, 0.5);

    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)l_kneeAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    wireBox(0.4, 2.0, 0.5);

    glPopMatrix();
}

void right_leg() {

    glPushMatrix();
    glTranslatef(0.8, -2.0, 0.0);
    glRotatef((GLfloat)r_legAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    wireBox(0.4, 2.0, 0.5);

    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)r_kneeAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    wireBox(0.4, 2.0, 0.5);

    glPopMatrix();
}

void head() {
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glRotatef((GLfloat)headAngle, 0.0, 1.0, 0.0);
    wireBox(1.0, 1.0, 1.0);
    glPopMatrix();
}

void body() {
    glPushMatrix();
    //glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)bodyAngle, 0.0, 1.0, 0.0);
    //glTranslatef(0.0, 0.0, 1.0);
    wireBox(2.0, 4.0, 1.0);
    head();
    right_arm();
    left_arm();
    left_leg();
    right_leg();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    body();
    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}

void init() {
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robot Arm");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    init();
    glutMainLoop();
}