
#include <stdio.h>

void showlist(int number[],int length){
    printf("{%d",number[0]);
    for(int i = 1; i<length ;i++){
        printf(",%d",number[i]);
    }
    printf("}\n");
}

void mergesort(int number[],int left, int right){
    int i, j, k, mid;
    int work[10];  // 作業用配列
    if (left < right) {
        mid = (left + right)/2; // 真ん中
        mergesort(number, left, mid);  // 左を整列
        mergesort(number, mid+1, right);  // 右を整列

        for (i = mid; i >= left; i--) { work[i] = number[i]; } // 左半分
        for (j = mid+1; j <= right; j++) {
            work[right-j+mid+1] = number[j]; // 右半分を逆順
        }
        i = left; j = right;
        for (k = left; k <= right; k++) {
            if (work[i] < work[j]) { number[k] = work[i++]; }
            else                   { number[k] = work[j--]; }
        }
    }
}

int main(void){
    static int list[] = {8,4,10,12,5,18,6};
    int len = 7,left=0,right=6;
    showlist(list,len);
    mergesort(list,left,right);
    showlist(list,len );

    return 0;
}