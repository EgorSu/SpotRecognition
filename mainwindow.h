#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <main.h>
#include <QLabel>
#include <QFile>
#include <QMutex>
#include <QGraphicsScene>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void SetImage(Mat);
  void SetParapetrs(float, float, int, Point);
  static QMutex mutex;
public slots:
  void onValueChanged(float sigmaX, float sigmaY, int alpha, int centerX, int centerY, QImage*);
  void onFrameChanged(QImage*);

private slots:
  void on_pushButton_1_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_4_clicked();
  void on_MainButton_clicked();

  void on_pushButton_frame1_clicked();
  void on_pushButton_frame2_clicked();
  void on_pushButton_frame3_clicked();
  void on_pushButton_frame4_clicked();
  void on_pushButton_frame5_clicked();
  void on_pushButton_Average_clicked();

private:
  Ui::MainWindow *ui;
  QGraphicsPixmapItem *itemFrame;
  QGraphicsPixmapItem *itemValue;
  QGraphicsScene* sceneFrame;
  QGraphicsScene* sceneBeam;
  bool firstFrame;// = true;
  bool firstMeasure;// = true;
  void DeleteFrameItem();
  void DeleteValueItem();

signals:
  void frameNumberChanged(int);
  void rectChanged(int);
  void pathChanged(QString);
};

#endif // MAINWINDOW_H
