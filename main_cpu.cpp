#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
using namespace std;

int main() {



    long long rows1, cols1, rows2, cols2;
    cout << "Enter the number of rows and columns for Matrix 1: ";
    cin >> rows1 >> cols1;
    cout << "Enter the number of rows and columns for Matrix 2: ";
    cin >> rows2 >> cols2;

    if (cols1 != rows2) {
        cout << "Matrix multiplication is not possible. The number of columns in Matrix 1 must be equal to the number of rows in Matrix 2." << endl;
        return 1;
    }


    vector<vector<long long>> M1(rows1, vector<long long>(cols1));
    vector<vector<long long>> M2(rows2, vector<long long>(cols2));
    vector<vector<long long>> M_result(rows1, vector<long long>(cols2, 0));

    // Ввод элементов для первой матрицы
    cout << "Enter the elements of Matrix 1:" << endl;
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            cin >> M1[i][j];
        }
    }

    // Ввод элементов для второй матрицы
    cout << "Enter the elements of Matrix 2:" << endl;
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            cin >> M2[i][j];
        }
    }

    //старт времени
    auto start_time = std::chrono::steady_clock::now();
    // паралелизм
#pragma omp parallel for shared(M1, M2, M_result) collapse(2)
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                M_result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << endl;
    std::cout << elapsed_ns.count() << " ns\n";
    // Выводим результат
    cout << "Result Matrix:" << endl;
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            cout << M_result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}