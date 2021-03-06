#include <stdio.h>

void showlist(int number[], int first, int last ){
    printf("{%d",number[first]);
    for(int i = first + 1; i<= last;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}


void quicksort(int number[], int first, int last ){

    int t, e, pivot, temp;

    if (first < last){
        pivot = first;
        t = first;
        e = last;
        
        while(t<e){
            while(number[pivot]>number[t])
                t++;
            while(number[pivot]<number[e])
                e--;
            if(t<e){
                temp = number[t];
                number[t] = number[e];
                number[e] = temp;

            }

        }
        temp = number[t];
        number[t] = number[pivot];
        number[pivot] = temp;

        quicksort(number,pivot,t-1);
        quicksort(number,e+1,last);
    }
}

int main(void){
    static int list[] = {8,4,10,12,5,18,6};
    int first = 0;
    int last = 6;
    showlist(list,first,last);
    quicksort(list,first,last);
    showlist(list,first,last);

    return 0;
}