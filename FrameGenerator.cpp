#include "FrameGenerator.h"
class FrameGenerator;
FrameGenerator::FrameGenerator() {}
FrameGenerator::FrameGenerator(Mat bg, int sX, int sY, int a)
{
  bg.copyTo(background);
  numCols = background.cols;
  numRows = background.rows;
  sigmaX = sX;
  sigmaY = sY;
  alpha = a - 90;
}
Mat FrameGenerator::GenerateFlash(Point zeroPoint)
{
  Mat flash = Mat::zeros(numRows * 2, numCols * 2, CV_8UC1);
  for(int i = 0; i < flash.cols; i++)
  {
    for(int j = 0; j < flash.rows; j++)
    {
      int x = i - flash.cols/2;
      int y = j - flash.rows/2;
      flash.at<unsigned char>(j,i) = (int) (255 * exp(-(pow((x),2)/(2 * sigmaX * sigmaX) + pow((y),2)/(2 * sigmaY * sigmaY))));
    }
  }
  Mat rotMat( 2, 3, CV_32FC1 );
  rotMat = getRotationMatrix2D(Point (flash.cols/2, flash.rows/2), alpha, 1.0);
  warpAffine(flash, flash, rotMat, flash.size());

  Mat frame(flash, Rect(flash.cols/2 - zeroPoint.x,flash.rows/2 - zeroPoint.y, numCols, numRows));
  return frame;
}
Mat FrameGenerator::GetResultFrame(int t)
{
  Mat result;
  ResultFrame(t).copyTo(result);
  return result;
}
Mat FrameGenerator::ResultFrame(int t)
{
  Point center = CenterPoint();

  cout<<" flash center "<<center.x<<" "<<center.y<<endl;
  Mat flash;
  GenerateFlash(center).copyTo(flash);
  Mat noise;
  NoiseGenerator(background).copyTo(noise);
  Mat light;
  AddLight(background, center).copyTo(light);
  Mat result = Mat::zeros(numRows, numCols, CV_8UC1);
  switch(t)
  {
    case 1:
      result = flash;
      break;
    case 2:
      result = flash + noise;
      break;
    case 3:
      result = flash + noise + light;
      break;
    default:
      break;
  }
  return result;
}
Mat FrameGenerator::SumFrame(Mat frame1, Mat frame2)
{
  Mat result = frame1 + frame2;
  for(int i = 0; i < numCols; i++)
  {
    for(int j = 0; j < numRows; j++)
    {
      //int pixelVolume = (int) (frame1.at<unsigned char>(j,i) + frame2.at<unsigned char>(j,i));
      //result.at<unsigned char>(j,i) = (pixelVolume < 255) ? pixelVolume:255;
    }
  }
  return result;
}
Point FrameGenerator::CenterPoint ()
{
  int MIN_RANGE_ROWS = background.cols/4;
  int MIN_RANGE_COLS = background.cols/4;
  int MAX_RANGE_COLS = background.cols/2;
  int MAX_RANGE_ROWS = background.cols/2;
  /*
  int MIN_RANGE_ROWS = sigmaY;
  int MIN_RANGE_COLS = sigmaX;
  int MAX_RANGE_COLS = background.cols - sigmaX;
  int MAX_RANGE_ROWS = background.rows - sigmaY;
  */
  Point center;
  center.x = MIN_RANGE_COLS + rand()% MAX_RANGE_COLS;
  center.y = MIN_RANGE_ROWS + rand()% MAX_RANGE_ROWS;
  //center.y = 299;
  //center.x = background.cols/2;
  //center.y = background.rows/2;
  return center;
}
Mat FrameGenerator::NoiseGenerator(Mat frame)
{
  Mat noiseFrame(frame.rows, frame.cols, CV_8UC1);
  int noiseSum = 0;
  for(int i = 0; i < frame.rows; i++)
  {
    for(int j = 0; j < frame.cols; j++)
    {
      int a = 0;
      for(int k = 0; k < 10; k++)
        a += rand()%10;
      a /= 10;
      noiseFrame.at<unsigned char>(i,j) = (int) (a);
      noiseSum += a;
    }
  }
  return frame + noiseFrame;
}
Mat FrameGenerator::AddLight(Mat frame, Point center)
{
  int maxLight = 80;
  int zeroCols = (center.x > frame.cols/2)? frame.cols:0;
  int zeroRows = (center.y > frame.rows/2)? frame.rows:0;
  Mat light (frame.rows, frame.cols, CV_8UC1);
  for(int i = 0; i < frame.rows; i++) // свет по x
  {
    for(int j = 0; j < frame.cols; j++)
    {
      int a;
      if(abs(j - center.x) < maxLight * 2 && abs(i - zeroRows) < maxLight * 2 &&
      (maxLight - abs((j - center.x)/2)) > abs((i - zeroRows))/2)
      {
        a = (maxLight - abs((j - center.x)/2)) - abs((i - zeroRows)/2);
      }
      else a = 0;
      light.at<unsigned char>(i,j) = (int) (a);
    }
  }
  for(int i = 0; i < frame.cols; i++)//свет по y
  {
    for(int j = 0; j < frame.rows; j++)
    {
      int a;
      if(abs(j - center.y) < maxLight * 2 && abs(i - zeroRows) < maxLight * 2 &&
      (maxLight - abs((j - center.y)/2)) > abs((i - zeroCols))/2)
      {
        a = (maxLight - abs((j - center.y)/2)) - abs((i - zeroCols)/2);
      }
      else a = 0;
      light.at<unsigned char>(j,i) += (int) (a);
    }
  }
  return light;
}
