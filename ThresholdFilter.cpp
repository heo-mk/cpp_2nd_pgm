#include "ThresholdFilter.h"

void ThresholdFilter::apply(unsigned char* pixels, int width, int height) {
    unsigned char* p = pixels;
    unsigned char* end = pixels + width * height;
    for (; p < end; ++p) {
        // TODO: 기준값(threshold_)보다 밝으면 255(흰색), 아니면 0(검은색)으로 만들어보세요
        // 힌트: if / else 와 *p 를 사용
        if (*p > threshold_) {
            *p = 255;
        } else {
            *p = 0;
        }
    }
}
