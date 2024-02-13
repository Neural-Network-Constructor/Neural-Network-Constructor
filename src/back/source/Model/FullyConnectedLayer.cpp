#include "./FullyConnectedLayer.h"
#include <cstdlib>
#include <ctime>


FullyConnectedLayer::FullyConnectedLayer(const uint32_t &values_num, const std::function<double(double)> &activation, const std::function<double(double)> &activation_derivative)
    : Layer(values_num, activation, activation_derivative){
  std::srand(std::time(nullptr));
  this->biases.resize(values_num);
  this->desired_values.resize(values_num);
  this->errors.resize(values_num);
}

FullyConnectedLayer::FullyConnectedLayer(const uint32_t &values_num, const std::function<double(double)> &activation, const std::function<double(double)> &activation_derivative, const bool &is_output)
    : Layer(values_num, activation, activation_derivative, is_output){
  std::srand(std::time(nullptr));
  this->biases.resize(values_num);
  this->desired_values.resize(values_num);
  this->errors.resize(values_num);
}

void FullyConnectedLayer::Predict(){
  this->ClearValues();
  for (auto curr_layer : this->inputs){
    std::vector <double> curr_layer_values = curr_layer->GetValues();
    for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
      for (uint32_t weight_index = 0; weight_index < curr_layer->GetValuesNum(); ++weight_index){
        this->values[neuron_index] += this->weights[curr_layer][neuron_index][weight_index] * curr_layer_values[weight_index];
      }
    }
  }

  for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
    this->values[neuron_index] += this->biases[neuron_index];
    this->values[neuron_index] = this->activation(this->values[neuron_index]);
  }
}

void FullyConnectedLayer::ConnectTo(Layer *input){
  this->inputs.push_back(input);
  ++this->inputs_num;
  input->AddOutput(this);

  this->weights[input] = std::vector <std::vector <double>>(this->values_num, std::vector <double>(input->GetValuesNum()));
  // this->biases = std::vector <double>(this->values_num);

  for (auto it_neuron = this->weights[input].begin(); it_neuron < this->weights[input].end(); ++it_neuron){
    for (auto it_weight = it_neuron->begin(); it_weight < it_neuron->end(); ++it_weight){
      *it_weight = static_cast<double>(rand()) / RAND_MAX;
    }
  }

  for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
    this->biases[neuron_index] = static_cast<double>(rand()) / RAND_MAX;
  }
}

void FullyConnectedLayer::PrintInfo() {
  std::cout << "┍━━━━━━ FullyConnectedLayer Info ━━━━━━┑" << '\n';
  std::cout << "┝━ Values_num = " << this->values_num << '\n';
  std::cout << "┝━ Inputs_num = " << this->inputs_num << '\n';
  std::cout << "┝━ Outputs_num = " << this->outputs_num << '\n';

  for (auto curr_layer : this->inputs){
    std::cout << "┝┯ Layer " << curr_layer << ": " << '\n';
    std::vector <double> curr_layer_values = curr_layer->GetValues();
    for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
      std::cout << "│┕━━ ";
      for (uint32_t weight_index = 0; weight_index < curr_layer->GetValuesNum(); ++weight_index){
        std::cout << this->weights[curr_layer][neuron_index][weight_index] << '\t';
      }
      std::cout << '\n';
    }
    // std::cout << '\n';
  }

  std::cout << "┝┯ Biases: " << '\n';
  for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
    std::cout << "│┕━━ ";
    std::cout << this->biases[neuron_index];
    std::cout << '\n';
  }

  std::cout << "┝┯ Values: " << '\n';
  for (uint32_t neuron_index = 0; neuron_index < this->values_num; ++neuron_index){
    std::cout << "│┕━━ ";
    std::cout << this->values[neuron_index];
    std::cout << '\n';
  }

  std::cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << '\n';
}


