#include <iostream>
#include <random>
#include <ctime>
using namespace std;

void InsertionSort(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			swap(arr[j], arr[j - 1]);
	}
	//cout << "insertion" << endl;
}

void Combine(int *arr, int start, int mid, int end)
{
	int size1 = mid - start + 1, size2 = end - mid;
	int *left = new int[size1 + 1];
	int *right = new int[size2 + 1];
	for (int i = 0; i < size1; i++)
		left[i] = arr[start + i];
	left[size1] = INT_MAX;
	for (int j = 0; j < size2; j++)
		right[j] = arr[mid + j + 1];
	right[size2] = INT_MAX;
	for (int i = 0, j = 0, k = start; k <= end;)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	delete[]left;
	delete[]right;
}

void MergeSort(int *arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);
		Combine(arr, start, mid, end);
	}
}

void modifiedMergeSort(int *arr, int start, int end, int k)
{
	if (start < end)
	{
		int arrSize = end - start;
		if ((arrSize+1) <= k)
			InsertionSort(arr, arrSize);
		else
		{
			int mid = (start + end) / 2;
			MergeSort(arr, start, mid);
			MergeSort(arr, mid + 1, end);
			Combine(arr, start, mid, end);
		}
	}
}

int main()
{
	system("Color 8F");
	cout << '\t' << '\t' << '\t' << '\t' << "INSERTION SORT ON SMALL ARRAY INSTEAD OF MERGE SORT  ";
	cout << "\n Data size of array ?(-1 to quit): ";
	int size;
	cin >> size;
	while (size != -1)
	{
		double start_s, stop_s, avgRT[5], total = 0;
		int *input_arr = new int[size];
		int *processing_arr = new int[size];
		int seed;
		mt19937 rng;
		rng.seed(time(NULL));
		uniform_int_distribution<int> randomGenerator(1, 1000);
		for (int i = 0; i < size; i++)
			input_arr[i] = randomGenerator(rng);
		cout << "Merge sort when data size = " << size ;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < size; j++)
				processing_arr[j] = input_arr[j];
			start_s = clock();
			MergeSort(processing_arr, 0, size - 1);
			stop_s = clock();
			avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
			total = total + avgRT[i];
			cout << '\n' << "Iteration" << i + 1 << ": " << avgRT[i] << " in ms" ;
		}
		double avg = total / 5;
		cout  << '\n'<< "Average: " << avg;
		delete[]processing_arr;
		cout << '\n' << '\n' << "Modified Merge Sort" ;
		cout << '\n' << "k ?(-1 to quit) : ";
		int k;
		cin >> k;
		while (k != -1)
		{
			processing_arr = new int[size];
			total = 0;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < size; j++)
					processing_arr[j] = input_arr[j];
				start_s = clock();
				modifiedMergeSort(processing_arr, 0, size - 1, k);
				stop_s = clock();
				avgRT[i] = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;  //Time in ms
				total = total + avgRT[i];
				cout << '\n' << "Iteration" << i + 1 << ": " << avgRT[i] << " in ms" ;
			}
			double avg = total / 5;
			cout << '\n'<<"Average: " << avg ;
			cout << '\n' << '\n' << "k ?(-1 to quit): ";
			cin >> k;
		}
		delete[]processing_arr;
		delete[]input_arr;
		cout << '\n' << "Data size of array ?(-1 to quit): ";
		cin >> size;
	}
	system("PAUSE");
	return 0;
}