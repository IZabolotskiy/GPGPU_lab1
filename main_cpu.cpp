#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <fstream>
using namespace std;

int main() {

    std::ofstream out("point4.txt");

    for(int j=1;j<=10;j++){

    int width,height,SIZE;
	width = 5000*j;
	height = 1000;
	SIZE = width * height;

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


    vector<vector<int>> M1(width, vector<int>(height));
    vector<vector<int>> M2(width, vector<int>(height));
    vector<vector<int>> M_result(width, vector<int>(height));


    //старт времени
    auto start_time = std::chrono::steady_clock::now();
    // паралелизм
//#pragma omp parallel for shared(M1, M2, M_result) collapse(2)
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
          
                M_result[i][j] += M1[i][j] * M2[i][j];
            
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
   std:: cout << elapsed_ns.count()<< endl;
    out << elapsed_ns.count() << endl;
 
    }
out.close();
    return 0;
}
