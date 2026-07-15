#include "ProductionController.h"

#include <optional>

namespace sos::controller {

ProductionController::ProductionController(model::SampleRepository& sampleRepository,
                                             model::OrderRepository& orderRepository,
                                             model::ProductionQueue& productionQueue,
                                             view::ProductionView& productionView)
    : sampleRepository_(sampleRepository),
      orderRepository_(orderRepository),
      productionQueue_(productionQueue),
      productionView_(productionView) {}

void ProductionController::Run() {
    bool running = true;
    while (running) {
        productionView_.PrintSubMenu();
        switch (productionView_.ReadChoice()) {
            case view::ProductionMenuChoice::CurrentJob:
                ShowCurrentJob();
                break;
            case view::ProductionMenuChoice::WaitingQueue:
                ShowWaitingQueue();
                break;
            case view::ProductionMenuChoice::CompleteCurrentJob:
                CompleteCurrentJob();
                break;
            case view::ProductionMenuChoice::Back:
                running = false;
                break;
            default:
                break;
        }
    }
}

view::ProductionJobRow ProductionController::ToRow(const model::ProductionJob& job) const {
    view::ProductionJobRow row;
    row.orderId = job.orderId;
    row.sampleId = job.sampleId;
    model::Sample* sample = sampleRepository_.FindById(job.sampleId);
    row.sampleName = (sample != nullptr) ? sample->name : "(알 수 없음)";
    row.shortageQuantity = job.shortageQuantity;
    row.actualProductionQuantity = job.actualProductionQuantity;
    row.totalProductionTime = job.totalProductionTime;
    row.producedQuantity = job.producedQuantity;
    return row;
}

void ProductionController::ShowCurrentJob() {
    model::ProductionJob* job = productionQueue_.CurrentJob();
    if (job == nullptr) {
        productionView_.PrintCurrentJob(std::nullopt);
        return;
    }
    productionView_.PrintCurrentJob(ToRow(*job));
}

void ProductionController::ShowWaitingQueue() {
    std::vector<view::ProductionJobRow> rows;
    for (const auto& job : productionQueue_.GetWaitingQueueSnapshot()) {
        rows.push_back(ToRow(job));
    }
    productionView_.PrintWaitingQueue(rows);
}

void ProductionController::CompleteCurrentJob() {
    model::ProductionJob* job = productionQueue_.CurrentJob();
    if (job == nullptr) {
        productionView_.PrintNoJobMessage();
        return;
    }

    model::Sample* sample = sampleRepository_.FindById(job->sampleId);
    if (sample != nullptr) {
        sample->stock += job->actualProductionQuantity;
    }

    model::Order* order = orderRepository_.FindById(job->orderId);
    if (order != nullptr) {
        order->status = model::OrderStatus::CONFIRMED;
    }

    int completedOrderId = job->orderId;
    productionQueue_.CompleteCurrentJob();
    productionView_.PrintCompleteResult(completedOrderId);
}

}  // namespace sos::controller
