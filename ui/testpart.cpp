#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_startTestTask_clicked()
{
    testClear();

    ui->testSplineKoef->setRowCount(testN);
    ui->testComp->setRowCount(testN * 5 + 1);
    ui->testCompDer->setRowCount(testN * 5 + 1);
    ui->testCompSecDer->setRowCount(testN * 5 + 1);

    testSeries = new QLineSeries();
    testSeries->setName("Сплайн");

    testFuncSeries = new QLineSeries();
    testFuncSeries->setName("Тестовая функция");

    testDSeries = new QLineSeries();
    testDSeries->setName("Производная Сплайна");

    testDFuncSeries = new QLineSeries();
    testDFuncSeries->setName("Производная Тестовой функции");

    testDDSeries = new QLineSeries();
    testDDSeries->setName("Вторая Производная Сплайна");

    testDDFuncSeries = new QLineSeries();
    testDDFuncSeries->setName("Вторая Производная Тестовой функции");

    testCompSeries = new QLineSeries();
    testCompSeries->setName("Разность функций");

    testCompDSeries = new QLineSeries();
    testCompDSeries->setName("Разность производных");

    testCompDDSeries = new QLineSeries();
    testCompDDSeries->setName("Разность вторых производных");


    testSeries->setVisible(false);
    testDSeries->setVisible(false);
    testDDSeries->setVisible(false);

    testFuncSeries->setVisible(false);
    testDFuncSeries->setVisible(false);
    testDDFuncSeries->setVisible(false);

    testCompSeries->setVisible(false);
    testCompDSeries->setVisible(false);
    testCompDDSeries->setVisible(false);

    if (ui->showDotsTest->isChecked()) testSeries->setPointsVisible(true);
    else testSeries->setPointsVisible(false);

    Spline test(testN, -1., 0., 1.);
    test.solution(functionTest);

    std::vector<double> ai(test.getAi());
    std::vector<double> bi(test.getBi());
    std::vector<double> ci(test.getCi());
    std::vector<double> di(test.getDi());

    double h = 2. / static_cast<double>(testN);

    for (int i = 0; i < testN; i++)
    {
        ui->testSplineKoef->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->testSplineKoef->setItem(i, 1, new QTableWidgetItem(QString::number(-1. + static_cast<double>(i) * h)));
        ui->testSplineKoef->setItem(i, 2, new QTableWidgetItem(QString::number(-1. + static_cast<double>(i + 1) * h)));
        ui->testSplineKoef->setItem(i, 3, new QTableWidgetItem(QString::number(ai[i + 1])));
        ui->testSplineKoef->setItem(i, 4, new QTableWidgetItem(QString::number(bi[i + 1])));
        ui->testSplineKoef->setItem(i, 5, new QTableWidgetItem(QString::number(ci[i + 1])));
        ui->testSplineKoef->setItem(i, 6, new QTableWidgetItem(QString::number(di[i + 1])));
    }

    double totalS = 0., totalDerS = 0., totalSecDerS = 0.;
    double totalXS = 0., totalXDerS = 0., totalXSecDerS = 0.;

    h /= 5.;

    double x, spline, function, dspline, dfunction, ddspline, ddfunction, scomp, dscomp, ddscomp;

    for (int i = 0, j = 1; i <= testN * 5; i++)
    {
        x = -1. + static_cast<double>(i) * h;

        spline = test.S(j, x);
        function = functionTest(x);
        scomp = function - spline;

        if (abs(scomp) > totalS)
        {
            totalS = abs(scomp);
            totalXS = x;
        }

        dspline = test.dS(j, x);
        dfunction = functionTestD(x);
        dscomp = dfunction - dspline;

        if (abs(dscomp) > totalDerS)
        {
            totalDerS = abs(dscomp);
            totalXDerS = x;
        }

        ddspline = test.ddS(j, x);
        ddfunction = functionTestDD(x);
        ddscomp = ddfunction - ddspline;

        if (abs(ddscomp) > totalSecDerS)
        {
            totalSecDerS = abs(ddscomp);
            totalXSecDerS = x;
        }

        ui->testComp->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->testComp->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->testComp->setItem(i, 2, new QTableWidgetItem(QString::number(function)));
        ui->testComp->setItem(i, 3, new QTableWidgetItem(QString::number(spline)));
        ui->testComp->setItem(i, 4, new QTableWidgetItem(QString::number(scomp)));

        ui->testCompDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->testCompDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->testCompDer->setItem(i, 2, new QTableWidgetItem(QString::number(dfunction)));
        ui->testCompDer->setItem(i, 3, new QTableWidgetItem(QString::number(dspline)));
        ui->testCompDer->setItem(i, 4, new QTableWidgetItem(QString::number(dscomp)));

        ui->testCompSecDer->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        ui->testCompSecDer->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        ui->testCompSecDer->setItem(i, 2, new QTableWidgetItem(QString::number(ddfunction)));
        ui->testCompSecDer->setItem(i, 3, new QTableWidgetItem(QString::number(ddspline)));
        ui->testCompSecDer->setItem(i, 4, new QTableWidgetItem(QString::number(ddscomp)));

        *testSeries << QPointF(x, spline);
        *testFuncSeries << QPointF(x, function);
        *testDSeries << QPointF(x, dspline);
        *testDFuncSeries << QPointF(x, dfunction);
        *testDDSeries << QPointF(x, ddspline);
        *testDDFuncSeries << QPointF(x, ddfunction);
        *testCompSeries << QPointF(x, scomp);
        *testCompDSeries << QPointF(x, dscomp);
        *testCompDDSeries << QPointF(x, ddscomp);

        if (i != 0) if ((i % 5) == 0) j++;
    }

    chartTest->addSeries(testSeries);
    chartTest->addSeries(testFuncSeries);
    chartTest->addSeries(testDSeries);
    chartTest->addSeries(testDFuncSeries);
    chartTest->addSeries(testDDSeries);
    chartTest->addSeries(testDDFuncSeries);
    chartTest->addSeries(testCompSeries);
    chartTest->addSeries(testCompDSeries);
    chartTest->addSeries(testCompDDSeries);

    ui->graphicsView->setChart(chartTest);
    testSeries->attachAxis(testX);
    testSeries->attachAxis(testY);

    testX->setRange(-1., 1.);

    if (ui->testComboBox->currentIndex() < 3)
    {
        testY->setRange(0., 2.);
    }
    else
    {
        if (ui->testComboBox->currentIndex() == 3) testY->setRange(0., totalS);
        else if (ui->testComboBox->currentIndex() == 4) testY->setRange(0., totalDerS);
        else testY->setRange(0., totalSecDerS);
    }
    //ui->graphicsView->zoomIt(false);

    if (ui->testComboBox->currentIndex() == 0)
    {
        if (ui->testSplineBox->isChecked()) testSeries->setVisible(true);
        else testSeries->setVisible(false);

        if (ui->testFuncBox->isChecked()) testFuncSeries->setVisible(true);
        else testFuncSeries->setVisible(false);
    }
    else if (ui->testComboBox->currentIndex() == 1)
    {
        if (ui->testSplineBox->isChecked()) testDSeries->setVisible(true);
        else testDSeries->setVisible(false);

        if (ui->testFuncBox->isChecked()) testDFuncSeries->setVisible(true);
        else testDFuncSeries->setVisible(false);
    }
    else if (ui->testComboBox->currentIndex() == 2)
    {
        if (ui->testSplineBox->isChecked()) testDDSeries->setVisible(true);
        else testDDSeries->setVisible(false);

        if (ui->testFuncBox->isChecked()) testDDFuncSeries->setVisible(true);
        else testDDFuncSeries->setVisible(false);
    }
    else if (ui->testComboBox->currentIndex() == 3)
    {
        testCompSeries->setVisible(true);
    }
    else if (ui->testComboBox->currentIndex() == 4)
    {
        testCompDSeries->setVisible(true);
    }
    else
    {
        testCompDDSeries->setVisible(true);
    }

    ui->testNEdit->setText(QString().number(testN * 5));
    ui->testnEdit->setText(QString().number(testN));

    ui->testSComp->setText(QString().number(totalS));
    ui->testxSComp->setText(QString().number(totalXS));

    ui->testDerSComp->setText(QString().number(totalDerS));
    ui->testxDerSComp->setText(QString().number(totalXDerS));

    ui->testSecDerSComp->setText(QString().number(totalSecDerS));
    ui->testxSecDerSComp->setText(QString().number(totalXSecDerS));
}


