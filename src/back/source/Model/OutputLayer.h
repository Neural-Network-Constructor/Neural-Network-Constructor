#pragma once

#include "./Layer.h"

class OutputLayer : public Layer {
private:
public:
  OutputLayer(const uint32_t &);

  std::vector <double> GetValues();
};
