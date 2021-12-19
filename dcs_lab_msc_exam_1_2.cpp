/*
A simple program to calculate the equation of a function containing factorial.
Author: Asif Rahman Rumee
Date: 18/12/2021

*/

#include<iostream>
#include<math.h>
#include<iomanip>

using namespace std;

unsigned long long factorial(int n){
    unsigned long long fact = 0;
    if(n<2){
        return 1;
    }
    return n*factorial(n-1);
}

main(){
    double sum = 0;
    for(short i=0; i<21; i++){
        sum += pow(5,i)/factorial(i);
    }
    sum *= pow(exp(1), -5);
    cout<< "Probability of having more than 20 users: "<< setprecision(15)<< 1-sum;

    return 0;
}
