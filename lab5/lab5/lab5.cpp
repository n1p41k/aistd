#include <iostream>
#include <fstream>
#include <string>
#include <random>
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

void fileIn(std::string filename, int* array, const int size) {
    std::ifstream file(filename);
    int i = 0;
    file.is_open();
    while ((file >> array[i]) || (i < size)) {
        i++;
    }
    file.close();
}

void algotithm_hoare_3(int* array, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = l, j = r;
    int x = array[(l + r) / 2];
    while (i <= j)
    {
        while (array[i] < x)
        {
            i++;
        }
        while (array[j] > x)
        {
            j--;
        }
        if (i <= j)
        {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }
    algotithm_hoare_3(array, l, j);
    algotithm_hoare_3(array, i, r);
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
    int l = 0, r = size - 1;

    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();

        algotithm_hoare_3(array2, l, r);

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