#ifndef SPOT_H
#define SPOT_H
#include <main.h>
#include <Histogram.h>
class Spot
{
private:

  int startFrame;
  int endFrame;
  bool draw;

    Histogram GetAmount(int*, int*, Mat*);
    void SigmaRotation();
    void Sigma();
    float CalcSigma(char type);
    int MaxVal (int*, int);
    int MinVal (int*, int);
    void RotateMat (Mat, int*, int*);
    void RotateMat (Mat);


public:

    float sigmaC; // sigma cols
    float sigmaR; // sigma rows
    float sigmaRR; // sigma rows rotate
    float sigmaCR; // sigma cols rotate

    float noiseC;
    float noiseR;
    float noiseRR;
    float noiseCR;
    float maxC;
    float maxR;
    float maxRR;
    float maxCR;
    float avC;
    float avR;
    float avRR;
    float avCR;

    int framesNumber;
    float bigAxis;
    float smallAxis;
    float alpha;
    Point centerPoint;
    Mat AverageFrame ();
    Mat *frames;
    Histogram histS;
    Histogram histSR;

    Spot();
    Spot(Mat);
    Spot(Mat*, int);
    Mat Result();
    Mat RotateResult();
    Mat DrawEllipce(Mat);
    void FindParam();
};

#endif // SPOT_H
