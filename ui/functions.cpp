#include "functions.h"

double functionTest(double x)
{
    if (x < 0) return x * x * x + 3. * x * x;
    else return -x * x * x + 3. * x * x;
}

double functionTestD(double x)
{
    if (x < 0) return 3. * x * x + 6. * x;
    else return -3. * x * x + 6. * x;
}

double functionTestDD(double x)
{
    if (x < 0) return 6. * x + 6.;
    else return -6. * x + 6.;
}

double functionMain(double x)
{
    return sqrt(x * x - 1.) / x;
}

double functionMainD(double x)
{
    return 1. / sqrt(x * x - 1.) / x / x;
}

double functionMainDD(double x)
{
    return -sqrt(x * x - 1.) * (3. * x * x - 2.) / (pow(x, 7.) - 2. * pow(x, 5.) + pow(x, 3.));
}

double functionOscill(double x)
{
    return sqrt(x * x - 1.) / x + cos(10. * x);
}

double functionOscillD(double x)
{
    return 1. / sqrt(x * x - 1.) / x / x - 10. * sin(10. * x);
}

double functionOscillDD(double x)
{
    return -sqrt(x * x - 1.) * (3. * x * x - 2.) / (pow(x, 7.) - 2. * pow(x, 5.) + pow(x, 3.)) - 100. *  cos(10. * x);
}
