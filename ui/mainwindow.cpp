#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("GFTS4");

    ui->tabWidget->setCurrentIndex(0);

    ui->tabWidget_2->setCurrentIndex(0);

    ui->tabWidget_3->setCurrentIndex(0);

    ui->tabWidget_5->setCurrentIndex(0);

    // Тестовая функция
    chartTest = new QChart();
    chartTest->legend()->setVisible(true);
    chartTest->setTitle("Тестовая функция");

    testX = new QValueAxis();
    testX->setLabelFormat("%.5lf");
    testX->setTickCount(11);
    testX->setTitleText("x");
    chartTest->addAxis(testX, Qt::AlignBottom);

    testY = new QValueAxis();
    testY->setLabelFormat("%.5lf");
    testY->setTickCount(11);
    testY->setTitleText("y");
    chartTest->addAxis(testY, Qt::AlignLeft);

    ui->showDotsTest->setChecked(true);
    ui->testFuncBox->setChecked(true);
    ui->testSplineBox->setChecked(true);
    ui->testSplineKoef->verticalHeader()->setVisible(false);
    ui->testComp->verticalHeader()->setVisible(false);
    ui->testCompDer->verticalHeader()->setVisible(false);
    ui->testCompSecDer->verticalHeader()->setVisible(false);

    // Основная функция
    chartMain = new QChart();
    chartMain->legend()->setVisible(false);
    chartMain->setTitle("Основная функция");

    mainX = new QValueAxis();
    mainX->setLabelFormat("%f");
    mainX->setTickCount(11);
    mainX->setTitleText("x");
    chartMain->addAxis(mainX, Qt::AlignBottom);

    mainY = new QValueAxis();
    mainY->setLabelFormat("%f");
    mainY->setTickCount(11);
    mainY->setTitleText("y");
    chartMain->addAxis(mainY, Qt::AlignLeft);

    ui->showDotsMain->setChecked(true);
    ui->mainFuncBox->setChecked(true);
    ui->mainSplineBox->setChecked(true);
    ui->mainSplineKoef->verticalHeader()->setVisible(false);
    ui->mainComp->verticalHeader()->setVisible(false);
    ui->mainCompDer->verticalHeader()->setVisible(false);
    ui->mainCompSecDer->verticalHeader()->setVisible(false);

    // Осциллирующая функция
    chartOscill = new QChart();
    chartOscill->legend()->setVisible(false);
    chartOscill->setTitle("Осциллирующая функция");

    oscillX = new QValueAxis();
    oscillX->setLabelFormat("%f");
    oscillX->setTickCount(11);
    oscillX->setTitleText("x");
    chartOscill->addAxis(oscillX, Qt::AlignBottom);

    oscillY = new QValueAxis();
    oscillY->setLabelFormat("%f");
    oscillY->setTickCount(11);
    oscillY->setTitleText("y");
    chartOscill->addAxis(oscillY, Qt::AlignLeft);

    ui->showDotsOscill->setChecked(true);
    ui->oscillFuncBox->setChecked(true);
    ui->oscillSplineBox->setChecked(true);
    ui->oscillSplineKoef->verticalHeader()->setVisible(false);
    ui->oscillComp->verticalHeader()->setVisible(false);
    ui->oscillCompDer->verticalHeader()->setVisible(false);
    ui->oscillCompSecDer->verticalHeader()->setVisible(false);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}
