#include "ProductionQueue.h"

namespace sos::model {

void ProductionQueue::Enqueue(const ProductionJob& job) {
    queue_.push_back(job);
}

bool ProductionQueue::HasCurrentJob() const {
    return !queue_.empty();
}

ProductionJob* ProductionQueue::CurrentJob() {
    if (queue_.empty()) {
        return nullptr;
    }
    return &queue_.front();
}

void ProductionQueue::CompleteCurrentJob() {
    if (!queue_.empty()) {
        queue_.pop_front();
    }
}

std::vector<ProductionJob> ProductionQueue::GetWaitingQueueSnapshot() const {
    if (queue_.size() <= 1) {
        return {};
    }
    return std::vector<ProductionJob>(queue_.begin() + 1, queue_.end());
}

}  // namespace sos::model
