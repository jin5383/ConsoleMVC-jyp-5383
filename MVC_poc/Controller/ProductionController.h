#pragma once

#include "../Model/OrderRepository.h"
#include "../Model/ProductionQueue.h"
#include "../Model/SampleRepository.h"
#include "../View/ProductionView.h"

namespace sos::controller {

// 4.5 생산 라인 오케스트레이션
class ProductionController {
public:
    ProductionController(model::SampleRepository& sampleRepository,
                          model::OrderRepository& orderRepository,
                          model::ProductionQueue& productionQueue,
                          view::ProductionView& productionView);

    void Run();

private:
    view::ProductionJobRow ToRow(const model::ProductionJob& job) const;

    void ShowCurrentJob();
    void ShowWaitingQueue();
    void CompleteCurrentJob();

    model::SampleRepository& sampleRepository_;
    model::OrderRepository& orderRepository_;
    model::ProductionQueue& productionQueue_;
    view::ProductionView& productionView_;
};

}  // namespace sos::controller
