#pragma once

#include <string>
#include <vector>

#include "../Model/Order.h"
#include "../Model/OrderStatus.h"

namespace sos::view {

enum class OrderMenuChoice {
    Place = 1,
    ListPending = 2,
    Approve = 3,
    Reject = 4,
    Back = 0,
    Invalid = -1
};

struct NewOrderInput {
    int sampleId = 0;
    std::string customerName;
    int quantity = 0;
};

// 4.2, 4.3 주문 접수 / 승인 / 거절 화면
class OrderView {
public:
    void PrintSubMenu() const;
    OrderMenuChoice ReadChoice() const;

    NewOrderInput ReadNewOrderInput() const;
    int ReadOrderId(const std::string& prompt) const;

    void PrintPendingOrders(const std::vector<model::Order*>& orders) const;
    void PrintPlaceResult(const model::Order& order) const;
    void PrintDecisionResult(int orderId, model::OrderStatus resultStatus) const;
    void PrintError(const std::string& message) const;
};

}  // namespace sos::view
