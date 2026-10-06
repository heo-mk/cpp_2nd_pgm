#pragma once
#include "Filter.h"

class BlurFilter : public Filter {
public:
    void apply(unsigned char* pixels, int width, int height);
};
