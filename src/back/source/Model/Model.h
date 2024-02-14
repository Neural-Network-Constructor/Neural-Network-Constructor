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

  std::map<void *, Layer *> layers;

public:
  Model(const std::map<void *, std::pair<std::vector<void *>, bool>> &,
        const std::map<void *, uint8_t> &, const std::map<void *, uint32_t> &,
        const std::map<void *, bool> &, const double &, const std::string &,
        const std::string &);
};
