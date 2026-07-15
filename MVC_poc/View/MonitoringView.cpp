#include "MonitoringView.h"

#include <iostream>

#include "ConsoleIO.h"

namespace sos::view {

void MonitoringView::PrintSubMenu() const {
    PrintDivider();
    std::cout << "[모니터링]\n";
    std::cout << "1. 주문량 확인 (상태별)\n";
    std::cout << "2. 재고량 확인 (시료별)\n";
    std::cout << "0. 이전 메뉴\n";
    PrintDivider();
}

MonitoringMenuChoice MonitoringView::ReadChoice() const {
    int choice = ReadInt("선택: ");
    switch (choice) {
        case 0: return MonitoringMenuChoice::Back;
        case 1: return MonitoringMenuChoice::OrderSummary;
        case 2: return MonitoringMenuChoice::StockStatus;
        default: return MonitoringMenuChoice::Invalid;
    }
}

void MonitoringView::PrintOrderStatusSummary(
    const std::vector<std::pair<model::OrderStatus, int>>& summary) const {
    std::cout << "상태\t건수\n";
    for (const auto& [status, count] : summary) {
        std::cout << model::ToString(status) << "\t" << count << "\n";
    }
}

void MonitoringView::PrintStockStatus(const std::vector<StockStatusRow>& rows) const {
    if (rows.empty()) {
        PrintMessage("등록된 시료가 없습니다.");
        return;
    }
    std::cout << "ID\t이름\t재고\t주문수요\t상태\n";
    for (const auto& row : rows) {
        std::cout << row.sampleId << "\t" << row.sampleName << "\t" << row.stock << "\t"
                   << row.demand << "\t" << row.statusLabel << "\n";
    }
}

}  // namespace sos::view
