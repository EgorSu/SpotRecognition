#include "mythread.h"


MyThread::MyThread() {}
MyThread::~MyThread()
{

}
Mat MyThread::LocalROI (Mat frame, int a, Scalar *MeanScalar)
{
  Mat LocalROI;
  CvRect LocalROIrect;

  LocalROIrect.width = (int) frame.cols/a;
  LocalROIrect.height = (int) frame.rows/a;
  for(int i = 0; i < a; i++)
  {
    LocalROIrect.y = i * LocalROIrect.height;
    for(int j = 0; j < a; j++)
    {
      LocalROIrect.x = j * LocalROIrect.width;
      frame(LocalROIrect).copyTo(LocalROI);
      MeanScalar[a * i + j] = mean(LocalROI);
    }
  }
  return frame;
}
Mat MyThread::GlobalROI (Mat frame)
{
  Mat ROI;
  CvRect ROIrect;
  ROIrect.width = (int) frame.cols*3/5;
  ROIrect.height = (int) frame.rows*3/5;
  ROIrect.x = (int) frame.cols/5;
  ROIrect.y = (int) frame.rows/5;
  frame(ROIrect).copyTo(ROI);
  return ROI;
}
bool MyThread::Detected (Scalar Mean, Scalar LastMean, Scalar delta)
{
  return Mean.val[0] > LastMean.val[0] + delta.val[0];
}
Mat MyThread::ProcessImg()
{
  Spot spot(f, maxFrameAfter);
  spot.FindParam();
  sX = spot.smallAxis/2;
  sY = spot.bigAxis/2;
  alpha = spot.alpha;
  centerPoint = spot.centerPoint;
  return spot.AverageFrame();
}
void MyThread::run()
{
  //параметры LocalRoi и Detected
  int NumberROI = 10; // кол-во roi в ряду кадра
                      //(всего NumberROI * NumberROI областей интереса в одном кадре)
                      // 10 выбрано т.к. неплохо работает
  Scalar LastMeanScalar[NumberROI * NumberROI];
  Scalar MeanScalar[NumberROI * NumberROI];
  Scalar delta(3); //разница между средними значениями областей LocalRoi настоящего и предыдущего кадров в значении нулевого канала GrayScale

  //запись кадров и построение гистрограмм
  bool rec=false;
  bool firstFrame = true;
  bool firstBeam = true;

  int nframe = maxFrameAfter;
  Mat ROIs[maxFrameAfter];
  Mat saveLastROI; // кадр перед вспышкой

  QFile file(":/new/prefix1/config.txt");//
  file.open(QIODevice::ReadOnly);
  char video_name[100] = {};
  file.readLine(video_name, 100);
  file.close();
  video_name[strcspn(video_name, "\r\n")] = 0;
  VideoCapture cap(video_name);

  if(!cap.isOpened())
  {
    cout << "can not open the video file" << endl;
  }
  else
  {
    cout<<"opened"<<endl;
  }

  Mat roi;
  Mat lastRoi;

  while(cap.read(frame))
  {
    delta = maxDelta * 2;
    Mat GrayFrame;
    cvtColor(frame, GrayFrame, CV_BGR2GRAY);
    ROIFrame = GrayFrame;
    if(firstFrame)
    {
      rect = Rect(0, 0, ROIFrame.cols, ROIFrame.rows);
      newRect = Rect(0, 0, ROIFrame.cols, ROIFrame.rows);
    }
    Rect currentRect = rect;
    Mat(ROIFrame, currentRect).copyTo(roi);
    Mat tempImg1;// = Mat::zeros(roi.rows,roi.cols, CV_8UC3);
    cvtColor(roi, tempImg1, CV_GRAY2RGB);
    if(!firstFrame)
        delete frameImg;
    else
        firstFrame = false;
    frameImg = new QImage((unsigned char*)tempImg1.data, tempImg1.cols, tempImg1.rows, tempImg1.step,QImage::Format_RGB888);
    emit frameChanged(frameImg);
    LocalROI(roi - lastRoi, NumberROI, MeanScalar);

    for(int i = 0; i < NumberROI * NumberROI; i++)
    {
      if(Detected(MeanScalar[i], LastMeanScalar[i], delta) == true && lastRoi.rows != 0)
      {
        nframe = 0;
        saveLastROI = Mat(lastRoi.rows, lastRoi.cols, lastRoi.type());
        lastRoi.copyTo(saveLastROI); // сохранение кадра перед вспышкой
        break;
      }
      LastMeanScalar[i] = MeanScalar[i];
    }
    if(nframe < maxFrameAfter)//запись кадров после вспышки
    {
      Mat deltaFrame;
      f[nframe] = Mat::zeros(ROIs[nframe].rows, ROIs[nframe].cols, CV_8UC1);
      deltaFrame = roi - saveLastROI;
      deltaFrame.copyTo(f[nframe]);
      if(nframe == maxFrameAfter - 1 ) rec = true; // rec должна стать true на последнем nframe
      nframe++;
    }

    if(rec)
    {
      Mat averageFrame;
      ProcessImg().copyTo(averageFrame);
      Mat tempMat2;
      cvtColor(averageFrame, tempMat2, CV_GRAY2RGB);
      if(!firstBeam)
          delete avBeamImg;
      else
          firstBeam = false;
      avBeamImg = new QImage((unsigned char*) tempMat2.data, tempMat2.cols, tempMat2.rows, QImage::Format_RGB888);
      //
      emit valueChanged(sX, sY, alpha, centerPoint.x, centerPoint.y, avBeamImg);
      rec = false;
    }

    if(rectChanged)
      SetFramePart(ROIFrame).copyTo(roi);
    roi.copyTo(lastRoi);
    firstFrame = false;
  }
}
Mat MyThread::SetFramePart (Mat frame)
{
  rectChanged = false;
  rect = newRect;
  return Mat(frame, rect);
}
void MyThread::onRectChanged(int part)
{
  rectChanged = true;
  switch (part) {
    case 0:
      newRect = Rect(0, 0, ROIFrame.cols, ROIFrame.rows);
      break;
    case 1:
      newRect = Rect(0, 0, ROIFrame.cols/2, ROIFrame.rows/2);
      break;
    case 2:
      newRect = Rect(ROIFrame.cols/2, 0, ROIFrame.cols/2, ROIFrame.rows/2);
      break;
    case 3:
      newRect = Rect(0,ROIFrame.rows/2, ROIFrame.cols/2, ROIFrame.rows/2);
      break;
    case 4:
      newRect = Rect(ROIFrame.cols/2, ROIFrame.rows/2, ROIFrame.cols/2, ROIFrame.rows/2);
      break;
  }
}
void MyThread::onFrameNumberChanged(int number)
{
    if(number == 0)
    {
        emit valueChanged(sX, sY, alpha, centerPoint.x, centerPoint.y, avBeamImg);
    }
    else if(maxFrameAfter >= number)
    {
        if(!frameBeamImg->isNull()) delete frameBeamImg;
        Mat tempMat;
        cvtColor(f[number - 1], tempMat, CV_GRAY2RGB);
        frameBeamImg = new QImage((unsigned char*) tempMat.data, tempMat.cols, tempMat.rows, QImage::Format_RGB888);
        emit valueChanged(sX, sY, alpha, centerPoint.x, centerPoint.y, frameBeamImg);
    }
}

