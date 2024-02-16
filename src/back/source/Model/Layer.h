#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
#include "./State.h"

class Layer {
public:
  double error = 0;
  double loss = 0;

  Layer() = default;
  ~Layer() = default;

  // Конструктор от количества нейронов в слое, функции активации и ее
  // производной
  Layer(const uint32_t &, const std::function<double(double)> &,
        const std::function<double(double)> &, const double &);
  // Конструктор от количества нейронов в слое, функции активации, ее
  // производной, и переменной, которая показывает является ли слой выходным
  Layer(const uint32_t &, const std::function<double(double)> &,
        const std::function<double(double)> &, const bool &, const double &);

  // Функция, которая считает значения нейронов в слое и сохраняет их в values
  virtual void Predict();
  
  virtual void Learn();

  // Зануление значений нейронов в слое
  virtual void ClearValues();

  virtual void PrintInfo();
  
  virtual void SetValues(const std::vector <double> &);
  virtual void SetDesiredValues(const std::vector <double> &);

  // Геттер для values
  virtual std::vector<double> GetValues();

  // Создает связь между слоем и его входом
  // (вызывается из экземляра слоя и передается входной слой)
  // а также инициализирует все гиперпараметры для обучения
  virtual void ConnectTo(Layer *);

  uint32_t GetValuesNum() const;

  // Создает связь между слоем и его выходом
  // (вызывается из экземляра слоя и передается выходной слой)
  virtual void AddOutput(Layer *);

  virtual State GetState() {};

protected:
    bool is_output = 0;       // Яваляется ли слой выходным
    uint32_t inputs_num = 0;  // Количество входный слоев
    uint32_t outputs_num = 0; // Количество выходный слоев
    uint32_t values_num = 0;  // Количество нейронов в слое
    std::vector<Layer *> inputs; // Указатели на входные слои
    std::vector<Layer *> outputs; // Указатели на выходные слои
    std::vector<double> values; // Значения нейронов в слое
    std::function<double(double)> activation; // Функция активации
    std::function<double(double)>
            activation_derivative; // Приозводная функции активации
    double learning_rate;
};
