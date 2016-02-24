#include <string>
#include <iostream>
using namespace std;

const string thous[4] = {"", " Thousand", " Million", " Billion" };
const string numbers[20] = {" Zero", " One", " Two", " Three", " Four", " Five",
        " Six", " Seven", " Eight", " Nine", " Ten", " Eleven"," Twelve",
        " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen",
        " Eighteen", " Nineteen"};
const string tens[] = {"",""," Twenty", " Thirty", " Forty", " Fifty", " Sixty",
        " Seventy", " Eighty", " Ninety"};

class Solution {

public:

    string get1000(int num){
        //if(num >= 1000) return "!";
        //if(num == 0) return "";
        string res;
        int hundred = num / 100;
        if(hundred != 0){
            res = numbers[hundred] + " Hundred";
        }
        num = num % 100;
        if(num == 0) return res;
        if(num < 20){
            res = res + numbers[num];
            //no "And"
        }else{
            int ten = num / 10;
            res = res + tens[ten];
            num = num % 10;
            if(num == 0) return res;
            res = res + numbers[num];
        }
        return res;
    }

    string numberToWords(int num) {
        string ans;
        int unit = 0;
        if(num == 0) return "Zero";
        while(num > 0){
            if(num%1000 > 0){ // 1000000001
                ans = get1000(num % 1000) + thous[unit] + ans;
            }
            num = num / 1000;
            unit++;
        }
        return ans.substr(1,1000);
    }

};

int main(){
    Solution solution;
    int num;

    cin >> num;
    cout << solution.numberToWords(num);

    return 0;

}
