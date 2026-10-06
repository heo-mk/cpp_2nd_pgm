#include "InvertFilter.h"

void InvertFilter::apply(unsigned char* pixels, int width, int height) {
    unsigned char* p = pixels;
    unsigned char* end = pixels + width * height;
    for (; p < end; ++p) {
        // TODO: 이 픽셀(*p)의 밝기를 반전시켜보세요
        // 힌트: 포인터가 가리키는 '값'을 바꾸려면 어떤 연산자를 쓸까? 반전 공식은 255 - 값
        *p = 255 - *p;
    }
}
