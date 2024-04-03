#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_startMainTask_clicked()
{
    mainClear();

    ui->mainSplineKoef->setRowCount(mainN);
    ui->mainComp->setRowCount(mainN * mainM + 1);
    ui->mainCompDer->setRowCount(mainN * mainM + 1);
    ui->mainCompSecDer->setRowCount(mainN * mainM + 1);

    mainSeries = new QLineSeries();
    mainSeries->setName("Сплайн");

    mainFuncSeries = new QLineSeries();
    mainFuncSeries->setName("Тестовая функция");

    mainDSeries = new QLineSeries();
    mainDSeries->setName("Производная Сплайна");

    mainDFuncSeries = new QLineSeries();
    mainDFuncSeries->setName("Производная Тестовой функции");

    mainDDSeries = new QLineSeries();
    mainDDSeries->setName("Вторая Производная Сплайна");

    mainDDFuncSeries = new QLineSeries();
    mainDDFuncSeries->setName("Вторая Производная Тестовой функции");

    mainCompSeries = new QLineSeries();
    mainCompSeries->setName("Разность функций");

    mainCompDSeries = new QLineSeries();
    mainCompDSeries->setName("Разность производных");

    mainCompDDSeries = new QLineSeries();
    mainCompDDSeries->setName("Разность вторых производных");

    Spline main(mainN, 2., 0., 4.);
    main.solution(functionMain);

    std::vector<double> ai(main.getAi());
    std::vector<double> bi(main.getBi());
    std::vector<double> ci(main.getCi());
    std::vector<double> di(main.getDi());

    double h = 2. / static_cast<double>(mainN);

    for (int i = 0; i < mainN; i++)
    {
        ui->mainSplineKoef->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->mainSplineKoef->setItem(i, 1, new QTableWidgetItem(QString::number(2. + static_cast<double>(i) * h)));
        ui->mainSplineKoef->setItem(i, 2, new QTableWidgetItem(QString::number(2. + static_cast<double>(i + 1) * h)));
        ui->mainSplineKoef->setItem(i, 3, new QTableWidgetItem(QString::number(ai[i + 1])));
        ui->mainSplineKoef->setItem(i, 4, new QTableWidgetItem(QString::number(bi[i + 1])));
        ui->mainSplineKoef->setItem(i, 5, new QTableWidgetItem(QString::number(ci[i + 1])));
        ui->mainSplineKoef->setItem(i, 6, new QTableWidgetItem(QString::number(di[i + 1])));
    }

    double totalS = 0., totalDerS = 0., totalSecDerS = 0.;
    double totalXS = 0., totalXDerS = 0., totalXSecDerS = 0.;

    h /= mainM;

    double x, spline, function, dspline, dfunction, ddspline, ddfunction, scomp, dscomp, ddscomp;

    for (int i = 0, j = 1; i <= mainN * mainM; i++)
    {
        x = 2. + static_cast<double>(i) * h;

        spline = main.S(j, x);
        function = functionMain(x);
        scomp = function - spline;

        if (abs(scomp) > totalS)
        {
            totalS = abs(scomp);
            totalXS = x;
        }

        dspline = main.dS(j, x);
        dfunction = functionMainD(x);
        dscomp = dfunction - dspline;

        if (abs(dscomp) > totalDerS)
        {
            totalDerS = abs(dscomp);
            totalXDerS = x;
        }

        ddspline = main.ddS(j, x);
        ddfunction = functionMainDD(x);
        ddscomp = ddfunction - ddspline;

        if (abs(ddscomp) > totalSecDerS)
        {
            totalSecDerS = abs(ddscomp);
            totalXSecDerS = x;
        }

        ui->mainComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainComp->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->mainComp->setItem(i, 2, new QTableWidgetItem(QString::number(function)));
        ui->mainComp->setItem(i, 3, new QTableWidgetItem(QString::number(spline)));
        ui->mainComp->setItem(i, 4, new QTableWidgetItem(QString::number(scomp)));

        ui->mainCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->mainCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(dfunction)));
        ui->mainCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(dspline)));
        ui->mainCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(dscomp)));

        ui->mainCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->mainCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->mainCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(ddfunction)));
        ui->mainCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(ddspline)));
        ui->mainCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(ddscomp)));

        *mainSeries << QPointF(x, spline);
        *mainFuncSeries << QPointF(x, function);
        *mainDSeries << QPointF(x, dspline);
        *mainDFuncSeries << QPointF(x, dfunction);
        *mainDDSeries << QPointF(x, ddspline);
        *mainDDFuncSeries << QPointF(x, ddfunction);
        *mainCompSeries << QPointF(x, scomp);
        *mainCompDSeries << QPointF(x, dscomp);
        *mainCompDDSeries << QPointF(x, ddscomp);

        if (i != 0) if ((i % mainM) == 0) j++;
    }

    chartMain->addSeries(mainSeries);
    chartMain->addSeries(mainFuncSeries);
    chartMain->addSeries(mainDSeries);
    chartMain->addSeries(mainDFuncSeries);
    chartMain->addSeries(mainDDSeries);
    chartMain->addSeries(mainDDFuncSeries);
    chartMain->addSeries(mainCompSeries);
    chartMain->addSeries(mainCompDSeries);
    chartMain->addSeries(mainCompDDSeries);

    ui->graphicsView_2->setChart(chartMain);

    mainSeries->attachAxis(mainX);
    mainSeries->attachAxis(mainY);

    mainFuncSeries->attachAxis(mainX);
    mainFuncSeries->attachAxis(mainY);

    mainDSeries->attachAxis(mainX);
    mainDSeries->attachAxis(mainY);

    mainDFuncSeries->attachAxis(mainX);
    mainDFuncSeries->attachAxis(mainY);

    mainDDSeries->attachAxis(mainX);
    mainDDSeries->attachAxis(mainY);

    mainDDFuncSeries->attachAxis(mainX);
    mainDDFuncSeries->attachAxis(mainY);

    mainCompSeries->attachAxis(mainX);
    mainCompSeries->attachAxis(mainY);

    mainCompDSeries->attachAxis(mainX);
    mainCompDSeries->attachAxis(mainY);

    mainCompDDSeries->attachAxis(mainX);
    mainCompDDSeries->attachAxis(mainY);

    ui->mainNEdit->setText(QString().number(mainN * mainM + 1));
    ui->mainnEdit->setText(QString().number(mainN + 1));

    ui->mainSComp->setText(QString().number(totalS));
    ui->mainxSComp->setText(QString().number(totalXS));

    ui->mainDerSComp->setText(QString().number(totalDerS));
    ui->mainxDerSComp->setText(QString().number(totalXDerS));

    ui->mainSecDerSComp->setText(QString().number(totalSecDerS));
    ui->mainxSecDerSComp->setText(QString().number(totalXSecDerS));

    on_showDotsMain_clicked(ui->showDotsMain->isChecked());

    on_mainFuncBox_clicked(ui->mainFuncBox->isChecked());

    on_mainSplineBox_clicked(ui->mainSplineBox->isChecked());

    on_mainComboBox_currentIndexChanged(ui->mainComboBox->currentIndex());

    ui->graphicsView_2->zoomIt(true);
}


