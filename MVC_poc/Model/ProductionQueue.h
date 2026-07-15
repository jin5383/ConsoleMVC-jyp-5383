#pragma once

#include <deque>
#include <vector>

#include "ProductionJob.h"

namespace sos::model {

// 4.5 생산 라인 - FIFO 생산 큐 및 현재 생산 중인 작업 관리
class ProductionQueue {
public:
    void Enqueue(const ProductionJob& job);

    bool HasCurrentJob() const;
    ProductionJob* CurrentJob();

    // 현재 작업을 큐에서 제거하고 다음 작업을 현재 작업으로 승격한다.
    void CompleteCurrentJob();

    // 대기열(현재 작업 제외)의 스냅샷을 순서대로 반환한다.
    std::vector<ProductionJob> GetWaitingQueueSnapshot() const;

private:
    std::deque<ProductionJob> queue_;
};

}  // namespace sos::model
