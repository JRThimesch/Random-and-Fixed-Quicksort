#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;


#define MAX_RANGE 10000

bool RANDOM = false;
bool RANDOM_PIVOT = false;
int random_time = 0;

void print_all(vector <long unsigned int> & v, ofstream &f) {
	for(unsigned int i = 0; i < v.size(); i++){
		if (i % 25 == 0) {
			f << endl;
		}

		if (v.size() == 1) {
			cout << "[" << v[i] << "]";
			f << "[" << v[i] << "]";
		}
		else if (i == 0) {
			cout << "[" << v[i] << ", ";
			f << "[" << v[i] << ", ";
		}
		else if (i == v.size() - 1) {
			cout << v[i] << "]";
			f << v[i] << "]";
		}
		else {
			cout << v[i] << ", ";
			f << v[i] << ", ";
		}
	}
}
void print(vector <long unsigned int> & v, unsigned int st, unsigned int end) { for(unsigned int i=st; i<=end; i++) cout << v[i] << " ";}

int partition(vector <long unsigned int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {


        if (arr[j] <= pivot) {

            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_r(vector <long unsigned int> & arr, int low, int high)
{
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
    srand(time(NULL));
    int random = low + rand() % (high - low);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    random_time += duration_cast<microseconds>( t4 - t3 ).count();

    // Swap A[random] with A[high]
    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

void quickSort(vector <long unsigned int> & arr, int low, int high)
{
	int pi = 0;
    if (low < high) {

        /* pi is partitioning index, arr[p] is now
        at right place */
    	if (RANDOM_PIVOT) {
    		pi = partition_r(arr, low, high);
    	} else {
    		pi = partition(arr, low, high);
    	}

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main() {
  ofstream file;
  file.open("output.txt");
  long unsigned int numOfInt = 0;
  long unsigned int incremental = 0;
  string reply = "";
  cout << "Input number of integers: ";
  cin >> numOfInt;
  cout << "Would you like to generate random numbers? (Y/N): ";
  cin >> reply;
  transform(reply.begin(), reply.end(), reply.begin(), ::tolower);

  if (reply == "y" || reply == "yes") {
	  RANDOM = true;
	  cout << "Using random numbers." << endl;
  } else {
	  cout << "Random numbers not set." << endl;
	  cout << "Set a number to multiply and increment the sorted array elements by: " << endl;
	  cin >> incremental;
	  cout << endl;
  }

  cout << "Would you like to use randomized quicksort? (Y/N): ";
  cin >> reply;

  if (reply == "y" || reply == "yes") {
	  cout << "Using randomized quicksort." << endl;
  	  RANDOM_PIVOT = true;
  } else {
  	  cout << "Using regular quicksort." << endl;
  }


  vector<long unsigned int> a(numOfInt);
  cout << "Generating a list of " << numOfInt << " numbers..." << endl;

  if (RANDOM) {
	  srand( time(NULL) );
	  for(long unsigned int i = 0; i < numOfInt; i++)
		  a[i] = rand() % MAX_RANGE;
  } else {
	  for(long unsigned int i = 0; i < numOfInt; i++)
		  a[i] = ((i + 1) + (i + 1) * (incremental));
  }

  //time_t begin, end;
  cout << "BEFORE :";
  file << "BEFORE :";
  print_all (a, file);

  //time(&begin);
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  quickSort(a, 0, a.size()-1);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  //time(&end);




  cout << endl << "AFTER :";
  file << endl << "AFTER :";
  print_all (a, file);

  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  //double duration = difftime(end, begin);
  cout << endl << duration - random_time << " microseconds";
  file << endl << "RUN TIME: " << duration - random_time << " microseconds";
  file.close();
  return 0;
}
