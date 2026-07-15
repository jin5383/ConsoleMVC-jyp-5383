#include "SampleRepository.h"

namespace sos::model {

Sample& SampleRepository::Add(const std::string& name, double avgProductionTime, double yield) {
    Sample sample;
    sample.id = nextId_++;
    sample.name = name;
    sample.avgProductionTime = avgProductionTime;
    sample.yield = yield;
    sample.stock = 0;
    samples_.push_back(sample);
    return samples_.back();
}

std::vector<Sample>& SampleRepository::GetAll() {
    return samples_;
}

Sample* SampleRepository::FindById(int id) {
    for (auto& sample : samples_) {
        if (sample.id == id) {
            return &sample;
        }
    }
    return nullptr;
}

std::vector<Sample*> SampleRepository::FindByNameContains(const std::string& keyword) {
    std::vector<Sample*> result;
    for (auto& sample : samples_) {
        if (sample.name.find(keyword) != std::string::npos) {
            result.push_back(&sample);
        }
    }
    return result;
}

}  // namespace sos::model
