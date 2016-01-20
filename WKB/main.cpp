#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma comment(lib, "gsl.lib")
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <gsl/gsl_poly.h>
using namespace std;

const int N = 1000; //空間分割数
const double b = 1.0 / 3.5;

const double E_BEGIN = -1.0 / (6.0 * b*b);
const double E_END = 0.0;
const int EN = 1000;

double i2x(int i, double x1, double h){
    return x1 + i * h;
}

double i2E(int i){
    return E_BEGIN + i * (E_END - E_BEGIN) / EN;
}

//ポテンシャル
double V(double x){
    return -(b / 3.0)*x*x*x + (1.0 / 2.0) * x*x -1.0 / (6.0 * b*b);
}

//被積分関数
double f(double x, double E){
    if (E > V(x)){
        cout << "x: " << x << "\t" << "E > V(x)" << endl;
    }
    return sqrt(2 * (V(x) - E));
}

void calcTurningPoints(vector<double> &x, double E){
    //求解
    gsl_poly_solve_cubic(-3.0 / (2 * b), 0.0, (3.0 / b)*(1 / (6.0*b*b) + E), &x[0], &x[1], &x[2]);

    ////転回点の表示
    //cout << E << "\t";
    //for (int i = 1; i < (int)x.size(); i++){
    //    cout << "x" << i << " : " << x[i] << endl;
    //}
    //cout << endl;
}

double calcEta(vector<double> &x, double E){
    double h = (x[2] - x[1]) / N;

    double S_even, S_odd;
    S_even = S_odd = 0.0;

    for (int i = 1; i < (N / 2) - 1; i++){
        S_even += f(i2x(2 * i, x[1], h), E);
    }

    for (int i = 1; i < N / 2; i++){
        S_odd += f(i2x(2 * i - 1, x[1], h), E);
    }
    return h * (f(i2x(0, x[1], h) + 0.00001, E) + 2 * S_even + 4 * S_odd + f(i2x(N - 1, x[1], h), E)) / 3.0;
}

double calcT(double eta){
    return exp(-2 * eta) / pow(1 + pow(exp(-eta) / 2.0, 2), 2);
}

int main(){
    vector<double> x(3);

    ofstream ofs("./output/T.txt");

    for (int i = 1; i < EN; i++){
        double E = i2E(i);
        calcTurningPoints(x, E);
        double eta = calcEta(x, E);
        double T = calcT(eta);

        ofs << fixed;
        ofs << E << "\t";
        ofs << scientific;
        ofs << (1.0 / (2.0 * 2.0 * M_PI)) * T << endl;
    }

    return 0;
}