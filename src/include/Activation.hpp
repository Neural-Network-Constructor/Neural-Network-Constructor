#include <functional>
#include <vector>

#ifndef ACTIVATION_H
#define ACTIVATION_H

// Функции активации, необходимые для преобразования, поэлеметно применяющегося к пришедшим на вход данным, и их производные
double Sigmoid(double x);
double SigmoidDerivative(double x);
double Relu(double x);
double ReluDerivative(double x);
double Tanh(double x);
double TanhDerivative(double x);
double Softmax(std::vector<double> z, double i);
double SoftmaxDerivative(std::vector<double> z, double i);

#endif