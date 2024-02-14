#include "Activation.hpp"

#include <algorithm>
#include <cmath>

double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}
double SigmoidDerivative(double x)
{
    double sigma = Sigmoid(x);
    return sigma * (1 - sigma);
}

double Relu(double x)
{
    return std::max(0., x);
}
double ReluDerivative(double x)
{
    return x > 0 ? 1 : 0;
}

double Tanh(double x)
{
    return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
}
double TanhDerivative(double x)
{
    double sigma = Tanh(x);
    return 1 - sigma * sigma;
}

double Softmax(std::vector<double> z, double i)
{
    int K = z.size();
    double Sigma = 0;
    for (int j = 0; j < K; ++j)
    {
        Sigma += std::exp(z[j]);
    }
    return std::exp(z[i]) / Sigma;
}
double SoftmaxDerivative(double x)
{
    return x * (1 - x);
}