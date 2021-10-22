#include "Histogram.h"
class Histogram;
Histogram::Histogram (){}
Histogram::Histogram(Mat mat)
{
  mat.copyTo(frame);
  numCols = frame.cols;
  numRows = frame.rows;
  cols = new int[numCols];
  rows = new int[numRows];
  CalcHistRows(rows);
  CalcHistCols(cols);
  correct = (CorrectHist('r') && CorrectHist('c')) ? true:false;
  maxPosC =  Point (FMCM('c').x, FMCM('c').y);
  maxPosR =  Point (FMCM('r').x, FMCM('r').y);

  averageC = FindAverageVal('c');
  averageR = FindAverageVal('r');;
  maxC = maxPosC.y;
  maxR = maxPosC.y;
  noiseC = FindA('c', 20);
  noiseR = FindA('r', 20);
}
Histogram::Histogram (int *arrC, int *arrR, int numC, int numR)
{
  numCols = numC;
  numRows = numR;
  cols = new int[numCols];
  rows = new int[numRows];
  for(int i = 0; i < numCols; i++) cols[i] = arrC[i];
  for(int i = 0; i < numRows; i++) rows[i] = arrR[i];
  correct = (CorrectHist('r') && CorrectHist('c')) ? true:false;
  maxPosC =  Point (FMCM('c').x, FMCM('c').y);
  maxPosR =  Point (FMCM('r').x, FMCM('r').y);

  centerMass = Point(FindCenterMass('c'), FindCenterMass('r'));
  averageC = FindAverageVal('c');
  averageR = FindAverageVal('r');;
  maxC = maxPosC.y;
  maxR = maxPosR.y;
  noiseC = FindA('c', 20);
  noiseR = FindA('r', 20);
}
void Histogram::CalcHistCols (int* arr)
{
  for(int i = 0;i< numCols; i++ ) arr[i] = 0;
  for(int i = 0; i < numCols; i++)
  {
    for(int j = 0; j < numRows; j++)
    {
      arr[i] += (int) frame.at<unsigned char>(j,i);
    }
  }
}
void Histogram::CalcHistRows (int* arr)
{
  for(int i = 0;i< numRows; i++ ) arr[i] = 0;
  for(int i = 0; i < numRows; i++)
  {
    for(int j = 0; j < numCols; j++)
    {
      arr[i] += (int) frame.at<unsigned char>(i,j);
    }
  }
}
float Histogram::FWHMSigma(char type)
{
   Point maxVal;
   if(type == 'c') maxVal = maxPosC;
   if(type == 'r') maxVal = maxPosR;
   int FWHM = 0;
   int size = CheckSize(type);
   int arr[size];
   int a;
   CheckType(type, arr, &a);
   int thresh = (maxVal.y + a)/2; // (max - a)/2 + a
   if(maxVal.x != 0 && maxVal.x != size)
   {
     bool aboveThreshRight = true;
     bool aboveThreshLeft = true;
     int i = 0;
     int leftEdge = 0, rightEdge = 0;
     while(maxVal.x + i < size && maxVal.x - i > 0)
     {
       if(aboveThreshLeft)
       {
         aboveThreshLeft = arr[maxVal.x - i] > thresh;
         leftEdge = i;
       }
       if(aboveThreshRight)
       {
         aboveThreshRight = arr[maxVal.x + i] > thresh;
         rightEdge = i;
       }
       if(aboveThreshLeft || aboveThreshRight) i++;
       else break;
     }
     i = 0;
     if(aboveThreshRight && aboveThreshLeft)
     {
       bool maxLeft = maxVal.x < size/2;
       aboveThreshRight = !(maxLeft);
       aboveThreshLeft = maxLeft;
     }
     if(aboveThreshRight || aboveThreshLeft)
     {
       FWHM = (aboveThreshRight) ? 2 * leftEdge:2 * rightEdge;
     }
     else
     {
       FWHM = rightEdge + leftEdge;
     }
   }
   else
   {
     return -1;
   }

   if(FWHM == 0)
     {
       cout<<"beam was not found"<<endl;
       return 0;
     }
   return (float) FWHM/2.355;
}
bool Histogram::CorrectHist (char type)
{
  //int a = FindA(type, 20);
  int av;
  //int max = FindMaxVal(type).y;
  switch(type)
  {
   case 'c': av = averageC;
    break;
  case 'r': av = averageR;
    break;
  }
  //float k = (float)abs((av/max));
  return true;//k < 0.4;
}
int Histogram::FindCenterMass (char type)
{
  int sumI = 0;
  int sumXI = 0;

  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  a = FindA(type, 20);
  for(int i = 0; i < size; i++)
  {
    if(arr[i] >= a)//иначе к сумме прибавляем ноль
    {
      sumXI += (arr[i] - a)  * i;
      sumI += arr[i] - a;
    }
  }
  if(sumI > 0)return (int)sumXI/sumI;
  else return 0;
}
int Histogram::FindA (char type, int num)
{
  //среднее значение подложки, расчитывается по среднему значению
  //двадчати столбцов гистограммы с края, наиболее удалённого
  //от точки максимального значения гистограммы
  num = 20;
  Point maxVal = FindMaxVal(type);
  int a = 0;
  int size = CheckSize(type);
  int arr[size];
  CheckType(type, arr);
  if(maxVal.x > size/2)
  {
    for(int i = 0; i < num; i++) a += arr[i];
  }
  else
  {
    for(int i = 1; i < num; i++) a += arr[size - i];
  }
  a = a/num;
  return a;
}
int Histogram::FindAverageVal (char type)
{
  int average = 0;
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  for(int i = 0; i < size; i++)
  {
    average += arr[i];
  }
  return average/size;
}
Point Histogram::FindMaxVal (char type)
{
  Point maxVal(0,0);
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  for(int i = 0; i < size ;i++)
  {
    if(maxVal.y == 0)
    {
      maxVal.y = arr[i];
    }
    else if(arr[i] > maxVal.y)
    {
      maxVal.y = arr[i];
      maxVal.x = i;
    }
  }
  return maxVal;
}
Point Histogram::FindMinVal (char type)
{
  Point minVal(0,0);
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  for(int i = 0; i < size; i++)
  {
    if(minVal.y == 0)
    {
      minVal.y = arr[i];
    }
    else if(arr[i] < minVal.y)
    {
      minVal.y = arr[i];
      minVal.x = i;
    }
  }
  return minVal;
}
int Histogram::CheckSize(char type)
{
  switch (type)
  {
    case 'c': return numCols;
    case 'r': return numRows;
    default: cout<<"unknown type in CheckSize method"<<endl;
      break;
  }
  return 0;
}
void Histogram::CheckType(char type, int* arr, int* a)
{
  switch (type)
  {
    case 'c':
      for(int i = 0; i < numCols; i++) arr[i] = cols[i];
      *a = noiseC;
      break;
    case 'r':
      for(int i = 0; i < numRows; i++) arr[i] = rows[i];
      *a = noiseR;
      break;
    default: cout<<"unknown type in CheckType method"<<endl;
      break;
  }
}
void Histogram::CheckType(char type, int* arr)
{
  switch (type)
  {
    case 'c':
      for(int i = 0; i < numCols; i++) arr[i] = cols[i];
      break;
    case 'r':
      for(int i = 0; i < numRows; i++) arr[i] = rows[i];
      break;
    default: cout<<"unknown type in CheckType method"<<endl;
      break;
  }
}
Mat Histogram::PlotHist (int histSize, char type)
{
    Mat hist;
    int *arr;
    Point maxVal;
    Point minVal;
    switch (type)
    {
      case 'c': // cols hist
        hist = Mat::zeros(histSize, numCols, CV_8UC1);
        maxVal = FindMaxVal('c');
        minVal = FindMinVal('c');
        arr = new int[numCols];
        for(int k = 0; k < numCols; k++)
        {
          arr[k] = cols[k] * histSize/maxVal.y;
          line(hist, Point(k, 0), Point(k, arr[k]), Scalar(255), 1);
        }
        break;
      case 'r': // rows hist
        hist = Mat::zeros(numRows, histSize, CV_8UC1);
        maxVal = FindMaxVal('r');
        minVal = FindMinVal('r');
        arr = new int[numRows];
        for(int k = 0; k < numRows; k++)
        {
          arr[k] = rows[k] * histSize/maxVal.y;
          line(hist, Point(0, k), Point( arr[k], k), Scalar(255), 1);
        }
        break;
      default:
        cout<<"type <"<<type<<"> is unknown type of histogram"<<endl;
        return Mat::zeros(1, 1, CV_8UC1);
        break;
    }
    return hist;
}
Point Histogram::FMCM(char type)//Find Max of Center Mass
{
  Point maxPoint = FindMaxVal(type);
  Point maxVal = maxPoint;
  int centerMass = FindCenterMass(type);
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  Point leftMaxVal(0,0);
  Point rightMaxVal(0,0);
  Point centerMaxVal(centerMass, arr[centerMass]);
  int i = 1;
  while(true)
  {
    if(centerMass + i < size && rightMaxVal.y < arr[centerMass + i])
    {
      rightMaxVal.y = arr[centerMass + i];
      rightMaxVal.x = centerMass + i;
    }
    if(centerMass - i >= 0 && leftMaxVal.y < arr[centerMass - i])
    {
      leftMaxVal.y = arr[centerMass - i];
      leftMaxVal.x = centerMass - i;
    }
    if(centerMass + i >= size && centerMass - i < 0) break;
    i++;
  }
  if(centerMass > 0 &&
  (rightMaxVal.y - arr[centerMass])/(rightMaxVal.x - centerMass) <
  (leftMaxVal.y - arr[centerMass])/(centerMass - leftMaxVal.x))
  {
    maxVal = leftMaxVal;
  }
  else
  {
    maxVal = rightMaxVal;
  }
  maxVal = (centerMaxVal.y > maxVal.y) ? centerMaxVal:maxVal;
  return maxVal;
}
float Histogram::Sigma (char type)//нахождение сигма через ширину на полувысоте
{
  Point maxVal = FindMaxVal(type);
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  float sigma = 0;
  int a0 = 0;
  if(maxVal.x > size/2)
    {
      for(int i = 0; i < 10; i++)
        {
          a0 += arr[i];
        }
    }
  else
    {
      for(int i = 0; i < 10; i++)
        {
          a0 += arr[size - 1 - i];
        }
    }
  a0 = a0/10;

  int a1 = maxVal.y - a0;
  float sum1 = 0, sum2 = 0;
  for(int i = 0; i < size; i++)
    {
      sum1 += (arr[i] - a0) *  (maxVal.x - i) * exp(-pow(i - maxVal.x, 2));
      sum2 += a1  * (maxVal.x - i) * pow(exp(-pow(i - maxVal.x, 2)), 2);
    }

  sigma = sqrt(1/log(sum1/sum2)/2);
  return sigma;
}
float Histogram::OLSSigma (char type)//метод наименьших квадратов
{
  int size = CheckSize(type);
  int arr[size];
  int a;
  CheckType(type, arr, &a);
  float sigma = 1;
  Point maxPoint = FMCM(type);;
  float func;
  float sum = 0, sumLast = 0;

  for(int i = 0; i < size; i++)
  {
    func = maxPoint.y * exp(-(pow((i-maxPoint.x),2)/(2)));
    sumLast += pow((func - arr[i]),2);
  }
  sum = sumLast;

  for(sigma = 2; sumLast >= sum; sigma++)
  {
    sumLast = sum;
    sum = 0;
    for(int i = 0; i < size; i++)
    {
      func = maxPoint.y * exp(-(pow((i-maxPoint.x),2)/(2 * sigma * sigma)));
      sum += pow((func - arr[i]),2);
    }
  }

  float min_sigma = sigma - 5;
  float min_sum = sum;
  for( float s = sigma; s > min_sigma; s = s - 0.1)
  {
    sum = 0;
    for(int i = 0; i < size; i++)
    {
      func = maxPoint.y * exp(-(pow((i-maxPoint.x),2)/(2 * s * s)));
      sum += pow((func - arr[i]),2);
    }
    if(sum < min_sum)
    {
      min_sum = sum;
      sigma = s;
    }
  }
  return sigma;
}
