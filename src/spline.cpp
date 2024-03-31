#include "..\include\spline.h"
#include "..\include\task.h"

Spline::Spline(int numberPartitions,
               double leftBorder,
               double middleBorder,
               double rightBorder) : n(numberPartitions), a(leftBorder), c(middleBorder), b(rightBorder)

{
    h = (b - a) / static_cast<double>(n);
    ai.resize(n + 1);
    bi.resize(n + 1);
    ci.resize(n + 1);
    di.resize(n + 1);
}

void Spline::solution(double (*f)(double))
{
    std::vector<double> A(n + 1);             // Для прогонки
    std::vector<double> B(n + 1);             // Для прогонки
    std::vector<double> C(n + 1);             // Для прогонки
    std::vector<double> Phi(n + 1);           // Для прогонки


    A[0] = 0.;
    C[0] = 0.;
    B[0] = 0.;
    A[n] = 0.;
    B[n] = 0.;
    C[n] = 0.;
    Phi[0] = 0.;
    Phi[n] = 0.;

    for (int i = 1; i < n; i++)
    {
        A[i] = h;
        B[i] = h;
        C[i] = 4. * h;
        Phi[i] = 6. * (f(a + static_cast<double>(i + 1) * h) / h -
                       2. * f(a + static_cast<double>(i) * h) / h +
                       f(a + static_cast<double>(i - 1) * h) / h);
    }

    Task testSpline(n + 1);

    testSpline.setProgonka(A, B, C, Phi);
    testSpline.progonka();
    ci = testSpline.getV();

    for (int i = 1; i <= n; i++)
    {
        ai[i] = f(a + static_cast<double>(i) * h);
        di[i] = ci[i] / h - ci[i - 1] / h;
        bi[i] = f(a + static_cast<double>(i) * h) / h - f(a + static_cast<double>(i - 1) * h) / h +
                ci[i] * h / 3. + ci[i - 1] * h / 6.;
    }
}

double Spline::S(int i, double x)
{
    double res = x - (a + static_cast<double>(i) * h);
    return ai[i] + bi[i] * res + ci[i] * pow(res, 2.) + di[i] * pow(res, 3.);
}

double Spline::dS(int i, double x)
{
    double res = x - (a + static_cast<double>(i) * h);
    return bi[i] + ci[i] * res + di[i] * pow(res, 2.);
}

double Spline::ddS(int i, double x)
{
    double res = x - (a + static_cast<double>(i) * h);
    return ci[i] + di[i] * res;
}

inline std::vector<double> Spline::getai()
{
    return ai;
}

inline std::vector<double> Spline::getbi()
{
    return bi;
}

inline std::vector<double> Spline::getci()
{
    return ci;
}

inline std::vector<double> Spline::getdi()
{
    return di;
}
