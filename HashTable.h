//
// Created by ibraheem-96 on 04/01/2019.
//

#ifndef UNTITLED28_HASH_H
#define UNTITLED28_HASH_H

#include "EmployeeAux.h"

typedef enum{SUCCESS_HASH,FAILURE_HASH}HashStatus;

class HashTable{

public:

    long long int size;
    long long int current_size;
    long long int zeroEmployeeCount;
    long long int GradesSum;
    EmployeeAux** employeeAux_array;
    EmployeeAux* toDeleteEmployee;


    HashTable();
    ~HashTable();
    long long int setFunc(long long int x);
    void Rehash();
    HashStatus insert(EmployeeAux* employee1);
    HashStatus delete1(long long int employeeId);
    static void  initaliz(EmployeeAux** array,long long int n);
    HashStatus searchFunc(long long int x,long long int* res);

};




#endif //UNTITLED28_HASH_H
