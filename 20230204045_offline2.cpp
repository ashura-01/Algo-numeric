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

int dataFileGenerator()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ofstream outFile("data2.txt");
    if (!outFile)
    {
        cerr << "Cannot open file for writing!\n";
        return -1;
    }

    for (int i = 1; i <= 100000; i++)
    {
        outFile << i << " ";
    }

    outFile.close();
    return 0;
}

vector<int> vectorFillFromDataFile()
{
    ifstream inFile("data2.txt");
    if (!inFile)
    {
        cerr << "Cannot open file for reading!\n";
    }

    vector<int> arr;
    int num;
    while (inFile >> num)
    {
        arr.push_back(num);
    }
    inFile.close();

    return arr;
}

int binarySearch(vector<int> &arr, int target)
{
    int low = 0;
    int high = (int)arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

int linearSearch(vector<int> &arr, int target)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int main()
{
    // dataFileGenerator();
    vector<int> arr = vectorFillFromDataFile();
    int existing_target=100000;
    int non_existing_target =-45;
    int index=0;

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // -------- Your algorithm here --------
    // case 1: for last element searching
    // index= binarySearch(arr, existing_target);
    // index= linearSearch(arr, existing_target);
    
    // case 2: number not exist in the dataset
    // index= binarySearch(arr, non_existing_target);
    index= linearSearch(arr, non_existing_target);
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

        printf("Execution time: %.17f seconds\n", elapsed);
        printf("Estimated energy consumption: %.7f Joules\n", energy);
        printf("Peak Memory Usage: %zu KB\n", peakMemUsed / 1024);
        printf("Estimated CO2 emissions (Bangladesh): %.17f kg\n", co2);
    }
    else
    {
        printf("Failed to get memory info.\n");
    }

    cout<<"the searched output------->"<<index<<endl;

    return 0;
}