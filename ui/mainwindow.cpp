#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\include\testSpline.h"

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
    chartTest->legend()->setVisible(false);
    chartTest->setTitle("Тестовая функция");

    testX = new QValueAxis();
    testX->setLabelFormat("%f");
    testX->setTickCount(11);
    testX->setTitleText("x");
    chartTest->addAxis(testX, Qt::AlignBottom);

    testY = new QValueAxis();
    testY->setLabelFormat("%f");
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

// Тестовая функция

void MainWindow::on_startTestTask_clicked()
{
    double totalS = 15., totalDerS = 2.0, totalSecDerS = 20.;
    double totalXS = 15., totalXDerS = 2.0, totalXSecDerS = 20.;

    ui->testSplineKoef->setRowCount(testN);
    ui->testComp->setRowCount(testN + 1);
    ui->testCompDer->setRowCount(testN + 1);
    ui->testCompSecDer->setRowCount(testN + 1);

    testSeries = new QLineSeries();

    if (ui->showDotsTest->isChecked()) testSeries->setPointsVisible(true);
    else testSeries->setPointsVisible(false);

    TestSpline test(testN);

    test.getResults(testSeries, ui->testSplineKoef, ui->testComp, ui->testCompDer, ui->testCompSecDer);

    for (int i = 0; i < testN + 1; i++)
    {
        /*if (i > 0) ui->testSplineKoef->setItem(i - 1, 0, new QTableWidgetItem(QString::number(i)));
        ui->testComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        ui->testComp->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));

        ui->testComp->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));

        ui->testComp->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));

        ui->testComp->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));*/

        *testSeries << QPointF(i, i * i);
    }

    chartTest->addSeries(testSeries);
    testSeries->attachAxis(testX);
    testSeries->attachAxis(testY);
    ui->graphicsView->setChart(chartTest);
    ui->graphicsView->zoomIt(false);

    ui->testNEdit->setText(QString().number(testN));
    ui->testnEdit->setText(QString().number(testN + 1));

    ui->testSComp->setText(QString().number(totalS));
    ui->testxSComp->setText(QString().number(totalXS));

    ui->testDerSComp->setText(QString().number(totalDerS));
    ui->testxDerSComp->setText(QString().number(totalXDerS));

    ui->testSecDerSComp->setText(QString().number(totalSecDerS));
    ui->testxSecDerSComp->setText(QString().number(totalXSecDerS));
}


void MainWindow::on_clearTestTask_clicked()
{
    if (testSeries)
    {
        ui->graphicsView->zoomIt(false);
        chartTest->removeAllSeries();
        testSeries = nullptr;
    }
}


void MainWindow::on_numberTest_editingFinished()
{
    bool ok;
    ui->numberTest->text().toInt(&ok);

    if (ok == false)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Недопустимые символы");
        msgBox.exec();

        ui->startTestTask->setEnabled(false);

        return;
    }

    testN = ui->numberTest->text().toInt();

    if (testN < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Количество разбиений не может быть меньше 0");
        msgBox.exec();

        ui->startTestTask->setEnabled(false);

        return;
    }

    ui->startTestTask->setEnabled(true);
}


void MainWindow::on_showDotsTest_clicked(bool checked)
{
    if (testSeries)
    {
        if (checked)
        {
            testSeries->setPointsVisible(true);
        }
        else
        {
            testSeries->setPointsVisible(false);
        }
    }
}

void MainWindow::on_testFuncBox_clicked(bool checked)
{
    if (testSeries)
    {
        if (checked) testSeries->setVisible(true);
        else testSeries->setVisible(false);
    }
}


void MainWindow::on_testSplineBox_clicked(bool checked)
{

}

// Основная функция

void MainWindow::on_clearMainTask_clicked()
{
    if (mainSeries)
    {
        ui->graphicsView_2->zoomIt(false);
        chartMain->removeAllSeries();
        mainSeries = nullptr;
    }
}


void MainWindow::on_showDotsMain_clicked(bool checked)
{
    if (mainSeries)
    {
        if (checked)
        {
            mainSeries->setPointsVisible(true);
        }
        else
        {
            mainSeries->setPointsVisible(false);
        }
    }
}


