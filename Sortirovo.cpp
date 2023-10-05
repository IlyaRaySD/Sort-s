#include <iostream>

using namespace std;

const int n = 200;
// these variables serve separately for quick and heap sort
int com_quick = 0, per_quick = 0;
int com_heap = 0, per_heap = 0;

// the function is used to return the initial values ​​to the array
void repair_sorted_array(int array[],int copy_array[]) {
	for (int i = 0; i < n; i++)
		array[i] = copy_array[i];
}

// the function is used to output array values ​​to the console // only for testing
void showing_array(int array[]) {
	cout  << "Array:\n";
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

// bubble sort function
void buble_sort(int array[]) {
	int comparisons = 0, permutations = 0;
	bool flag;
	for (int i = 0; i < n; i++) {
		// condition for stopping
		if (i != 0 and flag == 0) {
			cout << endl << "Bubble sort results:\n" << "Comparisons: " << comparisons << " Permutations: " << permutations << endl << endl;
			return;	
		}
		flag = 0;
		for (int j = 0; j < n - 1 - i; j++) {
			comparisons++;
			flag = 0;
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
				permutations++;
				flag = 1;
			}
		}
	}
	cout << endl << "Bubble sort results:\n" << "Comparisons: " << comparisons << " Permutations: " << permutations << endl << endl;
}

// selection sort function
void selection_sort(int array[]) {
	int index, com = 0, per = 0;
	for (int i = 0; i < n - 1; i++) {
		index = i;
		for (int j = i + 1; j < n; j++) {
			if (array[j] < array[index])
				index=j;
			com++;
		}
		if (i != index) {
			swap(array[i], array[index]);
			per++;
		}
	}
	cout << endl << "Selection sort results:\n" << "Comparisons: " << com << " Permutations: " << per << endl << endl;
}

// shaker sort function
void shaker_sort(int array[]) {
	int left = 1, right = n - 1, move = n - 1, com = 0, per = 0;
	while (left <= right) {
		for (int i = right; i >= left; i--) {
			if (array[i - 1] > array[i]) {
				swap(array[i - 1], array[i]);
				move = i;
				per++;
			}
			com++;
		}
		left = move + 1;
		for (int i = left; i <= right; i++) {
			if (array[i] < array[i - 1]) {
				swap(array[i], array[i - 1]);
				move = i;
				per++;
			}
			com++;
		}
		right = move - 1;
	}
	cout << endl << "Shaker sort results:\n" << "Comparisons: " << com << " Permutations: " << per << endl << endl;
}

// quick sort function
void quick_sort(int array[], int left, int right) {
	// main condition
	if (left > right) 
		return;
	int p = array[(left + right) / 2];
	int i = left, j = right;
	while (i <= j) {
		while (array[i] < p) {
			com_quick++;
			i++;
		}
		while (array[j] > p) {
			com_quick++;
			j--;
		}
		if (i <= j) {
			swap(array[i], array[j]); 
			per_quick++;
			i++;
			j--;
		}
	}
	quick_sort(array, left, j);
	quick_sort(array, i, right);
}

// insertion sort function
void insertion_sort(int array[]) {
	int per = 0, com = 0;
	for (int i = 1; i < n; i++) {
		int sorted_piece = i - 1;
		while (sorted_piece > -1) {
			if (array[sorted_piece] > array[sorted_piece + 1]) {
				per++;
				com++;
				swap(array[sorted_piece], array[sorted_piece + 1]);
			}
			else
				com++;
			sorted_piece--;
		}
	}
	cout << endl << "Incertion sort results:\n" << "Comperisons: " << com << " Permutations: " << per << endl << endl;
}

