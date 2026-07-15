#include "MainMenuView.h"

#include <iostream>

#include "../Model/OrderStatus.h"
#include "ConsoleIO.h"

namespace sos::view {

void MainMenuView::PrintMenu(const std::vector<model::Sample>& samples,
                              const std::vector<model::Order>& orders) const {
    int totalStock = 0;
    for (const auto& sample : samples) {
        totalStock += sample.stock;
    }

    int activeOrderCount = 0;
    for (const auto& order : orders) {
        if (order.status != model::OrderStatus::REJECTED) {
            ++activeOrderCount;
        }
    }

    PrintDivider();
    std::cout << "반도체 시료 생산주문관리 시스템 (SampleOrderSystem)\n";
    PrintDivider();
    std::cout << "[요약] 등록 시료 " << samples.size() << "종 / 총 재고 " << totalStock
               << "개 / 유효 주문 " << activeOrderCount << "건\n";
    PrintDivider();
    std::cout << "1. 시료 관리\n";
    std::cout << "2. 주문 (접수 / 승인 / 거절)\n";
    std::cout << "3. 모니터링\n";
    std::cout << "4. 출고 처리\n";
    std::cout << "5. 생산 라인\n";
    std::cout << "0. 종료\n";
    PrintDivider();
}

MainMenuChoice MainMenuView::ReadChoice() const {
    int choice = ReadInt("메뉴를 선택하세요: ");
    switch (choice) {
        case 0: return MainMenuChoice::Exit;
        case 1: return MainMenuChoice::SampleManagement;
        case 2: return MainMenuChoice::Order;
        case 3: return MainMenuChoice::Monitoring;
        case 4: return MainMenuChoice::Release;
        case 5: return MainMenuChoice::ProductionLine;
        default: return MainMenuChoice::Invalid;
    }
}

}  // namespace sos::view
