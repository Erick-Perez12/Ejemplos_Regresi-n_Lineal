#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Sumatorias {
    double sum_X = 0;
    double sum_Y = 0;
    double sum_XY = 0;
    double sum_X2 = 0;
    double sum_X_2 = 0;
    int n = 0;
};

struct Articulo {
    int word_count;
    int shares;
};

vector<Articulo> leerDatos(const string& nombreArchivo) {
    vector<Articulo> datos;
    ifstream archivo(nombreArchivo);
    string linea,token;
    getline(archivo, linea);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return datos;
    }

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string word_count_str, shares_str;
        getline(ss, token, ',');
        getline(ss, token, ',');
        getline(ss, word_count_str, ',');
        getline(ss, token, ',');
        getline(ss, token, ',');
        getline(ss, token, ',');
        getline(ss, token, ',');
        getline(ss, shares_str, ',');
        int word_count = stoi(word_count_str);
        int shares = stoi(shares_str);
        if (word_count <= 3500 && shares <= 80000) {
            datos.push_back({word_count, shares});
        }
    }

    archivo.close();
    return datos;
}

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

double Pendiente(const Sumatorias& sums) {
    double m = ((sums.n * sums.sum_XY) - (sums.sum_X * sums.sum_Y)) / ((sums.n * sums.sum_X2) - sums.sum_X_2);
    return m;
}

double Interseccion(const Sumatorias& sums) {
    double b = ((sums.sum_Y * sums.sum_X2) - (sums.sum_X * sums.sum_XY)) / ((sums.n * sums.sum_X2) - sums.sum_X_2);
    return b;
}
double predecirCompartidos(double m, double b, int word_count) {
    return m * word_count + b;
}

int main() {
    vector<Articulo> datos = leerDatos("articulos_ml.csv");
    vector<int> vectorX, vectorY;

    for(const auto& articulo : datos) {
        vectorX.push_back(articulo.word_count);
        vectorY.push_back(articulo.shares);
    }
    Sumatorias sums = calcularSums(vectorX, vectorY);
    double m = Pendiente(sums);
    double b = Interseccion(sums);

    int word_count = 2000;
    double prediccion = predecirCompartidos(m, b, word_count);

    cout << "La pendiente es: " << m << endl;
    cout << "La intersección es: " << b << endl;
    cout << "La predicción para un artículo de " << word_count << " palabras es: " << prediccion << " compartidos." << endl;

    return 0;
}
