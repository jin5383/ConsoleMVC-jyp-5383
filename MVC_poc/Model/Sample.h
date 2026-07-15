#pragma once

#include <string>

namespace sos::model {

// 4.1 시료 관리 - 시료 ID, 이름, 평균 생산시간, 수율, 재고
struct Sample {
    int id = 0;
    std::string name;
    double avgProductionTime = 0.0;  // 단위: 분 (자유 결정)
    double yield = 1.0;              // 정상 시료 수 / 총 생산 시료 수
    int stock = 0;
};

}  // namespace sos::model
