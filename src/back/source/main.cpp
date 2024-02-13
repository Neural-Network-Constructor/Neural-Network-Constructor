#include "./Model/Activations.h"
#include "./Model/FullyConnectedLayer.h"
#include "./Model/InputLayer.h"
#include <iostream>

int main() {
  // FullyConnectedLayer fcn(5, 2);
  // fcn.Predict();

  InputLayer in1(1);
  InputLayer in2(2);
  FullyConnectedLayer fcl1(2, activations::ReLU, activations::ReLU_derivative,
                           1);

  fcl1.ConnectTo(&in1);
  fcl1.ConnectTo(&in2);

  std::vector<double> values_in_0 = {.4};
  std::vector<double> values_in_1 = {1.43, -.6};
  in1.SetValues(values_in_0);
  in2.SetValues(values_in_1);

  fcl1.Predict();

  std::cout << "IN_1: " << '\n';
  in1.PrintInfo();
  std::cout << "\n\n";

  std::cout << "IN_2: " << '\n';
  in2.PrintInfo();
  std::cout << "\n\n";

  std::cout << "FCL_1: " << '\n';
  fcl1.PrintInfo();
  std::cout << "\n\n";

  std::vector<double> values_out_0 = fcl1.GetValues();
  for (auto el : values_out_0) {
    std::cout << el << ' ';
  }

  return 0;
}
