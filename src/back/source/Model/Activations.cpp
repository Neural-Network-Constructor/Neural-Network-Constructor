#include "./Activations.h"

double activations::functions::ReLU(const double &x){
  return (x > 0 ? x : 0);
}

double activations::functions::ReLU_derivative(const double &x){
  return (x > 0 ? 1 : 0);
}
