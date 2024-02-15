#include "./FullyConnectedLayer.h"
#include <cstdlib>
#include <ctime>

FullyConnectedLayer::FullyConnectedLayer(
    const uint32_t &values_num, const std::function<double(double)> &activation,
    const std::function<double(double)> &activation_derivative,
    const double &learning_rate)
    : Layer(values_num, activation, activation_derivative, learning_rate) {
  std::srand(std::time(nullptr));
  this->biases.resize(values_num);
  this->desired_values.resize(values_num);
  this->errors.resize(values_num);
  this->values_z.resize(values_num);
}

FullyConnectedLayer::FullyConnectedLayer(
    const uint32_t &values_num, const std::function<double(double)> &activation,
    const std::function<double(double)> &activation_derivative,
    const bool &is_output, const double &learning_rate)
    : Layer(values_num, activation, activation_derivative, is_output,
            learning_rate) {
  std::srand(std::time(nullptr));
  this->biases.resize(values_num);
  this->desired_values.resize(values_num);
  this->errors.resize(values_num);
  this->values_z.resize(values_num);
}

void FullyConnectedLayer::Predict() {
  this->ClearValues();
  for (auto curr_layer : this->inputs) {
    std::vector<double> curr_layer_values = curr_layer->GetValues();
    for (uint32_t neuron_index = 0; neuron_index < this->values_num;
         ++neuron_index) {
      for (uint32_t weight_index = 0; weight_index < curr_layer->GetValuesNum();
           ++weight_index) {
        this->values[neuron_index] +=
            this->weights[curr_layer][neuron_index][weight_index] *
            curr_layer_values[weight_index];
      }
    }
  }

  for (uint32_t neuron_index = 0; neuron_index < this->values_num;
       ++neuron_index) {
    this->values[neuron_index] += this->biases[neuron_index];
    this->values_z[neuron_index] = this->values[neuron_index];
    this->values[neuron_index] = this->activation(this->values[neuron_index]);
  }
}

void FullyConnectedLayer::ConnectTo(Layer *input) {
  this->inputs.push_back(input);
  ++this->inputs_num;
  input->AddOutput(this);

  this->weights[input] = std::vector<std::vector<double>>(
      this->values_num, std::vector<double>(input->GetValuesNum()));
  // this->biases = std::vector <double>(this->values_num);

  for (auto it_neuron = this->weights[input].begin();
       it_neuron < this->weights[input].end(); ++it_neuron) {
    for (auto it_weight = it_neuron->begin(); it_weight < it_neuron->end();
         ++it_weight) {
      *it_weight = (static_cast<double>(rand()) / RAND_MAX) * 2 - 1;
    }
  }

  for (uint32_t neuron_index = 0; neuron_index < this->values_num;
       ++neuron_index) {
    this->biases[neuron_index] = static_cast<double>(rand()) / RAND_MAX;
  }
}

void FullyConnectedLayer::PrintInfo() {
  std::cout << "┍━━━━━━ FullyConnectedLayer Info ━━━━━━┑" << '\n';
  std::cout << "┝━ Values_num = " << this->values_num << '\n';
  std::cout << "┝━ Inputs_num = " << this->inputs_num << '\n';
  std::cout << "┝━ Outputs_num = " << this->outputs_num << '\n';

  for (auto curr_layer : this->inputs) {
    std::cout << "┝┯ Layer " << curr_layer << ": " << '\n';
    std::vector<double> curr_layer_values = curr_layer->GetValues();
    for (uint32_t neuron_index = 0; neuron_index < this->values_num;
         ++neuron_index) {
      std::cout << "│┕━━ ";
      for (uint32_t weight_index = 0; weight_index < curr_layer->GetValuesNum();
           ++weight_index) {
        std::cout << this->weights[curr_layer][neuron_index][weight_index]
                  << '\t';
      }
      std::cout << '\n';
    }
    // std::cout << '\n';
  }

  std::cout << "┝┯ Biases: " << '\n';
  for (uint32_t neuron_index = 0; neuron_index < this->values_num;
       ++neuron_index) {
    std::cout << "│┕━━ ";
    std::cout << this->biases[neuron_index];
    std::cout << '\n';
  }

  std::cout << "┝┯ Values: " << '\n';
  for (uint32_t neuron_index = 0; neuron_index < this->values_num;
       ++neuron_index) {
    std::cout << "│┕━━ ";
    std::cout << this->values[neuron_index];
    std::cout << '\n';
  }

  std::cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙" << '\n';
}

void FullyConnectedLayer::SetDesiredValues(
    const std::vector<double> &desired_values) {
  if (desired_values.size() != this->values_num) {
    throw std::logic_error("[FullyConnectedLayer::SetValues()]  desired_values "
                           "size != values_num");
  }

  for (uint32_t i = 0; i < this->values_num; ++i) {
    this->desired_values[i] = desired_values[i];
  }
}

void FullyConnectedLayer::Learn() {
  double total_error = 0;
  if (this->is_output) {
    for (uint32_t neuron_index = 0; neuron_index < this->values_num;
         ++neuron_index) {
      this->errors[neuron_index] =
          (this->values[neuron_index] - this->desired_values[neuron_index]);
      total_error += this->errors[neuron_index];
    }
  } else {
    total_error = this->error;
  }
  for (uint32_t neuron_index = 0; neuron_index < this->values_num;
       ++neuron_index) {
    for (Layer *curr_layer : this->inputs) {
      std::vector<double> prev_layer_values = curr_layer->GetValues();
      for (uint32_t weight_index = 0; weight_index < prev_layer_values.size();
           ++weight_index) {
        double d_weight =
            // this->errors[neuron_index] *
            total_error *
            this->activation_derivative(this->values_z[neuron_index]) *
            prev_layer_values[weight_index];
        this->weights[curr_layer][neuron_index][weight_index] -=
            d_weight * this->learning_rate;

        curr_layer->error +=
            this->errors[neuron_index] *
            this->activation_derivative(this->values_z[neuron_index]) *
            this->weights[curr_layer][neuron_index][weight_index];
      }
    }
    double d_bias =
        total_error * this->activation_derivative(this->values_z[neuron_index]);
    this->biases[neuron_index] -= d_bias * this->learning_rate;
  }

  this->error = 0;
  // std::cout << "сам обучись сука \t"
  //           << "error = " << total_error << " / " << this->desired_values[0]
  //           << ' ' << this->values[0] << '\n';
}
