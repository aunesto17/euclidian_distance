#ifndef euc_dist_hpp
#define euc_dist_hpp

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

class RNG
{
public:
    RNG() : gen(random_device()()) {} // Seeds the mt19937.

    double getRandom(double l){  
        uniform_real_distribution<double> dis(0, l);
        double random = dis(gen);
        return random;
    }

private:
    mt19937 gen;
};


template <class T>
class euc_dist
{
private:
    int N; // N-dimension
    int S; // sample size
    vector< vector<T> > data;
    double dist, sum, tmp, min, max;
    vector< vector<T> > dist_matrix;
    RNG rng_;

public:
    euc_dist(int dim, int size, double mi, double ma) 
    {
        N = dim;
        S = size;
        min = mi;
        max = ma;
        //gen_data();
        dist_matrix.resize(S, vector<T>(N));
    }

    void calc_distance();

    void gen_data();
    void define_data(int,int);

    void print_data();
    void print_dist_matrix();

    ~euc_dist();
};

template<class T>
void euc_dist<T>::calc_distance(){
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i <= j) continue; // lower triangular
            sum = 0;
            tmp = 0;
            for (int k = 0; k < N; k++) // distance operation
            {
                //cout << "x_i: " << data[i][k] << " " << "y_i: " << data[j][k] << endl;
                tmp = data[i][k] - data[j][k];     
                sum += tmp*tmp;
            }
            dist = sqrt(sum); 
            //cout << "(" << i << "," << j << "):" << dist << " "; 
        }
        //cout << endl;
    }
    
}


template<class T>
void euc_dist<T>::gen_data()
{
    for (int i = 0; i < S; ++i) {
        vector<T> tmp;
        for (int j = 0; j < N; ++j)
        {
            tmp.push_back(rng_.getRandom(max));
        }
        data.push_back(tmp);
    }
}

template<class T>
void euc_dist<T>::define_data(int dim, int size)
{ 
    N = dim;
    S = size;
    //remove al vectors inside data
    data.clear();
    data.resize(0);
    //gen_data();
}


template<class T>
void euc_dist<T>::print_data()
{
    for (vector<T> row: data) {
        for (T val: row) {
            cout << val << " ";
        }
        cout << '\n';
    }
}

template<class T>
void euc_dist<T>::print_dist_matrix()
{
    for (vector<T> row: dist_matrix) {
        for (T val: row) {
            cout << val << " ";
        }
        cout << '\n';
    }
}

template<class T>
euc_dist<T>::~euc_dist()
{
    cout << "Object deleted" << endl;
}





#endif /* euc_dist_hpp */
