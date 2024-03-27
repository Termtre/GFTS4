#ifndef TESTSPLINE_H
#define TESTSPLINE_H

#include <QLineSeries>
#include <QTableWidget>
#include <vector>

class TestSpline
{
private:
    int n;//Количество узлов
    double maxCompS;//Максимальная разность между функцией и сплайном
    double maxXCompS;//x, при котором максимальная разность между функцией и сплайном
    double maxCompDerS;//Максимальная разность между производной функции и производной сплайна
    double maxXCompDerS;//x, при котором аксимальная разность между производной функции и производной сплайна
    double maxCompSecDerS;//Максимальная разность между второй производной функции и второй производной сплайна
    double maxXCompSecDerS;//x, при котором максимальная разность между второй производной функции и второй производной сплайна

    double a = -1.;// левая граница
    double c = 0.;// промежуток
    double b = 1.;// правая граница
    double h;// шаг

    std::vector<double> A, B, C, Phi;
    std::vector<double> ai, bi, ci, di;

private:
    double f(double x);
    double f1(double x);
    double f2(double x);
    double derf(double x);
    double secDerf(double x);

    double S(int i, double x);
    double derS(int i, double x);
    double secDerS(int i, double x);

    void getSolution();

public:
    TestSpline(int _n);
    ~TestSpline() {}

    double getMaxCompS();
    double getXMaxCompS();
    double getMaxCompDerS();
    double getXMaxCompDerS();
    double getMaxCompSecDerS();
    double getXMaxCompSecDerS();
    void getResults(QLineSeries*&, QTableWidget*& koefTable,
                    QTableWidget*& funcTable, QTableWidget*& derTable,
                    QTableWidget*& secDerTable);
};

#endif // TESTSPLINE_H
