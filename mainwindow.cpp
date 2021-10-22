#include "mainwindow.h"
#include "mythread.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  sceneFrame = new QGraphicsScene();
  ui->graphicsView->setScene(sceneFrame);
  sceneBeam = new QGraphicsScene();
  ui->graphicsView_2->setScene(sceneBeam);
  firstFrame = true;
  firstMeasure = true;
}
MainWindow::~MainWindow()
{
  delete sceneBeam;
  delete sceneFrame;
  delete itemFrame;
  delete itemValue;
  delete ui;
}
void MainWindow::onFrameChanged(QImage *image)
{
  if(!firstFrame)
    delete itemFrame;
  else
    firstFrame = false;
  if(!image->isNull())
  {
      QPixmap pixmap = QPixmap::fromImage(*image);
      pixmap = pixmap.scaled(ui->graphicsView->size());
      itemFrame = new QGraphicsPixmapItem(pixmap);
      ui->graphicsView->scene()->addItem(itemFrame);
      ui->graphicsView->show();
  }
  else
      cout<<"frame image is null"<<endl;
}
void MainWindow::onValueChanged(float sigmaX, float sigmaY, int alpha, int centerX, int centerY, QImage *image)
{
  ui->sigmaX->setText(QString::number(sigmaX));
  ui->sigmaY->setText(QString::number(sigmaY));
  ui->CenterX->setText(QString::number(centerX));
  ui->CenterY->setText(QString::number(centerY));
  ui->alpha->setText(QString::number(alpha));
  if(!firstMeasure)
    DeleteValueItem();
  else
    firstMeasure = false;
  if(!image->isNull())
  {
      QPixmap pixmap = QPixmap::fromImage(*image);
      pixmap = pixmap.scaled(ui->graphicsView_2->size());
      itemValue = new QGraphicsPixmapItem(pixmap);
      ui->graphicsView_2->scene()->addItem(itemValue);
      ui->graphicsView_2->show();
  }
  else
      cout<<"beam image is null"<<endl;
}
void MainWindow::DeleteFrameItem()
{
  delete itemFrame;
}
void MainWindow::DeleteValueItem()
{
  delete itemValue;
}
void MainWindow::on_pushButton_1_clicked()
{
  emit rectChanged(1);
}
void MainWindow::on_pushButton_2_clicked()
{
  emit rectChanged(2);
}
void MainWindow::on_pushButton_3_clicked()
{
  emit rectChanged(3);
}
void MainWindow::on_pushButton_4_clicked()
{
  emit rectChanged(4);
}
void MainWindow::on_MainButton_clicked()
{
  emit rectChanged(0);
}
void MainWindow::on_pushButton_frame1_clicked()
{
    emit frameNumberChanged(1);
}
void MainWindow::on_pushButton_frame2_clicked()
{
    emit frameNumberChanged(2);
}
void MainWindow::on_pushButton_frame3_clicked()
{
    emit frameNumberChanged(3);
}
void MainWindow::on_pushButton_frame4_clicked()
{
    emit frameNumberChanged(4);
}
void MainWindow::on_pushButton_frame5_clicked()
{
    emit frameNumberChanged(5);
}
void MainWindow::on_pushButton_Average_clicked()
{
    emit frameNumberChanged(0);
}
