#include "MonitoringController.h"

#include <array>
#include <unordered_map>

namespace sos::controller {

namespace {
constexpr std::array<model::OrderStatus, 4> kMonitoredStatuses = {
    model::OrderStatus::RESERVED, model::OrderStatus::CONFIRMED,
    model::OrderStatus::PRODUCING, model::OrderStatus::RELEASE};
}  // namespace

MonitoringController::MonitoringController(model::SampleRepository& sampleRepository,
                                             model::OrderRepository& orderRepository,
                                             view::MonitoringView& monitoringView)
    : sampleRepository_(sampleRepository),
      orderRepository_(orderRepository),
      monitoringView_(monitoringView) {}

void MonitoringController::Run() {
    bool running = true;
    while (running) {
        monitoringView_.PrintSubMenu();
        switch (monitoringView_.ReadChoice()) {
            case view::MonitoringMenuChoice::OrderSummary:
                ShowOrderSummary();
                break;
            case view::MonitoringMenuChoice::StockStatus:
                ShowStockStatus();
                break;
            case view::MonitoringMenuChoice::Back:
                running = false;
                break;
            default:
                break;
        }
    }
}

void MonitoringController::ShowOrderSummary() {
    // REJECTED는 유효 주문이 아니므로 집계에서 제외한다.
    std::unordered_map<model::OrderStatus, int> counts;
    for (auto status : kMonitoredStatuses) {
        counts[status] = 0;
    }
    for (const auto& order : orderRepository_.GetAll()) {
        if (order.status != model::OrderStatus::REJECTED) {
            ++counts[order.status];
        }
    }

    std::vector<std::pair<model::OrderStatus, int>> summary;
    for (auto status : kMonitoredStatuses) {
        summary.emplace_back(status, counts[status]);
    }
    monitoringView_.PrintOrderStatusSummary(summary);
}

void MonitoringController::ShowStockStatus() {
    // 아직 출고되지 않은(RELEASE 이전) 유효 주문 수량을 시료별 수요로 집계한다.
    std::unordered_map<int, int> demandBySampleId;
    for (const auto& order : orderRepository_.GetAll()) {
        if (order.status == model::OrderStatus::RESERVED ||
            order.status == model::OrderStatus::PRODUCING ||
            order.status == model::OrderStatus::CONFIRMED) {
            demandBySampleId[order.sampleId] += order.quantity;
        }
    }

    std::vector<view::StockStatusRow> rows;
    for (const auto& sample : sampleRepository_.GetAll()) {
        view::StockStatusRow row;
        row.sampleId = sample.id;
        row.sampleName = sample.name;
        row.stock = sample.stock;
        row.demand = demandBySampleId[sample.id];

        if (sample.stock == 0) {
            row.statusLabel = "고갈";
        } else if (sample.stock < row.demand) {
            row.statusLabel = "부족";
        } else {
            row.statusLabel = "여유";
        }
        rows.push_back(row);
    }
    monitoringView_.PrintStockStatus(rows);
}

}  // namespace sos::controller
