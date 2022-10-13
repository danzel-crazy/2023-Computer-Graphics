// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#include <Windows.h> 
#include <GL/glut.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <iostream> 
#include <vector>
#include <time.h>
#include <sstream>

using namespace std;

//user
double xr = 0, yr = 0;
double step = 1;
double x = 0, y = -10;
int score = 0;
int final_state = 0;
double len = 6.0;
double bonus = 0.0;
const double START = clock();
//circle
int speed = 60;
struct a {
    double x;
    double y;
};
double circle_radius = 0.5;
int circle_num = 3;
vector <a> obj(circle_num, {-20, -20});
int circle_count = 0;

//triangle
double tri_x = -20.0, tri_y = 10.0;
int tri_state = 0;

//display
int start_state = 1;
void rect();
void circle();
void triangle();
void p_score();
void start_screen();
void print_final();
void print_success();

bool tri_CheckCollision(double x, double y, double tri_x, double tri_y) {
    if ((-10 <= tri_y - 1 && tri_y - 1 <= -10 + len) && (x <= tri_x - 0.5 && tri_x - 0.5 <= x + len)) {
        //<< "left" << endl;
        return true;
    }
    else if ((-10 <= tri_y - 1 && tri_y - 1 <= -10 + len) && (x <= tri_x + 0.5 && tri_x + 0.5 <= x + len)) {
        //cout << "right" << endl;
        return true;
    }
    else false;
}

bool CheckCollision(double x, double y, a p) {
    if ((-10 <= p.y + circle_radius && p.y + circle_radius <= -10 + len) && (x <= p.x && p.x <= x + len)) {
        score++;
        //cout << score << endl;
        //<< "down" << endl;
        return true;
    }
    else if ((-10 <= p.y && p.y <= -10 + len) && (x <= p.x + circle_radius && p.x+ circle_radius <= x + len)) {
        score++;
        //cout << score << endl;
        //cout << "right" << endl;
        return true;
    }
    else if ((-10 <= p.y && p.y <= -10 + len) && (x <= p.x - circle_radius && p.x - circle_radius <= x + len)) {
        score++;
        /*cout << score << endl;
        cout << "left" << endl;*/
        return true;
    }
    else return false;
}

// Clears the current window and draws a triangle.
void specialkey(unsigned char key, int a, int b) {
    switch (key) {
    case 'w':
        /*if (score >= 45) {
            if ((y + 2.0) >= 10) y += 0;
            else y += step;
        }*/
        glutPostRedisplay();
        break;
    case 's':
        /*if (score >= 45) {
            if (y <= -10) y -= 0;
            else y -= step;
        }*/
        glutPostRedisplay();
        break;
    case 'a':
        if (x <= -10) x -= 0;
        else x -= step;
        glutPostRedisplay();
        break;
    case 'd':
        if ((x + len) >= 10) x += 0;
        else x += step;
        glutPostRedisplay();
        break;
    case 'h':
        start_state = 0;
        break;
    case 'q':
        final_state = 1;
        break;
    }
}

void display(){
    // Set every pixel in the frame buffer to the current clear color.
    switch (score) {
    case 15:
        len = 4.0 + bonus;
        break;
    case 30:
        len = 2.0 + bonus;
        break;
    case 50:
        len = 1.0 + bonus;
        break;
    case 70:
        len = 0.5 + bonus;
        break;
    }
    if (circle_count % 20 == 0 && circle_count != 0) {
        tri_state = 1;
    }
    if (score == 80) final_state = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.373, 0.620, 0.627, 0.0);
    if (!final_state) {
        if (start_state) {
            start_screen();
        }
        else {
            glLoadIdentity();
            rect();
            circle();
            if(tri_state) triangle();
            p_score();
        }
    }
    else {
        if (score == 80) print_success();
        else print_final();
    }
    glFlush();
    glutSwapBuffers();
    
}

void rect(){
    glBegin(GL_POLYGON);
    glColor3f(0.098, 0.098, 0.439);
    glVertex2d(x, y);
    glVertex2d(x, y+ len);
    
    glVertex2d(x + len, y+ len);
    glVertex2d(x + len, y);
    glEnd();
}

