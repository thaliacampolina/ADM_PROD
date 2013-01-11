#include "period.cc"
#include <iostream>
using namespace std;

int main()
{
    int size = 8;
    Period matrix[size];

    matrix[2] = Period(10, 9, 8, 7, 6, 5, 4, 0, 2);
    matrix[2].setStockMean(6.1);

    pprint(matrix, size);

    return 0;
}
