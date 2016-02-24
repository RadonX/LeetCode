#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Solution {

public:
    int partition(vector<int>& nums,int p,int r){
        int pivot, tmp, i, j;
        // the selection of pivot
        // - method
        //  1. rand
        //  2. (min+max)/2

        //srand (time(NULL));//dangerous
        int xpivot = rand()%(r - p + 1) + p;
        tmp = nums[xpivot];
        nums[xpivot] = nums[r];
        nums[r] = tmp;
        pivot = nums[r];

        i = p - 1;
        for(j = p; j <= r; j++){
            if(nums[j] <= pivot){
                i++;
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
        return i;

        //can deal with the pivot pair
    }

    int singleNumber(vector<int>& nums) {
        if(!nums.size()) return 0; //0

        int p = 0, r = nums.size()-1, x;
        while(p < r){
            x = partition(nums, p, r);
            if(x%2 == 0){
                r = x;
            }else { //(x+1)%2 == 0
                p = x + 1;
            }
            printf("-%d\n", x);
            for(int i = 0; i < 7; i++){
                printf(" %d", nums[i]);
            }
            printf("\n");

        }

        return nums[p];


    }

};

int main(){
    Solution solution;
    vector<int> nums;

    int a[] = {1,3,1,-1,3};
    for(int i = 0; i < 5; i++){
        nums.push_back(a[i]);
        // for(int j = 0; j < 3; j++){
        //     matrix[i][j] = nums[i][j];
        // }
    }

    printf("%d\n",solution.singleNumber(nums) );

    return 0;

}