// function for findind optimal step for shell sort
int increm(int *inter, int size) {
	int multi1 = 1, multi2 = 1, multi3 = 1, counter = -1;
	do {
		if (++counter % 2){
			multi2 *= 2;
			inter[counter] = 8 * multi1 - 6 * multi2 + 1;
		}
		else {
			inter[counter] = 9 * multi1 - 9 * multi3 + 1;
			multi3 *= 2;
		}
		multi1 *= 2;
	} while (3 * inter[counter] < size);
	return((counter > 0) ? (--counter) : 0);
}
// shell sort with Sedgwick's algorithm
void shell_sejwick(int array[]) {
	int com = 0, per = 0;
	int inter, array_inter[n], count, j;
	count = increm(array_inter, n);
	while (count >= 0) {
		inter = array_inter[count--];
		for (int i = inter; i < n; i++) {
			int tmp = array[i];
			for (j = i - inter; j >= 0; j -= inter) {
				if (array[j] > array[j + inter]) {
					swap(array[j], array[j + inter]);
					per++;
					com++;
				}
				else
					com++;
			}
		}
	}
	cout << endl << "Shell sort (Sedgwick's algorithm) results:\n" << "Comperisons: " << com << " Permutations: " << per << endl << endl;
}

// shell sort function
void shell_sort(int array[]) {
	int com = 0, per = 0;
	// I took a step equal a half the size
	for (int step = n / 2; step > 0; step /= 2) {
		for (int i = step; i < n; i++) {
			for (int j = i - step; j >= 0; j -= step) {
				if (array[j] > array[j + step]) {
					swap(array[j], array[j + step]);
					per++;
					com++;
				}
				else
					com++;
			}
		}
	}
	cout << endl << "Shell sort (Shell's method) results:\n" << "Comperisons: " << com << " Permutations: " << per << endl << endl;
}

// function is used to build a heap from an array 
void heap_build(int array[], int n, int root){
	int largest = root;
	int l_child = 2 * root + 1;
	int r_child = 2 * root + 2;
	if (l_child < n && array[l_child] > array[largest]) 
		largest = l_child;
	if (l_child < n)
		com_heap++;
	if (r_child < n && array[r_child] > array[largest]) 
		largest = r_child;
	if (r_child < n)
		com_heap++;
	if (largest != root){
		swap(array[root], array[largest]);
		per_heap++;
		heap_build(array, n, largest);
	}
	com_heap++;
}
// heap (bunary tree) function
void heap_sort(int array[], int n){
	int degree = log2(n) - 1; // numnber of child of a tree equal helf the size 
	for (int i = n / 2 - 1; i >= 0; i--) {
		int degree_2 = log(i + 2);
		// this part of the code makes the child's child a heap
		if (degree_2 + 1 == degree)
			heap_build(array, n, i);
		else {
			for (int j = 0; j < degree - degree_2; j++) {
				heap_build(array, n, i * pow(2, j));
			}
		}
	}
	// this part of the code puts the root of the tree at the end of the array and then makes a heap from the remaining tree until there are no more elements
	for (int i = n - 1; i >= 0; i--) {
		swap(array[0], array[i]);
		//com_heap++;
		per_heap++;
		heap_build(array, i , 0);
	}
	cout << endl << "Heap sort results:\n" << "Comperisons: " << com_heap << " Permutations: " << per_heap << endl << endl;
}

// binary insertion (binary search) sort function
void binary_sort(int array[]) {
	int x, left, right, middle;
	int com = 0, per = 0;
	for (int i = 1; i < n; i++) {
			x = array[i];
			left = 0;
			right = i - 1;
			while (left <= right) {
				middle = (left + right) / 2;
				if (x < array[middle]) 
					right = middle - 1;
				else
					left = middle + 1;
				com++;
			}
			for (int j = i - 1; j >= left; j--) {
				array[j + 1] = array[j];
				per++;
			}
			array[left] = x;
			//com++;
			per++;
	}
	cout << endl << "Binary selection sort results:\n" << "Comperisons: " << com << " Permutations: " << per << endl << endl;
}

