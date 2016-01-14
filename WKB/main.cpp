#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma comment(lib, "mkl_rt.lib")
#pragma comment(lib, "gsl.lib")
#include <mkl.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <gsl/gsl_poly.h>
using namespace std;

const int N = 100; //空間分割数
const double b = 1.0 / 3.0;

const double E_BEGIN = -1.0 / (6.0*b*b);
const double E_END = 0.0;

double i2x(int i, double x1, double h){
    return x1 + i * h;
}

//ポテンシャル
double V(double x){
    return -(b / 3.0)*x*x*x + (1.0 / 2.0) * x*x - 1.0 / (6.0 * b*b);
}

//被積分関数
double f(double x, double E){
    if (E > V(x)){
        cout << "E > V(x)" << endl;
    }
    return sqrt(2 * (V(x) - E));
}

void getTurningPoints(vector<double> &x, double E){
    //求解
    gsl_poly_solve_cubic(-3.0 / (2 * b), 0.0, (3.0 / b)*(1 / (6.0*b*b) + E), &x[0], &x[1], &x[2]);

    //転回点の表示
    for (int i = 0; i < x.size(); i++){
        cout << "x" << i << " : " << x[i];
    }
}

int main(){

    double h = (x2 - x1) / N;
    double S_even, S_odd, S;
    S_even = S_odd = S = 0.0;
    double E = -1.2;

    for (int i = 1; i < (N / 2) - 1; i++){
        S_even += f(i2x(2 * i, x1, h), E);
    }

    for (int i = 1; i < N / 2; i++){
        S_odd += f(i2x(2 * i - 1, x1, h), E);
    }

    S = h * (f(i2x(0, x1, h), E) + 2 * S_even + 4 * S_odd + f(i2x(N - 1, x1, h), E)) / 3.0;

    cout << S << endl;

    return 0;
}