#include "State.h"

State::State(const std::vector<double> &values, const std::vector<double> &biases, const std::vector<std::vector<std::vector <double>>> &weights) {
    this->biases = biases;
    this->values = values;
    this->weights = weights;
}

State::State(const std::vector<double> &values) {
    this->values = values;
}

std::vector <double> State::GetValues() {
    return this->values;
}

std::optional<std::vector<double>> State::GetBiases() {
    return this->biases;
}

std::optional<std::vector<std::vector<std::vector <double>>>> State::GetWeights() {
    return this->weights;
}