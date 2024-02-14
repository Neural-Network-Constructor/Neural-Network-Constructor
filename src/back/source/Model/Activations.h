#pragma once

#include <cmath>
#include <functional>

namespace activations{

namespace functions {
double Linear(const double &);
double Linear_derivative(const double &);
double ReLU(const double &);
double ReLU_derivative(const double &);
double Sigmoid(const double &);
double Sigmoid_derivative(const double &);
double Tanh(const double &);
double Tanh_derivative(const double &);
}

const std::function<double(double)> ReLU = functions::ReLU;
const std::function<double(double)> ReLU_derivative = functions::ReLU_derivative;
const std::function<double(double)> Sigmoid = functions::Sigmoid;
const std::function<double(double)> Sigmoid_derivative = functions::Sigmoid_derivative;
const std::function<double(double)> Linear = functions::Linear;
const std::function<double(double)> Linear_derivative = functions::Linear_derivative;
const std::function<double(double)> Tanh = functions::Tanh;
const std::function<double(double)> Tanh_derivative = functions::Tanh_derivative;

}
