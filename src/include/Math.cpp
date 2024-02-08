#include "Math.hpp"
#include "Const.hpp"

double Derivative(std::function<double(double)> f, double x)
{
    return (f(x + Const::difference_step) - f(x - Const::difference_step)) / (2 * Const::difference_step);
}