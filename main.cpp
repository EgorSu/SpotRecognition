#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "Spot.h"
#include <FrameGenerator.h>
#include <mythread.cpp>
#include <QThread>
int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  MainWindow *w = new MainWindow();
  MyThread *workerThread = new MyThread();

  QObject::connect(workerThread, SIGNAL(valueChanged(float , float , int , int, int, QImage*)), w,
                        SLOT(onValueChanged(float, float, int, int, int, QImage*)));
  QObject::connect(workerThread, SIGNAL(frameChanged(QImage*)), w,
                        SLOT(onFrameChanged(QImage*)));
  QObject::connect(w, SIGNAL(rectChanged(int)), workerThread,
                        SLOT(onRectChanged(int)));
  QObject::connect(w, SIGNAL(frameNumberChanged(int)), workerThread,
                   SLOT(onFrameNumberChanged(int)));
  w->show();
  workerThread->start();
  return a.exec();
}
