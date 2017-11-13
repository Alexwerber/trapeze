#ifndef TRAPEZE_H
#define TRAPEZE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

typedef struct data  // Струкрура данных трапеции
{
   int lineWidth;
   int color[3];
   float array[2][8];
} dt;

class Trapeze
{
   private:
      dt value;
   public:
    void set_lineWidth(int x); // Установление значения ширины линии
    int get_lineWidth();      // Возвращение значения ширины линии
    void set_color(int i, float x);  // Установление значения цвета
    float get_color(int i);         // Возвращение значения цвета
    void set_array(int i, int j, float x);  // Установление точки
    float get_array(int i, int j);  // Возвращение значения точки
    void drawFrame();    // Рисование рамки
    void drawArea();   // Рисование закрашенной фигуры
    void drawNestedFigure();   // Рисование вложенной фигуры
    int read(const char str[], int ch);   // Считывание данных из файла
    bool correct(float x1Begin, float y1Begin, float x1End, float y1End, float x2Begin, float y2Begin, float x2End, float y2End);   // Проверка является ли фигура трапецией
    bool isItNested(float x0, float y0);   // Проверка является ли фигура вложенной в другую
};
#endif