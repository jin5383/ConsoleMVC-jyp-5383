#include "SampleView.h"

#include <iostream>

#include "ConsoleIO.h"

namespace sos::view {

void SampleView::PrintSubMenu() const {
    PrintDivider();
    std::cout << "[시료 관리]\n";
    std::cout << "1. 시료 등록\n";
    std::cout << "2. 시료 조회\n";
    std::cout << "3. 시료 검색\n";
    std::cout << "0. 이전 메뉴\n";
    PrintDivider();
}

SampleMenuChoice SampleView::ReadChoice() const {
    int choice = ReadInt("선택: ");
    switch (choice) {
        case 0: return SampleMenuChoice::Back;
        case 1: return SampleMenuChoice::Register;
        case 2: return SampleMenuChoice::List;
        case 3: return SampleMenuChoice::Search;
        default: return SampleMenuChoice::Invalid;
    }
}

NewSampleInput SampleView::ReadNewSampleInput() const {
    NewSampleInput input;
    input.name = ReadLine("시료 이름: ");
    input.avgProductionTime = ReadInt("평균 생산시간(분): ");
    int yieldPercent = ReadInt("수율(%, 0~100): ");
    input.yield = yieldPercent / 100.0;
    return input;
}

std::string SampleView::ReadSearchKeyword() const {
    return ReadLine("검색할 이름 키워드: ");
}

void SampleView::PrintSampleList(const std::vector<model::Sample>& samples) const {
    if (samples.empty()) {
        PrintMessage("등록된 시료가 없습니다.");
        return;
    }
    std::cout << "ID\t이름\t평균생산시간\t수율\t재고\n";
    for (const auto& sample : samples) {
        std::cout << sample.id << "\t" << sample.name << "\t" << sample.avgProductionTime
                   << "\t" << sample.yield << "\t" << sample.stock << "\n";
    }
}

void SampleView::PrintRegisterResult(const model::Sample& sample) const {
    std::cout << "시료가 등록되었습니다. (ID: " << sample.id << ", 이름: " << sample.name << ")\n";
}

}  // namespace sos::view
