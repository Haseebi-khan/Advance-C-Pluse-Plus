#include <iostream>
using namespace std;

int main()
{
    int arr[] = {5,6,2,3,4,9,3};
    int length = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    // for(int i = 0; i < length; i++){
    //     if( arr[i] == 3){
    //         for(int j = i; j < length - 1; j++){
    //             arr[j] = arr[j + 1];
    //         }
    //         length--;
    //     }    
    // }

    // for(int i = 0; i < length; i++){
    //     cout << arr[i]<<" ";
    // }
    int size =0;
    int* arr2 = new int[size];

    for (auto i : arr)
    {
        if (i != k)
        {
            arr2[size++] = i;
        }
        
    }

    for (int i = 0; i < size; i++)
    {
        cout << arr2[i] << " ";
    }
  
    return 0;
}
