#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <fstream>
using namespace std;

int main() {

    std::ofstream out("point2.txt");

    for(int j=1;j<=10;j++){

    int width,height,SIZE;
	width = 500*j;
	height = 1000;
	SIZE = width * height;



    vector<vector<int>> M1(width, vector<int>(height));
    vector<vector<int>> M2(width, vector<int>(height));
    vector<vector<int>> M_result(height, vector<int>(height));

    // Ввод элементов для первой матрицы
    cout << "Enter the elements of Matrix 1:" << endl;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
           // cin >>  i*abs(rand()%100);
           M1[i][j]=i*abs(rand()%100);
        }
    }

    // Ввод элементов для второй матрицы
    cout << "Enter the elements of Matrix 2:" << endl;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
           // cin >> 
           M2[i][j]=i*abs(rand()%100);
        }
    }

    //старт времени
    auto start_time = std::chrono::steady_clock::now();
    // паралелизм
#pragma omp parallel for shared(M1, M2, M_result) collapse(2)
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
          //  for (int k = 0; k < cols1; ++k) {
                M_result[i][j] += M1[i][j] * M2[i][j];
            
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
  //  cout << endl;
    out << elapsed_ns.count() << " ns\n";
    // Выводим результат
  //  cout << "Result Matrix:" << endl;
    //for (int i = 0; i < width; ++i) {
      //  for (int j = 0; j < cols2; ++j) {
          //  cout << M_result[i][j] << " ";
      //  }
     //   cout << endl;
    //}
    }
out.close();
    return 0;
}
