#include "Entry.h"
#include <stdexcept>

Entry::Entry(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero"); // 检查分母是否为零
    }
    fraction_ = {numerator, denominator};
    reduce(); // 初始化时自动约分
}

int Entry::getNumerator() const {
    return fraction_.first; // 返回分子
}

int Entry::getDenominator() const {
    return fraction_.second; // 返回分母
}

int Entry::gcd(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a; // 返回最大公约数
}

void Entry::reduce() {
    int numerator = fraction_.first;
    int denominator = fraction_.second;
    int divisor = gcd(numerator, denominator); // 计算最大公约数

    fraction_.first = numerator / divisor; // 约分分子
    fraction_.second = denominator / divisor; // 约分分母

    // 确保分母为正
    if (fraction_.second < 0) {
        fraction_.first = -fraction_.first;
        fraction_.second = -fraction_.second;
    }
}
