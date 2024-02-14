#include "./Activations.h"

double activations::functions::ReLU(const double &x) { return (x > 0 ? x : 0); }

double activations::functions::ReLU_derivative(const double &x) {
  return (x > 0 ? 1 : 0);
}

double activations::functions::Sigmoid(const double &x) {
  return (double)1 / (1 + exp(-x));
}

double activations::functions::Sigmoid_derivative(const double &x) {
  return activations::functions::Sigmoid(x) *
         (1 - activations::functions::Sigmoid(x));
}

double activations::functions::Linear(const double &x){
  return x;
}

double activations::functions::Linear_derivative(const double &x){
  return 1;
}

double activations::functions::Tanh(const double &x){
  return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

double activations::functions::Tanh_derivative(const double &x){
  return 1 - (activations::functions::Tanh(x) * activations::functions::Tanh(x));
}
