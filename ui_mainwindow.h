/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_1;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *MainButton;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_SX;
    QLineEdit *sigmaX;
    QLabel *label_SY;
    QLineEdit *sigmaY;
    QLabel *label_A;
    QLineEdit *alpha;
    QLabel *label_CX;
    QLineEdit *CenterX;
    QLabel *label_CY;
    QLineEdit *CenterY;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 372);
        MainWindow->setWindowOpacity(1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(360, 0, 182, 90));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_1 = new QPushButton(verticalLayoutWidget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setEnabled(true);
        pushButton_1->setMinimumSize(QSize(40, 40));
        pushButton_1->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_1);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setEnabled(true);
        pushButton_3->setMinimumSize(QSize(40, 40));
        pushButton_3->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(true);
        pushButton_2->setMinimumSize(QSize(40, 40));
        pushButton_2->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setEnabled(true);
        pushButton_4->setMinimumSize(QSize(40, 40));
        pushButton_4->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);

        MainButton = new QPushButton(verticalLayoutWidget);
        MainButton->setObjectName(QString::fromUtf8("MainButton"));
        MainButton->setMinimumSize(QSize(50, 40));

        verticalLayout->addWidget(MainButton);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 50, 311, 241));
        graphicsView->setInteractive(false);
        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(330, 100, 251, 191));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 300, 581, 26));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_SX = new QLabel(horizontalLayoutWidget);
        label_SX->setObjectName(QString::fromUtf8("label_SX"));
        label_SX->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(10);
        label_SX->setFont(font);

        horizontalLayout_2->addWidget(label_SX);

        sigmaX = new QLineEdit(horizontalLayoutWidget);
        sigmaX->setObjectName(QString::fromUtf8("sigmaX"));
        sigmaX->setFrame(false);
        sigmaX->setEchoMode(QLineEdit::Normal);
        sigmaX->setReadOnly(false);

        horizontalLayout_2->addWidget(sigmaX);

        label_SY = new QLabel(horizontalLayoutWidget);
        label_SY->setObjectName(QString::fromUtf8("label_SY"));
        label_SY->setBaseSize(QSize(0, 0));
        label_SY->setFont(font);

        horizontalLayout_2->addWidget(label_SY);

        sigmaY = new QLineEdit(horizontalLayoutWidget);
        sigmaY->setObjectName(QString::fromUtf8("sigmaY"));
        sigmaY->setFrame(false);
        sigmaY->setEchoMode(QLineEdit::Normal);
        sigmaY->setReadOnly(false);

        horizontalLayout_2->addWidget(sigmaY);

        label_A = new QLabel(horizontalLayoutWidget);
        label_A->setObjectName(QString::fromUtf8("label_A"));
        label_A->setBaseSize(QSize(0, 0));
        label_A->setFont(font);

        horizontalLayout_2->addWidget(label_A);

        alpha = new QLineEdit(horizontalLayoutWidget);
        alpha->setObjectName(QString::fromUtf8("alpha"));
        alpha->setFrame(false);
        alpha->setEchoMode(QLineEdit::Normal);
        alpha->setReadOnly(false);

        horizontalLayout_2->addWidget(alpha);

        label_CX = new QLabel(horizontalLayoutWidget);
        label_CX->setObjectName(QString::fromUtf8("label_CX"));
        label_CX->setBaseSize(QSize(0, 0));
        label_CX->setFont(font);

        horizontalLayout_2->addWidget(label_CX);

        CenterX = new QLineEdit(horizontalLayoutWidget);
        CenterX->setObjectName(QString::fromUtf8("CenterX"));
        CenterX->setFrame(false);
        CenterX->setEchoMode(QLineEdit::Normal);
        CenterX->setReadOnly(false);

        horizontalLayout_2->addWidget(CenterX);

        label_CY = new QLabel(horizontalLayoutWidget);
        label_CY->setObjectName(QString::fromUtf8("label_CY"));
        label_CY->setBaseSize(QSize(0, 0));
        label_CY->setFont(font);

        horizontalLayout_2->addWidget(label_CY);

        CenterY = new QLineEdit(horizontalLayoutWidget);
        CenterY->setObjectName(QString::fromUtf8("CenterY"));
        CenterY->setFrame(false);
        CenterY->setEchoMode(QLineEdit::Normal);
        CenterY->setReadOnly(false);

        horizontalLayout_2->addWidget(CenterY);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_1->setText(QApplication::translate("MainWindow", "1", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "2", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "3", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "4", 0));
        MainButton->setText(QApplication::translate("MainWindow", "Main Window", 0));
        label_SX->setText(QApplication::translate("MainWindow", "sigma X", 0));
        label_SY->setText(QApplication::translate("MainWindow", "sigma Y", 0));
        label_A->setText(QApplication::translate("MainWindow", "alpha", 0));
        label_CX->setText(QApplication::translate("MainWindow", "center X", 0));
        label_CY->setText(QApplication::translate("MainWindow", "center Y", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
