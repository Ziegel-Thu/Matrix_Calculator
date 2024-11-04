#pragma once
#include <utility> // for std::pair

class Entry {
public:
    Entry(int numerator, int denominator);

    // 获取分子和分母
    int getNumerator() const;
    int getDenominator() const;

    // 约分方法
    void reduce();

private:
    std::pair<int, int> fraction_; // 存储分数的分子和分母
    int gcd(int a, int b) const; // 计算最大公约数
};
