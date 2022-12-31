//
// Created by ibrah on 6/7/2022.
//

#ifndef IBR_UNIONFIND_H
#define IBR_UNIONFIND_H


#include "Company.h"

class UnionFind {
public:
    long long int companysNum;
    Company* companysArray;

    explicit UnionFind(long long int k=0):companysNum(k), companysArray(new Company[k+1]){

        for(long long int i=1;i<k+1;i++){
            companysArray[i].compId=i;
            companysArray[i].compVal=(long double)i;
            companysArray[i].groupVal=(long double)i;
        }
    }
    ~UnionFind(){
        delete [] companysArray;
    }
    long long int find(long long int companyNum);
    long long int union1(long long int p,long long int q);





};


#endif //IBR_UNIONFIND_H
