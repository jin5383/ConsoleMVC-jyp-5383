#pragma once

#include "../Model/OrderRepository.h"
#include "../Model/ProductionQueue.h"
#include "../Model/SampleRepository.h"
#include "../View/MainMenuView.h"
#include "MonitoringController.h"
#include "OrderController.h"
#include "ProductionController.h"
#include "ReleaseController.h"
#include "SampleController.h"

namespace sos::controller {

// 애플리케이션 전체 흐름을 담당하는 최상위 Controller.
// Model / View 인스턴스를 소유하고, 메인 메뉴 선택에 따라 하위 Controller를 실행한다.
class AppController {
public:
    AppController();

    void Run();

private:
    // Model
    model::SampleRepository sampleRepository_;
    model::OrderRepository orderRepository_;
    model::ProductionQueue productionQueue_;

    // View
    view::MainMenuView mainMenuView_;
    view::SampleView sampleView_;
    view::OrderView orderView_;
    view::MonitoringView monitoringView_;
    view::ProductionView productionView_;
    view::ReleaseView releaseView_;

    // Controller
    SampleController sampleController_;
    OrderController orderController_;
    MonitoringController monitoringController_;
    ProductionController productionController_;
    ReleaseController releaseController_;
};

}  // namespace sos::controller
