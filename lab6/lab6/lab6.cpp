#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

void randMass(int* array, const int size, int from, int to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < size; i++) {
        array[i] = rd() % (to + 1 - from) + from;
    }
}

bool checkArray(int* array, const int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

int* copyArray(int* array, const int size) {
    int* A = new int[size];
    for (int i = 0; i < size; i++)
    {
        A[i] = array[i];
    }
    return A;
}

void outputMass(int* array, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << "   ";
    }
    std::cout << "\n";
}

void fileOut(std::string filename, int* array, int size) {
    std::ofstream file(filename);
    for (int i = 0; i < size; i++) {
        file << array[i] << " ";
    }
    file.close();
}

void fileIn(std::string filename, int* array, const int size) {
    std::ifstream file(filename);
    int i = 0;
    file.is_open();
    while ((file >> array[i]) || (i < size)) {
        i++;
    }
    file.close();
}

void bitsort(int* array, int l, int r, int k) {
    if (l >= r || k < 0)
        return;

    int i = l, j = r;
    int tmp;

    if (k == 31) {
        while (i <= j) {
            while ((i <= j) && ((array[i] >> k) & 1) == 0) {
                i++;
            }
            while ((i <= j) && ((array[j] >> k) & 1) == 1) {
                j--;
            }
            if (i < j) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                i++;
                j--;
            }
        }
    }
    else
    {
        while (i <= j) {
            while ((i <= j) && ((array[i] >> k) & 1) == 0) {
                i++;
            }
            while ((i <= j) && ((array[j] >> k) & 1) == 1) {
                j--;
            }

            if (i < j)
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                i++;
                j--;
            }
        }
    }
    // Рекурсивные вызовы для сортировки двух частей
    bitsort(array, l, j, k - 1);
    bitsort(array, i, r, k - 1);
}

void launch(const int size, int from, int to, int number)
{
    clock_t start, stop;
    double time, averageTime = 0;
    int* array = new int[size];
    std::vector<int> arraySteps;
    std::string filename = "ARRAY" + std::to_string(number) + ".txt";
    std::ifstream file(filename);
    fileIn(filename, array, size);
    int* array2 = new int[size];
    int l = 0, r = size - 1, k=0, b = to;

    while (to > 0)
    {
        to /= 2;
        k++;
    }

    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();

        bitsort(array2, l, r, k);

        stop = clock();

        if (checkArray(array2, size)) {
            std::cout << "\nthe array is ordered\n";
        }
        time = (double)(stop - start) / CLOCKS_PER_SEC;
        std::cout << "execution time" << i << " - " << time << "\n";
        averageTime += time;
        
    }

    std::cout << "\naverage time  = " << averageTime / 3 << "\n";
    std::cout << "--------------\n";

    delete[] array;
    delete[] array2;
}

int main()
{
    launch(10000, -10, 10, 1);
    launch(10000, -1000, 1000, 2);
    launch(10000, -100000, 100000, 3);
    launch(100000, -10, 10, 4);
    launch(100000, -1000, 1000, 5);
    launch(100000, -100000, 100000, 6);
    launch(1000000, -10, 10, 7);
    launch(1000000, -1000, 1000, 8);
    launch(1000000, -100000, 100000, 9);
    return 0;
}