#pragma once

#include <string>
#include <vector>

#include "../Model/Order.h"

namespace sos::view {

// 4.6 출고 처리 화면
class ReleaseView {
public:
    void PrintConfirmedOrders(const std::vector<model::Order*>& orders) const;
    int ReadOrderIdToRelease() const;
    void PrintReleaseResult(const model::Order& order) const;
    void PrintError(const std::string& message) const;
};

}  // namespace sos::view
