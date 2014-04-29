#pragma once

#include "sevine.h"


class simaff_system_t: public divine::affine_explicit_system_t
{
 public:
  simaff_system_t(divine::error_vector_t &);
  ~simaff_system_t();
 private:
};
