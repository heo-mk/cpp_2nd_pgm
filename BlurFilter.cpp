#include "BlurFilter.h"
#include <vector>

// 3x3 평균 블러. 가장자리는 이미지 안쪽 픽셀만으로 평균낸다.
void BlurFilter::apply(unsigned char* pixels, int width, int height) {
    std::vector<unsigned char> src(pixels, pixels + width * height);  // 원본 복사본

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sum = 0;
            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;
                    sum += src[ny * width + nx];
                    ++count;
                }
            }
            pixels[y * width + x] = static_cast<unsigned char>(sum / count);
        }
    }
}
