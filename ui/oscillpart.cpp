#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_startOscillTask_clicked()
{
    oscillClear();

    ui->oscillSplineKoef->setRowCount(oscillN);
    ui->oscillComp->setRowCount(oscillN * 5 + 1);
    ui->oscillCompDer->setRowCount(oscillN * 5 + 1);
    ui->oscillCompSecDer->setRowCount(oscillN * 5 + 1);

    oscillSeries = new QLineSeries();
    oscillSeries->setName("Сплайн");

    oscillFuncSeries = new QLineSeries();
    oscillFuncSeries->setName("Тестовая функция");

    oscillDSeries = new QLineSeries();
    oscillDSeries->setName("Производная Сплайна");

    oscillDFuncSeries = new QLineSeries();
    oscillDFuncSeries->setName("Производная Тестовой функции");

    oscillDDSeries = new QLineSeries();
    oscillDDSeries->setName("Вторая Производная Сплайна");

    oscillDDFuncSeries = new QLineSeries();
    oscillDDFuncSeries->setName("Вторая Производная Тестовой функции");

    oscillCompSeries = new QLineSeries();
    oscillCompSeries->setName("Разность функций");

    oscillCompDSeries = new QLineSeries();
    oscillCompDSeries->setName("Разность производных");

    oscillCompDDSeries = new QLineSeries();
    oscillCompDDSeries->setName("Разность вторых производных");


    oscillSeries->setVisible(false);
    oscillDSeries->setVisible(false);
    oscillDDSeries->setVisible(false);

    oscillFuncSeries->setVisible(false);
    oscillDFuncSeries->setVisible(false);
    oscillDDFuncSeries->setVisible(false);

    oscillCompSeries->setVisible(false);
    oscillCompDSeries->setVisible(false);
    oscillCompDDSeries->setVisible(false);

    if (ui->showDotsOscill->isChecked()) oscillSeries->setPointsVisible(true);
    else oscillSeries->setPointsVisible(false);

    Spline oscill(oscillN, 2., 0., 4.);
    oscill.solution(functionOscill);

    std::vector<double> ai(oscill.getAi());
    std::vector<double> bi(oscill.getBi());
    std::vector<double> ci(oscill.getCi());
    std::vector<double> di(oscill.getDi());

    double h = 2. / static_cast<double>(oscillN);

    for (int i = 0; i < oscillN; i++)
    {
        ui->oscillSplineKoef->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->oscillSplineKoef->setItem(i, 1, new QTableWidgetItem(QString::number(2. + static_cast<double>(i) * h)));
        ui->oscillSplineKoef->setItem(i, 2, new QTableWidgetItem(QString::number(2. + static_cast<double>(i + 1) * h)));
        ui->oscillSplineKoef->setItem(i, 3, new QTableWidgetItem(QString::number(ai[i + 1])));
        ui->oscillSplineKoef->setItem(i, 4, new QTableWidgetItem(QString::number(bi[i + 1])));
        ui->oscillSplineKoef->setItem(i, 5, new QTableWidgetItem(QString::number(ci[i + 1])));
        ui->oscillSplineKoef->setItem(i, 6, new QTableWidgetItem(QString::number(di[i + 1])));
    }

    double totalS = 0., totalDerS = 0., totalSecDerS = 0.;
    double totalXS = 0., totalXDerS = 0., totalXSecDerS = 0.;

    h /= 5.;

    double x, spline, function, dspline, dfunction, ddspline, ddfunction, scomp, dscomp, ddscomp;

    for (int i = 0, j = 1; i <= oscillN * 5; i++)
    {
        x = 2. + static_cast<double>(i) * h;

        spline = oscill.S(j, x);
        function = functionOscill(x);
        scomp = function - spline;

        if (abs(scomp) > totalS)
        {
            totalS = abs(scomp);
            totalXS = x;
        }

        dspline = oscill.dS(j, x);
        dfunction = functionOscillD(x);
        dscomp = dfunction - dspline;

        if (abs(dscomp) > totalDerS)
        {
            totalDerS = abs(dscomp);
            totalXDerS = x;
        }

        ddspline = oscill.ddS(j, x);
        ddfunction = functionOscillDD(x);
        ddscomp = ddfunction - ddspline;

        if (abs(ddscomp) > totalSecDerS)
        {
            totalSecDerS = abs(ddscomp);
            totalXSecDerS = x;
        }

        ui->oscillComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillComp->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->oscillComp->setItem(i, 2, new QTableWidgetItem(QString::number(function)));
        ui->oscillComp->setItem(i, 3, new QTableWidgetItem(QString::number(spline)));
        ui->oscillComp->setItem(i, 4, new QTableWidgetItem(QString::number(scomp)));

        ui->oscillCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->oscillCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(dfunction)));
        ui->oscillCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(dspline)));
        ui->oscillCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(dscomp)));

        ui->oscillCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->oscillCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->oscillCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(ddfunction)));
        ui->oscillCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(ddspline)));
        ui->oscillCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(ddscomp)));

        *oscillSeries << QPointF(x, spline);
        *oscillFuncSeries << QPointF(x, function);
        *oscillDSeries << QPointF(x, dspline);
        *oscillDFuncSeries << QPointF(x, dfunction);
        *oscillDDSeries << QPointF(x, ddspline);
        *oscillDDFuncSeries << QPointF(x, ddfunction);
        *oscillCompSeries << QPointF(x, scomp);
        *oscillCompDSeries << QPointF(x, dscomp);
        *oscillCompDDSeries << QPointF(x, ddscomp);

        if (i != 0) if ((i % 5) == 0) j++;
    }

    chartOscill->addSeries(oscillSeries);
    chartOscill->addSeries(oscillFuncSeries);
    chartOscill->addSeries(oscillDSeries);
    chartOscill->addSeries(oscillDFuncSeries);
    chartOscill->addSeries(oscillDDSeries);
    chartOscill->addSeries(oscillDDFuncSeries);
    chartOscill->addSeries(oscillCompSeries);
    chartOscill->addSeries(oscillCompDSeries);
    chartOscill->addSeries(oscillCompDDSeries);

    ui->graphicsView_3->setChart(chartOscill);
    oscillSeries->attachAxis(oscillX);
    oscillSeries->attachAxis(oscillY);

    oscillX->setRange(2., 4.);

    if (ui->oscillComboBox->currentIndex() < 3)
    {
        oscillY->setRange(0., 2.);
    }
    else
    {
        if (ui->oscillComboBox->currentIndex() == 3) oscillY->setRange(0., totalS);
        else if (ui->oscillComboBox->currentIndex() == 4) oscillY->setRange(0., totalDerS);
        else oscillY->setRange(0., totalSecDerS);
    }
    //ui->graphicsView->zoomIt(false);

    if (ui->oscillComboBox->currentIndex() == 0)
    {
        if (ui->oscillSplineBox->isChecked()) oscillSeries->setVisible(true);
        else oscillSeries->setVisible(false);

        if (ui->oscillFuncBox->isChecked()) oscillFuncSeries->setVisible(true);
        else oscillFuncSeries->setVisible(false);
    }
    else if (ui->oscillComboBox->currentIndex() == 1)
    {
        if (ui->oscillSplineBox->isChecked()) oscillDSeries->setVisible(true);
        else oscillDSeries->setVisible(false);

        if (ui->oscillFuncBox->isChecked()) oscillDFuncSeries->setVisible(true);
        else oscillDFuncSeries->setVisible(false);
    }
    else if (ui->oscillComboBox->currentIndex() == 2)
    {
        if (ui->oscillSplineBox->isChecked()) oscillDDSeries->setVisible(true);
        else oscillDDSeries->setVisible(false);

        if (ui->oscillFuncBox->isChecked()) oscillDDFuncSeries->setVisible(true);
        else oscillDDFuncSeries->setVisible(false);
    }
    else if (ui->oscillComboBox->currentIndex() == 3)
    {
        oscillCompSeries->setVisible(true);
    }
    else if (ui->oscillComboBox->currentIndex() == 4)
    {
        oscillCompDSeries->setVisible(true);
    }
    else
    {
        oscillCompDDSeries->setVisible(true);
    }

    ui->oscillNEdit->setText(QString().number(oscillN * 5));
    ui->oscillnEdit->setText(QString().number(oscillN));

    ui->oscillSComp->setText(QString().number(totalS));
    ui->oscillxSComp->setText(QString().number(totalXS));

    ui->oscillDerSComp->setText(QString().number(totalDerS));
    ui->oscillxDerSComp->setText(QString().number(totalXDerS));

    ui->oscillSecDerSComp->setText(QString().number(totalSecDerS));
    ui->oscillxSecDerSComp->setText(QString().number(totalXSecDerS));
}


