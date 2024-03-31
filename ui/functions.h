#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

double testFunc(double x)
{
    if (x < 0) return x * x * x + 3. * x * x;
    else return -x * x * x + 3. * x * x;
}

double mainFunc(double x)
{
    return sqrt(x * x - 1.) / x;
}

double oscillFunc(double x)
{
    return sqrt(x * x - 1.) / x + cos(10. * x);
}

#endif // FUNCTIONS_H
