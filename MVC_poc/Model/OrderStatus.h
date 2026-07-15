#pragma once

namespace sos::model {

// 4.2~4.6, 전체 프로세스 상태 다이어그램 참고
enum class OrderStatus {
    RESERVED,   // 주문 접수
    REJECTED,   // 주문 거절 (모니터링 제외)
    PRODUCING,  // 승인 완료, 재고 부족으로 생산 중
    CONFIRMED,  // 승인 완료, 출고 대기 중
    RELEASE     // 출고 완료
};

inline const char* ToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::RESERVED:  return "RESERVED";
        case OrderStatus::REJECTED:  return "REJECTED";
        case OrderStatus::PRODUCING: return "PRODUCING";
        case OrderStatus::CONFIRMED: return "CONFIRMED";
        case OrderStatus::RELEASE:   return "RELEASE";
    }
    return "UNKNOWN";
}

}  // namespace sos::model
