#include <iostream>
#include <vector>
#include <chrono>

#include <cuda_runtime.h>

using namespace std;


__global__ void matrixMultiply(int* d_M1, int* d_M2, int* d_M_result, int rows1, int cols1, int cols2) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows1 && col < cols2) {
        int value = 0;
        for (int k = 0; k < cols1; ++k) {
            value += d_M1[row * cols1 + k] * d_M2[k * cols2 + col];
        }
        d_M_result[row * cols2 + col] = value;
    }
}

int main() {
   
    int rows1, cols1, rows2, cols2;
    cout << "Enter the number of rows and columns for Matrix 1: ";
    cin >> rows1 >> cols1;
    cout << "Enter the number of rows and columns for Matrix 2: ";
    cin >> rows2 >> cols2;

    if (cols1 != rows2) {
        cout << "Matrix multiplication is not possible. The number of columns in Matrix 1 must be equal to the number of rows in Matrix 2." << endl;
        return 1;
    }

    vector<int> h_M1(rows1 * cols1);
    vector<int> h_M2(rows2 * cols2);
    vector<int> h_M_result(rows1 * cols2);

    cout << "Enter the elements of Matrix 1:" << endl;
    for (int i = 0; i < rows1 * cols1; ++i) {
        cin >> h_M1[i];
    }

    cout << "Enter the elements of Matrix 2:" << endl;
    for (int i = 0; i < rows2 * cols2; ++i) {
        cin >> h_M2[i];
    }

    //старт времени
    auto start_time = std::chrono::steady_clock::now();
    // Allocate device memory and copy data from host to device
    int* d_M1;
    int* d_M2;
    int* d_M_result;

    cudaMalloc((void**)&d_M1, sizeof(int) * rows1 * cols1);
    cudaMalloc((void**)&d_M2, sizeof(int) * rows2 * cols2);
    cudaMalloc((void**)&d_M_result, sizeof(int) * rows1 * cols2);

    cudaMemcpy(d_M1, h_M1.data(), sizeof(int) * rows1 * cols1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M2, h_M2.data(), sizeof(int) * rows2 * cols2, cudaMemcpyHostToDevice);

  
    dim3 blockDim(16, 16);  
    dim3 gridDim((cols2 + blockDim.x - 1) / blockDim.x, (rows1 + blockDim.y - 1) / blockDim.y);

    matrixMultiply<<<gridDim, blockDim>>>(d_M1, d_M2, d_M_result, rows1, cols1, cols2);
    cudaDeviceSynchronize();

    cudaMemcpy(h_M_result.data(), d_M_result, sizeof(int) * rows1 * cols2, cudaMemcpyDeviceToHost);

 auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << endl;
    std::cout << elapsed_ns.count() << " ns\n";
   
    cout << "Result Matrix:" << endl;
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            cout << h_M_result[i * cols2 + j] << " ";
        }
        cout << endl;
    }

    cudaFree(d_M1);
    cudaFree(d_M2);
    cudaFree(d_M_result);

    return 0;
}