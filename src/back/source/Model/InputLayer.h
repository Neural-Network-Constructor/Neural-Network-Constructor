#pragma once

#include "./Layer.h"

class InputLayer : public Layer {
private:
public:
  InputLayer(const uint32_t &);
  InputLayer(const uint32_t &, const bool &);

  void SetValues(const std::vector <double> &);
  
  void PrintInfo();
};
