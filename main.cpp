// 사용법: main <invert|threshold|blur> <입력.pgm> <출력.pgm>
// 예:     main invert input.pgm out_invert.pgm
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "BlurFilter.h"
#include "Filter.h"
#include "InvertFilter.h"
#include "ThresholdFilter.h"

// 바이너리 PGM(P5, 8비트)을 읽는다. 헤더는 텍스트, 픽셀은 이진 데이터.
static bool readPgm(const std::string& path, int& width, int& height, std::vector<unsigned char>& pixels) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;

    std::string magic;
    in >> magic;
    if (magic != "P5") return false;

    auto readInt = [&in]() {
        int value = 0;
        while (in >> std::ws && in.peek() == '#') {  // 주석 줄 건너뛰기
            std::string comment;
            std::getline(in, comment);
        }
        in >> value;
        return value;
    };

    width = readInt();
    height = readInt();
    int maxValue = readInt();
    if (width <= 0 || height <= 0 || maxValue != 255) return false;

    in.get();  // 헤더 마지막 공백 문자 1개 소비
    pixels.resize(static_cast<size_t>(width) * height);
    in.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    return static_cast<size_t>(in.gcount()) == pixels.size();
}

static bool writePgm(const std::string& path, int width, int height, const std::vector<unsigned char>& pixels) {
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;
    out << "P5\n" << width << " " << height << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    return static_cast<bool>(out);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "사용법: main <invert|threshold|blur> <입력.pgm> <출력.pgm>\n";
        return 1;
    }
    std::string name = argv[1];

    std::unique_ptr<Filter> filter;
    if (name == "invert") filter = std::make_unique<InvertFilter>();
    else if (name == "threshold") filter = std::make_unique<ThresholdFilter>();
    else if (name == "blur") filter = std::make_unique<BlurFilter>();
    else {
        std::cerr << "알 수 없는 필터: " << name << "\n";
        return 1;
    }

    int width = 0, height = 0;
    std::vector<unsigned char> pixels;
    if (!readPgm(argv[2], width, height, pixels)) {
        std::cerr << "PGM(P5) 읽기 실패: " << argv[2] << "\n";
        return 1;
    }

    filter->apply(pixels.data(), width, height);

    if (!writePgm(argv[3], width, height, pixels)) {
        std::cerr << "저장 실패: " << argv[3] << "\n";
        return 1;
    }
    std::cout << name << " 적용 완료 -> " << argv[3] << " (" << width << "x" << height << ")\n";
    return 0;
}
