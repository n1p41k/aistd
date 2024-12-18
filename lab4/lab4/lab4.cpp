#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

bool checkArray(int* array,const int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

int* copyArray(int* array,const int size) {
    int* A = new int[size];
    for (int i = 0; i < size; i++)
    {
        A[i] = array[i];
    }
    return A;
}

void outputMass(int* array,const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << "   ";
    }
    std::cout << "\n";
}

void fileIn(std::string filename, int* array,const int size) {
    std::ifstream file(filename);
    int i = 0;
    file.is_open();
    while ((file >> array[i]) || (i < size)) {
        i++;
    }
    file.close();
}

void sifting(int* array,const int size, int i)
{
    int j = 2 * i + 1;
    while (j < size)
    {
        if (j + 1 < size)
        {
            if (array[j + 1] > array[j])
            {
                j = j + 1;
            }
        }
        if (array[j] > array[i])
        {
            std::swap(array[i], array[j]);
            i = j;
            j = 2 * i + 1;
        }
        else
        {
            break;
        }
    }
}
void CreatePyramide(int* array, const int size)
{
    int i = size / 2 - 1;
    while (i >= 0)
    {
        sifting(array, size, i);
        i--;
    }
}

void PyramideSort(int* array, const int size)
{
    CreatePyramide(array, size);
    int i = size - 1;
    while (i >= 0)
    {
        std::swap(array[0], array[i]);
        sifting(array, i - 1, 0);
        i--;
    }
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

    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();
        PyramideSort(array, size);
        stop = clock();

        if (checkArray(array2, size)) {
            std::cout << "\nthe array is ordered\n";
        }
        time = (double)(stop - start) / CLOCKS_PER_SEC;
        std::cout << "execution time" << i << " - " << time << "\n";
        averageTime += time;
    }

    std::cout << "\naverage time  = " << averageTime << "\n";
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