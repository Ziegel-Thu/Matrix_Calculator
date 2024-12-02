#pragma once

#include "Entry.h"
#include <vector>

class EntryPolynomial {
public:
    EntryPolynomial() : coefficients_({Entry(0, 1)}) {}
    EntryPolynomial(const std::vector<Entry>& coefficients);
    ~EntryPolynomial();
    std::vector<Entry> getCoefficients() const;
    void setCoefficients(const std::vector<Entry>& coefficients);
    void setIthCoefficient(int i, const Entry& coefficient);
    Entry getIthCoefficient(int i) const;
    int getDegree() const;
    void multiply(const Entry& factor);
    void degreeCorrection();
    EntryPolynomial operator*(const EntryPolynomial& factor);
    EntryPolynomial operator+(const EntryPolynomial& factor);
    EntryPolynomial operator-() const;
    EntryPolynomial operator-(const EntryPolynomial& factor);
    EntryPolynomial divideLinearFactor(const Entry& root);
    std::vector<std::pair<Entry,int> > solveRationalRoots();
    static std::pair<std::vector<long long>,std::vector<int> > factorize(const long long &n);
    static long long multiply(const std::vector<long long> &primeList,const std::vector<int> &primePower);
    static std::vector<int> nextFactor(std::vector<int> cur, const std::pair<std::vector<long long>,std::vector<int> > &result);


private:
    std::vector<Entry> coefficients_;
    Entry plugIn(const Entry& value) const;
    long long findCommonMultiple(const EntryPolynomial& factor);
    Entry solveRationalRoot(); 
};