void MainWindow::mainClear()
{
    if (mainSeries)
    {
        //ui->graphicsView->zoomIt(false);
        chartMain->removeAllSeries();
        mainSeries = nullptr;
        mainFuncSeries = nullptr;
        mainDSeries = nullptr;
        mainDFuncSeries = nullptr;
        mainDDSeries = nullptr;
        mainDDFuncSeries = nullptr;
        mainCompSeries = nullptr;
        mainCompDSeries = nullptr;
        mainCompDDSeries = nullptr;
    }
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


void MainWindow::on_showDotsMain_clicked(bool checked)
{
    if (mainSeries)
    {
        if (checked)
        {
            mainSeries->setPointsVisible(true);
            mainDSeries->setPointsVisible(true);
            mainDDSeries->setPointsVisible(true);

            mainFuncSeries->setPointsVisible(true);
            mainDFuncSeries->setPointsVisible(true);
            mainDDFuncSeries->setPointsVisible(true);

            mainCompSeries->setPointsVisible(true);
            mainCompDSeries->setPointsVisible(true);
            mainCompDDSeries->setPointsVisible(true);
        }
        else
        {
            mainSeries->setPointsVisible(false);
            mainDSeries->setPointsVisible(false);
            mainDDSeries->setPointsVisible(false);

            mainFuncSeries->setPointsVisible(false);
            mainDFuncSeries->setPointsVisible(false);
            mainDDFuncSeries->setPointsVisible(false);

            mainCompSeries->setPointsVisible(false);
            mainCompDSeries->setPointsVisible(false);
            mainCompDDSeries->setPointsVisible(false);
        }
    }
}

void MainWindow::on_mainFuncBox_clicked(bool checked)
{
    if (mainFuncSeries)
    {
        if (checked && ui->mainComboBox->currentIndex() == 0) mainFuncSeries->setVisible(true);
        else mainFuncSeries->setVisible(false);

        if (checked && ui->mainComboBox->currentIndex() == 1) mainDFuncSeries->setVisible(true);
        else mainDFuncSeries->setVisible(false);

        if (checked && ui->mainComboBox->currentIndex() == 2) mainDDFuncSeries->setVisible(true);
        else mainDDFuncSeries->setVisible(false);
    }
}


void MainWindow::on_mainSplineBox_clicked(bool checked)
{
    if (mainSeries)
    {
        if (checked && ui->mainComboBox->currentIndex() == 0) mainSeries->setVisible(true);
        else mainSeries->setVisible(false);

        if (checked && ui->mainComboBox->currentIndex() == 1) mainDSeries->setVisible(true);
        else mainDSeries->setVisible(false);

        if (checked && ui->mainComboBox->currentIndex() == 2) mainDDSeries->setVisible(true);
        else mainDDSeries->setVisible(false);
    }
}

void MainWindow::on_mainComboBox_currentIndexChanged(int index)
{
    if (mainSeries)
    {
        mainX->setRange(2., 4.);

        mainSeries->setVisible(false);
        mainDSeries->setVisible(false);
        mainDDSeries->setVisible(false);

        mainFuncSeries->setVisible(false);
        mainDFuncSeries->setVisible(false);
        mainDDFuncSeries->setVisible(false);

        mainCompSeries->setVisible(false);
        mainCompDSeries->setVisible(false);
        mainCompDDSeries->setVisible(false);

        switch(index)
        {
        case 0:
        {
            if (ui->mainSplineBox->isChecked()) mainSeries->setVisible(true);
            if (ui->mainSplineBox->isChecked()) mainFuncSeries->setVisible(true);
            mainY->setRange(0., 2.);
            break;
        }
        case 1:
        {
            if (ui->mainSplineBox->isChecked()) mainDSeries->setVisible(true);
            if (ui->mainSplineBox->isChecked()) mainDFuncSeries->setVisible(true);
            mainY->setRange(0., 2.);
            break;
        }
        case 2:
        {
            if (ui->mainSplineBox->isChecked()) mainDDSeries->setVisible(true);
            if (ui->mainSplineBox->isChecked())mainDDFuncSeries->setVisible(true);
            mainY->setRange(0., 2.);
            break;
        }
        case 3:
        {
            mainCompSeries->setVisible(true);
            mainY->setRange(0., ui->mainSComp->text().toDouble());
            break;
        }
        case 4:
        {
            mainCompDSeries->setVisible(true);
            mainY->setRange(0., ui->mainDerSComp->text().toDouble());
            break;
        }
        case 5:
        {
            mainCompDDSeries->setVisible(true);
            mainY->setRange(0., ui->mainSecDerSComp->text().toDouble());
            break;
        }
        }
    }
}

void MainWindow::on_mainMultiplier_editingFinished()
{
    bool ok;
    ui->mainMultiplier->text().toInt(&ok);

    if (ok == false)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Недопустимые символы");
        msgBox.exec();

        ui->startMainTask->setEnabled(false);

        return;
    }

    mainM = ui->mainMultiplier->text().toInt();

    if (mainM < 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Множитель не может быть отрицательным числом");
        msgBox.exec();

        ui->startMainTask->setEnabled(false);

        return;
    }

    ui->startMainTask->setEnabled(true);
}
