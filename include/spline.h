#ifndef SPLINE_H
#define SPLINE_H

#include <QLineSeries>
#include <QTableWidget>
#include <vector>

class Spline
{
private:
    int n;//Количество разбиений
    double a;// левая граница
    double c;// промежуток
    double b;// правая граница
    double h;// шаг

    std::vector<double> ai, bi, ci, di;// коэффициенты сплайна

public:
    Spline(int, double, double, double);
    ~Spline() {}

    void solution(double (*f)(double));// расчет коэффициентов
    double S(int i, double x);// функция сплайна
    double dS(int, double);// функция первой производной сплайна
    double ddS(int, double);// функция второй производной сплайна
    std::vector<double> getAi();
    std::vector<double> getBi();
    std::vector<double> getCi();
    std::vector<double> getDi();
};

#endif // SPLINE_H
