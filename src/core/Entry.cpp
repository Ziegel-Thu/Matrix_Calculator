#include "Entry.h"
#include <stdexcept>
#include <limits>


Entry::Entry(long long numerator, long long denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    fraction_ = {numerator, denominator};
    reduce();
    hasValue_ = false;
}
Entry::~Entry() {
}   
long long Entry::getNumerator() const {
    return fraction_.first;
}

long long Entry::getDenominator() const {
    return fraction_.second;
}

long long Entry::gcd(long long a, long long b) const {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
};

void Entry::reduce() {
    long long numerator = fraction_.first;
    long long denominator = fraction_.second;
    long long divisor = gcd(numerator, denominator);

    fraction_.first = numerator / divisor;
    fraction_.second = denominator / divisor;

    if (fraction_.second < 0) {
        fraction_.first = -fraction_.first;
        fraction_.second = -fraction_.second;
    }
}

Entry Entry::operator+(const Entry& other) const {
    long long numerator = fraction_.first * other.fraction_.second + other.fraction_.first * fraction_.second;
    long long denominator = fraction_.second * other.fraction_.second;

    if (numerator > std::numeric_limits<long long>::max() || numerator < std::numeric_limits<long long>::min()) {
        throw std::overflow_error("Addition result exceeds long long limits");
    }

    return Entry(numerator, denominator);
}

Entry Entry::operator-(const Entry& other) const {
    long long numerator = fraction_.first * other.fraction_.second - other.fraction_.first * fraction_.second;
    long long denominator = fraction_.second * other.fraction_.second;

    if (numerator > std::numeric_limits<long long>::max() || numerator < std::numeric_limits<long long>::min()) {
        throw std::overflow_error("Subtraction result exceeds long long limits");
    }

    return Entry(numerator, denominator);
}

Entry Entry::operator*(const Entry& other) const {
    long long numerator = fraction_.first * other.fraction_.first;
    long long denominator = fraction_.second * other.fraction_.second;

    if (numerator > std::numeric_limits<long long>::max() || numerator < std::numeric_limits<long long>::min()) {
        throw std::overflow_error("Multiplication result exceeds long long limits");
    }

    return Entry(numerator, denominator);
}

Entry Entry::operator-() const {
    return Entry(-fraction_.first, fraction_.second);
}

bool Entry::operator==(const Entry& other) const {
    return fraction_.first == other.fraction_.first && fraction_.second == other.fraction_.second;
}

bool Entry::operator!=(const Entry& other) const {
    return !(this->operator==(other));
}

Entry Entry::operator/(const Entry& other) const {
    if (other.fraction_.first == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    long long numerator = fraction_.first * other.fraction_.second;
    long long denominator = fraction_.second * other.fraction_.first;

    if (numerator > std::numeric_limits<long long>::max() || numerator < std::numeric_limits<long long>::min() ||
        denominator > std::numeric_limits<long long>::max() || denominator < std::numeric_limits<long long>::min()) {
        throw std::overflow_error("Division result exceeds long long limits");
    }

    return Entry(numerator, denominator);
}

std::pair<Entry, long long> Entry::getSquareroot() const {
    if(primeList_.empty()){
        initializePrimeList();
    }
    long long numerator = fraction_.first;
    long long denominator = fraction_.second;
    Entry result(1, 1);

    std::vector<long long> primeList = getPrimeList();
    for(int i = 0; i < static_cast<int>(primeList.size());){
        if(numerator == 1 && denominator == 1){
            break;
        }
        if(primeList[i]*primeList[i] > numerator && primeList[i]*primeList[i] > denominator){
            continue;
        }
        if(numerator % (primeList[i]*primeList[i]) == 0){
            result.fraction_.first *= primeList[i];
        }
        else if (denominator % (primeList[i]*primeList[i]) == 0){
            result.fraction_.second *= primeList[i];
        }
        else{
            i++;
        }
        
    }
    result.fraction_.second *= denominator;
    long long root = numerator*denominator;
    return std::make_pair(result, root);

}
void Entry::initializePrimeList() {
    const long long maxPrime = 1000000; // 设定一个较大的上限
    const long long segmentSize = std::sqrt(maxPrime) + 1;

    // 生成小范围内的素数
    std::vector<bool> isSmallPrime(segmentSize, true);
    isSmallPrime[0] = isSmallPrime[1] = false;
    for (long long i = 2; i * i < segmentSize; ++i) {
        if (isSmallPrime[i]) {
            for (long long j = i * i; j < segmentSize; j += i) {
                isSmallPrime[j] = false;
            }
        }
    }

    // 将小范围内的素数存入列表
    std::vector<long long> smallPrimes;
    for (long long i = 2; i < segmentSize; ++i) {
        if (isSmallPrime[i]) {
            smallPrimes.push_back(i);
            primeList_.push_back(i);
        }
    }

    // 分段筛法
    std::vector<bool> isPrime(segmentSize, true);
    for (long long low = segmentSize; low <= maxPrime; low += segmentSize) {
        std::fill(isPrime.begin(), isPrime.end(), true);

        long long high = std::min(low + segmentSize - 1, maxPrime);

        for (long long prime : smallPrimes) {
            long long start = std::max(prime * prime, (low + prime - 1) / prime * prime);
            for (long long j = start; j <= high; j += prime) {
                isPrime[j - low] = false;
            }
        }

        for (long long i = low; i <= high; ++i) {
            if (isPrime[i - low]) {
                primeList_.push_back(i);
            }
        }
    }
}
std::vector<long long> Entry::getPrimeList() {
    return primeList_;
}
std::vector<long long> Entry::primeList_ = {};