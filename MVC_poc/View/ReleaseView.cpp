#include "ReleaseView.h"

#include <iostream>

#include "../Model/OrderStatus.h"
#include "ConsoleIO.h"

namespace sos::view {

void ReleaseView::PrintConfirmedOrders(const std::vector<model::Order*>& orders) const {
    PrintDivider();
    std::cout << "[출고 처리] 출고 대기 중인 주문 (CONFIRMED)\n";
    if (orders.empty()) {
        PrintMessage("출고 대기 중인 주문이 없습니다.");
        return;
    }
    std::cout << "주문ID\t시료ID\t고객명\t수량\n";
    for (const auto* order : orders) {
        std::cout << order->id << "\t" << order->sampleId << "\t" << order->customerName
                   << "\t" << order->quantity << "\n";
    }
}

int ReleaseView::ReadOrderIdToRelease() const {
    return ReadInt("출고 처리할 주문 ID (0: 취소): ");
}

void ReleaseView::PrintReleaseResult(const model::Order& order) const {
    std::cout << "주문 " << order.id << "이(가) 출고 처리되었습니다. (상태: "
               << model::ToString(order.status) << ")\n";
}

void ReleaseView::PrintError(const std::string& message) const {
    std::cout << "[오류] " << message << "\n";
}

}  // namespace sos::view
