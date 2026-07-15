#include "ReleaseController.h"

namespace sos::controller {

ReleaseController::ReleaseController(model::SampleRepository& sampleRepository,
                                       model::OrderRepository& orderRepository,
                                       view::ReleaseView& releaseView)
    : sampleRepository_(sampleRepository),
      orderRepository_(orderRepository),
      releaseView_(releaseView) {}

void ReleaseController::Run() {
    releaseView_.PrintConfirmedOrders(orderRepository_.GetByStatus(model::OrderStatus::CONFIRMED));

    int orderId = releaseView_.ReadOrderIdToRelease();
    if (orderId == 0) {
        return;
    }

    model::Order* order = orderRepository_.FindById(orderId);
    if (order == nullptr || order->status != model::OrderStatus::CONFIRMED) {
        releaseView_.PrintError("출고 대기(CONFIRMED) 상태의 주문만 출고 처리할 수 있습니다.");
        return;
    }

    model::Sample* sample = sampleRepository_.FindById(order->sampleId);
    if (sample == nullptr || sample->stock < order->quantity) {
        releaseView_.PrintError("재고가 부족하여 출고할 수 없습니다.");
        return;
    }

    sample->stock -= order->quantity;
    order->status = model::OrderStatus::RELEASE;
    releaseView_.PrintReleaseResult(*order);
}

}  // namespace sos::controller
