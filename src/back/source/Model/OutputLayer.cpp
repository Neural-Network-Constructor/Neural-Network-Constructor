#include "./OutputLayer.h"
#include <cstdlib>
#include <ctime>

OutputLayer::OutputLayer(const uint32_t &values_num)
  : Layer() {
  this->values_num = values_num;
}
