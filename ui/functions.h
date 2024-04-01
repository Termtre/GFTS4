#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

double testFunc(double x)
{
    if (x < 0) return x * x * x + 3. * x * x;
    else return -x * x * x + 3. * x * x;
}

double testDFunc(double x)
{
    if (x < 0) return 3. * x * x + 6. * x;
    else return -3. * x * x + 6. * x;
}

double testDDFunc(double x)
{
    if (x < 0) return 6. * x + 6.;
    else return -6. * x + 6.;
}

double mainFunc(double x)
{
    return sqrt(x * x - 1.) / x;
}

double mainDFunc(double x)
{
    return 1. / sqrt(x * x - 1.) / x / x;
}

double mainDDFunc(double x)
{
    return -sqrt(x * x - 1.) * (3. * x * x - 2.) / (pow(x, 7.) - 2. * pow(x, 5.) + pow(x, 3.));
}

double oscillFunc(double x)
{
    return sqrt(x * x - 1.) / x + cos(10. * x);
}

double oscillDFunc(double x)
{
    return 1. / sqrt(x * x - 1.) / x / x - 10. * sin(10. * x);
}

double oscillDDFunc(double x)
{
    return -sqrt(x * x - 1.) * (3. * x * x - 2.) / (pow(x, 7.) - 2. * pow(x, 5.) + pow(x, 3.)) - 100. *  cos(10. * x);
}

#endif // FUNCTIONS_H
