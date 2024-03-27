#include "..\include\testSpline.h"
#include "..\include\task.h"

TestSpline::TestSpline(int _n) : n(_n)
{
    h = (b - a) / static_cast<double>(n);

    A.resize(n + 1);
    B.resize(n + 1);
    C.resize(n + 1);
    Phi.resize(n + 1);
    ai.resize(n + 1);
    bi.resize(n + 1);
    ci.resize(n + 1);
    di.resize(n + 1);
}

double TestSpline::f(double x)
{
    if (x < 0)
    {
        return f1(x);
    }
    else
    {
        return f2(x);
    }
}

double TestSpline::f1(double x)
{
    return x * x * x + 3. * x * x;
}

double TestSpline::f2(double x)
{
    return -x * x * x + 3. * x * x;
}

double TestSpline::S(int i, double x)
{
    double temp = x - static_cast<double>(i) * h;
    return ai[i] + bi[i] * temp + ci[i] * temp * temp / 2. + di[i] * temp * temp * temp / 6.;
}

double TestSpline::derS(int i, double x)
{
    double temp = x - static_cast<double>(i) * h;
    return bi[i] + ci[i] * temp + di[i] * temp * temp / 2.;
}

double TestSpline::secDerS(int i, double x)
{
    double temp = x - static_cast<double>(i) * h;
    return ci[i] + di[i] * temp;
}

double TestSpline::getMaxCompS()
{
    return maxCompS;
}

double TestSpline::getXMaxCompS()
{
    return maxXCompS;
}

double TestSpline::getMaxCompDerS()
{
    return maxCompDerS;
}

double TestSpline::getXMaxCompDerS()
{
    return maxXCompDerS;
}

double TestSpline::getMaxCompSecDerS()
{
    return maxCompSecDerS;
}

double TestSpline::getXMaxCompSecDerS()
{
    return maxXCompSecDerS;
}

void TestSpline::getSolution()
{
    A[0] = 0.;
    C[0] = 0.;
    B[0] = 0.;
    A[n] = 0.;
    B[n] = 0.;
    C[n] = 0.;
    Phi[0] = f1(a);
    Phi[n] = f2(b);
    ai[0] = f1(a);
    ai[n] = f2(b);

    for (int i = 1; i < n; i++)
    {
        A[i] = h;
        B[i] = h;
        C[i] = 2. * (h + h);
        Phi[i] = 6. * (f(a + static_cast<double>(i + 1) * h) / h
                - 2. * f(a + static_cast<double>(i) * h) / h
                + f(a + static_cast<double>(i - 1) * h) / h);
    }

    Task testSpline(n + 1);

    testSpline.setProgonka(A, B, C, Phi);
    testSpline.progonka();
    ci = testSpline.getV();

    for (int i = 1; i < n; i++)
    {
        ai[i] = f(a + static_cast<double>(i) * h);
        di[i] = (ci[i] - ci[i - 1]) / h;
        bi[i] = f(a + static_cast<double>(i) * h) / h - f(a + static_cast<double>(i - 1) * h) / h
                + ci[i] * h / 3. + ci[i - 1] * h / 6.;
    }
}

void TestSpline::getResults(QLineSeries *& graphic, QTableWidget *&koefTable, QTableWidget *&funcTable,
                            QTableWidget *&derTable, QTableWidget *&secDerTable)
{
    getSolution();

    for (int i = 1; i < n + 1; i++)
    {
        koefTable->setItem(i - 1, 0, new QTableWidgetItem(QString::number(i)));
        koefTable->setItem(i - 1, 1, new QTableWidgetItem(QString::number(a + static_cast<double>(i - 1) * h)));
        koefTable->setItem(i - 1, 2, new QTableWidgetItem(QString::number(a + static_cast<double>(i) * h)));
        koefTable->setItem(i - 1, 3, new QTableWidgetItem(QString::number(ai[i])));
        koefTable->setItem(i - 1, 4, new QTableWidgetItem(QString::number(bi[i])));
        koefTable->setItem(i - 1, 5, new QTableWidgetItem(QString::number(ci[i])));
        koefTable->setItem(i - 1, 6, new QTableWidgetItem(QString::number(di[i])));
    }

    funcTable->setRowCount(n * 5 + 1);

    for (int i = 0; i < n * 5 + 1; i++)
    {
        double x1 = a + static_cast<double>(i) * h / 5.;
        funcTable->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        funcTable->setItem(i, 1, new QTableWidgetItem(QString::number(x1)));
        funcTable->setItem(i, 2, new QTableWidgetItem(QString::number(f(x1))));
        funcTable->setItem(i, 3, new QTableWidgetItem(QString::number(S(i / n + 1, x1))));
        funcTable->setItem(i, 4, new QTableWidgetItem(QString::number(f(x1) - S(i / n + 1, x1))));
    }
}
