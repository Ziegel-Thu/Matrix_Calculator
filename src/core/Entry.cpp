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


