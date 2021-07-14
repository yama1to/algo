#include <stdio.h>

void showlist(int number[],int length){
    printf("{%d",number[0]);
    for(int i = 1; i<length ;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}

void bubblesort(int number[],int length){
    int temp;
    for(int i=0; i <length-1 ; i++){
        for(int j = length-1; j > i  ; j--){
            if(number[j-1] > number[j]){
                temp = number[j-1];
                number[j-1] = number[j];
                number[j] = temp;

            }
        }
    }
}


int main(void){
    static int list[] = {8,4,10,12,5,18,6};
    int len = 7;
    showlist(list,len);
    bubblesort(list,len );
    showlist(list,len );

    return 0;
}