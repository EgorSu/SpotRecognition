#include "Spot.h"
class Spot;
Spot::Spot(){}
Spot::Spot(Mat mat)
{
  sigmaC = 0;
  sigmaCR = 0;
  sigmaR = 0;
  sigmaRR = 0;
  smallAxis = 0;
  bigAxis = 0;
  alpha = 0;

  framesNumber = 1;
  frames = new Mat[framesNumber];
  mat.copyTo(frames[0]);
}
Spot::Spot(Mat* mat, int size)
{
  sigmaC = 0;
  sigmaCR = 0;
  sigmaR = 0;
  sigmaRR = 0;

  smallAxis = 0;
  bigAxis = 0;
  alpha = 0;

  framesNumber = size;
  frames = new Mat[framesNumber];
  for(int i = 0; i < framesNumber; i++) mat[i].copyTo(frames[i]);
}
Mat Spot::AverageFrame ()
{
  Mat average = Mat::zeros(frames[0].rows, frames[0].cols, frames[0].type());
    for(int j = 0; j < frames[0].rows; j++)
    {
      for(int k = 0; k < frames[0].cols; k++)
      {
        int sum = 0;
        for(int i=0; i < framesNumber; i++)
        {
          sum += frames[i].at<unsigned char>(j,k);
        }
        average.at<unsigned char>(j,k) = (int) sum/framesNumber;
      }
    }
    ;
  return DrawEllipce(average);
}
Mat Spot::DrawEllipce (Mat mat)
{
    Point center (histS.maxPosC.x, histS.maxPosR.x);
    if(smallAxis > 0 && bigAxis > 0)
    {
        ellipse(mat, center, Size(smallAxis, bigAxis), (double)alpha, 0.0, 360.0,Scalar(155));
    }
    return mat;
}
Mat Spot::Result() //вывод изображения кадра с гисторграммами
{
  Mat copyFrame(frames[0].rows, frames[0].cols, CV_8UC1);
  frames[0].copyTo(copyFrame);
  Mat histCols = histS.PlotHist(histS.numRows, 'c');
  Mat histRows = histS.PlotHist(histS.numCols, 'r');

  line(histRows, Point(0, histS.maxPosR.x), Point(histCols.cols, histS.maxPosR.x), Scalar(100));
  line(histCols, Point(histS.maxPosC.x, 0), Point(histS.maxPosC.x, histCols.rows), Scalar(100));

  line(histRows, Point(0, histS.centerMass.y), Point(histCols.cols, histS.centerMass.y), Scalar(180));
  line(histCols, Point(histS.centerMass.x, 0), Point(histS.centerMass.x, histCols.rows), Scalar(180));

  Mat resultMat = Mat::zeros(2 * frames[0].rows, 2 * frames[0].cols, CV_8UC1);
  Mat m11(resultMat, Rect(0,0,frames[0].cols,frames[0].rows));
  Mat m12(resultMat, Rect(histS.numCols,0,histS.numCols,histS.numRows));
  Mat m21(resultMat, Rect(0,histS.numRows,histS.numCols,histS.numRows));
  histRows.copyTo(m12);
  histCols.copyTo(m21);

  return resultMat;
}
Mat Spot::RotateResult() //вывод изображения кадра с гисторграммами
{
  Mat histCols = histSR.PlotHist(histSR.numRows, 'c');
  Mat histRows = histSR.PlotHist(histSR.numCols, 'r');

  Mat resultMat = Mat::zeros(2 * histSR.numRows, 2 * histSR.numCols, CV_8UC1);
  Mat m11(resultMat, Rect(0,0,histSR.numCols,histSR.numRows));
  Mat m12(resultMat, Rect(histSR.numCols,0,histSR.numCols,histSR.numRows));
  Mat m21(resultMat, Rect(0,histSR.numRows,histSR.numCols,histSR.numRows));
  histRows.copyTo(m12);
  histCols.copyTo(m21);

  return resultMat;
}
void Spot::FindParam ()
{
  Sigma();
  SigmaRotation();
  centerPoint = Point(histS.maxPosC.x, histS.maxPosR.x);
  if(sigmaR != 0 && sigmaC != 0 && sigmaCR != 0 && sigmaRR != 0)
  {
    float a1 = pow((sigmaRR * sigmaC),2);
    float a2 = pow((sigmaCR * sigmaR),2);
    float a3 = pow((sigmaCR * sigmaC),2);
    float a4 = pow((sigmaRR * sigmaR),2);
    float ALPHA2 = (float) atan((a1 - a2 - a3 + a4)/(a1 - a2 + a3 - a4));
    float ALPHA = (ALPHA2/2);
    ALPHA = (isnan(ALPHA)) ? 0:ALPHA;

    while(abs(sin(ALPHA)) == abs(cos(ALPHA)))
    {
      ALPHA += PI/180;
    }

    double r11 = pow(sin(ALPHA) * sigmaC, 2) - pow(cos(ALPHA) * sigmaR, 2);
    double r12 = pow(sin(ALPHA) * sigmaR, 2) - pow(cos(ALPHA) * sigmaC, 2);
    double r13 = pow(sin(ALPHA),4) - pow(cos(ALPHA),4);
    float r1, r2;

    r1 = sqrt(abs(r11/r13));
    r2 = sqrt(abs(r12/r13));

    if(r2 < r1 && ALPHA < 0)
    {
      ALPHA += PI;
      smallAxis = r2;
      bigAxis = r1;
    }
    else if (r2 > r1)
    {
      ALPHA +=PI/2;
      smallAxis = r1;
      bigAxis = r2;
    }
    else
    {
      smallAxis = r2;
      bigAxis = r1;
    }

    alpha = (180 - ALPHA * 180/PI);
  }
  else
  {
    smallAxis = 0;
    bigAxis = 0;
    cout<<"some sigma = 0"<<endl;
  }
}
void Spot::Sigma()
{
  int arr1[frames[0].cols] = {1};
  int arr2[frames[0].rows] = {1};
  for(int i = 0; i < frames[0].cols; i++) arr1[i] = 1;
  for(int i = 0; i < frames[0].rows; i++) arr2[i] = 1;
  histS = GetAmount(arr1, arr2, frames);

  if(histS.correct)
  {
    sigmaC = histS.FWHMSigma('c');
    sigmaR = histS.FWHMSigma('r');
    noiseC = histS.noiseC;
    noiseR = histS.noiseR;
    maxC = histS.maxC;
    maxR = histS.maxC;
    avC = histS.averageC;
    avR = histS.averageR;
  }
}
void Spot::SigmaRotation()
{

  int size = sqrt(pow(frames[0].cols,2) + pow(frames[0].rows,2));
  Mat framesRotation[framesNumber];
  Mat copyFrame[framesNumber];

  int coeffC[size] = {0};
  int coeffR[size] = {0};

  for(int k = 0; k < framesNumber; k++)
  {
    framesRotation[k] = Mat::zeros(size, size, CV_8UC1);
    frames[k].copyTo(copyFrame[k]);
    for(int i = 0; i < copyFrame[i].rows; i++)
    {
      for(int j = 0; j < copyFrame[i].cols; j++ )
      {
        if(copyFrame[k].at<unsigned char>(i, j) != 255)
        {
            copyFrame[k].at<unsigned char>(i, j)++; //+1 для определения коэффициентов в RotateMat
        }
      }
    }
    if(k == 0) RotateMat(copyFrame[k], coeffC, coeffR);
    else RotateMat(copyFrame[k]);
  }

  histSR = GetAmount(coeffC, coeffR, copyFrame);

  if(histSR.correct)
  {
    sigmaCR = histSR.FWHMSigma('c');
    sigmaRR = histSR.FWHMSigma('r');
    noiseC = histSR.noiseC;
    noiseR = histSR.noiseR;
    maxCR = histSR.maxC;
    maxRR = histSR.maxR;
    avCR = histSR.averageC;
    avRR = histSR.averageR;
  }
  else cout<<"this beam not have correct hist"<<endl;
}
Histogram Spot::GetAmount (int *coeffC, int *coeffR, Mat* mat)
{   
  Histogram hist[framesNumber];
  for(int i = 0; i < framesNumber; i++)
  {
    hist[i] = Histogram(mat[i]);
  }
  int sumC[hist[0].numCols] = {0};
  int sumR[hist[0].numRows] = {0};
  int minCoeffC = MinVal(coeffC, hist[0].numCols);
  int minCoeffR = MinVal(coeffR, hist[0].numRows);
  int resultFramesNumber = framesNumber;

  for(int i = 0; i < framesNumber; i++)
  {
    if(hist[i].correct)
    {
      for(int j = 0; j < hist[i].numCols; j++)
      {
        if(coeffC[j] != 0)
        {
          sumC[j] += hist[i].cols[j] * minCoeffC/coeffC[j];
        }
      }
      for(int j = 0; j < hist[i].numRows; j++)
      {
        if(coeffR[j] != 0)
        {
          sumR[j] += hist[i].rows[j] * minCoeffR/coeffR[j];
        }
      }
      endFrame = i + 1;
    }
    else resultFramesNumber--;
  }

  if(resultFramesNumber > 0)
  {
    startFrame = endFrame - resultFramesNumber;
    for(int i = 0; i < resultFramesNumber; i++)
    {

    }
    for(int j = 0; j < hist[0].numCols; j++) sumC[j] /= resultFramesNumber;
    for(int j = 0; j < hist[0].numRows; j++) sumR[j] /= resultFramesNumber;
    Histogram histSummary = Histogram(sumC, sumR, hist[0].numCols, hist[0].numRows);
    return histSummary;
  }
  else
  {
    return Histogram();
  }
}
int Spot::MaxVal (int* arr, int size)
{
  int maxVal = 0;
  for(int i = 0; i < size; i++)
  {
    if(arr[i] > maxVal)
    {
      maxVal = arr[i];
    }
  }
  return maxVal;
}
int Spot::MinVal (int* arr, int size)
{
  int minVal = 	2147483647;
  for(int i = 1; i < size; i++)
  {
    if(arr[i] < minVal && arr[i] != 0)//if == 0 то mincoef = 0 и вся сумма в GetAmount = 0
    {
      minVal = arr[i];
    }
  }
  return minVal;
}
void Spot::RotateMat (Mat mat)
{
  Mat rotMat( 2, 3, CV_32FC1 );
  rotMat = getRotationMatrix2D(Point (mat.cols/2, mat.rows/2), 45.0, 1.0);
  warpAffine(mat, mat, rotMat, mat.size());
}
void Spot::RotateMat (Mat mat, int *arrCoeffC, int *arrCoeffR)
{
  Mat rotMat( 2, 3, CV_32FC1 );
  rotMat = getRotationMatrix2D(Point (mat.cols/2, mat.rows/2), 45.0, 1.0);
  warpAffine(mat, mat, rotMat, mat.size());

  for(int i = 0; i < mat.rows; i++)
  {
    for(int j = 0; j < mat.cols; j++)
    {
      if(mat.at<unsigned char>(i, j) == 255)
      {
        arrCoeffC[j]++;
        arrCoeffR[i]++;
      }
      else if(mat.at<unsigned char>(i, j) > 0)
      {
        arrCoeffC[j]++;
        arrCoeffR[i]++;
        mat.at<unsigned char>(i, j)--;
      }
    }
  }
}
