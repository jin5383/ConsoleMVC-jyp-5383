#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../Model/OrderStatus.h"

namespace sos::view {

enum class MonitoringMenuChoice {
    OrderSummary = 1,
    StockStatus = 2,
    Back = 0,
    Invalid = -1
};

// 재고 상태 표기용 데이터. 여유/부족/고갈 판정은 Controller가 계산하여 채운다.
struct StockStatusRow {
    int sampleId = 0;
    std::string sampleName;
    int stock = 0;
    int demand = 0;
    std::string statusLabel;  // "여유" / "부족" / "고갈"
};

// 4.4 모니터링 화면
class MonitoringView {
public:
    void PrintSubMenu() const;
    MonitoringMenuChoice ReadChoice() const;

    void PrintOrderStatusSummary(const std::vector<std::pair<model::OrderStatus, int>>& summary) const;
    void PrintStockStatus(const std::vector<StockStatusRow>& rows) const;
};

}  // namespace sos::view
