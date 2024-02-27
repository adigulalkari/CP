// You have been an integer n and an array of size n as input. 
// You have to print the count of special numbers in an array. 
// A number is said to be special if it is divisible by at least one other element of the array.


#include<iostream>
using namespace std;

void special(int arr[], int len){
    
    for(int i=0; i<len; i++){
        bool flag =0;
        for(int j=0; j<len; j++){
            if(i!=j && arr[i]%arr[j]==0){
                flag =1;
                break;
            }
        }
        if(flag){
            cout<<arr[i]<<endl;
        }
    }
}

int main(){
    int arr[] = {2,4,5,7,32};
    int len = sizeof(arr)/sizeof(arr[0]);
    special(arr,len); 
    return 0;
}