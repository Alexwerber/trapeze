#include "trapeze.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void Trapeze::set_lineWidth(int x)
{
   value.lineWidth = x;
}

int Trapeze::get_lineWidth()
{
   return value.lineWidth;
}

void Trapeze::set_color(int i, float x)
{
    value.color[i] = x;
}

float Trapeze::get_color(int i)
{
   return value.color[i];
}

void Trapeze::set_array(int i, int j, float x)
{
   value.array[i][j] = x;
}

float Trapeze::get_array(int i, int j)
{
   return value.array[i][j];
}

int Trapeze::read(const char str[], int ch)   // Считывание данных из файла
{
   FILE *f = fopen(str, "r");
   float x, y, color;
   int lineWidth;
   
   if(f == NULL)
   {
      printf("Файл не найден\n");
      return 0;
   }
   else
   {
      fscanf(f, "%d", &lineWidth);
      set_lineWidth(lineWidth);
      for(int i = 0; i < 3; i++)
      {
         fscanf(f, "%f", &color);
         set_color(i, color);
      }
      if(ch != 3)
         for(int i = 0; i < 4; i++)
         {
            fscanf(f, "%f %f", &x, &y);
            set_array(i, 0, x);
            set_array(i, 1, y);
         }
      else 
         for(int i = 0; i < 8; i++)
         {
            fscanf(f, "%f %f", &x, &y);
            set_array(i, 0, x);
            set_array(i, 1, y);
         }
   }
}

bool Trapeze::correct(float x1Begin, float y1Begin, float x1End, float y1End, float x2Begin, float y2Begin, float x2End, float y2End)   // Проверка является ли фигура трапецией
{
   float AB[2];
   float CD[2];

   AB[0] = x1End - x1Begin;
   AB[1] = y1End - y1Begin;
   CD[0] = x2End - x2Begin;
   CD[1] = y2End - y2Begin;

   float Nab = sqrtf(AB[0] * AB[0] + AB[1] * AB[1]);
   float Ncd = sqrtf(CD[0] * CD[0] + CD[1] * CD[1]);

   AB[0] = AB[0] / Nab;
   AB[1] = AB[1] / Nab;
   CD[0] = CD[0] / Ncd;
   CD[1] = CD[1] / Ncd;

   if(AB[0] + CD[0] == 0 && AB[1] + CD[1] == 0 || AB[0] - CD[0] == 0 && AB[1] - CD[1] == 0)
      return true;
   else 
      return false;
}

bool Trapeze::isItNested(float x0, float y0)   // Проверка является ли фигура вложенной в другую
{
   float a = (get_array(0, 0) - x0) * (get_array(1, 1) - get_array(0, 1)) - (get_array(1, 0) - get_array(0, 0)) * (get_array(0, 1) - y0);
   float b = (get_array(1, 0) - x0) * (get_array(2, 1) - get_array(1, 1)) - (get_array(2, 0) - get_array(1, 0)) * (get_array(1, 1) - y0);
   float c = (get_array(2, 0) - x0) * (get_array(0, 1) - get_array(2, 1)) - (get_array(0, 0) - get_array(2, 0)) * (get_array(2, 1) - y0);
   float a1 = (get_array(2, 0) - x0) * (get_array(3, 1) - get_array(2, 1)) - (get_array(3, 0) - get_array(2, 0)) * (get_array(2, 1) - y0);
   float b1 = (get_array(3, 0) - x0) * (get_array(0, 1) - get_array(3, 1)) - (get_array(0, 0) - get_array(3, 0)) * (get_array(3, 1) - y0);
   float c1 = (get_array(0, 0) - x0) * (get_array(2, 1) - get_array(0, 1)) - (get_array(2, 0) - get_array(0, 0)) * (get_array(0, 1) - y0);

   if((a <= 0 && b <= 0 && c <= 0 || a1 <= 0 && b1 <= 0 && c <= 0) || 
      (a >= 0 && b >= 0 && c >= 0 || a1 >= 0 && b1 >= 0 && c1 >= 0))
     return true;
   else 
     return false;
}