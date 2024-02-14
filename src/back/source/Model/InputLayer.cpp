#include "./InputLayer.h"
#include "./Activations.h"
#include <stdexcept>

InputLayer::InputLayer(const uint32_t &values_num, const bool &is_output)
  : Layer(values_num, activations::ReLU, activations::ReLU_derivative, is_output, 0) {}

InputLayer::InputLayer(const uint32_t &values_num)
  : Layer(values_num, activations::ReLU, activations::ReLU_derivative, 0) {}

void InputLayer::SetValues(const std::vector <double> &values){
  if (values.size() != this->values_num){
    throw std::logic_error("[InputLayer::SetValues()]  values size != values_num");
  }

  for (uint32_t i = 0; i < this->values_num; ++i){
    this->values[i] = values[i];
  }
}

void InputLayer::PrintInfo() {
  std::cout << "┍━━━━━━━━━━ InputLayer Info ━━━━━━━━━━┑" << '\n';
  std::cout << "┝━ Values_num = " << this->values_num << '\n';
  std::cout << "┝━ Outputs_num = " << this->outputs_num << '\n';

  std::cout << "┝┯ Values: " << '\n';
  for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
    std::cout << "│┕━━ ";
    std::cout << this->values[neuron_index];
    std::cout << '\n';
  }

  std::cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << '\n';
}
