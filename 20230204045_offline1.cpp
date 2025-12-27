#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <vector>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

#pragma comment(lib, "Psapi.lib") // Needed for MSVC linking

// Replace with your CPU's approximate average power (Watts)
#define CPU_POWER_WATTS 65.0
// Bangladesh grid emission factor (kg CO₂ / kWh)
#define BD_EMISSION_FACTOR 0.62

// merge sort code
void merge(vector<int> &arr, int low, int mid, int high)
{
    int size_left = mid - low + 1;
    int size_right = high - mid;

    vector<int> arrayLeft, arrayRight;

    for (int i = 0; i < size_left; i++)
        arrayLeft.push_back(arr[low + i]);
    for (int i = 0; i < size_right; i++)
        arrayRight.push_back(arr[mid + 1 + i]);

    arrayLeft.push_back(INT_MAX);
    arrayRight.push_back(INT_MAX);

    int i = 0, j = 0;
    for (int k = low; k <= high; k++)
    {
        if (arrayLeft[i] <= arrayRight[j])
            arr[k] = arrayLeft[i++];
        else
            arr[k] = arrayRight[j++];
    }
}
void mergeSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// quick sort code
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int left = low;
    int right = high;

    while (left < right)
    {
        while (arr[left] <= pivot && left < right)
            left++;
        while (arr[right] > pivot)
            right--;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[low], arr[right]);
    return right;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// iinsertion sort code
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int dataFileGenerator()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ofstream outFile("data.txt"); 
    if (!outFile)
    {
        cerr << "Cannot open file for writing!\n";
        return -1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 1000000); 
    for (int i = 0; i < 100000; i++)
    {
        outFile << dis(gen) << " ";
    }
    outFile.close();

    return 0;
}

vector<int> vectorFillFromDataFile()
{
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Cannot open file for reading!\n";
    }

    vector<int> arr;
    int num;
    while (inFile >> num) {
        arr.push_back(num);
    }
    inFile.close();

    return arr;
}

int main()
{
    // dataFileGenerator();
    vector<int> arr = vectorFillFromDataFile();

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // -------- Your algorithm here --------

    
    insertionSort(arr);
    
    // mergeSort(arr, 0, arr.size() - 1);
    
    // quickSort(arr, 0, arr.size() - 1);

    // -------------------------------------

    QueryPerformanceCounter(&end);

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    double energy = CPU_POWER_WATTS * elapsed;    // Joules
    double energy_kWh = energy / 3.6e6;           // kWh
    double co2 = energy_kWh * BD_EMISSION_FACTOR; // kg CO₂

    // ----- Memory usage -----
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
    {
        SIZE_T peakMemUsed = pmc.PeakWorkingSetSize; // Peak RAM usage

        printf("Execution time: %.6f seconds\n", elapsed);
        printf("Estimated energy consumption: %.2f Joules\n", energy);
        printf("Peak Memory Usage: %zu KB\n", peakMemUsed / 1024);
        printf("Estimated CO2 emissions (Bangladesh): %.8f kg\n", co2);
    }
    else
    {
        printf("Failed to get memory info.\n");
    }

    return 0;
}