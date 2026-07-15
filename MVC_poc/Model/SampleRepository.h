#pragma once

#include <string>
#include <vector>

#include "Sample.h"

namespace sos::model {

// 시료 데이터 저장/조회 담당. PoC 단계에서는 메모리 상에서만 관리한다.
// (데이터 영속성 처리는 별도 PoC 과제에서 다룬다.)
class SampleRepository {
public:
    Sample& Add(const std::string& name, double avgProductionTime, double yield);

    std::vector<Sample>& GetAll();
    Sample* FindById(int id);
    std::vector<Sample*> FindByNameContains(const std::string& keyword);

private:
    std::vector<Sample> samples_;
    int nextId_ = 1;
};

}  // namespace sos::model
