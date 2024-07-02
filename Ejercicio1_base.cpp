
#include <iostream>
#include <vector>
using namespace std;

struct Sumatorias {
    double sum_X = 0;
    double sum_Y = 0;
    double sum_XY = 0;
    double sum_X2 = 0;
    double sum_X_2 = 0;
    int n = 0;
};

Sumatorias calcularSums(const vector<int>& vectorX, const vector<int>& vectorY) {
    Sumatorias sums;
    sums.n = vectorX.size();

    for(int i = 0; i < sums.n; ++i) {
        sums.sum_X += vectorX[i];
        sums.sum_Y += vectorY[i];
        sums.sum_XY += vectorX[i] * vectorY[i];
        sums.sum_X2 += vectorX[i] * vectorX[i];
    }
    sums.sum_X_2 = sums.sum_X * sums.sum_X;

    return sums;
}

double pendiente(const Sumatorias& sums) {
    double m = ((sums.n * sums.sum_XY) - (sums.sum_X * sums.sum_Y)) / ((sums.n * sums.sum_X2) - sums.sum_X_2);
    return m;
}

double interseccion(const Sumatorias& sums) {
    double b = ((sums.sum_Y * sums.sum_X2) - (sums.sum_X * sums.sum_XY)) / ((sums.n * sums.sum_X2) - sums.sum_X_2);
    return b;
}


int main() {
    vector<int> vectorX = {3, 6, 8, 2, 1, 6};
    vector<int> vectorY = {8, 10, 15, 8, 5, 12};
    Sumatorias sums = calcularSums(vectorX, vectorY);
    double m = pendiente(sums);
    cout << "La pendiente es: " << m << endl;
    double b = interseccion(sums);
    cout << "La interseccion es: " << b << endl;

    return 0;
}
