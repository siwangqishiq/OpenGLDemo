      1. 把解压得到的glut.h放到"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include\gl"（与具体安装位置有关，应该是 安装目录\microsoft sdks\windows\v7.0A\include\gl）
      2. 把解压得到的glut.lib和glut32.lib放到"“Programfiles(x86)\Microsoft Visual studio 10.0\VC\lib" 中（与具体安装位置有关，同上）
      3. 把解压得到的glut.dll放到"C:\Windows\System32"
      4. 把glut32.dll放到“Programfiles(x86)\Microsoft Visual studio 10.0\VC\bin”下(注意这个，网上有人说放到system32里，但是我试过，会报错)（与具体安装位置有关，同上）
      5. 打开vs2010,随便打开或新建一个项目。 选择 project->project property-> Configuration Properties->Linker->Input->Additional Dependencies 在其中添加opengl32.lib glu32.lib glut32.lib
 
新建Win32 Console Application，(不是win32 application).选择一个名字，然后按OK。在谈出的对话框左边点Application Settings，找到Empty project并勾上，选择Finish。然后向该工程添加一个代码文件，取名为“OpenGL.c”，注意用.c来作为文件结尾。（其实不必一定以.c结尾，.cpp也可）
搞定了，就跟平时的工程没什么两样的。
#include <gl\glut.h>  
void myDisplay(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT);  
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);  
    glFlush();  
}  
int main(int argc, char *argv[])  
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  
    glutInitWindowPosition(100, 100);  
    glutInitWindowSize(400, 400);  
    glutCreateWindow("第一个OpenGL程序");  
    glutDisplayFunc(&myDisplay);  
    glutMainLoop();  
    return 0;  
}  