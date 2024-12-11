#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

void createStepsArray1(std::vector<int>& arraySteps, int size) {
    for (int i = 0; size / 2 > 0; i++) {
        arraySteps.push_back(size / 2);
        size /= 2;
    }
}

void createStepsArray2(std::vector<int>& arraySteps, int const size) {
    for (int i = log2(size); i > 0; i--) {
        arraySteps.push_back(pow(2, i) - 1);
    }
}

void createStepsArray3(std::vector<int>& arraySteps, int const size) {
    int t = log2(size);
    arraySteps.push_back(1);
    for (int i = 1; i < t - 1; i++) {
        arraySteps.insert(arraySteps.begin(), 3 * arraySteps[0] + 1);
    }
}

void insert(int* array, int size, int b, int s) {
    for (int j = b + s; j < size; j += s) {
        int x = array[j];
        int k = j - s;
        while ((k >= 0) && (array[k] > x)) {
            array[k + s] = array[k];
            k = k - s;
        }
        array[k + s] = x;
    }
}

bool checkArray(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

int* copyArray(int* array, int size) {
    int* A = new int[size];
    for (int i = 0; i < size; i++)
    {
        A[i] = array[i];
    }
    return A;
}

void shell(int* array, int size, std::vector<int> arraySteps) {
    int s, b, i = 0;
    for (int i = 0; i <= arraySteps.size() - 1; i++) {
        s = arraySteps[i];
        for (b = 0; b < s; b++) {
            insert(array, size, b, s);
        }
    }
}

void randMass(int* array, int size, int from, int to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < size; i++) {
        array[i] = rd() % (to + 1 - from) + from;
    }
}

void outputMass(int* array, int size) {
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

void fileIn(std::string filename, int* array, int size) {
    std::ifstream file(filename);
    int i = 0;
    file.is_open();
    while ((file >> array[i]) || (i < size)) 
    {
        i++;
    }
    file.close();
}

void launch(int size, int from, int to, int number)
{
    clock_t start, stop;
    double time, averageTime = 0;
    int* array = new int[size];
    std::vector<int> arraySteps;
    std::string filename = "ARRAY" + std::to_string(number) + ".txt";
    std::ifstream file(filename);
    fileIn(filename, array, size);
    std::cout << "Array number - " << number << "\n";
    int* array2 = new int[size];
    std::cout << "\n" << "Method Shell\n";
    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();
        createStepsArray1(arraySteps, size);
        shell(array2, size, arraySteps);
        stop = clock();

        if (checkArray(array2, size)) {
            std::cout << "the array is sorted\n";
        }
        time = (double)(stop - start) / CLOCKS_PER_SEC;
        std::cout << "execution time" << i+1 << " - " << time << "\n";
        arraySteps.clear();

        averageTime += time;
    }
    std::cout << "average time - " << averageTime / 3 << "\n\n";
    averageTime = 0;
    std::cout << "Method Hibbard\n";
    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();
        createStepsArray2(arraySteps, size);
        shell(array2, size, arraySteps);
        stop = clock();

        if (checkArray(array2, size)) {
            std::cout << "the array is sorted\n";
        }
        time = (double)(stop - start) / CLOCKS_PER_SEC;
        std::cout << "execution time" << i+1 << " - " << time << "\n";
        arraySteps.clear();

        averageTime += time;
    }
    std::cout << "average time - " << averageTime / 3 << "\n\n";
    averageTime = 0;

    std::cout << "Method Knuth\n";
    for (int i = 0; i < 3; i++)
    {
        array2 = copyArray(array, size);

        start = clock();
        createStepsArray3(arraySteps, size);
        shell(array2, size, arraySteps);
        stop = clock();

        if (checkArray(array2, size)) {
            std::cout << "the array is sorted\n";
        }
        time = (double)(stop - start) / CLOCKS_PER_SEC;
        std::cout << "execution time" << i+1 << " - " << time << "\n";
        arraySteps.clear();

        averageTime += time;
    }
    std::cout << "average time - " << averageTime / 3 << "\n\n";
    averageTime = 0;

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