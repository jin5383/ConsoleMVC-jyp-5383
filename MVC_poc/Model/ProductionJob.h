#pragma once

namespace sos::model {

// 4.5 생산 라인 - 생산 큐(FIFO)에 들어가는 생산 작업 단위
struct ProductionJob {
    int orderId = 0;
    int sampleId = 0;
    int shortageQuantity = 0;           // 주문량 대비 부족분
    int actualProductionQuantity = 0;   // ceil(부족분 / 수율)
    double totalProductionTime = 0.0;   // 평균 생산시간 * 실 생산량
    int producedQuantity = 0;           // 현재까지 생산량 (진행 표시용)
};

}  // namespace sos::model
