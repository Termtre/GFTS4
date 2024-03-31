#include "mainwindow.h"
#include "ui_mainwindow.h"

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
