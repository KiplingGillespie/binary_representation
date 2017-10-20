#ifndef BINVEC_H
#define BINVEC_H

#include <vector>

/*
BinVec Class
The purpose of this class is to encapsulate a vector of integers and create
functionality that will allow me to treat it like a single binary number.
*/

class BinVec
{
    friend void GenBin(BinVec &x, BinVec &y, BinVec &N, int n);

    public:
        BinVec();
        virtual ~BinVec();
        BinVec(const BinVec& other);
        BinVec(const char* input);
        BinVec& operator=(const BinVec& other);
        BinVec& operator+=(const BinVec& other);
        const BinVec operator+(const BinVec& other);
        BinVec& operator-=(const BinVec& other);
        const BinVec operator-(const BinVec& other);
        BinVec& operator*=(const BinVec& other);
        const BinVec operator*(const BinVec& other);
        const BinVec BinDiv(const BinVec& y, BinVec& r);
        const BinVec BinMod(BinVec& y, BinVec& N);
        bool operator==(const BinVec& other) const;
        bool operator<(const BinVec& other) const;
        bool operator<=(const BinVec& other) const;
        bool operator>(const BinVec& other) const;
        bool operator>=(const BinVec& other) const;

        // Accessors
        std::vector<int> getOperand();
        char* getBinary();
        const unsigned long long getDec();

        // Mutators

    protected:
    private:
        std::vector<int> operand;
};

void GenBin(BinVec &x, BinVec &y, BinVec &N, int n);

#endif // BINVEC_H
