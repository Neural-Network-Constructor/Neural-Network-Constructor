#include "./Model.h"
#include "Activations.h"
#include "FullyConnectedLayer.h"
#include "InputLayer.h"
#include "Layer.h"
#include <list>
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
      this->layers[curr_layer.first] =
          new InputLayer(this->values_nums[curr_layer.first]);
      this->input_layer = this->layers[curr_layer.first];
    } else {
      this->layers[curr_layer.first] = new FullyConnectedLayer(
          this->values_nums[curr_layer.first],
          this->activations[curr_layer.first].first,
          this->activations[curr_layer.first].second,
          this->graph[curr_layer.first].second, this->learning_rate);
    }
  }

  for (auto layer_from : this->graph) {
    this->layers_ids.push_back(layer_from.first);
  }

  for (void *from_layer_id : this->layers_ids) {
    std::cout << from_layer_id << ": " << '\n';
    std::vector<void *> to_layers = this->graph[from_layer_id].first;
    for (void *to_layer_id : to_layers) {
      std::cout << "\t" << from_layer_id << " > " << to_layer_id << '\n';
      if (this->graph.count(to_layer_id) != 0) {
        this->layers[to_layer_id]->ConnectTo(this->layers[from_layer_id]);
      } else {
        this->output_layer = this->layers[from_layer_id];
      }
    }
  }

  for (auto curr_layer : this->layers) {
    curr_layer.second->PrintInfo();
    std::cout << "\n\n";
  }

  this->TEST_function();
}

void Model::SetValues(const std::vector<double> &values) {
  this->input_layer->SetValues(values);
}

void Model::SetDesiredValues(const std::vector<double> &values) {
  this->output_layer->SetDesiredValues(values);
}

void Model::ForwardDfs() {
  std::map<Layer *, std::vector<Layer *>> graph;


  for (void *from_layer_id : this->layers_ids) {
    std::vector<void *> to_layers = this->graph[from_layer_id].first;
    for (void *to_layer_id : to_layers) {
      if (this->graph.count(to_layer_id) != 0) {
        graph[this->layers[to_layer_id]].push_back(this->layers[from_layer_id]);
      }
    }
  }

  this->forward_propogation_list = this->Dfs(graph, this->output_layer);

}

void Model::BackwardDfs() {
  std::map<Layer *, std::vector<Layer *>> graph;

  for (void *from_layer_id : this->layers_ids) {
    std::vector<void *> to_layers = this->graph[from_layer_id].first;
    for (void *to_layer_id : to_layers) {
      if (this->graph.count(to_layer_id) != 0) {
        graph[this->layers[from_layer_id]].push_back(this->layers[to_layer_id]);
      }
    }
  }

  this->backward_propogation_list = this->Dfs(graph, this->input_layer);
}

std::vector<Layer *>
Model::Dfs(const std::map<Layer *, std::vector<Layer *>> &graph, Layer *from) {
  std::map<Layer *, bool> used;
  std::vector<Layer *> result;

  for (void *curr : this->layers_ids) {
    used[this->layers[curr]] = 0;
  }

  std::list<Layer *> q;

  used[from] = 1;
  q.push_back(from);

  while (!q.empty()) {
    Layer *v = q.front();
    q.pop_front();
    result.push_back(v);

    if (graph.count(v) != 0) {
      for (Layer *u : graph.at(v)) {
        if (!used[u]) {
          used[u] = 1;
          q.push_back(u);
        }
      }
    }
  }

  return result;
}

void Model::Predict() {
  for (auto curr = this->forward_propogation_list.begin();
       curr < this->forward_propogation_list.end(); ++curr) {
    (*curr)->Predict();
  }
}

void Model::Learn() {
  for (auto curr = this->backward_propogation_list.begin();
       curr < this->backward_propogation_list.end(); ++curr) {
    (*curr)->Learn();
  }
}

void Model::TEST_function() {
  this->ForwardDfs();
  this->BackwardDfs();

  int q = 500;

  std::vector<std::vector<double>> values_in;
  std::vector<std::vector<double>> values_out;

  for (int i = 0; i < q; ++i) {
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

  for (int i = 0; i < q; ++i) {
    this->SetValues(values_in[i]);
    this->Predict();

    // std::cout << values_out[i][0] << ": " << this->output_layer->GetValues()[0] << '\n';
    std::cout << (values_out[i][0] - this->output_layer->GetValues()[0]) * (values_out[i][0] - this->output_layer->GetValues()[0]) << '\n';

    this->SetDesiredValues(values_out[i]);
    this->Learn();
  }
}