void MainWindow::testClear()
{
    if (testSeries)
    {
        //ui->graphicsView->zoomIt(false);
        chartTest->removeAllSeries();
        testSeries = nullptr;
        testFuncSeries = nullptr;
        testDSeries = nullptr;
        testDFuncSeries = nullptr;
        testDDSeries = nullptr;
        testDDFuncSeries = nullptr;
        testCompSeries = nullptr;
        testCompDSeries = nullptr;
        testCompDDSeries = nullptr;
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
            testDSeries->setPointsVisible(true);
            testDDSeries->setPointsVisible(true);

            testFuncSeries->setPointsVisible(true);
            testDFuncSeries->setPointsVisible(true);
            testDFuncSeries->setPointsVisible(true);

            testCompSeries->setPointsVisible(true);
            testCompDSeries->setPointsVisible(true);
            testCompDDSeries->setPointsVisible(true);
        }
        else
        {
            testSeries->setPointsVisible(false);
            testDSeries->setPointsVisible(false);
            testDDSeries->setPointsVisible(false);

            testFuncSeries->setPointsVisible(false);
            testDFuncSeries->setPointsVisible(false);
            testDDFuncSeries->setPointsVisible(false);

            testCompSeries->setPointsVisible(false);
            testCompDSeries->setPointsVisible(false);
            testCompDDSeries->setPointsVisible(false);
        }
    }
}

