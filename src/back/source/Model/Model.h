#pragma once

#include "./Activations.h"
#include "./FullyConnectedLayer.h"
#include "./InputLayer.h"
#include "./Layer.h"

#include <map>
#include <string>
#include <vector>

class Model {
private:
  std::map<void *, std::pair<std::vector<void *>, bool>> graph;
  std::map<void *, std::pair<std::function<double(double)>,
                             std::function<double(double)>>>
      activations;
  std::map<void *, uint32_t> values_nums;
  std::map<void *, bool> is_input;

  double learning_rate;
  std::string train_data_file_path;
  std::string test_data_file_path;

  std::vector<void *> layers_ids;

  std::map<void *, Layer *> layers;

  Layer* input_layer;
  Layer* output_layer;

  std::vector <Layer*> forward_propogation_list;
  std::vector <Layer*> backward_propogation_list;


  std::vector <Layer*> Dfs(const std::map<Layer *, std::vector<Layer *>> &, Layer*);


public:
  Model(const std::map<void *, std::pair<std::vector<void *>, bool>> &,
        const std::map<void *, uint8_t> &, const std::map<void *, uint32_t> &,
        const std::map<void *, bool> &, const double &, const std::string &,
        const std::string &);

  void ForwardDfs();
  void BackwardDfs();

  void SetValues(const std::vector <double> &);
  void SetDesiredValues(const std::vector <double> &);

  void Predict();

  void Learn();

  void TEST_function();
};
