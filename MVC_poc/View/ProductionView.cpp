#include "ProductionView.h"

#include <iostream>

#include "ConsoleIO.h"

namespace sos::view {

void ProductionView::PrintSubMenu() const {
    PrintDivider();
    std::cout << "[생산 라인]\n";
    std::cout << "1. 현재 생산 중인 시료 확인\n";
    std::cout << "2. 생산 대기열(큐) 확인\n";
    std::cout << "3. 현재 작업 생산 완료 처리\n";
    std::cout << "0. 이전 메뉴\n";
    PrintDivider();
}

ProductionMenuChoice ProductionView::ReadChoice() const {
    int choice = ReadInt("선택: ");
    switch (choice) {
        case 0: return ProductionMenuChoice::Back;
        case 1: return ProductionMenuChoice::CurrentJob;
        case 2: return ProductionMenuChoice::WaitingQueue;
        case 3: return ProductionMenuChoice::CompleteCurrentJob;
        default: return ProductionMenuChoice::Invalid;
    }
}

void ProductionView::PrintCurrentJob(const std::optional<ProductionJobRow>& job) const {
    if (!job.has_value()) {
        PrintMessage("현재 생산 중인 시료가 없습니다.");
        return;
    }
    std::cout << "주문ID\t시료ID\t시료명\t부족분\t실생산량\t총생산시간\n";
    std::cout << job->orderId << "\t" << job->sampleId << "\t" << job->sampleName << "\t"
               << job->shortageQuantity << "\t" << job->actualProductionQuantity << "\t"
               << job->totalProductionTime << "\n";
}

void ProductionView::PrintWaitingQueue(const std::vector<ProductionJobRow>& jobs) const {
    if (jobs.empty()) {
        PrintMessage("대기 중인 생산 작업이 없습니다.");
        return;
    }
    std::cout << "순번\t주문ID\t시료명\t부족분\t실생산량\n";
    int order = 1;
    for (const auto& job : jobs) {
        std::cout << order++ << "\t" << job.orderId << "\t" << job.sampleName << "\t"
                   << job.shortageQuantity << "\t" << job.actualProductionQuantity << "\n";
    }
}

void ProductionView::PrintCompleteResult(int orderId) const {
    std::cout << "주문 " << orderId << "의 생산이 완료되어 CONFIRMED 상태로 전환되었습니다.\n";
}

void ProductionView::PrintNoJobMessage() const {
    PrintMessage("완료 처리할 생산 작업이 없습니다.");
}

}  // namespace sos::view
