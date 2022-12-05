#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <GL/glut.h>

#define M_PI 3.14
using namespace std;

GLfloat large_x = 0.0;
GLfloat large_y = 0.0;
GLfloat large_z = 0.0;

int winWidth, winHeight;
float angle = 0.0, axis[3], trans[3];
bool trackingmouse = false;
bool redrawContinue = false;
bool trackballMove = false;
float lastPos[3] = { 0.0f, 0.0f, 0.0f };
int curx, cury;
int startX, startY;
string filePath = "Dino.obj";

class model {
public:
    model(string filename);
    void Draw();
    vector<vector<GLfloat>>v;
    vector<vector<GLint>>f;
};

model::model(string filename)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, 1) == "v")
        {
            vector<GLfloat> Point;
            GLfloat x, y, z;
            istringstream s(line.substr(2));
            s >> x; 
            s >> y; 
            s >> z;
            if (abs(x) > large_x) large_x = abs(x);
            if (abs(y) > large_y) large_y = abs(y);
            if (abs(z) > large_z) large_z = abs(z);
            Point.push_back(x);
            Point.push_back(y);
            Point.push_back(z);
            v.push_back(Point);

        }
        else if (line.substr(0, 1) == "f")
        {
            vector<GLint> vIndex;
            GLint u, v, w;
            istringstream vtns(line.substr(2));
            vtns >> u; 
            vtns >> v; 
            vtns >> w;
            vIndex.push_back(u - 1);
            vIndex.push_back(v - 1);
            vIndex.push_back(w - 1);
            f.push_back(vIndex);
        }
    }
    file.close();
}

void model::Draw() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < f.size(); i++) {
        
        GLfloat VN[3];
        GLfloat SV1[3];
        GLfloat SV2[3];
        GLfloat SV3[3];

        GLint firstVertex = f[i][0];
        GLint secondVertex = f[i][1];
        GLint thirdVertex = f[i][2];

        SV1[0] = v[firstVertex][0] ;
        
        SV1[1] = v[firstVertex][1] ;
        
        SV1[2] = v[firstVertex][2] ;
        
        
        SV2[0] = v[secondVertex][0] ;
        
        SV2[1] = v[secondVertex][1] ;
        
        SV2[2] = v[secondVertex][2] ;
        

        SV3[0] = v[thirdVertex][0] ;
        
        SV3[1] = v[thirdVertex][1] ;
        
        SV3[2] = v[thirdVertex][2] ;
        

        GLfloat vec1[3], vec2[3], vec3[3];
        vec1[0] = SV1[0] - SV2[0];
        vec1[1] = SV1[1] - SV2[1];
        vec1[2] = SV1[2] - SV2[2];

        vec2[0] = SV1[0] - SV3[0];
        vec2[1] = SV1[1] - SV3[1];
        vec2[2] = SV1[2] - SV3[2];

        vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
        vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

        GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));
        VN[0] = vec3[0] / D;
        VN[1] = vec3[1] / D;
        VN[2] = vec3[2] / D;
        glNormal3f(VN[0], VN[1] , VN[2] );
        
        glVertex3f(SV1[0], SV1[1], SV1[2]);
        glVertex3f(SV2[0], SV2[1], SV2[2]);
        glVertex3f(SV3[0], SV3[1], SV3[2]);
    }
    glEnd();
}



model objModel = model(filePath);
static float c = 3.1415926 / 180.0f;
static float cy = 3.1415926 / 90.0f;
static float r = 10.0f;
static float ry = 100.0f;
static int degreex = 180;
static int degreey = 90;
static int oldPosY = -1;
static int oldPosX = -1;

//安置光源
void setLightRes() {
    GLfloat lightPosition[] = { 5.0f, 15.0f, 1.0f, 0.0f };
    GLfloat aWhiteLight[] = { 1, 1, 1, 1.0 };
    GLfloat aModelAmbient[] = { 0.1, 0.1, 0.1, 0.1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_SPECULAR, aWhiteLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, aWhiteLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, aModelAmbient);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

void display()
{
    GLfloat aSpecularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glColor3f(1.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.5, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, aSpecularMaterial);
    setLightRes();
    /*if (trackballMove) {
        glRotatef(angle, axis[0], axis[1], axis[2]);
    }*/
    
    glPushMatrix();
    cout << r * cos(c * degreey) << " " << r * cos(c * degreex) << endl;
    glScalef(1/ large_y, 1/large_y, 1/ large_y);
    if (trackballMove) {
        gluLookAt(r * cos(c * degreex), 0, r * sin(c * degreex), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        gluLookAt(0, r * cos(cy * degreey), r * sin(cy * degreey), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }
    objModel.Draw();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 300.0f);
    glMatrixMode(GL_MODELVIEW);
}

void moseMove(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            trackballMove = true;
            oldPosX = x; oldPosY = y;
        }
    }
    else {
        trackballMove = false;
    }
}
void changeViewPoint(int x, int y)
{
    /*cout << x << " " << y << endl;*/
    int temp = x - oldPosX;
    int ttemp = y - oldPosY;
    degreex += temp;
    degreey += ttemp;
    oldPosX = x;
    oldPosY = y;
}

void myIdle()
{
    glutPostRedisplay();
}

void trackbakk_potv(int x, int y, int width, int height, float v[3]) {
    float d, a;
    v[0] = (2.0f * x - width) / width;
    v[1] = (height - 2.0f*y) / height;
    d = (float)sqrt(v[0] * v[0] + v[1] * v[1]);
    v[2] = (float)cos((M_PI / 2.0f) * ((d < 1.0f) ? d : 1.0f));
    a = 1.0f / (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}

void startMotion(int x, int y) {
    trackingmouse = true;
    redrawContinue = false;
    startX = x;
    startY = y;
    curx = x;
    cury = y;
    trackbakk_potv(x, y, winWidth, winHeight, lastPos);
    trackballMove = true;
}

void stopMotion(int x, int y) {
    trackballMove = false;
    if (startX != x || startY != y) {
        redrawContinue = true;
    }
    else {
        angle = 0.0f;
        redrawContinue = false;
        trackballMove = false;
    }
}

void mousebotton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) switch (state)
    {
    case GLUT_DOWN:
        y = winHeight - y;
        startMotion(x, y);
        
        break;
    case GLUT_UP:
        stopMotion(x, y);
        break;
    }
}

void mousemotion(int x, int y) {
    float curPos[3], dx, dy, dz;
    trackbakk_potv(x, y, winWidth, winHeight, curPos);
    if (trackingmouse) {
        dx = curPos[0] - lastPos[0];
        dy = curPos[1] - lastPos[1];
        dz = curPos[2] = lastPos[2];

        if (dx || dy || dz) {
            angle = 90.0f * sqrt(dx * dx + dy * dy + dz * dz);
            cout << angle << endl;
            axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1];
            axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
            axis[2] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];
            lastPos[0] = curPos[0];
            lastPos[1] = curPos[1];
            lastPos[2] = curPos[2];
        }
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("ObjLoader");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(moseMove);
    glutMotionFunc(changeViewPoint);
    glutIdleFunc(myIdle);
    glutMainLoop();
    return 0;
}
