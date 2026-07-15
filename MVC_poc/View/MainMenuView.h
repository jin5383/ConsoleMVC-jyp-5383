#pragma once

#include <vector>

#include "../Model/Order.h"
#include "../Model/Sample.h"

namespace sos::view {

enum class MainMenuChoice {
    SampleManagement = 1,
    Order = 2,
    Monitoring = 3,
    Release = 4,
    ProductionLine = 5,
    Exit = 0,
    Invalid = -1
};

// 3. 메인 메뉴 - 기능별 선택 화면 + 전체 시료 요약 정보
class MainMenuView {
public:
    void PrintMenu(const std::vector<model::Sample>& samples,
                   const std::vector<model::Order>& orders) const;
    MainMenuChoice ReadChoice() const;
};

}  // namespace sos::view
