#include<iostream>
#include<stdio.h>
#include <stdarg.h>
#include<vector>
using namespace std;

void sort(int n, ...)                                                                           //int n is the number of arguments to be read after the it
{
    va_list ele;
    
    vector<int> arr;
    va_start(ele, n);                                                                           //reads n arguments after n
    int t;
    

    arr = va_arg(ele, vector<int>);                                                             //makes the arguments into a vector int form and stoes it in arr
    // cout<<arr;

    
    cout<<endl<<"The unsorted array is : "<<endl;                                                 
    for(int i = 0; i < n; i ++)
    {
        printf("%d\t", arr[i]);
    }

    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n - 1 - i; j ++)
        {
            if(arr[j] > arr[j + 1])
            {   
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }  
    }
    cout<<endl<<"The sorted array is : "<<endl; 
    for(int i = 0; i < n; i ++)
    {
        cout<<arr[i]<<"\t";
    }
    va_end(ele);
}

int main( )
{   
    
    int n;
    string input;
    cout<<"Enter the input as a string, for eg \n2\t3\t4\n6\t7 as {{2,3,4},{6,7}} : \n";
    cin>>input;                                                                                                 
    int k = 0;
    int j = 1;
    int a[100][100];
    char arguments[k + 1][100];

    for(int i = 0; i < 100; i ++)                                                                              //to remove junk value in a
    {
        for(int j = 0; j < 100; j ++)
        {
            a[i][j] = 0;
        }
    }

    // int k = 0;  
    // int j = 1;

    for(int i = 0; input[i] != '\0'; i++)                                                                       //converts the given input to a 2d array, the first element of each row of the 2d-array will correspond to the number of elements in that row excuding the first element. 
    {
        if(input[i] == ',')
        {
            j++;
            continue;
        }
        if(input[i] == '}')
        {
            a[k][0] = j;
            k++;
            i++;
            j = 1;
            continue;
        }
        if(input[i] != '{')
        {    
            a[k][j] = a[k][j]*10 + (input[i] - 48);
        }
    }
    vector <int> arg;


    for(int i = 0; i < k; i ++)                                                                         //storing each array in a vector and sending them to sort.
    {
        for(int j = 1; j <= a[i][0]; j ++)                                                              //note that a vector will be stored like an ellipse only.
        {
            arg.push_back(a[i][j]);                                                                     //pusing into the vector. 
            // cout<<arg[j - 1]<<"\t";
        }
        sort(a[i][0], arg);                                                                             //if the vector is = {1, 2, 3}, sort will expand as sort(3,1,2,3)
        arg.clear();                                                                                    //clearing the whole vector to store the next array.
        cout<<endl;
    }

    cout<<endl;
    return(0);
}