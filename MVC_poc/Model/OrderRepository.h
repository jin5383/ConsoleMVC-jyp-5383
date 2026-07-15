#pragma once

#include <string>
#include <vector>

#include "Order.h"
#include "OrderStatus.h"

namespace sos::model {

// 주문 데이터 저장/조회 담당.
class OrderRepository {
public:
    Order& Add(int sampleId, const std::string& customerName, int quantity);

    std::vector<Order>& GetAll();
    std::vector<Order*> GetByStatus(OrderStatus status);
    Order* FindById(int id);

private:
    std::vector<Order> orders_;
    int nextId_ = 1;
};

}  // namespace sos::model
