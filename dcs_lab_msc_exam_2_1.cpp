/*
A simple program to map from binary sequences to complex numbers and vice-versa.
Author: Asif Rahman Rumee
Date: 18/12/2021

*/

#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class point{
    float x_cord, y_cord;
public:
    point(float x=0, float y=0){
        x_cord = x;
        y_cord = y;
    }
    float get_x(){
        return x_cord;
    }
    float get_y(){
        return y_cord;
    }
    void display(){
        if(y_cord == 1){
            cout<< x_cord << " + " << "j"<<endl;
        }else if(y_cord == -1){
            cout<< x_cord << " - " << "j"<<endl;
        }else if(y_cord < 0){
            cout<< x_cord << " - " << y_cord * -1 << "j"<<endl;
        }
        else{
            cout<< x_cord << " + " << y_cord << "j"<<endl;
        }
    }
};

point points_list[16];
points_set(){
    int index = 0;
    int sign_x[4] = {1,1,-1,-1};
    int sign_y[4] = {1,-1,1,-1};
    for(int i=1; i<4; i+=2){
        for(int j=1; j<4; j+=2){
            for(int k=0; k<4; k++){
                points_list[index] = point(i*sign_x[k], j*sign_y[k]);
                index++;
            }
        }
    }
}

class complex_binary_alter{
    point a, r, b;
    short a_bits[4], b_bits[4];
public:
    void create_a(){
        short sign_real, sign_imaginary, digit_real, digit_imaginary;
        srand(time(NULL));
        for(int i=0; i<4; i++){
            a_bits[i] = rand()%2;
        }

        a_bits[0] == 0 ? sign_real = 1 : sign_real = -1;
        a_bits[1] == 0 ? sign_imaginary = 1 : sign_imaginary = -1;
        a_bits[2] == 0 ? digit_real = 1 : digit_real = 3;
        a_bits[3] == 0 ? digit_imaginary = 1 : digit_imaginary = 3;

        a = point(sign_real*digit_real, sign_imaginary*digit_imaginary);
    }

    void create_r(){
        unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
        default_random_engine e (seed);
        normal_distribution<double> gauss_distribution(0,sqrt(5));

        r = point(a.get_x() + gauss_distribution(e), a.get_y() + gauss_distribution(e));
    }

    short demap_b(){
        create_a();
        create_r();
        b = find_minimum(r);

        b.get_x() > 0 ? b_bits[0] = 0 : b_bits[0] = 1;
        b.get_y() > 0 ? b_bits[1] = 0 : b_bits[1] = 1;
        abs(b.get_x()) == 1 ? b_bits[2] = 0 : b_bits[2] = 1;
        abs(b.get_y()) == 1 ? b_bits[3] = 0 : b_bits[3] = 1;

        return count_bit_differences();
    }

    float find_distance(point p, point q){
        return sqrt((p.get_x() - q.get_x())*(p.get_x() - q.get_x()) + (p.get_y() - q.get_y())*(p.get_y() - q.get_y()));
    }

    point find_minimum(point p){
        float minimum = find_distance(p, points_list[0]);
        int min_idx = 0;

        for(int i=1; i<16; i++){
            if(minimum > find_distance(p, points_list[i])){
                minimum = find_distance(p, points_list[i]);
                min_idx = i;
            }
        }
        return points_list[min_idx];
    }

    short count_bit_differences(){
        short counts = 0;

        for(int i=0; i<4; i++){
            if(a_bits[i] != b_bits[i]){
                counts++;
            }
        }
        return counts;
    }
};

main(){
points_set();
int sum = 0;
for(int i=1; i<=10000; i++){
    complex_binary_alter trial;
    sum += trial.demap_b();
    cout<<endl;
}
cout<< "total number of bit differences: "<< sum;

return 0;
}