void MainWindow::oscillClear()
{
    if (oscillSeries)
    {
        //ui->graphicsView->zoomIt(false);
        chartOscill->removeAllSeries();
        oscillSeries = nullptr;
        oscillFuncSeries = nullptr;
        oscillDSeries = nullptr;
        oscillDFuncSeries = nullptr;
        oscillDDSeries = nullptr;
        oscillDDFuncSeries = nullptr;
        oscillCompSeries = nullptr;
        oscillCompDSeries = nullptr;
        oscillCompDDSeries = nullptr;
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


void MainWindow::on_showDotsOscill_clicked(bool checked)
{
    if (oscillSeries)
    {
        if (checked)
        {
            oscillSeries->setPointsVisible(true);
            oscillDSeries->setPointsVisible(true);
            oscillDDSeries->setPointsVisible(true);

            oscillFuncSeries->setPointsVisible(true);
            oscillDFuncSeries->setPointsVisible(true);
            oscillDFuncSeries->setPointsVisible(true);

            oscillCompSeries->setPointsVisible(true);
            oscillCompDSeries->setPointsVisible(true);
            oscillCompDDSeries->setPointsVisible(true);
        }
        else
        {
            oscillSeries->setPointsVisible(false);
            oscillDSeries->setPointsVisible(false);
            oscillDDSeries->setPointsVisible(false);

            oscillFuncSeries->setPointsVisible(false);
            oscillDFuncSeries->setPointsVisible(false);
            oscillDDFuncSeries->setPointsVisible(false);

            oscillCompSeries->setPointsVisible(false);
            oscillCompDSeries->setPointsVisible(false);
            oscillCompDDSeries->setPointsVisible(false);
        }
    }
}

void MainWindow::on_oscillFuncBox_clicked(bool checked)
{
    if (oscillFuncSeries)
    {
        if (checked && ui->oscillComboBox->currentIndex() == 0) oscillFuncSeries->setVisible(true);
        else oscillFuncSeries->setVisible(false);

        if (checked && ui->oscillComboBox->currentIndex() == 1) oscillDFuncSeries->setVisible(true);
        else oscillDFuncSeries->setVisible(false);

        if (checked && ui->oscillComboBox->currentIndex() == 2) oscillDDFuncSeries->setVisible(true);
        else oscillDDFuncSeries->setVisible(false);
    }
}


void MainWindow::on_oscillSplineBox_clicked(bool checked)
{
    if (oscillSeries)
    {
        if (checked && ui->oscillComboBox->currentIndex() == 0) oscillSeries->setVisible(true);
        else oscillSeries->setVisible(false);

        if (checked && ui->oscillComboBox->currentIndex() == 1) oscillDSeries->setVisible(true);
        else oscillDSeries->setVisible(false);

        if (checked && ui->oscillComboBox->currentIndex() == 2) oscillDDSeries->setVisible(true);
        else oscillDDSeries->setVisible(false);
    }
}

void MainWindow::on_oscillComboBox_currentIndexChanged(int index)
{
    if (oscillSeries)
    {
        oscillX->setRange(2., 4.);

        oscillSeries->setVisible(false);
        oscillDSeries->setVisible(false);
        oscillDDSeries->setVisible(false);

        oscillFuncSeries->setVisible(false);
        oscillDFuncSeries->setVisible(false);
        oscillDDFuncSeries->setVisible(false);

        oscillCompSeries->setVisible(false);
        oscillCompDSeries->setVisible(false);
        oscillCompDDSeries->setVisible(false);

        switch(index)
        {
        case 0:
        {
            if (ui->oscillSplineBox->isChecked()) oscillSeries->setVisible(true);
            if (ui->oscillSplineBox->isChecked()) oscillFuncSeries->setVisible(true);
            oscillY->setRange(0., 2.);
            break;
        }
        case 1:
        {
            if (ui->oscillSplineBox->isChecked()) oscillDSeries->setVisible(true);
            if (ui->oscillSplineBox->isChecked()) oscillDFuncSeries->setVisible(true);
            oscillY->setRange(0., 2.);
            break;
        }
        case 2:
        {
            if (ui->oscillSplineBox->isChecked()) oscillDDSeries->setVisible(true);
            if (ui->oscillSplineBox->isChecked())oscillDDFuncSeries->setVisible(true);
            oscillY->setRange(0., 2.);
            break;
        }
        case 3:
        {
            oscillCompSeries->setVisible(true);
            oscillY->setRange(0., ui->oscillSComp->text().toDouble());
            break;
        }
        case 4:
        {
            oscillCompDSeries->setVisible(true);
            oscillY->setRange(0., ui->oscillDerSComp->text().toDouble());
            break;
        }
        case 5:
        {
            oscillCompDDSeries->setVisible(true);
            oscillY->setRange(0., ui->oscillSecDerSComp->text().toDouble());
            break;
        }
        }
    }
}
