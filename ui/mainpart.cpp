#include "mainwindow.h"
#include "ui_mainwindow.h"

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
