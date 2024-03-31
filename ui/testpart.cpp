#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\include\spline.h"
#include "functions.h"

void MainWindow::on_startTestTask_clicked()
{
    ui->testSplineKoef->setRowCount(testN);
    ui->testComp->setRowCount(testN + 1);
    ui->testCompDer->setRowCount(testN + 1);
    ui->testCompSecDer->setRowCount(testN + 1);

    testSeries = new QLineSeries();

    if (ui->showDotsTest->isChecked()) testSeries->setPointsVisible(true);
    else testSeries->setPointsVisible(false);

    Spline test(testN, -1., 0., 1.);
    test.solution(testFunc);

    double totalS = 15., totalDerS = 2.0, totalSecDerS = 20.;
    double totalXS = 15., totalXDerS = 2.0, totalXSecDerS = 20.;

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
