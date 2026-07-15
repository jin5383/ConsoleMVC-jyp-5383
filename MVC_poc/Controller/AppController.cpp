#include "AppController.h"

namespace sos::controller {

AppController::AppController()
    : sampleController_(sampleRepository_, sampleView_),
      orderController_(sampleRepository_, orderRepository_, productionQueue_, orderView_),
      monitoringController_(sampleRepository_, orderRepository_, monitoringView_),
      productionController_(sampleRepository_, orderRepository_, productionQueue_,
                             productionView_),
      releaseController_(sampleRepository_, orderRepository_, releaseView_) {}

void AppController::Run() {
    bool running = true;
    while (running) {
        mainMenuView_.PrintMenu(sampleRepository_.GetAll(), orderRepository_.GetAll());
        switch (mainMenuView_.ReadChoice()) {
            case view::MainMenuChoice::SampleManagement:
                sampleController_.Run();
                break;
            case view::MainMenuChoice::Order:
                orderController_.Run();
                break;
            case view::MainMenuChoice::Monitoring:
                monitoringController_.Run();
                break;
            case view::MainMenuChoice::Release:
                releaseController_.Run();
                break;
            case view::MainMenuChoice::ProductionLine:
                productionController_.Run();
                break;
            case view::MainMenuChoice::Exit:
                running = false;
                break;
            default:
                break;
        }
    }
}

}  // namespace sos::controller
