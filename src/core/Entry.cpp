#include "Entry.h"
#include <stdexcept>

Entry::Entry(long long numerator, long long denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    fraction_ = {numerator, denominator};
    reduce();
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
}

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
