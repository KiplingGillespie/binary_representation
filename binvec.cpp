#include "binvec.h"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

BinVec::BinVec()
// Empty Constructor
{
}

BinVec::~BinVec()
// Destructor
// It empties out any members left in the operand array
{
    operand.clear();
}

BinVec::BinVec(const BinVec& other)
// Copy constructor
// copies values from the input BinVec's operand into this's operand.
{
    this->operand = other.operand;
}

BinVec::BinVec(const char* input)
// Constructor that takes in a cstyle string. It loops through the string and adds
// each character to the operand array starting from the first member of the string
// going to the last.
{
    size_t len = strlen(input);
    for(size_t i = 1; i <= len; i++){
        operand.push_back(input[i-1] - 48);
    }
}

BinVec& BinVec::operator=(const BinVec& rhs)
// Assignment operator
{
    // Prevent self assignment
    if (this == &rhs)
        return *this; // handle self assignment

    // Clears our this operand's values
    this->operand.clear();
    this->operand = rhs.operand;

    //assignment operator
    return *this;
}

BinVec& BinVec::operator+=(const BinVec& other){
    // Input: The RHS operator must have fewer
    // This method will handle my + operation. I will take in another BinVec class
    // and add each digit together with modulus addition.
    BinVec big;
    BinVec small;

    // Tells me which operand is bigger than the other
    if(*this < other){
        big = other;
        small = *this;
    }
    else{
        big = *this;
        small = other;
    }

    // Initialize the carrybit, sum, and size's 1 and 2.
    bool carry = false;
    int sum = 0;
    size_t size1 = big.operand.size();
    size_t size2 = small.operand.size();

    // Loop through each member of the smaller operand and add the
    // matching member from the bigger operand
    for(size_t i = 0; i < size2; i++){
        // If the carry bit is check add and extra 1
        if(carry){
            sum = (big.operand[i] + small.operand[i] + 1);
            big.operand[i] = sum % 2;
            // Set carry bit if sum/2 = 1.
            (sum/2) ? carry = true : carry = false;
        }
        else{
            sum = (big.operand[i] + small.operand[i]);
            big.operand[i] = sum % 2;
            // Set carry bit if sum/2 = 1
            (sum/2) ? carry = true : carry = false;
            }
    }

    // Propogate the carry bit through the rest of the first operand
    for(size_t i = size2; i < size1; i++){
        if(carry){
            sum = big.operand[i] + 1;
            big.operand[i] = sum %2;
            if(sum/2)
                carry = true;
            else{
                // The carry bit has been set to false and we
                // have propogated as far as we need to.
                carry = false;
                break;
            }
        }
    }

    // if there is still a carry bit after we checked all of the
    // bigger operand add one more 1
    if(carry)
        big.operand.push_back(1);

    // Copy the values of big to this.
    *this = big;

    return *this;
}

const BinVec BinVec::operator+(const BinVec& other)
// Sets result to the value of LHS operand
// Takes in another BinVec and adds it to the LHS
{
    BinVec result = *this;
    result += other;
    return result;
}

BinVec& BinVec::operator-=(const BinVec& other)
// I subtract the binary value in other from the binary value
// in this.
{
    // Get sizes of each BinVec
    size_t size1 = this->operand.size();
    size_t size2 = other.operand.size();

    // Loop through the BinVec with fewer digits
    for(size_t i = 0; i < size2; i++){
        // Check to see if I need a carry bit
        if(!this->operand[i] && other.operand[i]){
            // I need a carry bit so I find the next 1 value in the
            // bigger operand.
            for(size_t j = i; j < size1; j++){
                if(this->operand[j]){
                    // I found the bit I need to carry back so I set it to 0
                    this->operand[j] = 0;
                    // Next toggle all the 0's to 1's back to where I need to subtract from.
                    for(int k = j-1; k >= (int)i; k--){
                        this->operand[k] = 1;
                    }
                    // I carried the bit trough to where I need it. Break;
                    break;
                }
            }
        }
        else{
            // I don't need a carry bit so if the the current digit of
            // each operand is 1 I set the largers to 0 and continue on.
            if(this->operand[i] && other.operand[i])
                this->operand[i] = 0;
        }
    }


    for(int i = this->operand.size(); i > 0; i--)
    {
        if(this->operand[i-1] == 0)
            this->operand.pop_back();
        else
            break;
    }

    return *this;
}

