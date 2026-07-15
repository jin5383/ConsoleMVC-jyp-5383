#pragma once

#include "../Model/SampleRepository.h"
#include "../View/SampleView.h"

namespace sos::controller {

// 4.1 시료 관리 기능 오케스트레이션
class SampleController {
public:
    SampleController(model::SampleRepository& sampleRepository, view::SampleView& sampleView);

    void Run();

private:
    void RegisterSample();
    void ListSamples();
    void SearchSamples();

    model::SampleRepository& sampleRepository_;
    view::SampleView& sampleView_;
};

}  // namespace sos::controller
