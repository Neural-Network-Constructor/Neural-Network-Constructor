#include "./Model/Activations.h"
#include "./Model/FullyConnectedLayer.h"
#include "./Model/InputLayer.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
  // FullyConnectedLayer fcn(5, 2);
  // fcn.Predict();

  const int danya_loh = 100000;

  InputLayer in(2);
  // FullyConnectedLayer fcl1(3, activations::ReLU,
  //                          activations::ReLU_derivative, 0, 0.03);
  // FullyConnectedLayer fcl2(1, activations::ReLU,
  //                          activations::ReLU_derivative, 1, 0.03);
  FullyConnectedLayer fcl1(5, activations::Sigmoid,
                           activations::Sigmoid_derivative, 0, 0.3);
  FullyConnectedLayer fcl15(5, activations::Sigmoid,
                            activations::Sigmoid_derivative, 0, 0.3);
  FullyConnectedLayer fcl2(1, activations::Sigmoid,
                           activations::Sigmoid_derivative, 1, 0.3);

  fcl1.ConnectTo(&in);
  fcl15.ConnectTo(&fcl1);
  fcl2.ConnectTo(&fcl15);

  // fcl2.ConnectTo(&in);

  std::vector<std::vector<double>> values_in;
  std::vector<std::vector<double>> values_out;

  for (int i = 0; i < danya_loh; ++i) {
    double x = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10 + 1;
    double y = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10 + 1;
    double ans;

    if (0.25 * x - y + 1 >= 0) {
      ans = 1;
    } else {
      ans = 0;
    }

    values_in.push_back({x, y});
    values_out.push_back({ans});
  }

  for (int i = 0; i < danya_loh; ++i) {
    in.SetValues(values_in[i]);
    fcl1.Predict();
    fcl15.Predict();
    fcl2.Predict();

    fcl2.SetDesiredValues(values_out[i]);

    fcl2.Learn();
    fcl15.Learn();
    fcl1.Learn();
  }

  std::cout << "------" << '\n';

  int true_answers = 0;
  for (int i = 0; i < danya_loh; ++i) {
    in.SetValues(values_in[i]);
    fcl1.Predict();
    fcl15.Predict();
    fcl2.Predict();

    std::vector<double> res = fcl2.GetValues();
    std::cout << values_in[i][0] << " " << values_in[i][1] << "\t"
              << values_out[i][0] << " " << res[0] << '\n';
    if ((res[0] >= 0.5 && values_out[i][0] == 1) ||
        (res[0] <= 0.5 && values_out[i][0] == 0)) {
      ++true_answers;
    }
  }

  std::cout << "------" << '\n';

  std::cout << "Correct: " << true_answers << "/" << danya_loh << '\n';

  // fcl1.Predict();

  std::cout << "IN: " << '\n';
  in.PrintInfo();
  std::cout << "\n\n";

  std::cout << "FCL_1: " << '\n';
  fcl1.PrintInfo();
  std::cout << "\n\n";

  std::cout << "FCL_15: " << '\n';
  fcl15.PrintInfo();
  std::cout << "\n\n";

  std::cout << "FCL_2: " << '\n';
  fcl2.PrintInfo();
  std::cout << "\n\n";

  int t = 0;
  for (int i = 0; i < danya_loh; ++i) {
    // std::cout << values_in[i][0] << " " << values_in[i][1] << " -> " <<
    // values_out[i][0] << '\n';
    t += (values_out[i][0] == 1);
  }
  std::cout << t << " " << danya_loh - t;

  return 0;
}
