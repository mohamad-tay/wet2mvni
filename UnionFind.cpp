//
// Created by ibrah on 6/7/2022.
//

#include "UnionFind.h"

long long int UnionFind::find(long long int companyNum) {

    long long int temp=companyNum;
    long long int relativeValueSum=0;
    while(companysArray[temp].father!=-1) {

        relativeValueSum+=companysArray[temp].relativeValue;
        temp = companysArray[temp].father;

    }
    while(companysArray[companyNum].father!=-1) {
        long long int temp2=companysArray[companyNum].relativeValue;
        companysArray[companyNum].relativeValue=relativeValueSum;
        companysArray[companyNum].compVal=relativeValueSum+companysArray[temp].compVal;
        relativeValueSum-=temp2;
        companysArray[companyNum].father=temp;
        companyNum = companysArray[companyNum].father;

    }
        return temp;
}

long long int UnionFind::union1(long long int p, long long int q) {

    if(companysArray[p].size<=companysArray[q].size){
        companysArray[q].size+=companysArray[p].size;
        companysArray[p].father=q;
        companysArray[p].relativeValue=companysArray[p].compVal-companysArray[q].compVal;

        return q;
    }else{
        companysArray[p].size+=companysArray[q].size;
        companysArray[q].father=p;
        companysArray[q].relativeValue=companysArray[q].compVal-companysArray[p].compVal;
        return p;
    }

}

