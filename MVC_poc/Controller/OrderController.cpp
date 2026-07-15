#include "OrderController.h"

#include <cmath>

namespace sos::controller {

OrderController::OrderController(model::SampleRepository& sampleRepository,
                                   model::OrderRepository& orderRepository,
                                   model::ProductionQueue& productionQueue,
                                   view::OrderView& orderView)
    : sampleRepository_(sampleRepository),
      orderRepository_(orderRepository),
      productionQueue_(productionQueue),
      orderView_(orderView) {}

void OrderController::Run() {
    bool running = true;
    while (running) {
        orderView_.PrintSubMenu();
        switch (orderView_.ReadChoice()) {
            case view::OrderMenuChoice::Place:
                PlaceOrder();
                break;
            case view::OrderMenuChoice::ListPending:
                ListPendingOrders();
                break;
            case view::OrderMenuChoice::Approve:
                ApproveOrder();
                break;
            case view::OrderMenuChoice::Reject:
                RejectOrder();
                break;
            case view::OrderMenuChoice::Back:
                running = false;
                break;
            default:
                break;
        }
    }
}

void OrderController::PlaceOrder() {
    view::NewOrderInput input = orderView_.ReadNewOrderInput();

    model::Sample* sample = sampleRepository_.FindById(input.sampleId);
    if (sample == nullptr) {
        orderView_.PrintError("존재하지 않는 시료 ID입니다.");
        return;
    }
    if (input.quantity <= 0) {
        orderView_.PrintError("주문 수량은 1개 이상이어야 합니다.");
        return;
    }

    model::Order& order =
        orderRepository_.Add(input.sampleId, input.customerName, input.quantity);
    orderView_.PrintPlaceResult(order);
}

void OrderController::ListPendingOrders() {
    orderView_.PrintPendingOrders(orderRepository_.GetByStatus(model::OrderStatus::RESERVED));
}

void OrderController::ApproveOrder() {
    int orderId = orderView_.ReadOrderId("승인할 주문 ID: ");
    model::Order* order = orderRepository_.FindById(orderId);
    if (order == nullptr || order->status != model::OrderStatus::RESERVED) {
        orderView_.PrintError("접수 상태(RESERVED)의 주문만 승인할 수 있습니다.");
        return;
    }

    model::Sample* sample = sampleRepository_.FindById(order->sampleId);
    if (sample == nullptr) {
        orderView_.PrintError("주문에 연결된 시료를 찾을 수 없습니다.");
        return;
    }

    if (sample->stock >= order->quantity) {
        order->status = model::OrderStatus::CONFIRMED;
    } else {
        int shortage = order->quantity - sample->stock;
        model::ProductionJob job;
        job.orderId = order->id;
        job.sampleId = sample->id;
        job.shortageQuantity = shortage;
        job.actualProductionQuantity =
            static_cast<int>(std::ceil(shortage / sample->yield));
        job.totalProductionTime = sample->avgProductionTime * job.actualProductionQuantity;
        productionQueue_.Enqueue(job);

        order->status = model::OrderStatus::PRODUCING;
    }

    orderView_.PrintDecisionResult(order->id, order->status);
}

void OrderController::RejectOrder() {
    int orderId = orderView_.ReadOrderId("거절할 주문 ID: ");
    model::Order* order = orderRepository_.FindById(orderId);
    if (order == nullptr || order->status != model::OrderStatus::RESERVED) {
        orderView_.PrintError("접수 상태(RESERVED)의 주문만 거절할 수 있습니다.");
        return;
    }

    order->status = model::OrderStatus::REJECTED;
    orderView_.PrintDecisionResult(order->id, order->status);
}

}  // namespace sos::controller
