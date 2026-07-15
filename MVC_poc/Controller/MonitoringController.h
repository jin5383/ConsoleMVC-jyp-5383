#pragma once

#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include "../View/MonitoringView.h"

namespace sos::controller {

// 4.4 모니터링 오케스트레이션
class MonitoringController {
public:
    MonitoringController(model::SampleRepository& sampleRepository,
                          model::OrderRepository& orderRepository,
                          view::MonitoringView& monitoringView);

    void Run();

private:
    void ShowOrderSummary();
    void ShowStockStatus();

    model::SampleRepository& sampleRepository_;
    model::OrderRepository& orderRepository_;
    view::MonitoringView& monitoringView_;
};

}  // namespace sos::controller