void MainWindow::on_testFuncBox_clicked(bool checked)
{
    if (testFuncSeries)
    {
        if (checked && ui->testComboBox->currentIndex() == 0) testFuncSeries->setVisible(true);
        else testFuncSeries->setVisible(false);

        if (checked && ui->testComboBox->currentIndex() == 1) testDFuncSeries->setVisible(true);
        else testDFuncSeries->setVisible(false);

        if (checked && ui->testComboBox->currentIndex() == 2) testDDFuncSeries->setVisible(true);
        else testDDFuncSeries->setVisible(false);
    }
}


void MainWindow::on_testSplineBox_clicked(bool checked)
{
    if (testSeries)
    {
        if (checked && ui->testComboBox->currentIndex() == 0) testSeries->setVisible(true);
        else testSeries->setVisible(false);

        if (checked && ui->testComboBox->currentIndex() == 1) testDSeries->setVisible(true);
        else testDSeries->setVisible(false);

        if (checked && ui->testComboBox->currentIndex() == 2) testDDSeries->setVisible(true);
        else testDDSeries->setVisible(false);
    }
}

void MainWindow::on_testComboBox_currentIndexChanged(int index)
{
    if (testSeries)
    {
        testX->setRange(-1., 1.);

        testSeries->setVisible(false);
        testDSeries->setVisible(false);
        testDDSeries->setVisible(false);

        testFuncSeries->setVisible(false);
        testDFuncSeries->setVisible(false);
        testDDFuncSeries->setVisible(false);

        testCompSeries->setVisible(false);
        testCompDSeries->setVisible(false);
        testCompDDSeries->setVisible(false);

        switch(index)
        {
        case 0:
        {
            if (ui->testSplineBox->isChecked()) testSeries->setVisible(true);
            if (ui->testSplineBox->isChecked()) testFuncSeries->setVisible(true);
            testY->setRange(0., 2.);
            break;
        }
        case 1:
        {
            if (ui->testSplineBox->isChecked()) testDSeries->setVisible(true);
            if (ui->testSplineBox->isChecked()) testDFuncSeries->setVisible(true);
            testY->setRange(0., 2.);
            break;
        }
        case 2:
        {
            if (ui->testSplineBox->isChecked()) testDDSeries->setVisible(true);
            if (ui->testSplineBox->isChecked())testDDFuncSeries->setVisible(true);
            testY->setRange(0., 2.);
            break;
        }
        case 3:
        {
            testCompSeries->setVisible(true);
            testY->setRange(0., ui->testSComp->text().toDouble());
            break;
        }
        case 4:
        {
            testCompDSeries->setVisible(true);
            testY->setRange(0., ui->testDerSComp->text().toDouble());
            break;
        }
        case 5:
        {
            testCompDDSeries->setVisible(true);
            testY->setRange(0., ui->testSecDerSComp->text().toDouble());
            break;
        }
        }
    }
}
