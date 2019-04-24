#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

#define MAX_RANGE 10000

bool RANDOM = false;
bool RANDOM_PIVOT = false;

void print_all(vector <long unsigned int> & v) {
	for(unsigned int i = 0; i < v.size(); i++)
		if (v.size() == 1) {
			cout << "[" << v[i] << "]";
		}
		else if (i == 0) {
			cout << "[" << v[i] << ", ";
		}
		else if (i == v.size() - 1) {
			cout << v[i] << "]";
		}
		else {
			cout << v[i] << ", ";
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
    srand(time(NULL));
    int random = low + rand() % (high - low);

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

  cout << "BEFORE :";
  print_all (a);

  quickSort(a, 0, a.size()-1);

  cout << endl << "AFTER :";
  print_all (a);
  return 0;
}
