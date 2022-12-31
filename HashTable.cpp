//
// Created by ibraheem-96 on 04/01/2019.
//

#include "HashTable.h"




void HashTable:: initaliz(EmployeeAux** array,long long int n){
    
    for(long long int i=0;i<n;i++){
        array[i]= nullptr;
    }
    return;
}
 



HashTable:: HashTable():size(11),current_size(0),zeroEmployeeCount(0),GradesSum(0),toDeleteEmployee(new EmployeeAux()){
    toDeleteEmployee->isDeleted= true;
	toDeleteEmployee->isZero= false;
    employeeAux_array = new EmployeeAux*[size];
    initaliz(employeeAux_array,size);
    return ;
}


HashTable::~HashTable(){
    delete toDeleteEmployee;
    delete[] employeeAux_array;
}


HashStatus HashTable:: searchFunc(long long int x,long long int *res){


    long long int i=0;
    long long int h=x%size;
    while(1){
        if(!employeeAux_array[h] )return FAILURE_HASH;
        if(employeeAux_array[h]->employeeId==x){
            *res=h;
            return SUCCESS_HASH;
        }
        h++;
        i++;
        if(size==i) {
            *res=-1;
            return FAILURE_HASH;

        }

        h%=size;
    }
}


long long int HashTable::setFunc(long long int x){

    long long int h=x%size;
    while(1){
        if(!employeeAux_array[h] || employeeAux_array[h]->isDeleted ){
            //need to delete
            return h;
        }
        h++;
        h%=size;
    }
}



void HashTable::Rehash() {

    if (current_size == size) {
        size = 2 * size;
        EmployeeAux** EmployeeAux_array1 = new EmployeeAux* [size];
        EmployeeAux** pEmployeeAux=employeeAux_array;
        employeeAux_array=EmployeeAux_array1;
        initaliz(EmployeeAux_array1, size);
        for (long long int i = 0; i < size / 2; i++) {
            auto  lo=pEmployeeAux[i];
            employeeAux_array[setFunc(pEmployeeAux[i]->employeeId)] = pEmployeeAux[i];
            pEmployeeAux[i]= nullptr;

        }
        delete[] pEmployeeAux;
    }

    if (current_size == ((1 / 4) * size)) {
        size = size / 2;
        EmployeeAux** EmployeeAux_array1 = new EmployeeAux* [size];
        EmployeeAux** pEmployeeAux=employeeAux_array;
        employeeAux_array=EmployeeAux_array1;
        initaliz(EmployeeAux_array1, size);
        for (long long int i = 0; i < size * 2; i++) {
            if(!pEmployeeAux[i]||pEmployeeAux[i]->isDeleted== true){

                continue;
            }
            employeeAux_array[setFunc(pEmployeeAux[i]->employeeId)] = pEmployeeAux[i];
            pEmployeeAux[i]= nullptr;
        }
        delete[] pEmployeeAux;
    }
}



HashStatus HashTable:: insert(EmployeeAux* employee1){

    long long int index=0;
    if( searchFunc(employee1->employeeId,&index)==SUCCESS_HASH)
        return FAILURE_HASH;

    long long int place=setFunc(employee1->employeeId);

    employeeAux_array[place]= employee1;

    current_size++;
    zeroEmployeeCount++;
    GradesSum+=employee1->employee.employeeGrade;
    Rehash();

    return SUCCESS_HASH;
}



HashStatus HashTable:: delete1(long long int employeeId){

    if(current_size==0){
        return FAILURE_HASH;
    }
    long long int index=0;

    if(searchFunc(employeeId,&index)==FAILURE_HASH)return FAILURE_HASH;
    if((employeeAux_array[index]->isZero))
    zeroEmployeeCount--;
    if(zeroEmployeeCount<0)zeroEmployeeCount=0;

    if((employeeAux_array[index]->isZero))
        GradesSum-=employeeAux_array[index]->employee.employeeGrade;
    if(GradesSum<0)GradesSum=0;
    employeeAux_array[index]= toDeleteEmployee;
    current_size--;
    Rehash();
    return SUCCESS_HASH;

}