const BinVec BinVec::operator-(const BinVec& other)
// I subtract Other from the LHS variable
{
    BinVec result = *this;
    result -= other;
    return result;
}

BinVec& BinVec::operator*=(const BinVec& other)
// This method will multiply the LHS operand by the
// right hand size operand.
{
    size_t size2 = other.operand.size();
    BinVec future;
    BinVec result;
    // future will be the bit shifted version
    // to be added to.

    // Initialize future
    future = *this;

    // This is so I don't accidentally add future to result twice.
    if(other.operand[0])
        result = *this;

    // For every digit in other add a zero to the LSB of future
    for(size_t i = 1; i < size2; i++){
        future.operand.insert(future.operand.begin(), 0);

        // If the current bit is 1 add future to result;
        if(other.operand[i]){
            result += future;
        }
    }

    if(!result.operand.size())
        result.operand.push_back(0);

    *this = result;
    return *this;
}

const BinVec BinVec::operator*(const BinVec& other)
// Multiply the LHS operand by the RHS operand
{
    BinVec result = *this;
    result *= other;
    return result;
}

const BinVec BinVec::BinDiv(const BinVec& y, BinVec& r)
// INPUT: three BinVecs, Y must have an integer value, r can be empty, (this)
//          must have a value
// OUTPUT: the BinVec r returns the remainder, and the BinVec q is the quotient.
// the calling binvec is divided by the binvec y.
{
    BinVec x = *this;
    BinVec q("0");

    // determine if x is currently odd, (LSB is 1)
    bool xOdd = bool(x.operand[0]);

    // If x is zero. return 0 for q and r
    if(x.operand.size()== 1 && x.operand[0] == 0)
    {
        // clear remainder
        r.operand.clear();
        r.operand.insert(r.operand.begin(), 0);
        q.operand.clear();
        q.operand.insert(q.operand.begin(), 0);
        return q;
    }

    // Divide x by 2 and add
    x.operand.erase(x.operand.begin());
    if(x.operand.size() < 1)
        x.operand.push_back(0);

    // Recursize call.
    q = x.BinDiv(y, r);


    // Multiply r and q by 2
    if(! (q == BinVec("0") ))
        q.operand.insert(q.operand.begin(), 0);

    if(! (r == BinVec("0") ))
        r.operand.insert(r.operand.begin(), 0);

    // increase remainder by one
    if(xOdd)
        r += BinVec("1");

    // if the remainder is greater than or equal to the denominator
    // subtract the denominator from r and increase quotient by 1.
    if(r >= y)
    {
        r = r - y;
        q += BinVec("1");
    }

    return q;
}

const BinVec BinVec::BinMod(BinVec& y, BinVec& N)
//INPUT:    the calling BinVec, BinVec y, and BinVec N
//OUTPUT:   BinVec z will be the remainder of this raised to y divided by N
{
    BinVec z("1");
    BinVec w = *this;
    BinVec temp("0");

    int ylen = y.operand.size();
    for(int i = 0; i < ylen; i++)
    {
        if(y.operand[i] == 1)
        {
            // stores remainder in z.
            temp = w*z;

            // z = temp Mod N
            temp.BinDiv(N, z);

        }

        temp = w*w;
        temp.BinDiv(N, w);
        //std::cout << "Z = " << z.getBinary() << std::endl;
    }

    return z;
}

