// package PAT
public class Permutaion {
    static void swap(char arr[], int i, int j){
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static int call(char arr[], int fixed_index, int len){
        if(fixed_index ==len){
            System.out.println(arr);
            return 0;
        }
        for(int i=fixed_index; i<len; i++){
            swap(arr, fixed_index, i);
            call(arr, fixed_index+1, len);
            swap(arr, fixed_index, i);
        }
        return 0;
    }

    public static void main(String args[]){
        char [] arr = {'A','B','C'};
        // arr = ['A','B','C'];
        call(arr, 0, 3);
    }
}
