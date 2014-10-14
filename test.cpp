
#include <GL/gl.h>
#include <GL/glut.h>

#include <math.h>
#include <string>
#include <stdio.h>
#include <memory.h>

#include "mmd_model.h"



// �Ƃ肠���������Ƀv���g�^�C�v�����Ă���

// �Ƃ肠����
MMD_File    mmdfile;
Texture     madoka_magic;

int WindowWidth = 512;
int WindowHeight = 512;



void Reshape(int x, int y)
{
    WindowWidth = x;
    WindowHeight = y;
    if ( WindowWidth < 1 ) WindowWidth = 1;
    if ( WindowHeight < 1 ) WindowHeight = 1;
}


void disp(void)
{
//    glClearColor(1 , 1 , 1 , 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, WindowWidth, WindowHeight);

    //�@���_�̐ݒ�
    gluLookAt( 
        0.0, 10.0, -32.0,
        0.0, 10.0, 0.0,
        0.0, 1.0, 0.0 );
#if 0
    gluLookAt( 
        0.0, 10.0, -32.0,
        0.0, 10.0, 0.0,
        0.0, 1.0, 0.0 );
#endif

    printf("draw start\n");

    // �����̐ݒ�
    const GLfloat lightPos[] = { 3 , 0 , -2 , 0 };
    const GLfloat lightCol[] = { 1 , 1 , 1 , 1 };
    const GLfloat ambient [] = { 0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION , lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , lightCol);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // �`��J�n //
//    glBegin(GL_TRIANGLES);

    glPushMatrix();
    glTranslated( 0, 0, 1);//���s�ړ��l�̐ݒ�(openGL���W�n�ł͉�ʎ�O��Z++�̕���)
    glPushMatrix();

    static double theta = 0.0f;
    theta += 2.1f;
    glRotated( theta , 0 , 1, 0);

    // �p�[�c���Ƃɕ`�悷��
    mmdfile.draw();

    glPopMatrix();
    glPopMatrix();

    // �`��I�� //
//    glEnd();

    glutSwapBuffers();
}

void timer(int value)
{
    disp();
}


int main(int argc , char ** argv)
{
    glutInit(&argc , argv);
    glutInitWindowPosition(100 , 50);
    glutInitWindowSize(WindowWidth , WindowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);


    glutCreateWindow("Window caption");
    glutDisplayFunc(disp);
    glutReshapeFunc(Reshape);
    glEnable(GL_TEXTURE_2D);
//    glDisable(GL_CULL_FACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glutTimerFunc(100 , timer , 0);

    mmdfile.setpath("/home/catalina/workspace/opengl/madoka/");
    mmdfile.load("md_m.pmd");

    glutMainLoop();

    return 0;
}

