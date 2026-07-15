#include "OrderRepository.h"

namespace sos::model {

Order& OrderRepository::Add(int sampleId, const std::string& customerName, int quantity) {
    Order order;
    order.id = nextId_++;
    order.sampleId = sampleId;
    order.customerName = customerName;
    order.quantity = quantity;
    order.status = OrderStatus::RESERVED;
    orders_.push_back(order);
    return orders_.back();
}

std::vector<Order>& OrderRepository::GetAll() {
    return orders_;
}

std::vector<Order*> OrderRepository::GetByStatus(OrderStatus status) {
    std::vector<Order*> result;
    for (auto& order : orders_) {
        if (order.status == status) {
            result.push_back(&order);
        }
    }
    return result;
}

Order* OrderRepository::FindById(int id) {
    for (auto& order : orders_) {
        if (order.id == id) {
            return &order;
        }
    }
    return nullptr;
}

}  // namespace sos::model
