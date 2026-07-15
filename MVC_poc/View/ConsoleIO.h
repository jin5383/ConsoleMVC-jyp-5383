#pragma once

#include <string>

namespace sos::view {

// 콘솔 입출력 공통 유틸리티. 다른 View들이 공유하는 최소한의 I/O 경계.
void PrintDivider();
void PrintMessage(const std::string& message);

int ReadInt(const std::string& prompt);
std::string ReadLine(const std::string& prompt);

}  // namespace sos::view
