#pragma once

#include <string>
#include <vector>

#include "../Model/Sample.h"

namespace sos::view {

enum class SampleMenuChoice {
    Register = 1,
    List = 2,
    Search = 3,
    Back = 0,
    Invalid = -1
};

struct NewSampleInput {
    std::string name;
    double avgProductionTime = 0.0;
    double yield = 0.0;
};

// 4.1 시료 관리 화면
class SampleView {
public:
    void PrintSubMenu() const;
    SampleMenuChoice ReadChoice() const;

    NewSampleInput ReadNewSampleInput() const;
    std::string ReadSearchKeyword() const;

    void PrintSampleList(const std::vector<model::Sample>& samples) const;
    void PrintRegisterResult(const model::Sample& sample) const;
};

}  // namespace sos::view
