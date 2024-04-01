#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>

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

    void on_clearMainTask_clicked();

    void on_showDotsMain_clicked(bool checked);

    void on_startMainTask_clicked();

    void on_numberMain_editingFinished();

    void on_clearOscillTask_clicked();

    void on_showDotsOscill_clicked(bool checked);

    void on_numberOscill_editingFinished();

    void on_startOscillTask_clicked();

    void on_testFuncBox_clicked(bool checked);

    void on_testSplineBox_clicked(bool checked);

    void testClear();

    void on_testComboBox_currentIndexChanged(int index);

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
    QValueAxis* mainX = nullptr;
    QValueAxis* mainY = nullptr;

    int mainN = 5;

    // Осциллирующая функция
    QChart* chartOscill = nullptr;
    QLineSeries* oscillSeries = nullptr;
    QValueAxis* oscillX = nullptr;
    QValueAxis* oscillY = nullptr;

    int oscillN = 5;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
