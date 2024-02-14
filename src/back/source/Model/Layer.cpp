#include "./Layer.h"

// Layer::Layer(uint32_t inputs_num, uint32_t outputs_num, uint32_t values_num)
// {
//   this->inputs_num = inputs_num;
//   this->outputs_num = outputs_num;
//   this->values_num = values_num;
//   this->
// };

Layer::Layer(const uint32_t &values_num,
             const std::function<double(double)> &activation,
             const std::function<double(double)> &activation_derivative, const double &learning_rate) {
  this->activation = activation;
  this->activation_derivative = activation_derivative;

  this->learning_rate = learning_rate;

  this->values_num = values_num;
  this->values.resize(values_num);
  this->ClearValues();
}

Layer::Layer(const uint32_t &values_num,
             const std::function<double(double)> &activation,
             const std::function<double(double)> &activation_derivative,
             const bool &is_output, const double &learning_rate) {
  this->activation = activation;
  this->activation_derivative = activation_derivative;

  this->is_output = is_output;
  this->learning_rate = learning_rate;

  this->values_num = values_num;
  this->values.resize(values_num);
  this->ClearValues();
}

void Layer::Predict() {
  std::cerr << "[Error] Predict() called in Layer class (по чьей вине вызвалось, тот уебок) (потом сделаю throw)";
}

void Layer::Learn() {
  std::cerr << "[Error] Learn() called in Layer class (по чьей вине вызвалось, тот уебок) (потом сделаю throw)";
}

void Layer::ClearValues() {
  for (auto &value : this->values) {
    value = 0;
  }
}

std::vector<double> Layer::GetValues() {
  // std::cerr << (!this->is_output ? "[Warning] Layer is not output \n" : "");
  return this->values;
}

void Layer::AddOutput(Layer *output) {
  ++this->outputs_num;
  this->outputs.push_back(output);
}

void Layer::ConnectTo(Layer *input) {
  this->inputs.push_back(input);
  ++this->inputs_num;
  input->AddOutput(this);
}

uint32_t Layer::GetValuesNum() const { return this->values_num; }

void Layer::PrintInfo(){
  std::cerr << "[Error] PrintInfo() called in Layer class (по чьей вине вызвалось, тот уебок) (потом сделаю throw)";
}
