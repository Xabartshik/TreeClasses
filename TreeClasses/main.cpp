#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <random>

using namespace chrono;
// Сделал Ошлаков Dанил, ИВТ-22
/*
   (2)
   / \
  (1) (3)
  /    \
(-7)    (6)





*/

template <typename T>
bool binarySearch(const std::vector<T>& vec, const T& target, size_t& index) {
	size_t left = 0;
	size_t right = vec.size() - 1;

	while (left <= right) {
		size_t mid = left + (right - left) / 2;

		if (vec[mid] == target) {
			index = mid;
			return true;
		}
		else if (vec[mid] < target) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return false;
}

int main() {
    BinarySearchTree<int>::runTests();
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(2);
    bst.insert(8);
    bst.insert(7);
    bst.insert(6);
    bst.insert(12);
    bst.insert(20);
    cout << "После создания" << endl;
    inOrderTraversalIterative(bst.get_root());
    preOrderTraversalIterative(bst.get_root());
    postOrderTraversalIterative(bst.get_root());
    std::cout << "Число узлов: " << bst.countNodes() << std::endl; // Вывод: 7
    std::cout << "Глубина древа: " << bst.getDepth() << std::endl; // Вывод: 4

    std::cout << bst.succesor(10) << endl;
    bst.printTree(); // Вывод дерева в виде дереваДою
    cout << endl;
    bst.remove(5);
    cout << endl;
    bst.printTree(); // Вывод дерева в виде дерева
    bst.clear();
    cout << "После очистки" << endl;
    inOrderTraversalIterative(bst.get_root());

	//Счетчик итераций
	int i = 1;
	//Символ для продолжения/остановки итерации
	char cend = 1;
	//Счетчики времени
	double time_sum1 = 0;
	//Счетчик итерации с текущим размером
	unsigned cur_it = 0;
	//Проверка работоспособности
	//Служебные массивы:
	vector<size_t> length = { 100, 1000, 10000, 50000, 100000, 150000, 200000,  500000, 1000000, 2000000, 4000000, 5000000,7500000, 10000000,  };
	//	vector<size_t> length = { 100, 1'000, 10'000, 50'000, 100'000, 150'000, 200'000,  500000, 1000000, 2000000, 5000000, 10000000 };
	//100, 1000, 10000, 50000, 100000, 150000, 200000 ,  500000, 1000000
	//vector<size_t> iters =  { 1'000, 100, 100,   50,     50,      30,  20};
	vector<size_t> iters = {  1000, 1000,   1000,    1000,     1000,    1000,     1000,      1000,    1000,     1000,     1000,  1000,   1000,        1000 };
	vector<double> result;
	int k = 0;
	//Размер массива
	int size = length[k];
	size_t index;
	vector<int> myVector(size);
	vector<int> myVectorShuffled(size);
	iota(myVector.begin(), myVector.end(), 1);
	myVectorShuffled = myVector;
	auto rng = default_random_engine{};
	shuffle(begin(myVectorShuffled), end(myVectorShuffled), rng);
	while (k != length.size())
	{
		cur_it++;
		size = length[k];

		//Инициализация рандомайзера
		srand(time(NULL));
		//Первый замер
		//shuffle(begin(myVectorShuffled), end(myVectorShuffled), rng);

		//Сортировка массива быстро
		std::uniform_int_distribution<> dis(1, myVector.size());
		if (i % 10 == 0)
		{
			shuffle(begin(myVectorShuffled), end(myVectorShuffled), rng);
		}
		// Получаем случайное число в диапазоне
		int random_number = dis(rng);
		//shellSort(arr);
		//Второй замер
		auto t0 = steady_clock::now();
		bst.search(random_number);

		//binarySearch(myVector, random_number, index);
		auto t1 = steady_clock::now();


		//Вычисление и преобразование в seconds
		auto delta = duration_cast<microseconds>(t1 - t0);
		time_sum1 += delta.count();

		//Проверка, достигнута ли очередная, сотая итерация. Использовалась для вычисления средних времязатрат и сброса соответсвующих параметров. 
		//* увеличивает размер массива в 10 раз, / -- уменьшает в 10 раз
		if (i % iters[k] == 0)
		{
			cout << "Iteration in micro  №" << i << "; Size == " << size << endl;
			cout << "0 == end | + == continue | * == size*10 | / == size/10 " << endl;
			result.push_back(time_sum1 / cur_it / 1);
			cout << "Search time secs " << delta.count() / 1 << " " << "Medium this iteration " << time_sum1 / cur_it / 1000 << endl;

			k++;
			if (k == length.size())
				break;
			size = length[k];
			cur_it = 0;
			time_sum1 = 0;
			bst.clear();
			vector<int> myVector(size);
			vector<int> myVectorShuffled(size);
			iota(myVector.begin(), myVector.end(), 1);
			myVectorShuffled = myVector;
			shuffle(begin(myVectorShuffled), end(myVectorShuffled), rng);
			for (int value : myVectorShuffled)
			{
				bst.insert(value);
			}
			
		}
		//Увеличение счетчика итерации
		i++;
	}
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << ", ";
	}



    return 0;
}