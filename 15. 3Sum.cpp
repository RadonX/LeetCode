//https://leetcode.com/problems/3sum/

//50ms
// similiar to my Solution1, where a hashmap is not necessary
// his way to deal with duplicates are more elegant
class otherSolution{
//https://leetcode.com/discuss/23595/share-my-solution-around-50ms-with-explanation-and-comments
public:
    vector<vector<int> > threeSum(vector<int> &num) {

        vector<vector<int> > res;

        std::sort(num.begin(), num.end());

        for (int i = 0; i < num.size(); i++) {

            int target = -num[i];
            int front = i + 1;
            int back = num.size() - 1;

            while (front < back) {

                int sum = num[front] + num[back];

                // Finding answer which start from number num[i]
                if (sum < target)
                    front++;

                else if (sum > target)
                    back--;

                else {
                    vector<int> triplet(3, 0);
                    triplet[0] = num[i];
                    triplet[1] = num[front];
                    triplet[2] = num[back];
                    res.push_back(triplet);

                    // Processing duplicates of Number 2
                    // Rolling the front pointer to the next different number forwards
                    while (front < back && num[front] == triplet[1]) front++;

                    // Processing duplicates of Number 3
                    // Rolling the back pointer to the next different number backwards
                    while (front < back && num[back] == triplet[2]) rear--;
                }

            }

            // Processing duplicates of Number 1
            while (i + 1 < num.size() && num[i + 1] == num[i])
                i++;

        }

        return res;

    }

}

// 68ms, 16.79%
class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > res;// = new vector<vector<int> >();
        if (nums.size() < 3) return res;

        vector<int> arr;

        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++){
            if (hashmap.count(nums[i]) > 0){
                hashmap[nums[i]]++;
            }else{
                hashmap[nums[i]] = 1;
                arr.push_back(nums[i]);// only make sense when there can be many duplicates
            }
        }
        sort(arr.begin(), arr.end());
        int tmp;
        for (int i = 0; i < arr.size(); i++){
            //[0,0,0]
            if (arr[i] == 0 && hashmap[0] >= 3){
                res.push_back(vector<int> {0,0,0});
            }
            //[a,a,b]
            if (hashmap[arr[i]] >= 2){
                tmp = - arr[i] - arr[i];
                if (tmp > arr[i] && hashmap.count(tmp) > 0 ) {
                    res.push_back(vector<int> {arr[i], arr[i], tmp});
                }
            }
            //[a,b,b]
            if (arr[i] % 2 == 0){//&1 = 0
                tmp = -arr[i]/2;
                if (tmp > arr[i] && hashmap.count(tmp) > 0 && hashmap[tmp] >= 2 ){
                    res.push_back(vector<int> {arr[i], tmp, tmp});
                }
            }
            //[a,b,c]
            for (int j = i + 1; j < arr.size(); j++){
                tmp = -arr[i]-arr[j];
                if (tmp > arr[j] && hashmap.count(tmp) > 0){
                    res.push_back(vector<int> {arr[i],arr[j],tmp});
                }
            }
        }

        return res;
    }
};

// 88ms, 7.14%

class Solution1 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > res;// = new vector<vector<int> >();
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end() );

        int target;
        unordered_set<int> hashmap;
        bool flag;
        for (int i = 0; i < nums.size(); i++){
            if (i > 0 && nums[i] == nums[i-1]) continue;
            hashmap.clear();
            flag = false;
            for(int j = i + 1; j < nums.size(); j++ ){
                if (hashmap.count(nums[j]) == 1) {
                    if(nums[j] == nums[j-1] && flag) continue;
                    res.push_back(vector<int> {nums[i], -nums[i] - nums[j],nums[j]}  );
                    flag = true;
                }else{
                    if (j > i+1 && nums[j] == nums[j-1]) continue;
                    hashmap.insert(- nums[i] - nums[j]);
                    flag = false;
                }
            }
        }

        return res;
    }
};
