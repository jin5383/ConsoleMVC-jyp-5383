#pragma once

#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"
#include "../View/ReleaseView.h"

namespace sos::controller {

// 4.6 출고 처리 오케스트레이션
class ReleaseController {
public:
    ReleaseController(model::SampleRepository& sampleRepository,
                       model::OrderRepository& orderRepository,
                       view::ReleaseView& releaseView);

    void Run();

private:
    model::SampleRepository& sampleRepository_;
    model::OrderRepository& orderRepository_;
    view::ReleaseView& releaseView_;
};

}  // namespace sos::controller
