#pragma once

#include <optional>
#include <string>
#include <vector>

namespace sos::view {

enum class ProductionMenuChoice {
    CurrentJob = 1,
    WaitingQueue = 2,
    CompleteCurrentJob = 3,
    Back = 0,
    Invalid = -1
};

// 생산 라인 화면 표시용 데이터 (시료 이름 등은 Controller가 조회하여 채운다)
struct ProductionJobRow {
    int orderId = 0;
    int sampleId = 0;
    std::string sampleName;
    int shortageQuantity = 0;
    int actualProductionQuantity = 0;
    double totalProductionTime = 0.0;
    int producedQuantity = 0;
};

// 4.5 생산 라인 화면
class ProductionView {
public:
    void PrintSubMenu() const;
    ProductionMenuChoice ReadChoice() const;

    void PrintCurrentJob(const std::optional<ProductionJobRow>& job) const;
    void PrintWaitingQueue(const std::vector<ProductionJobRow>& jobs) const;
    void PrintCompleteResult(int orderId) const;
    void PrintNoJobMessage() const;
};

}  // namespace sos::view
