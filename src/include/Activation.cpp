#include "activation.hpp"

#include <algorithm>
#include <cmath>

double Sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}
double Relu(double x)
{
    return std::max(0., x);
}
double Tanh(double x)
{
    return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
}
std::vector<double> Softmax(std::vector<double> z)
{
    int K = z.size();
    std::vector<double> softmax(z.size(), 0);
    double Sigma = 0;
    for (int i = 0; i < K; ++i)
    {
        Sigma += std::exp(z[i]);
    }
    for (int i = 0; i < K; ++i)
    {
        softmax[i] = std::exp(z[i] / Sigma);
    }
}