// GE_project.cpp : by KMV
//

#include <iostream>
#include "container.h"

using namespace std;

int main()
{
    Vector vec(list<float>{ 1, 2, 3 });
    Vector vec2(list<float>{ 10, 10, 10 });
    Matrix mat(list<list<float>>{ {1, 2, 3}, { 4, 5, 6 }, { 7, 8, 9 } });
    Matrix mat2(list<list<float>>{ {10, 10}, { 10, 10 }, { 10, 10 } });
    Matrix mat3(list<list<float>>{ {1, 2, 3}, { 3, 2, 1 }, { 1, 3, 2 }});

    Vector resAdd = vec + vec2; 
    Vector resSub = vec - vec2; 
    Matrix resMulMat = mat * mat2; 
    Vector resMulVec = mat * vec2; 
    Matrix inv = mat3.Inv();

    resMulMat.print();
    resMulVec.print();
    inv.print();
}
