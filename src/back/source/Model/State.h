#pragma once

#include <vector>
#include <iostream>
#include <optional>

struct State {
private:
    std::vector <double> values;
    std::optional<std::vector <double>> biases = std::nullopt;
    std::optional<std::vector <std::vector <std::vector <double>>>> weights = std::nullopt;

public:
    State(const std::vector <double> &, const std::vector <double> &, const std::vector<std::vector<std::vector <double>>> &);
    State(const std::vector <double> &);

    std::vector <double> GetValues();
    std::optional<std::vector <double>> GetBiases();
    std::optional<std::vector <std::vector <std::vector <double>>>> GetWeights();
};
