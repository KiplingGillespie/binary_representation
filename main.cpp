#include <iostream>
#include "binvec.h"
#include <cstring>
#include <chrono>
#include <cstdlib>

using namespace std;

/*
Kipling Gillespie
CS315-003
Homework 2
The purpose of this assignment is to simulate a binary number using a vector of 1's
and 0's and write an addition, subtraction, multiplication, division, and exponential modulation
algorithm that work on the binary vectors.
*/

int main(int argc, char* argv[])
{
    // If argc is less than 3 we didn't get enough inputs and should exit.
    if(argc < 4){
        cout << "Too few inputs." << endl;
        return 1;
    }

    // Switch value to determine which algorithm to run
    int operation;
    operation = atoi(argv[1]);

    char* binValue;
    BinVec result;

    // check arguments 2 to make sure it consist of only 1's, 0's and a NULL character.
    size_t size = strlen(argv[2]);
    char* argument = new char[size+1];
    for(size_t i = 0; i < size; i++){
        // make sure the current digit of the argument is only a 1, 0, or Null
        if(argv[2][i] == '0' || argv[2][i] == '1' || (int)argv[2][i] == 0){
            argument[i] = argv[2][i];
        }
        else{
            // A character that was not 1, 0, or NULL was detected. Exit Program
            cout << "Non-Binary Input Detected. Try new input." << endl;
            return 1;
        }
    }
    // Add a NULL character to the argument array to make it a cstyle string
    argument[size] = 0;
    BinVec op_1(argument);
    // clear argument array back to all NULL characters and release the memory;
    memset(argument, 0, size);
    delete[] argument;

    // Check argument 3 to make sure it consists of only 1's 0's and a NULL character
    size = strlen(argv[3]);
    argument = new char[size+1];
    for(size_t i = 0; i < size; i++){
        // check to see if the current digit of argument 2 is a 1, 0, or NULL character
        if(argv[3][i] == '0' || argv[3][i] == '1' || (int)argv[3][i] == 0){
            argument[i] = argv[3][i];
        }
        else{
            // Bad input
            cout << "Non-Binary Input Detected. Try new input." << endl;
            return 1;
        }
    }
    // Add NULL to end of the argument variable to make it a cstyle string
    argument[size] = 0;
    BinVec op_2(argument);
    // clear argument array back to all NULL characters;
    memset(argument, 0, size);
    delete[] argument;

    // Get value of N if there is a 4 argument
    BinVec N("0");
    if(argc == 5)
    {
        size = strlen(argv[4]);
        argument = new char[size+1];
        for(size_t i = 0; i < size; i++){
            // check to see if the current digit of argument 2 is a 1, 0, or NULL character
            if(argv[4][i] == '0' || argv[4][i] == '1' || (int)argv[4][i] == 0){
                argument[i] = argv[4][i];
            }
            else{
                // Bad input
                cout << "Non-Binary Input Detected. Try new input." << endl;
                return 1;
            }
        }
        // Add NULL to end of the argument variable to make it a cstyle string
        argument[size] = 0;
        N = BinVec(argument);
        // clear argument array back to all NULL characters;
        memset(argument, 0, size);
        delete[] argument;
    }


    // Display binary and decimal values for operand 1
    binValue = op_1.getBinary();
    cout << "Values of Operand 1" << endl;
    cout << "Bin:" << binValue << endl;
    delete[] binValue;
    cout << "Dec:" << op_1.getDec() << endl << endl;

    // Display binary and decimal values for operand 2
    binValue = op_2.getBinary();
    cout << "Values of Operand 2" << endl;
    cout << "Bin:" << op_2.getBinary() << endl;
    delete[] binValue;
    cout << "Dec:" <<op_2.getDec() << endl << endl;

    switch(operation)
    {
        // Addition
        case 0:
            {
                // Display the result of adding the operands
                result = op_1 + op_2;
                binValue = result.getBinary();
                cout << "Addition Result" << endl;
                cout << "Bin:" << binValue << endl;
                delete[] binValue;
                cout << "Dec:" << result.getDec() << endl;
                break;
            }

        // Subtraction
        case 1:
            {
                // Display the result of subtracting operand 2 from operand 1
                result = op_1 - op_2;
                binValue = result.getBinary();
                cout << "Subtraction Result" << endl;
                cout << "Bin:" << binValue << endl;
                delete[] binValue;
                cout << "Dec:" << result.getDec() << endl;
                break;
            }

        // multiplication
        case 2:
            {
                // Display the result of multiplying operand 1 by operand 2
                result = op_1 * op_2;
                binValue = result.getBinary();
                cout << "Multiplication Result" << endl;
                cout << "Bin:" << binValue << endl;
                delete[] binValue;
                cout << "Dec:" << result.getDec() << endl;
                break;
            }

        // Division
        case 3:
            {
                BinVec remainder = BinVec("0");
                BinVec quotient = BinVec("0");
                quotient = op_1.BinDiv(op_2, remainder);
                binValue = quotient.getBinary();
                cout << "Operand_1 div Operand_2" << endl;
                cout << "Quotient Result" << endl;
                cout << "Bin:" << binValue << endl;
                delete[] binValue;
                cout << "Dec:" << quotient.getDec() << endl;
                binValue = remainder.getBinary();
                cout << "Remainder" << endl;
                cout << "Bin:" << binValue << endl;
                delete[] binValue;
                cout << "Dec:" << remainder.getDec() << endl << endl;
                break;
            }

        // Exponential function
        case 4:
            {
                if(argc == 5)
                {
                    binValue = N.getBinary();
                    cout << "Value of N" << endl;
                    cout << "Bin:" << binValue << endl;
                    delete[] binValue;
                    cout << "Dec:" << N.getDec() << endl << endl;

                    BinVec result = op_1.BinMod(op_2, N);
                    binValue = result.getBinary();
                    cout << "operand_1^operand2 mod N = " << endl;
                    cout << "Bin:" << binValue << endl;
                    delete[] binValue;
                    cout << "Dec:" << result.getDec() << endl << endl;
                }
                break;
             }

        default:
            {
                cout << "Could not parse input" << endl;
            }

    }


    /*chrono::time_point<chrono::high_resolution_clock> start;
    chrono::time_point<chrono::high_resolution_clock> end;
    chrono::duration<double> diftime;
    int n = 1;
    while(diftime < chrono::duration<double>(600))
    {
        GenBin(op_1, op_2, N, n);
        start = chrono::high_resolution_clock::now();

        result = op_1.BinMod(op_2, N);

        end = std::chrono::high_resolution_clock::now();
        diftime = chrono::duration_cast<chrono::duration<double>>(end-start);

        cout << "Time of run " << n << " = " << diftime.count() << endl;
        cout << "X= " << op_1.getBinary() << endl;
        cout << "Y= " << op_2.getBinary() << endl;
        cout << "N= " << N.getBinary() << endl;
        cout << "Result = " << result.getBinary() << endl << endl << endl;

        n*=2;
    }*/


    return 0;
}
