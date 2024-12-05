#include "EntryPolynomial.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

EntryPolynomial::EntryPolynomial(const std::vector<Entry>& coefficients) : coefficients_(coefficients) {}

EntryPolynomial::~EntryPolynomial() {}

std::vector<Entry> EntryPolynomial::getCoefficients() const {
    return coefficients_;
}

void EntryPolynomial::setCoefficients(const std::vector<Entry>& coefficients) {
    coefficients_ = coefficients;
}

void EntryPolynomial::setIthCoefficient(int i, const Entry& coefficient) {
    while(i>=static_cast<int>(coefficients_.size())){
        coefficients_.push_back(Entry(0,1));
    }
    coefficients_[i] = coefficient;
}

Entry EntryPolynomial::getIthCoefficient(int i) const {
    if(i>=static_cast<int>(coefficients_.size())){
        return Entry(0,1);
    }
    return coefficients_[i];
}

int EntryPolynomial::getDegree() const {
    return coefficients_.size()-1;
}

void EntryPolynomial::multiply(const Entry& factor){
    for(int i=0;i<static_cast<int>(coefficients_.size());i++){
        coefficients_[i] = coefficients_[i] * factor;
    }
}

void EntryPolynomial::degreeCorrection(){
    while(coefficients_.size()>1&&coefficients_.back()==Entry(0,1)){
        coefficients_.pop_back();
    }
}

EntryPolynomial EntryPolynomial::operator*(const EntryPolynomial& factor){
    std::vector<Entry> result(coefficients_.size()+factor.getDegree(),Entry(0,1));
    for(int i=0;i<static_cast<int>(coefficients_.size());i++){
        for(int j=0;j<static_cast<int>(factor.getCoefficients().size());j++){
            result[i+j] = result[i+j] + coefficients_[i] * factor.getIthCoefficient(j);
        }
    }
    return EntryPolynomial(result);
}

EntryPolynomial EntryPolynomial::operator+(const EntryPolynomial& factor){
    std::vector<Entry> result(std::max(static_cast<int>(coefficients_.size()),static_cast<int>(factor.getDegree()+1)),Entry(0,1));
    for(int i=0;i<static_cast<int>(result.size());i++){
        if(i<static_cast<int>(coefficients_.size()  ))
        {result[i] = coefficients_[i] + factor.getIthCoefficient(i);}
        else{
            result[i] = factor.getIthCoefficient(i);
        }
    }
    degreeCorrection();
    return EntryPolynomial(result);
}

EntryPolynomial EntryPolynomial::operator-() const {
    std::vector<Entry> result(coefficients_);
    for(int i=0;i<static_cast<int>(result.size());i++){
        result[i] = -result[i];
    }
    return EntryPolynomial(result);
}

EntryPolynomial EntryPolynomial::operator-(const EntryPolynomial& factor){
    return *this + (-factor);
    
}

Entry EntryPolynomial::plugIn(const Entry& value) const {
    Entry result(0,1);
    for(int i = coefficients_.size()-1;i>=0;i--){
        result = result * value + coefficients_[i];
    }
    return result;
}

EntryPolynomial EntryPolynomial::divideLinearFactor(const Entry& root){
    EntryPolynomial numerator(coefficients_);
    EntryPolynomial result({Entry(0,1)});
    for(int i = numerator.getCoefficients().size()-1;i>=1;i--){
        result.setIthCoefficient(i-1,numerator.getIthCoefficient(i));
        numerator.setIthCoefficient(i-1,numerator.getIthCoefficient(i)*root+numerator.getIthCoefficient(i-1));
    }
    result.degreeCorrection();
    return result;
}

long long EntryPolynomial::findCommonMultiple(const EntryPolynomial& factor){
    long long result = 1;
    for(int i = 0;i<factor.getDegree();i++){
        long long temp = Entry::gcd(result,factor.getIthCoefficient(i).getDenominator());
        
        result = result/temp * factor.getIthCoefficient(i).getDenominator();//尽量防止溢出
        if(result>std::numeric_limits<long long>::max()){
            throw std::overflow_error("Common multiple exceeds long long limits");
        }
    }
    return result;
}

