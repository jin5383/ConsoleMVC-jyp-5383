#include "OrderView.h"

#include <iostream>

#include "ConsoleIO.h"

namespace sos::view {

void OrderView::PrintSubMenu() const {
    PrintDivider();
    std::cout << "[주문 (접수 / 승인 / 거절)]\n";
    std::cout << "1. 주문 접수\n";
    std::cout << "2. 접수된 주문 목록 (RESERVED)\n";
    std::cout << "3. 주문 승인\n";
    std::cout << "4. 주문 거절\n";
    std::cout << "0. 이전 메뉴\n";
    PrintDivider();
}

OrderMenuChoice OrderView::ReadChoice() const {
    int choice = ReadInt("선택: ");
    switch (choice) {
        case 0: return OrderMenuChoice::Back;
        case 1: return OrderMenuChoice::Place;
        case 2: return OrderMenuChoice::ListPending;
        case 3: return OrderMenuChoice::Approve;
        case 4: return OrderMenuChoice::Reject;
        default: return OrderMenuChoice::Invalid;
    }
}

NewOrderInput OrderView::ReadNewOrderInput() const {
    NewOrderInput input;
    input.sampleId = ReadInt("시료 ID: ");
    input.customerName = ReadLine("고객명: ");
    input.quantity = ReadInt("주문 수량: ");
    return input;
}

int OrderView::ReadOrderId(const std::string& prompt) const {
    return ReadInt(prompt);
}

void OrderView::PrintPendingOrders(const std::vector<model::Order*>& orders) const {
    if (orders.empty()) {
        PrintMessage("접수 대기 중인 주문이 없습니다.");
        return;
    }
    std::cout << "주문ID\t시료ID\t고객명\t수량\t상태\n";
    for (const auto* order : orders) {
        std::cout << order->id << "\t" << order->sampleId << "\t" << order->customerName
                   << "\t" << order->quantity << "\t" << model::ToString(order->status) << "\n";
    }
}

void OrderView::PrintPlaceResult(const model::Order& order) const {
    std::cout << "주문이 접수되었습니다. (주문ID: " << order.id
               << ", 상태: " << model::ToString(order.status) << ")\n";
}

void OrderView::PrintDecisionResult(int orderId, model::OrderStatus resultStatus) const {
    std::cout << "주문 " << orderId << " 처리 결과: " << model::ToString(resultStatus) << "\n";
}

void OrderView::PrintError(const std::string& message) const {
    std::cout << "[오류] " << message << "\n";
}

}  // namespace sos::view
