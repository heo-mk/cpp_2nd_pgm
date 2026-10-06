#pragma once

// 모든 필터의 베이스 클래스.
// pixels: 그레이스케일 픽셀 배열의 시작 주소 (0~255라서 unsigned char)
class Filter {
public:
    virtual ~Filter() {}

    // TODO: 아래 apply() 선언을 파생 클래스가 덮어쓸 수 있게 만들어보세요
    // 힌트: 베이스 포인터(Filter*)로 호출해도 파생 클래스의 함수가 실행되게 하려면 선언 앞에 어떤 키워드가 필요할까?
    virtual void apply(unsigned char* pixels, int width, int height) = 0;
};
