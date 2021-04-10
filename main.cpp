/*  
    - Curso : Estructuras de Datos Avanzadas - Laboratorio
    - Alumno: Alexander Baylon
    - Fecha : 09/04/2021
    - Distancia euclidiana entre puntos n-dimensionales
*/

#include "euc_dist.hpp"

int main () {
    // N-dimension, Sample Size
    int N,S;
    vector< vector<double> > time_matrix;
    chrono::time_point<chrono::steady_clock> start, end;

    time_matrix.resize(4, vector<double>(4));

    euc_dist<float> A(10, 10000, 0.0, 1.0);

    N = 10;
    S = 10000;

    for (int i = 0; i < 4; i+=1)
    {
        for (int j = 0; j < 4; j+=1)
        {
            A.define_data(N,S);
            A.gen_data();
            start = chrono::steady_clock::now();
            A.calc_distance();
            end = chrono::steady_clock::now();
            double duration = chrono::duration<double> (end-start).count();
            time_matrix[i][j] = duration;
            N = N+5;
        }
        S = S + 5000;
    }
    
    for (vector<double> row: time_matrix) {
        for (double val: row) {
            cout << val << " \t";
        }
        cout << '\n';
    }

    return 0;
}
