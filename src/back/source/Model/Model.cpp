#include "./Model.h"
#include "Activations.h"
#include "FullyConnectedLayer.h"
#include "InputLayer.h"
#include <utility>

Model::Model(
    const std::map<void *, std::pair<std::vector<void *>, bool>> &graph,
    const std::map<void *, uint8_t> &activations_ints,
    const std::map<void *, uint32_t> &values_nums,
    const std::map<void *, bool> &is_input, const double &learning_rate,
    const std::string &train_data, const std::string &test_data) {
  this->graph = graph;
  this->values_nums = values_nums;
  this->is_input = is_input;

  this->learning_rate = learning_rate;
  this->test_data_file_path = test_data;
  this->train_data_file_path = train_data;

  for (auto curr_activation : activations_ints) {
    if (curr_activation.second == 1) {
      this->activations[curr_activation.first] =
          std::make_pair(activations::ReLU, activations::ReLU_derivative);
    } else if (curr_activation.second == 2) {
      this->activations[curr_activation.first] =
          std::make_pair(activations::Sigmoid, activations::Sigmoid_derivative);
    } else if (curr_activation.second == 3) {
      this->activations[curr_activation.first] =
          std::make_pair(activations::Tanh, activations::Tanh_derivative);
    } else {
      std::cerr << "[Model::Model] Некорректный идентификатор функции активации"
                << '\n';
    }
  }

  for (auto curr_layer : graph) {
    if (this->is_input[curr_layer.first] == 1) {
      layers[curr_layer.first] =
          new InputLayer(this->values_nums[curr_layer.first]);
    } else {
      layers[curr_layer.first] =
          new FullyConnectedLayer(this->values_nums[curr_layer.first],
                                  this->activations[curr_layer.first].first,
                                  this->activations[curr_layer.first].second,
                                  this->graph[curr_layer.first].second, this->learning_rate);
    }
  }

  for (auto layer_from : graph) {
    for (auto layer_to : this->graph[layer_from.first].first) {
      this->layers[layer_to]->AddOutput(this->layers[layer_from.first]);
    }
  }

}
