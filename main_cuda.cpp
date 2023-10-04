#include <stdio.h>
#include <random>
#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
void VectorAdd(int* a, int* b, int* c, int n)
{
	int i;

	for (i = 0; i < n; ++i)
		c[i] = a[i] * b[i];
}

int main()
{
  std::ofstream out("points.txt");
  for(int j=1;j<=10;j++){
	int* a, * b, * c, width,height,SIZE;
	width = 5000*j;
	height = 1000;
	SIZE = width * height;

	a = (int*)malloc(SIZE * sizeof(int));
	b = (int*)malloc(SIZE * sizeof(int));
	c = (int*)malloc(SIZE * sizeof(int));

	for (int i = 0; i < SIZE; ++i)
	{
		a[i] = i*abs(rand()%100);
    std::cout<<a[i]<<std::endl;
		b[i] = i * abs(rand() % 100);
    std::cout<<b[i]<<std::endl;
		c[i] = 0;
	}
    //старт времени
    auto start_time = std::chrono::steady_clock::now();
	VectorAdd(a, b, c, SIZE);

	for (int i = 0; i < SIZE; ++i)
		printf("c[%d] = %d\n", i, c[i]);

 auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
//    std::cout << std::endl;
   // std::cout << elapsed_ns.count() << " ns\n";
	free(a);
	free(b);
	free(c);
 
	out << elapsed_ns.count() <<std::endl;
  }
	out.close();
  return 0;
}
