#pragma once
#include "Filter.h"

class InvertFilter : public Filter {
public:
    void apply(unsigned char* pixels, int width, int height);
};