std::vector<std::pair<Entry, int> > EntryPolynomial::solveRationalRoots() {
    EntryPolynomial factor = *this;
    long long commonMultiple = findCommonMultiple(factor);
    EntryPolynomial temp = factor;
    temp.multiply(Entry(commonMultiple, 1));
    std::vector<std::pair<Entry, int> > result;

    while (temp.getDegree() >= 1) {
        Entry root = temp.solveRationalRoot();

        temp = temp.divideLinearFactor(root);
        int count = 1;  
        while (temp.getDegree() >= 1 && temp.plugIn(root) == Entry(0, 1)) {
            count++;
            temp = temp.divideLinearFactor(root);
        }
        result.push_back(std::make_pair(root, count));
    }

    return result;
}

std::pair<std::vector<long long>,std::vector<int> > EntryPolynomial::factorize(const long long &n){
    if(n==0){
        throw std::invalid_argument("Number is 0");
    }
    long long temp = n;
    std::vector<long long> primeList;
    std::vector<int> primePower;
    if(Entry::getPrimeList().empty()){
        Entry::initializePrimeList();
    }
    for(long long i : Entry::getPrimeList()){
        if(i*i>temp){
            if(temp>1){
                primeList.push_back(temp);
                primePower.push_back(1);
            }
            break;
        }
        int count = 0;
        while(temp%i==0){
            temp/=i;
            count++;
        }
        if(count>0){
            primeList.push_back(i);
            primePower.push_back(count);
        }
    }
    
    return std::make_pair(primeList,primePower);
}
long long EntryPolynomial::multiply(const std::vector<long long> &primeList,const std::vector<int> &primePower){
    long long result = 1;
    for(int i = 0;i<primeList.size();i++){
        result *= std::pow(primeList[i],primePower[i]);
    }
    return result;
}
std::vector<int> EntryPolynomial::nextFactor(std::vector<int> cur, const std::pair<std::vector<long long>,std::vector<int> > &result){
    for(int i = 0;i<cur.size();i++){
        if(cur[i]<result.second[i]){
            cur[i]++;
            return cur;
        }
        cur[i] = 0;
    }
    return std::vector<int>(cur.size(),0);
}
Entry EntryPolynomial::solveRationalRoot(){
    EntryPolynomial factor = *this;
    if(factor.getDegree()==0){
        throw std::invalid_argument("Polynomial degree is 0");
    }
    if(factor.getIthCoefficient(0).getNumerator()==0){
        return Entry(0,1);
    }
    std::pair<std::vector<long long>,std::vector<int> > factorListLastTerm = factorize(std::abs(factor.getIthCoefficient(0).getNumerator()));
    std::pair<std::vector<long long>,std::vector<int> > factorListLeadTerm = factorize(std::abs(factor.getIthCoefficient(factor.getDegree()-1).getNumerator()));
    std::vector<int> curNumerator = std::vector<int>(factorListLastTerm.second.size(),0);
    std::vector<int> curDenominator = std::vector<int>(factorListLeadTerm.second.size(),0);
    bool flag = true;
    while(flag){
        Entry testRoot = Entry(multiply(factorListLastTerm.first,curNumerator),multiply(factorListLeadTerm.first,curDenominator));
        if(factor.plugIn(testRoot)==Entry(0,1)){
            return testRoot;
        }
        if(factor.plugIn(-testRoot)==Entry(0,1)){
            return -testRoot;
        }
        std::vector<int> temp = nextFactor(curNumerator,factorListLastTerm);
        if(temp==std::vector<int>(curNumerator.size(),0)){
            curDenominator = nextFactor(curDenominator,factorListLeadTerm);
            if(curDenominator==std::vector<int>(curDenominator.size(),0)){
                flag = false;
            }
        }
        curNumerator = temp;
    }
    throw std::runtime_error("Irrational root!");
}
