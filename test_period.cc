#include "period.cc"
#include <iostream>
using namespace std;

int main()
{
    int size = 8;
    Period* matrix = new Period[8];

    matrix[2] = Period(10, 9, 8, 7, 6, 5, 4, 3.1, 2); 

    pprint(matrix, size);

    return 0;
}
