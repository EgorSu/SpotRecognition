#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include "mainwindow.h"
#include <QObject>
#include <main.h>
#include <Spot.h>
#include <QMutex>
class MyThread: public QThread
{
  Q_OBJECT

  protected:
          void run();
  public:
    MyThread();
    ~MyThread();
    QMutex mutex;
  private:
    bool rectChanged;
    int maxFrameAfter = 5;
    int framePart;
    int alpha;
    float sX, sY;
    float maxDelta = 0;
    Point centerPoint;

    QString name;
    QImage* avBeamImg;
    QImage* frameImg;
    QImage* frameBeamImg;
    Rect rect;
    Rect newRect;
    Mat frame;
    Mat ROIFrame;
    Mat f[5];

    void Processing();
    bool Detected (Scalar Mean, Scalar LastMean, Scalar delta);
    Mat SetFramePart(Mat);
    Mat LocalROI (Mat frame, int a, Scalar *MeanScalar); // разбиение frame на a * a областей, a - количество областей в одном ряду
    Mat GlobalROI (Mat frame);//cut the edges of the frame
    Mat ProcessImg();


  public slots:
    void onRectChanged(int);
    void onFrameNumberChanged(int);

  signals:
    void valueChanged(float, float, int, int, int, QImage*);
    void frameChanged(QImage*);

};

#endif // MYTHREAD_H