void main() {
	int array_rand[n], array_already_sort[n], array_hard_sort[n];
	// initialization of arrays that will store copies of the main arrays
	int	copy_already_sort[n], copy_hard_sort[n], copy_rand[n];

	// filling a random array
	for (int i = 0; i < n; i++) {
		array_rand[i] = 0 + rand() % 100;
		copy_rand[i] = array_rand[i];
	}

	// filling a sorted array
	array_already_sort[0] = 1;
	copy_already_sort[0] = 1;
	for (int i = 1; i < n; i++) {
		array_already_sort[i] = array_already_sort[i - 1] + (0 + rand() % 3);
		copy_already_sort[i] = array_already_sort[i];
	}

	// filling an inverted array
	array_hard_sort[n-1] = 1;
	copy_hard_sort[n - 1] = 1;
	for (int i = n-2; i >= 0; i--) {
		array_hard_sort[i] = array_hard_sort[i + 1] + (0 + rand() % 3);
		copy_hard_sort[i] = array_hard_sort[i];
	}

	
	// calling the bubble sort function for every array
	cout << "\nSorted array:";
	buble_sort(array_already_sort);
	cout << "\nInverted array:";
	buble_sort(array_hard_sort);
	cout << "\nRandom arrray:";
	buble_sort(array_rand);

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);
	
	// calling the selection sort function for every array
	cout << "\nSorted array:";
	selection_sort(array_already_sort);
	cout << "\nInverted array:";
	selection_sort(array_hard_sort);
	//showing_array(array_hard_sort);
	cout << "\nRandom arrray:";
	selection_sort(array_rand);

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the shaker sort function for every array
	cout << "\nSorted array:";
	shaker_sort(array_already_sort);
	cout << "\nInverted array:";
	shaker_sort(array_hard_sort);
	cout << "\nRandom arrray:";
	shaker_sort(array_rand);

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the quick sort function for every array
	cout << "\nSorted array:";
	quick_sort(array_already_sort, 0, n - 1);
	cout << endl << "Quick sort results:\n" << "Comperisons: " << com_quick << " Permutations: " << per_quick << endl << endl;
	com_quick = 0, per_quick = 0;
	cout << "\nInverted array:";
	quick_sort(array_hard_sort, 0, n - 1);
	cout << endl << "Quick sort results:\n" << "Comperisons: " << com_quick << " Permutations: " << per_quick << endl << endl;
	com_quick = 0, per_quick = 0;
	cout << "\nRandom arrray:";
	quick_sort(array_rand, 0, n - 1);
	cout << endl << "Quick sort results:\n" << "Comperisons: " << com_quick << " Permutations: " << per_quick << endl << endl;
	com_quick = 0, per_quick = 0;

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the insertion sort function for every array
	cout << "\nSorted array:";
	insertion_sort(array_already_sort);
	cout << "\nInverted array:";
	insertion_sort(array_hard_sort);
	cout << "\nRandom arrray:";
	insertion_sort(array_rand);

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the shell's sort function for every array
	cout << "\nSorted array:";
	shell_sort(array_already_sort);
	cout << "\nInverted array:";
	shell_sort(array_hard_sort);
	cout << "\nRandom arrray:";
	shell_sort(array_rand);

	cout << "-------------------------------------------------";

	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	
	cout << "\nSorted array:";
	shell_sejwick(array_already_sort);
	//showing_array(array_already_sort);
	cout << "\nInverted array:";
	shell_sejwick(array_hard_sort);
	//showing_array(array_hard_sort);
	cout << "\nRandom arrray:";
	shell_sejwick(array_rand);
	//showing_array(array_rand);

	cout << "-------------------------------------------------";
	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the heap (binary tree) sort function for every array
	cout << "\nSorted array:";
	heap_sort(array_already_sort, n);
	cout << "\nInverted array:";
	heap_sort(array_hard_sort, n);
	cout << "\nRandom arrray:";
	heap_sort(array_rand, n);

	cout << "-------------------------------------------------";

	// calling a function that returns arrays to their original (unsorted) values
	repair_sorted_array(array_already_sort, copy_already_sort);
	repair_sorted_array(array_hard_sort, copy_hard_sort);
	repair_sorted_array(array_rand, copy_rand);

	// calling the binary insertion (binary search) sort function for every array
	cout << "\nSorted array:";
	binary_sort(array_already_sort);
	cout << "\nInverted array:";
	binary_sort(array_hard_sort);
	cout << "\nRandom arrray:";
	binary_sort(array_rand);
}
/* The results of all sorts will out in the console */

