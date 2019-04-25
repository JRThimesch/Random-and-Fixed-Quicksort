// Name: Jonathan Thimesch
// ID: D696H345

/*
 * Much of the partition and quicksort functions are borrowed from geeksforgeeks.com
 * LINK: https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>
#include <time.h>

using namespace std;
using namespace std::chrono;

#define MAX_RANGE 10000 // MAX RANGE OF NUMBERS

bool RANDOM = false;       // DEFAULT RANDOM NUMBER GENERATION TO FALSE
bool RANDOM_PIVOT = false; // DEFAULT THE RANDOMIZED QUICKSORT TO FALSE

// PRINT FUNCTION JUST TO OUTPUT RESULTS TO TERMINAL AND FILE
void printAll(vector<long unsigned int> &v, ofstream &f)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (i % 25 == 0)
        {
            f << endl;
        }
        if (v.size() == 1)
        {
            cout << "[" << v[i] << "]";
            f << "[" << v[i] << "]";
        }
        else if (i == 0)
        {
            cout << "[" << v[i] << ", ";
            f << "[" << v[i] << ", ";
        }
        else if (i == v.size() - 1)
        {
            cout << v[i] << "]";
            f << v[i] << "]";
        }
        else
        {
            cout << v[i] << ", ";
            f << v[i] << ", ";
        }
    }
}

// PARTITION FIXED
int partition(vector<long unsigned int> &arr, int low, int high)
{
    int pivot = arr[high]; // PIVOT TO HIGH
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]); // SORT ELEMENTS
        }
    }

    swap(arr[i + 1], arr[high]); // NEW HIGH
    return (i + 1);              // USED FOR INDEXING THE NEXT ARRAY IN RECURSION
}

// PARTITION RANDOMLY
int partitionR(vector<long unsigned int> &arr, int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low); // SELECTION OF RANDOM PIVOT

    // this puts the random number as the end number so that the partition func uses that instead of the end element it normally would
    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

// Quicksort function
void quicksort(vector<long unsigned int> &arr, int low, int high)
{
    int pi = 0;
    if (low < high)
    {

        if (RANDOM_PIVOT)
        {
            pi = partitionR(arr, low, high); // CALLS THE RANDOM PARTITION FUNCTION
        }
        else
        {
            pi = partition(arr, low, high); // PARTITIONS NORMALLY IF RANDOM_PIVOT IS NOT SET
        }

        // RECURSION FOR THE ARRAYS
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main()
{
    ofstream file;
    file.open("output.txt");
    long unsigned int numOfInt = 0;
    long unsigned int incremental = 0;
    string reply = "";

    // Uniform int distributor
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, MAX_RANGE);

    // START PROMPT
    cout << "Input number of integers: ";
    cin >> numOfInt;
    cout << "Would you like to generate random numbers? (Y/N): ";
    cin >> reply;
    transform(reply.begin(), reply.end(), reply.begin(), ::tolower);

    // SETS RANDOM NUMBER GENERATOR ONLY IF THE REPLY IS YES OR Y, OTHERWISE IT KEEPS RANDOM TO FALSE
    if (reply == "y" || reply == "yes")
    {
        RANDOM = true;
        cout << "Using random numbers." << endl;
    }
    else
    {
        cout << "Random numbers not set." << endl;
        cout << "Set a number to multiply and increment the sorted array elements by: ";
        cin >> incremental;
    }

    cout << "Would you like to use randomized quicksort? (Y/N): ";
    cin >> reply;

    // SETS RANDOM QUICKSORT ONLY IF THE REPLY IS YES OR Y, OTHERWISE IT KEEPS RANDOM_PIVOT TO FALSE
    if (reply == "y" || reply == "yes")
    {
        cout << "Using randomized quicksort." << endl;
        RANDOM_PIVOT = true;
    }
    else
    {
        cout << "Using regular quicksort." << endl;
    }
    // DONE PROMPT

    vector<long unsigned int> a(numOfInt);
    cout << "Generating a list of " << numOfInt << " numbers..." << endl;

    if (RANDOM)
    {
        for (long unsigned int i = 0; i < numOfInt; i++)
            // FILL ARRAY WITH RANDOM NUMBERS
            a[i] = distribution(generator);
    }
    else
    {
        for (long unsigned int i = 0; i < numOfInt; i++)
            // FILL ARRAY WITH SORTED INTEGERS
            a[i] = ((i + 1) + (i + 1) * (incremental));
    }

    cout << "BEFORE :";
    file << "BEFORE :";
    printAll(a, file);

    //START TIMER
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    quicksort(a, 0, a.size() - 1);

    //END TIMER
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    cout << endl
         << "AFTER :";
    file << endl
         << "AFTER :";
    printAll(a, file);

    auto duration = duration_cast<microseconds>(t2 - t1).count(); //CALCULATE TIME IT TOOK TO QUICKSORT
    cout << endl
         << duration << " microseconds";
    file.close();
    return 0;
}
