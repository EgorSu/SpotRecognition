#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <main.h>

  class Histogram
  {
  private:
    void CalcHistRows (int*);
    void CalcHistCols (int*);
    int FindAverageVal (char type);

    void CheckType (char type, int *, int*);
    void CheckType (char type, int *);
    int CheckSize(char type);
    int FindA (char type, int);

    Point FMCM(char); //func max of center mass
    bool CorrectHist (char type);


  public:

    int *cols;
    int *rows;
    int numCols;
    int numRows;
    Point maxPosC;
    Point maxPosR;
    Mat frame;
    bool correct;
    float sigmaC;
    float sigmaR;

    float averageC;
    float averageR;
    float maxC;
    float maxR;
    Point centerMass;
    float noiseC;
    float noiseR;

    Histogram();
    Histogram(Mat frame);
    Histogram(int* array_cols, int* array_rows, int,int);

    Point FindMaxVal (char type);
    Point FindMinVal (char type);
    int FindCenterMass (char);
    float FWHMSigma(char);//find sigma by calculating full width at half maximum
    float OLSSigma(char);//find sigma through least squares method
    float Sigma(char);

    Mat PlotHist (int*, int, Mat, int, bool, int, char, Scalar);
    Mat PlotHist (int, char);
  };



#endif // HISTOGRAM_H
