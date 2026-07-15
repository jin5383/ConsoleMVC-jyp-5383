#include "SampleController.h"

namespace sos::controller {

SampleController::SampleController(model::SampleRepository& sampleRepository,
                                     view::SampleView& sampleView)
    : sampleRepository_(sampleRepository), sampleView_(sampleView) {}

void SampleController::Run() {
    bool running = true;
    while (running) {
        sampleView_.PrintSubMenu();
        switch (sampleView_.ReadChoice()) {
            case view::SampleMenuChoice::Register:
                RegisterSample();
                break;
            case view::SampleMenuChoice::List:
                ListSamples();
                break;
            case view::SampleMenuChoice::Search:
                SearchSamples();
                break;
            case view::SampleMenuChoice::Back:
                running = false;
                break;
            default:
                break;
        }
    }
}

void SampleController::RegisterSample() {
    view::NewSampleInput input = sampleView_.ReadNewSampleInput();
    model::Sample& sample =
        sampleRepository_.Add(input.name, input.avgProductionTime, input.yield);
    sampleView_.PrintRegisterResult(sample);
}

void SampleController::ListSamples() {
    sampleView_.PrintSampleList(sampleRepository_.GetAll());
}

void SampleController::SearchSamples() {
    std::string keyword = sampleView_.ReadSearchKeyword();
    std::vector<model::Sample*> matches = sampleRepository_.FindByNameContains(keyword);

    std::vector<model::Sample> results;
    results.reserve(matches.size());
    for (const auto* sample : matches) {
        results.push_back(*sample);
    }
    sampleView_.PrintSampleList(results);
}

}  // namespace sos::controller
