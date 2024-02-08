#include <functional>
#include <vector>

#ifndef ACTIVATION_H
#define ACTIVATION_H

double Sigmoid(double x);
double Relu(double x);
double Tanh(double x);
std::vector<double> Softmax(std::vector<double> z);

#endif