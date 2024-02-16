#pragma once

#include "./Layer.h"

class InputLayer : public Layer {
public:
  InputLayer(const uint32_t &);
  InputLayer(const uint32_t &, const bool &);

  void SetValues(const std::vector <double> &) override;
  
  void PrintInfo() override;

  void Predict() override {}
  void Learn() override {}

  State GetState() override;

private:
};
