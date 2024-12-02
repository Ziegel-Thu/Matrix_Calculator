#pragma once
#include <utility> // for std::pair
#include <vector>
class Entry {
public:
    // 添加默认构造函数
    Entry() : hasValue_(false), fraction_(0, 1) {}
    Entry(long long numerator, long long denominator);
    ~Entry();

    // 获取分子和分母
    long long getNumerator() const;
    long long getDenominator() const;
    bool hasValue_; // 添加此行以定义 hasValue_ 变量

    Entry operator+(const Entry& other) const;
    Entry operator-(const Entry& other) const;
    Entry operator*(const Entry& other) const;
    Entry operator/(const Entry& other) const;
    Entry operator-() const;
    bool operator==(const Entry& other) const;
    bool operator!=(const Entry& other) const;
    std::pair<Entry, long long> getSquareroot() const;
    static std::vector<long long> getPrimeList() ; // 静态成员函数，初始化素数列表
    static long long gcd(long long a, long long b);
    static std::vector<long long> primeList_; // 静态成员变量，存储素数列表
    static void initializePrimeList(); // 静态成员函数，初始化素数列表
    // 约分方法
    void reduce();


private:
    std::pair<long long, long long> fraction_; // 存储分数的分子和分母

};