void circle() {
    for (int j = 0; j < circle_num; j++) {
        if (obj[j].x == -20 && obj[j].y == -20) {
            obj[j].x = (9.5 + 9.5) * rand() / (RAND_MAX + 1.0) - 9.5;
            //cout << obj[j].x << endl;
            obj[j].y = 9;
        }
        int i;
        int triangleAmount = 100; //# of triangles used to draw circle

        //GLfloat radius = 0.8f; //radius
        double twicePi = 2.0f * 3.1415926;

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.098, 0.098, 0.439);
        glVertex2f(obj[j].x, obj[j].y); // center of circle
        for (i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                obj[j].x + (circle_radius * cos(i * twicePi / triangleAmount)),
                obj[j].y + (circle_radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
        glFlush();
    } 
}

void triangle() {
    if(tri_x == -20.0)tri_x = (9.0 + 9.0) * rand() / (RAND_MAX + 1.0) - 9;
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex2d(tri_x-0.5, tri_y-1);
        glColor3f(0, 1, 0); glVertex2d(tri_x, tri_y);
        glColor3f(0, 0, 1); glVertex2d(tri_x+0.5, tri_y-1);
    glEnd();
}

void start_screen() {
        /*Begin(GL_TRIANGLE_FAN);
    
        glVertex3f(1.0f,4.0f,0.0f);
        glVertex3f(3.0f,3.0f,0.0f);
        glVertex3f(1.0f,2.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(-1.0f,2.0f,0.0f);
        glVertex3f(-3.0f,3.0f,0.0f);
        glVertex3f(-1.0f,4.0f,0.0f);

        glVertex3f(0.0f,6.0f,0.0f);
     
    glEnd();*/ 
    char word[26] = "Press h for start";
    glColor3f(0.502, 0.000, 0.502);
    glRasterPos2i(-5, 0);
    for (int i = 0; i < 21; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);
}

void p_score() {
    stringstream ss;
    string c;
    ss << "Score: " << score;
    c = ss.str().c_str();
    glColor3f(0.333, 0.420, 0.184);
    glRasterPos2i(-10, 9);
    for (int i = 0; i < c.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
    double END = clock();
    //cout << (END - START) / CLOCKS_PER_SEC << endl;
    stringstream s;
    string wc;
    double ans = double(END - START) / CLOCKS_PER_SEC;
    s << "Time: " << ans;
    wc = s.str().c_str();
    glColor3f(0.333, 0.420, 0.184);
    glRasterPos2i(5.5, 9);
    for (int i = 0; i < wc.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, wc[i]);
}

void print_final() {
    stringstream ss;
    string c;
    ss << "Final_Score: " << score;
    c = ss.str().c_str();
    glColor3f(0.184, 0.310, 0.310);
    glRasterPos2i(-5,0);
    for (int i = 0; i < c.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
}

void print_success() {
    char word[18] = "You are the best";
    glColor3f(0.184, 0.310, 0.310);
    glRasterPos2i(-5, 0);
    for (int i = 0; i < 18; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);

}

void reshape(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, +10, -10, +10);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int sec) {
    glutPostRedisplay();
    glutTimerFunc(speed, timer, 0);
    switch (score) {
        case 10:
            speed = 50;
            break;
        case 20:
            speed = 40;
            break;
        case 40:
            speed = 30;
            break;
        case 70:
            speed = 20;
            break;
    }
    if (!start_state && !final_state) {
        //circle
        for (int i = 0; i < obj.size(); i++) {
            //cout << obj[i].x  << endl;
            bool check = CheckCollision(x, y, obj[i]);
            if (check == true) {
                obj[i].x = (9.5 + 9.5) * rand() / (RAND_MAX + 1.0) - 9.5;
                obj[i].y = 9;
                circle_count++;
            }
            if (obj[i].y > -11) {
                obj[i].y -= .30;
            }
            else {
                obj[i].x = (9.5 + 9.5) * rand() / (RAND_MAX + 1.0) - 9.5;
                obj[i].y = 9;
                circle_count++;
            }
        }

        if (tri_state) {
            bool check = tri_CheckCollision(x, y, tri_x, tri_y);
            if (check == true) {
                bonus += 1;
                tri_x = -20.0;
                tri_y = 10.0;
                tri_state = 0;
            }
            if ((tri_y-2) > -11) {
               tri_y -= .30;
            }
            else {
                tri_x = -20.0;
                tri_y = 10.0;
                tri_state = 0;
            }
        }
    }
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    int mode = GLUT_RGB | GLUT_DOUBLE;
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(mode);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moving");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(specialkey);
    glutMainLoop();
   
    return 0;
}