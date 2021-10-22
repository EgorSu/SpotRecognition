#ifndef FRAMEGENERATOR_H
#define FRAMEGENERATOR_H
#include <main.h>

  class FrameGenerator
  {
    //класс для генерации изображений со вспышкой
    public:
    FrameGenerator();
    FrameGenerator(Mat, int, int ,int);
    Mat GetResultFrame(int);
    Mat resultMat;
    private:
    int numRows;
    int numCols;
    int sigmaX, sigmaY, alpha;
    Mat background;

    Mat AddLight(Mat, Point); //добавление засветки от стенок канала
    Mat ResultFrame(int);
    Mat SumFrame(Mat, Mat);
    Mat GenerateFlash(Point);//вспышка для измерения параметров двумерного распределения
    Point CenterPoint();
    Mat NoiseGenerator(Mat);

  };


#endif //FRAMEGENERATOR_H
