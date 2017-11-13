#include "trapeze.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

Trapeze *trapeze = new Trapeze;

void drawFrame()    // Рисование рамки
{
   glClear(GL_COLOR_BUFFER_BIT);
 
   glColor3f(trapeze->get_color(0), trapeze->get_color(1), trapeze->get_color(2));
   glLineWidth(trapeze->get_lineWidth());
 
     glBegin(GL_LINE_LOOP);
        glVertex2f(trapeze->get_array(0, 0), trapeze->get_array(0, 1));  
        glVertex2f(trapeze->get_array(1, 0), trapeze->get_array(1, 1));
        glVertex2f(trapeze->get_array(2, 0), trapeze->get_array(2, 1));
        glVertex2f(trapeze->get_array(3, 0), trapeze->get_array(3, 1));
     glEnd();
 
   glFlush();  
}

void drawArea()   // Рисование закрашенной фигуры
{
   glClear(GL_COLOR_BUFFER_BIT);
 
   glColor3f(trapeze->get_color(0), trapeze->get_color(1), trapeze->get_color(2));
   glLineWidth(trapeze->get_lineWidth());
 
     glBegin(GL_QUADS);
        glVertex2f(trapeze->get_array(0, 0), trapeze->get_array(0, 1));  
        glVertex2f(trapeze->get_array(1, 0), trapeze->get_array(1, 1));
        glVertex2f(trapeze->get_array(2, 0), trapeze->get_array(2, 1));
        glVertex2f(trapeze->get_array(3, 0), trapeze->get_array(3, 1));
     glEnd();
 
   glFlush();  
}

void drawNestedFigure()   // Рисование вложенной фигуры
{
   glClear(GL_COLOR_BUFFER_BIT);
   
   glBegin(GL_QUADS);
      glColor3f(1.0, 1.0, 1.0);
      glLineWidth(2);
      glVertex2f(trapeze->get_array(0, 0), trapeze->get_array(0, 1));  
      glVertex2f(trapeze->get_array(1, 0), trapeze->get_array(1, 1));
      glVertex2f(trapeze->get_array(2, 0), trapeze->get_array(2, 1));
      glVertex2f(trapeze->get_array(3, 0), trapeze->get_array(3, 1));
   glEnd();

   glBegin(GL_QUADS);
      glColor3f(0.0, 0.0, 0.0);
      glLineWidth(2);
      glVertex2f(trapeze->get_array(4, 0), trapeze->get_array(4, 1));  
      glVertex2f(trapeze->get_array(5, 0), trapeze->get_array(5, 1));
      glVertex2f(trapeze->get_array(6, 0), trapeze->get_array(6, 1));
      glVertex2f(trapeze->get_array(7, 0), trapeze->get_array(7, 1));
   glEnd();

   glFlush();
}

int main(int argc, char *argv[])
{ 
   bool unImput = 0;
   int ch;

   printf("1 - незакрашенная фигура\n2 - закрашенная фигура\n3 - вложенная фигура\n");
   scanf("%d", &ch);

   switch(ch)
   {
      case 1 : trapeze->read("test1.txt", ch); break;
      case 2 : trapeze->read("test2.txt", ch); break;
      case 3 : trapeze->read("test3.txt", ch); break;
      default : unImput = 1; break;
   }

   if(!unImput)
   {  
      if(trapeze->correct(trapeze->get_array(0, 0), trapeze->get_array(0, 1), trapeze->get_array(1, 0), trapeze->get_array(1, 1), trapeze->get_array(2, 0), trapeze->get_array(2, 1), trapeze->get_array(3, 0), trapeze->get_array(3, 1)) &&
         !trapeze->correct(trapeze->get_array(0, 0), trapeze->get_array(0, 1), trapeze->get_array(3, 0), trapeze->get_array(3, 1), trapeze->get_array(1, 0), trapeze->get_array(1, 1), trapeze->get_array(2, 0), trapeze->get_array(2, 1)) ||
         trapeze->correct(trapeze->get_array(0, 0), trapeze->get_array(0, 1), trapeze->get_array(3, 0), trapeze->get_array(3, 1), trapeze->get_array(1, 0), trapeze->get_array(1, 1), trapeze->get_array(2, 0), trapeze->get_array(2, 1)) && 
         !trapeze->correct(trapeze->get_array(0, 0), trapeze->get_array(0, 1), trapeze->get_array(1, 0), trapeze->get_array(1, 1), trapeze->get_array(2, 0), trapeze->get_array(2, 1), trapeze->get_array(3, 0), trapeze->get_array(3, 1)))
      {
         if(trapeze->isItNested(trapeze->get_array(4, 0), trapeze->get_array(4, 1)) && 
            trapeze->isItNested(trapeze->get_array(5, 0), trapeze->get_array(5, 1)) &&  
            trapeze->isItNested(trapeze->get_array(6, 0), trapeze->get_array(6, 1)) && 
            trapeze->isItNested(trapeze->get_array(7, 0), trapeze->get_array(7, 1)) || ch != 3)  
         {
            glutInit(&argc, argv);
            glutInitWindowSize(800, 600);
            glutInitWindowPosition(100, 50);
          
            glutInitDisplayMode(GLUT_RGB);
            glutCreateWindow("Трапеция");
       
            glutReshapeFunc(Reshape);
            switch(ch)
            {
               case 1 :glutDisplayFunc(drawFrame); break;
               case 2 : glutDisplayFunc(drawArea); break;
               case 3 : glutDisplayFunc(drawNestedFigure); break;
            }
            glClearColor(0, 0, 0, 0);
       
            glutMainLoop();
            return 0;
         } else printf("Ошибка: фигура не является вложенной\n");
      } else printf("Ошибка: фигура не является трапецией\n");
   } else printf("Ошибка: неправильная команда\n");
}