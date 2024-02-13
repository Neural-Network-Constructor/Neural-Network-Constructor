#pragma once

#include "./Layer.h"
#include <map>

class FullyConnectedLayer : public Layer {
private:
  // std::vector <double> weights;
  // std::vector <double> biases;
  std::map <Layer*, std::vector <std::vector <double>>> weights;
  std::vector <double> biases;
  std::vector<double> desired_values; // Требуемые значения нейронов в слое
  std::vector<double> errors;  

public:
  FullyConnectedLayer(const uint32_t &, const std::function<double(double)> &, const std::function<double(double)> &);
  FullyConnectedLayer(const uint32_t &, const std::function<double(double)> &, const std::function<double(double)> &, const bool &);
  
  void Predict();

  void Learn();

  // Создает связь между слоем и его входом
  // (вызывается из экземляра слоя и передается входной слой)
  // а также инициализирует все гиперпараметры для обучения
  virtual void ConnectTo(Layer *);

  void PrintInfo();
};
