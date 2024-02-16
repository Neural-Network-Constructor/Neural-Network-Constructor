#pragma once

#include "./Layer.h"
#include <map>

class FullyConnectedLayer : public Layer {
public:
  FullyConnectedLayer(const uint32_t &, const std::function<double(double)> &,
                      const std::function<double(double)> &, const double &);
  FullyConnectedLayer(const uint32_t &, const std::function<double(double)> &,
                      const std::function<double(double)> &, const bool &,
                      const double &);

  void Predict() override;

  void Learn() override;

  void SetDesiredValues(const std::vector<double> &) override;

  // Создает связь между слоем и его входом
  // (вызывается из экземляра слоя и передается входной слой)
  // а также инициализирует все гиперпараметры для обучения
  void ConnectTo(Layer *) override;

  void PrintInfo() override;

  State GetState() override;

  // void CalulateLoss(const std::vector<std::vector<double>> &inputs,
  //                   const std::vector<std::vector<double>> &outputs) {
  //   if (inputs.size() != outputs.size()) {
  //     std::cerr << "В FullyConnectedLayer::CalulateLoss переданы уебские "
  //                  "данные (не совпадают размеры inputs и outputs)"
  //               << '\n';
  //   }
  //   int size = inputs.size();
  //   double sum = 0;
  //   for (int test = 0; test < size; ++test){
  //     
  //   }
  // }

private:
    std::map<Layer *, std::vector<std::vector<double>>> weights;
    std::vector<double> biases;
    std::vector<double> desired_values; // Требуемые значения нейронов в слое
    std::vector<double> errors;
    std::vector<double> values_z;

    std::vector<double> losses;

};
