#pragma once

#include <cmath>
#include <functional>

namespace activations{

namespace functions {
double ReLU(const double &);
double ReLU_derivative(const double &);
}

const std::function<double(double)> ReLU = functions::ReLU;
const std::function<double(double)> ReLU_derivative = functions::ReLU_derivative;

}
