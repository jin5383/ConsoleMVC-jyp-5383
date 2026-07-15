#pragma once

#include "../Model/OrderRepository.h"
#include "../Model/ProductionQueue.h"
#include "../Model/SampleRepository.h"
#include "../View/OrderView.h"

namespace sos::controller {

// 4.2, 4.3 주문 접수 / 승인 / 거절 오케스트레이션
class OrderController {
public:
    OrderController(model::SampleRepository& sampleRepository,
                     model::OrderRepository& orderRepository,
                     model::ProductionQueue& productionQueue,
                     view::OrderView& orderView);

    void Run();

private:
    void PlaceOrder();
    void ListPendingOrders();
    void ApproveOrder();
    void RejectOrder();

    model::SampleRepository& sampleRepository_;
    model::OrderRepository& orderRepository_;
    model::ProductionQueue& productionQueue_;
    view::OrderView& orderView_;
};

}  // namespace sos::controller
