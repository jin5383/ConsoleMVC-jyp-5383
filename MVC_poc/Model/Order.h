#pragma once

#include <string>

#include "OrderStatus.h"

namespace sos::model {

// 4.2 시료 주문 (예약) - 시료 ID, 고객명, 주문 수량
struct Order {
    int id = 0;
    int sampleId = 0;
    std::string customerName;
    int quantity = 0;
    OrderStatus status = OrderStatus::RESERVED;
};

}  // namespace sos::model
