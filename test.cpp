
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

#if 0


void Reshape(int x, int y)
{
    WindowWidth = x;
    WindowHeight = y;
    if ( WindowWidth < 1 ) WindowWidth = 1;
    if ( WindowHeight < 1 ) WindowHeight = 1;
}


void disp(void)
{
    // �v���~�e�B�u�̕`����s���邱�Ƃ̊m�F�R�[�h
    if(0){
        const GLfloat vertex[] = {
            -0.9 , 0.9 , 0.9 , 0.9 , 0 , -0.9
        };

        const GLuint indices[] = { 0 , 1 , 2 , 3, 4, 5};

        {
            glClear(GL_COLOR_BUFFER_BIT);

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2 , GL_FLOAT , 0 , vertex);

            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);
            glFlush();
        }
        return;
    }


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

    glPushMatrix();
    glTranslated( 0, 0, 1);//���s�ړ��l�̐ݒ�(openGL���W�n�ł͉�ʎ�O��Z++�̕���)
    glPushMatrix();

    // �p�[�c���Ƃɕ`�悷��
    mmdfile.draw();

    glPopMatrix();
    glPopMatrix();

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
#else

const GLfloat vertex[] = {
    3.1 , 1.9 , -3 ,
    4.5 , 0.1 , -3 ,
    6 , 1.9 , -3 ,
    0.1 , 1.9 , -2 ,
    1.5 , 0.1 , -2 ,
    3 , 1.9 , -2 
};
const GLfloat color1[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};
const GLfloat color2[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

const GLuint indices[] = {
    0, 1, 2, 3, 4, 5
};

void disp( void ) {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3 , GL_FLOAT , 0 , vertex);
//    glColorPointer(3 , GL_FLOAT , 0 , color1);

    // mmd���̃R�[�h�������ɍČ����Ă����A
    // ���_���ǂ��ɂ��邩�m�F����
    // --------��������--------
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glViewport(0, 0, WindowWidth, WindowHeight);

    //�@���_�̐ݒ�
//    gluLookAt( 
//        0.0, 10.0, -32.0,
//        0.0, 10.0, 0.0,
//        0.0, 1.0, 0.0 );

    // �����̐ݒ�
    const GLfloat lightPos[] = { 3 , 0 , -2 , 0 };
    const GLfloat lightCol[] = { 1 , 1 , 1 , 1 };
    const GLfloat ambient [] = { 0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION , lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , lightCol);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_DEPTH_TEST);

//    glPushMatrix();
//    glTranslated( 0, 0, 1);//���s�ړ��l�̐ݒ�(openGL���W�n�ł͉�ʎ�O��Z++�̕���)
//    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(M_PI, 0.0f, 1.0f, 0.0f);
    // -------- �����܂� --------

    // glbegin��glend�̌Ăяo�������̂悤�ɂ��Ă܂Ƃ߂邱�Ƃ��ł���
    // ���ӎ���: glbegin, glend�̊Ԃł����̊֐����Ăяo���Ă��A�����\������Ȃ��B
        int primitive_count = 6;
        glDrawElements(GL_TRIANGLES,                    // �v���~�e�B�u�̎��
                        primitive_count,                // �����_�����O�v�f�̐�
                        GL_UNSIGNED_INT,                // �C���f�b�N�X�z��̌^
                        indices);                       // �C���f�b�N�X�z��������|�C���^
        glDrawElements(GL_TRIANGLES,                    // �v���~�e�B�u�̎��
                        primitive_count,                // �����_�����O�v�f�̐�
                        GL_UNSIGNED_INT,                // �C���f�b�N�X�z��̌^
                        indices);                       // �C���f�b�N�X�z��������|�C���^

    glFlush();
}

int main(int argc , char ** argv) {
    glutInit(&argc , argv);
    glutInitWindowPosition(100 , 50);
    glutInitWindowSize(400 , 300);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutCreateWindow("Kitty on your lap");
    glutDisplayFunc(disp);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0 , 4 , 2 , 0 , 2 , 10);

    glutMainLoop();
    return 0;
}
#endif
