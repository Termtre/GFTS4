#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>

#include "functions.h"
#include "../include/spline.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startTestTask_clicked();

    void on_numberTest_editingFinished();

    void on_showDotsTest_clicked(bool checked);

    void on_showDotsMain_clicked(bool checked);

    void on_startMainTask_clicked();

    void on_numberMain_editingFinished();

    void on_showDotsOscill_clicked(bool checked);

    void on_numberOscill_editingFinished();

    void on_startOscillTask_clicked();

    void on_testFuncBox_clicked(bool checked);

    void on_testSplineBox_clicked(bool checked);

    void testClear();

    void mainClear();

    void oscillClear();

    void on_testComboBox_currentIndexChanged(int index);

    void on_mainComboBox_currentIndexChanged(int index);

    void on_oscillFuncBox_clicked(bool checked);

    void on_oscillSplineBox_clicked(bool checked);

    void on_oscillComboBox_currentIndexChanged(int index);

    void on_mainFuncBox_clicked(bool checked);

    void on_mainSplineBox_clicked(bool checked);

private:
    // Тестовая функция
    QChart* chartTest = nullptr;

    QLineSeries* testSeries = nullptr;
    QLineSeries* testFuncSeries = nullptr;
    QLineSeries* testDSeries = nullptr;
    QLineSeries* testDFuncSeries = nullptr;
    QLineSeries* testDDSeries = nullptr;
    QLineSeries* testDDFuncSeries = nullptr;
    QLineSeries* testCompSeries = nullptr;
    QLineSeries* testCompDSeries = nullptr;
    QLineSeries* testCompDDSeries = nullptr;

    QValueAxis* testX = nullptr;
    QValueAxis* testY = nullptr;

    int testN = 5;

    // Основная функция
    QChart* chartMain = nullptr;

    QLineSeries* mainSeries = nullptr;
    QLineSeries* mainFuncSeries = nullptr;
    QLineSeries* mainDSeries = nullptr;
    QLineSeries* mainDFuncSeries = nullptr;
    QLineSeries* mainDDSeries = nullptr;
    QLineSeries* mainDDFuncSeries = nullptr;
    QLineSeries* mainCompSeries = nullptr;
    QLineSeries* mainCompDSeries = nullptr;
    QLineSeries* mainCompDDSeries = nullptr;

    QValueAxis* mainX = nullptr;
    QValueAxis* mainY = nullptr;

    int mainN = 5;

    // Осциллирующая функция
    QChart* chartOscill = nullptr;

    QLineSeries* oscillSeries = nullptr;
    QLineSeries* oscillFuncSeries = nullptr;
    QLineSeries* oscillDSeries = nullptr;
    QLineSeries* oscillDFuncSeries = nullptr;
    QLineSeries* oscillDDSeries = nullptr;
    QLineSeries* oscillDDFuncSeries = nullptr;
    QLineSeries* oscillCompSeries = nullptr;
    QLineSeries* oscillCompDSeries = nullptr;
    QLineSeries* oscillCompDDSeries = nullptr;

    QValueAxis* oscillX = nullptr;
    QValueAxis* oscillY = nullptr;

    int oscillN = 5;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
