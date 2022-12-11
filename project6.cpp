//Computing Structures
//Fall 2022
//Project 6
//Author: Bhavya Reddy Kanuganti
#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements
using namespace std;
// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D
    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
        // we want to retain the ordering of arr for shell sort
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];
    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array
                if (arrCopy[j] > arrCopy[j + 1])
                {
                    // swap
                    int temp = arrCopy[j];
                    arrCopy[j] = arrCopy[j + 1];
                    arrCopy[j + 1] = temp;
                }
        }
    }
    // return the completely sorted array
    return arrCopy;
}
// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;
    // need not make a copy of the arr array since shell sort is performed later / last
        // Start with a largest increment, then reduce by factors of 3 
        for (int inc = numElements / 3; inc > 1; inc /= 3)
        {
            // Insertion sort for the increment length
            for (int i = inc; i < numElements; ++i)
            {
                int temp = arr[i];
                j = i - inc;
                while ((j >= 0) && (arr[j] > temp))
                {
                    numComp++; // incrementing the number of comparisons done right before
                        // the if condition where the comparison happens each time
                        if (numComp >= D) // checking for number of comparisons
                            return arr; // return the not necessarily sorted array = approximately sorted array
                        arr[j + inc] = arr[j];
                    j = j - inc;
                }
                arr[j + inc] = temp;
            }
        }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
        for (int i = 1; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - 1;
            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                    arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = temp;
        }
    return arr;
}
//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;
    int s, l, u, D;
    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;
    // generate n random elements with the seed s, within the lower and upper range
    // you may use the unordered set to help generate unique elements
    srand(s); // using seed s

    int range = u - l + 1;

    unordered_set<int> numbers;//initializing unordered set

    while (numbers.size() < n)//loop to generate n random elements
    {
        numbers.insert(rand() % range + l);//insert elements into unordered ser
    }
  
    // store the randomly generated UNIQUE set of elements in an array 'A'
    int* A = new int[n];//initialise array to store random variables
    int i = 0;//initialise counter
    for (const int x : numbers) //loop to store unoredered set elements in array
    {
        A[i] = x;
        i++;
    }

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    // display the array A
    for (int i = 0; i < n; i++)
    {
        cout << A[i] <<" ";
    }
    //cout << sizeof(A);
    cout << endl << endl;
    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result
    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array 
    int* result = new int[numbers.size()];//initialise array to store sorted variables
    result = bubbleSort(A, numbers.size(), (numbers.size()) * (numbers.size()));// sorting random elements completely
    
    for (int i = 0; i < numbers.size(); i++)//displaying sorted array
    {
        cout << result[i]<<" ";
    }
    //cout << sizeof(result);
    cout << endl << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    // display bubResult
    int* bs = new int[numbers.size()];
    bs = bubbleSort(A, numbers.size(), D);
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << bs[i] << " ";
    }
   // cout << sizeof(bs);
    cout << endl << endl;
    // find both the quality metrics for bubResult
    cout << "Number of inversions in bubResult : ";
    int bsi = 0;
    //calculating the inversions
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int j = i + 1; j < numbers.size(); j++)
        {
            if (bs[i] > bs[j])
            {
                bsi++;
            }
        }
    }
    cout<<bsi<<endl;
    cout << "Chebyshev distance in bubResult: ";
    int displacement_b = 0, cb_b = 0;
    //calculating chebyshev distance
    for (int i = 0; i < numbers.size(); i++)
    {
        if (bs[i] != result[i])
        {
            for (int j = 0; j < numbers.size(); j++)
            {
                if (bs[i] == result[j])
                {
                    displacement_b = abs(i - j);
                    if (cb_b < displacement_b)
                        cb_b = displacement_b;
                }
            }
        }
    }
    cout << cb_b << endl;
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    int* ss = new int[numbers.size()];
    ss = shellSort(A, numbers.size(), D);
    // display shellResult
    
    for (int i = 0; i < numbers.size(); i++)
    {
        cout << ss[i] << " ";
    }
    //cout << sizeof(ss);
    cout << endl << endl;
    // find both the quality metrics for shellResult
    cout << "Number of inversions in shellResult : ";
    int ssi = 0;
    //calculating the inversions
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int j = i + 1; j < numbers.size(); j++)
        {
            if (ss[i] > ss[j])
            {
                ssi++;
            }
        }
    }
    cout << ssi << endl;
    cout << "Chebyshev distance in shellResult: ";
    int displacement_s = 0, cb_s = 0;
    //calculating chebyshev distance
    for (int i = 0; i < numbers.size(); i++)
    {
        if (ss[i] != result[i])
        {
            for (int j = 0; j < numbers.size(); j++)
            {
                if (ss[i] == result[j])
                {
                    displacement_s = abs(i - j);
                    if (cb_s < displacement_s)
                        cb_s = displacement_s;
                }
            }
        }
    }
    cout << cb_s << endl;
    cout << endl;
    return 0;
}