bool BinVec::operator==(const BinVec& other) const
// INPUT: this and BinVec other
// OUTPUT: returns true if this's operand matched other's operand
{
    size_t VecSize = operand.size();
    if(VecSize != other.operand.size())
        return false;

    for(size_t i = 0; i < VecSize; i++)
    {
        if(operand[i] != other.operand[i])
            return false;
    }

    return true;
}

bool BinVec::operator<(const BinVec& other)const
// Compare the number of digits in each BinVec's Operand member
// Return True if LHS is less than RHS.
{
    if(operand.size() > other.operand.size())
        return false;
    else if(operand.size() < other.operand.size())
        return true;

    int VecSize = operand.size();
    for(size_t i = VecSize; i > 0; i--)
    {
        if(operand[i-1] < other.operand[i-1])
            return true;
        else if(operand[i-1] > other.operand[i-1])
            return false;
    }

    return false;
}

bool BinVec::operator<=(const BinVec& other)const
// Compare the number of digits in each BinVec's Operand member
// Return True if LHS is less than RHS.
{
    if(*this > other)
        return false;
    else
        return true;


}

bool BinVec::operator>(const BinVec& other)const
// Compare the number of digits in each BinVec's Operand member
// Return True if LHS is greater than RHS.
{
    if(operand.size() < other.operand.size())
        return false;
    else if(operand.size() > other.operand.size())
        return true;

    int VecSize = operand.size();
    for(size_t i = VecSize; i > 0; i--)
    {
        if(operand[i-1] > other.operand[i-1])
            return true;
        else if(operand[i-1] < other.operand[i-1])
            return false;
    }
    return false;
}

bool BinVec::operator>=(const BinVec& other)const
// Return true if LHS is not smaller than RHS.
{
    if(*this < other)
        return false;
    else
        return true;
}

std::vector<int> BinVec::getOperand()
// returns the value of the operand vector
{
    return this->operand;
}

char* BinVec::getBinary()
// Returns the binary value of the BinVec as a cstyle string
{
    int len = operand.size();
    // create a dynamic character array of 1 digit longer than the
    // operand so I can add in a Null terminator at the end.
    char *output = new char[len+1];

    //  swap the order of the operand so that
    // the LSB is the last bit entered into the string
    for(int i = 0; i < len; i++){
        // cast the integer to a character and offset to get the correct
        // characters
        output[i] = (char)(operand[i]+48);
    }

    // set last character to null.
    output[len] = 0;

    return output;
}

const unsigned long long BinVec::getDec()
// Output the binary value as an unsigned long
// For each 1 in the operand I add it to the output variable multiplied
// by 2 to the power of it's position in the operand.
{
    unsigned long long dec;
    size_t size;

    // initialize our decimal output to 0
    dec = 0;
    size = operand.size();

    // Add the binary digit's value to our output
    for(size_t i = 0; i < size; i++){
        if(operand[i] == 1)
        {
            long double power = pow(2,i);
            dec += power;
        }
    }

    return dec;
}

void GenBin(BinVec &x, BinVec &y, BinVec &N, int n)
// This takes in 3 BinVecs x, y, and N and an integer N.
// It will add n 1's and n 0's to the middle of each BinVec
// and return's by reference their value
{
    int i;
    x = BinVec("11");

    // add n 0's to x
    for(i = 0; i < n; i++)
    {
        x.operand.push_back(0);
    }

    // add n 1's to x
    for(i = 0; i < n; i++)
    {
        x.operand.push_back(1);
    }


    y = BinVec("10");
    // add n 0's to y
    for(i = 0; i < n; i++)
    {
        y.operand.push_back(0);
    }

    // add n 1's to y
    for(i = 0; i < n; i++)
    {
        y.operand.push_back(1);
    }

    N = BinVec("101");
    // add n 0's to N
    for(i = 0; i < n; i++)
    {
        N.operand.push_back(0);
    }

    // add n 1's to N
    for(i = 0; i < n; i++)
    {
        N.operand.push_back(1);
    }
    N.operand.push_back(0);
    N.operand.push_back(1);
}
