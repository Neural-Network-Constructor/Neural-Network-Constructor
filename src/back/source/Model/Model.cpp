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
  this->train_data_file_path = train_data;
  this->train_data.open(train_data);
  this->test_data_file_path = test_data;
  this->test_data.open(test_data);

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

//  this->TEST_function();
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

  this->forward_propagation_list = this->Dfs(graph, this->output_layer);

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

  this->backward_propagation_list = this->Dfs(graph, this->input_layer);
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
  for (auto curr = this->backward_propagation_list.begin();
       curr < this->backward_propagation_list.end(); ++curr) {
//      std::cout << "Predict (" << *curr << ")" << '\n';
      (*curr)->Predict();
  }
}

void Model::Learn() {
  for (auto curr = this->forward_propagation_list.begin();
       curr < this->forward_propagation_list.end(); ++curr) {
//      std::cout << "Learn (" << *curr << ")" << '\n';
      (*curr)->Learn();
  }
}

//void Model::TEST_function() {
//  this->ForwardDfs();
//  this->BackwardDfs();
//
//  int q = 40000;
//
//  std::vector<std::vector<double>> values_in;
//  std::vector<std::vector<double>> values_out;
//
//  for (int i = 0; i < q; ++i) {
//    double x = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10 + 1;
//    double y = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10 + 1;
//    double ans;
//
//    if (0.25 * x - y + 1 >= 0) {
//      ans = 1;
//    } else {
//      ans = 0;
//    }
//
//    values_in.push_back({x, y});
//    values_out.push_back({ans});
//  }
//
//  for (int i = 0; i < q; ++i) {
//    this->SetValues(values_in[i]);
//    this->Predict();
//
//    // std::cout << values_out[i][0] << ": " << this->output_layer->GetValues()[0] << '\n';
////    std::cout << i << "/" << q << ": " << (values_out[i][0] - this->output_layer->GetValues()[0]) * (values_out[i][0] - this->output_layer->GetValues()[0]) << '\n';
//
//    this->SetDesiredValues(values_out[i]);
//    this->Learn();
//
////    for (void* curr_layer : this->layers_ids){
////      std::cout << this->layers[curr_layer] << ": " << this->layers[curr_layer]->error;
////      if (this->layers[curr_layer] == this->input_layer){
////        std::cout << "\t (input)";
////      } else if (this->layers[curr_layer] == this->output_layer){
////        std::cout << "\t (output)";
////      }
////      std::cout << '\n';
////        this->layers[curr_layer]->error = 0;
////        this->layers[curr_layer]->loss = 0;
////    }
//
////    std::cout << "---" << '\n';
//  }
//
//    for (auto curr_layer : this->layers) {
//        curr_layer.second->PrintInfo();
//        std::cout << "\n\n";
//    }
//}

void Model::TEST_function() {
    std::cout << "Model::TEST_function()" << '\n';
}


//State Model::GetState(void *layer_id) {
//    return this->layers[layer_id]->GetState();
//}

Layer* Model::GetLayer(void* layer_id){
    return this->layers[layer_id];
}

std::map <Layer*, State> Model::SetEpoch(const uint32_t &epoch) {
    while(this->epoch_states.size() < epoch){
        this->train_data.clear();
        this->train_data.seekg(0);
        this->test_data.clear();
        this->test_data.seekg(0);

        std::string raw_line;
        while(getline(this->train_data, raw_line)){
            std::vector <std::string> line_string_data;
            std::string curr_data = "";
            for (char symbol : raw_line){
                if (symbol == ';'){
                    line_string_data.push_back(curr_data);
                    curr_data = "";
                } else {
                    curr_data += symbol;
                }
            }
            line_string_data.push_back(curr_data);

            std::vector <double> input_data(this->input_layer->GetValuesNum());
            for (uint32_t i = 0; i < this->input_layer->GetValuesNum(); ++i){
                input_data[i] = std::stod(line_string_data[i]);
            }

            std::vector <double> output_data(this->output_layer->GetValuesNum());
            for (uint32_t i = 0; i < this->output_layer->GetValuesNum(); ++i){
                output_data[i] = std::stod(line_string_data[this->input_layer->GetValuesNum() + i]);
            }

            this->SetValues(input_data);
            this->Predict();
            this->SetDesiredValues(output_data);
            this->Learn();

            for (auto el : input_data){
                std::cout << el << " ";
            }
            std::cout << " | ";
            for (auto el : output_data){
                std::cout << el << " ";
            }
            std::cout << " | ";

            std::cout << this->output_layer->error << '\n';
        }

        uint64_t correct_answers = 0;
        uint64_t all_answers = 0;
        raw_line = "";
        while(getline(this->test_data, raw_line)){
            std::vector <std::string> line_string_data;
            std::string curr_data = "";
            for (char symbol : raw_line){
                if (symbol == ';'){
                    line_string_data.push_back(curr_data);
                    curr_data = "";
                } else {
                    curr_data += symbol;
                }
            }
            line_string_data.push_back(curr_data);

            std::vector <double> input_data(this->input_layer->GetValuesNum());
            for (uint32_t i = 0; i < this->input_layer->GetValuesNum(); ++i){
                input_data[i] = std::stod(line_string_data[i]);
            }

            std::vector <double> output_data(this->output_layer->GetValuesNum());
            for (uint32_t i = 0; i < this->output_layer->GetValuesNum(); ++i){
                output_data[i] = std::stod(line_string_data[this->input_layer->GetValuesNum() + i]);
            }

            this->SetValues(input_data);
            this->Predict();

            std::vector <double> answers = this->output_layer->GetValues();

            for (int i = 0; i < this->output_layer->GetValuesNum(); ++i){
//                std::cout << answers[i] << " " << round(answers[i]) << "\t\t" << output_data[i];
                if (round(answers[i]) != output_data[i]){
//                    std::cout << " + \n";
                    goto incorrect_answer;
//                } else {
//                    std::cout << '\n';
                }
            }

            ++correct_answers;
            // ну уж извините
            incorrect_answer:
            ++all_answers;
        }

        std::cout << correct_answers << "/" << all_answers << '\n';

        std::map <Layer*, State> result;
        for (auto layer_id : this->layers_ids){
//            result.at(this->layers[layer_id]) = this->layers[layer_id]->GetState();
            result.insert(std::make_pair(this->layers[layer_id], this->layers[layer_id]->GetState()));
        }

        this->epoch_states.push_back(result);

    }
    return this->epoch_states[epoch - 1];
}