void MainWindow::on_startMainTask_clicked()
{
    double totalS = 15., totalDerS = 2.0, totalSecDerS = 20.;
    double totalXS = 15., totalXDerS = 2.0, totalXSecDerS = 20.;

    ui->mainSplineKoef->setRowCount(mainN);
    ui->mainComp->setRowCount(mainN + 1);
    ui->mainCompDer->setRowCount(mainN + 1);
    ui->mainCompSecDer->setRowCount(mainN + 1);

    mainSeries = new QLineSeries();

    if (ui->showDotsMain->isChecked()) mainSeries->setPointsVisible(true);
    else mainSeries->setPointsVisible(false);

    for (int i = 0; i < mainN + 1; i++)
    {
        if (i > 0) ui->mainSplineKoef->setItem(i - 1, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        ui->mainComp->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));

        ui->mainComp->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));

        ui->mainComp->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));

        ui->mainComp->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));

        *mainSeries << QPointF(i, i * i);
    }

    chartMain->addSeries(mainSeries);
    mainSeries->attachAxis(mainX);
    mainSeries->attachAxis(mainY);
    ui->graphicsView_2->setChart(chartMain);
    ui->graphicsView_2->zoomIt(false);

    ui->mainNEdit->setText(QString().number(mainN));
    ui->mainnEdit->setText(QString().number(mainN + 1));

    ui->mainSComp->setText(QString().number(totalS));
    ui->mainxSComp->setText(QString().number(totalXS));

    ui->mainDerSComp->setText(QString().number(totalDerS));
    ui->mainxDerSComp->setText(QString().number(totalXDerS));

    ui->mainSecDerSComp->setText(QString().number(totalSecDerS));
    ui->mainxSecDerSComp->setText(QString().number(totalXSecDerS));
}


void MainWindow::on_numberMain_editingFinished()
{
    bool ok;
    ui->numberMain->text().toInt(&ok);

    if (ok == false)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Недопустимые символы");
        msgBox.exec();

        ui->startMainTask->setEnabled(false);

        return;
    }

    mainN = ui->numberMain->text().toInt();

    if (mainN < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Количество разбиений не может быть меньше 0");
        msgBox.exec();

        ui->startMainTask->setEnabled(false);

        return;
    }

    ui->startMainTask->setEnabled(true);
}

// Осциллирующая

void MainWindow::on_clearOscillTask_clicked()
{
    if (oscillSeries)
    {
        ui->graphicsView_3->zoomIt(false);
        chartOscill->removeAllSeries();
        oscillSeries = nullptr;
    }
}


void MainWindow::on_showDotsOscill_clicked(bool checked)
{
    if (oscillSeries)
    {
        if (checked)
        {
            oscillSeries->setPointsVisible(true);
        }
        else
        {
            oscillSeries->setPointsVisible(false);
        }
    }
}


void MainWindow::on_numberOscill_editingFinished()
{
    bool ok;
    ui->numberOscill->text().toInt(&ok);

    if (ok == false)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Недопустимые символы");
        msgBox.exec();

        ui->startOscillTask->setEnabled(false);

        return;
    }

    oscillN = ui->numberOscill->text().toInt();

    if (oscillN < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Количество разбиений не может быть меньше 0");
        msgBox.exec();

        ui->startOscillTask->setEnabled(false);

        return;
    }

    ui->startOscillTask->setEnabled(true);
}


void MainWindow::on_startOscillTask_clicked()
{
    double totalS = 15., totalDerS = 2.0, totalSecDerS = 20.;
    double totalXS = 15., totalXDerS = 2.0, totalXSecDerS = 20.;

    ui->oscillSplineKoef->setRowCount(oscillN);
    ui->oscillComp->setRowCount(oscillN + 1);
    ui->oscillCompDer->setRowCount(oscillN + 1);
    ui->oscillCompSecDer->setRowCount(oscillN + 1);

    oscillSeries = new QLineSeries();

    if (ui->showDotsOscill->isChecked()) oscillSeries->setPointsVisible(true);
    else oscillSeries->setPointsVisible(false);

    for (int i = 0; i < oscillN + 1; i++)
    {
        if (i > 0) ui->oscillSplineKoef->setItem(i - 1, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        ui->oscillComp->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(i)));

        ui->oscillComp->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(i)));

        ui->oscillComp->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(i)));

        ui->oscillComp->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(i)));

        *oscillSeries << QPointF(i, i * i);
    }

    chartOscill->addSeries(oscillSeries);
    oscillSeries->attachAxis(oscillX);
    oscillSeries->attachAxis(oscillY);
    ui->graphicsView_3->setChart(chartOscill);
    ui->graphicsView_3->zoomIt(true);

    ui->oscillNEdit->setText(QString().number(oscillN));
    ui->oscillnEdit->setText(QString().number(oscillN + 1));

    ui->oscillSComp->setText(QString().number(totalS));
    ui->oscillxSComp->setText(QString().number(totalXS));

    ui->oscillDerSComp->setText(QString().number(totalDerS));
    ui->oscillxDerSComp->setText(QString().number(totalXDerS));

    ui->oscillSecDerSComp->setText(QString().number(totalSecDerS));
    ui->oscillxSecDerSComp->setText(QString().number(totalXSecDerS));
}

