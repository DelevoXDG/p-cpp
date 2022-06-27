#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

void demo(int& a)
{
	a += 10;
}
struct Array {
private:
	int* _arr;
	size_t _size;
public:
	// Array() {}
	Array(const int size) : _size(size) {
		_arr = new int[size];
	}
	int* Get_Array() {
		return &_arr[0];
	}
	// int operator[] (const int i) {
	// 	return *(_arr + i);
	// }
	int& operator[](int index)
	{
		if (index >= _size) {
			std::cout << "Array index out of bound, exiting";
			exit(0);
		}
		return _arr[index];
	}
	int Get_Size() {
		return _size;
	}
	void Print() {
		for (size_t i = 0; i < _size - 1; i++) {
			std::cout << _arr[i] << " ";
		}
		if (_size > 0) std::cout << _arr[_size - 1] << std::endl;
	}
	void Fill_Random(const int min = 0, const int max = 9) {
		for (size_t i = 0; i < _size; i++) {
			_arr[i] = rand() % ((max + 1) - min);
		}
	}
};
bool even(const int var) {
	return var % 2 == 0;
}
int square(const int var) {
	return var * var;
}
Array* filter(bool (*func_ptr)(int), Array* arr) {
	size_t size = arr->Get_Size();
	size_t new_size = 0;
	Array* new_arr;
	// int* arr_p = arr->Get_Array();

	std::queue<int> FIFO;
	for (size_t i = 0; i < size; i++) {
		int arr_item = (*arr)[i];
		if ((func_ptr(arr_item)) == true) {
			FIFO.push(arr_item);
			new_size++;
		}
	}
	new_arr = new Array(new_size);
	for (size_t i = 0; i < new_size; i++) {
		(*new_arr)[i] = FIFO.front();
		FIFO.pop();
	}
	return new_arr;
}
Array* map(int (*func_ptr)(int), Array* arr) {
	size_t size = arr->Get_Size();
	Array* new_arr = new Array(size);
	for (size_t i = 0; i < size; i++) {
		(*new_arr)[i] = func_ptr((*arr)[i]);
	}
	return new_arr;
}
int sum(Array* arr) {
	int size = arr->Get_Size();
	int sum = 0;
	for (size_t i = 0; i < size; i++) {
		sum = sum + (*arr)[i];
	}
	return sum;
}
int reduce(int (*fucnt_ptr)(Array*), Array* arr) {
	return fucnt_ptr(arr);
}

void BubbleSort(int* arr, int size) {

}


int main()
{
	srand(time(0));

	Array* test = new Array(10);
	test->Fill_Random();
	test->Print();
	Array* filtered = filter(even, test);
	filtered->Print();
	Array* mapped = map(square, test);
	mapped->Print();
	std::cout << "sum: " << reduce(sum, test);


	return 0;
}

