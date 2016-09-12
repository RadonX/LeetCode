#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Twitter {
    int timestamp;
    typedef pair<int, int> Tweet; // timestamp, tweetId
    typedef pair<int, deque<Tweet>::iterator> TweetEle; // timestamp, tweetByUser::it
    map<int, deque<Tweet> > tweetByUser;
    map<int, set<int> > followingByUser; // follow oneselt when posting 1st (null) tweet

public:
    Twitter() {
        timestamp = 0;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if (tweetByUser.find(userId) == tweetByUser.end()) {
            // post tweet for the 1st time
            tweetByUser[userId].push_back(make_pair(-1, -1));
            followingByUser[userId].insert(userId);
        }
        tweetByUser[userId].push_back(make_pair(timestamp++, tweetId));
    }

    /**
     * Retrieve the 10 most recent tweet ids in the user's news feed.
     * Each item in the news feed must be posted by users who the user followed
     * or by the user herself. Tweets must be ordered from most recent to least recent.
     */
    vector<int> getNewsFeed(int userId) {
        vector<TweetEle> arr;
        for (auto & followee: followingByUser[userId]) {
            deque<Tweet>::iterator it = prev(tweetByUser[followee].end());
            arr.push_back(make_pair((*it).first, it));
        }
        priority_queue<TweetEle> heap(arr.begin(), arr.end()); // max heap

        if (heap.empty()) return vector<int>();
        vector<int> ans;
        while (heap.top().first != -1) {
            deque<Tweet>::iterator it = heap.top().second;
            ans.push_back((*it).second);
            if (ans.size() == 10) break;
            heap.pop();
            --it;
            heap.push(make_pair((*it).first, it));
        }
        return ans;
    }


    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (tweetByUser.find(followeeId) == tweetByUser.end()){
            // followeeId post a first and null (bound) tweet
            tweetByUser[followeeId].push_back(make_pair(-1, -1));
            followingByUser[followeeId].insert(followeeId);
        }
        followingByUser[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        // invalid
        if (followerId == followeeId) return;

        followingByUser[followerId].erase(followeeId);
    }
};



int main() {
    Twitter obj;

    obj.postTweet(1,5);
    obj.follow(1,2);
    obj.unfollow(1,1);
    obj.follow(2,1);
    for (auto &a: obj.getNewsFeed(2)) cout << a << ' '; cout << endl; // 5
    obj.postTweet(2,6);
    for (auto &a: obj.getNewsFeed(1)) cout << a << ' '; cout << endl; //
    for (auto &a: obj.getNewsFeed(2)) cout << a << ' '; cout << endl;
    obj.unfollow(2,1);
    for (auto &a: obj.getNewsFeed(1)) cout << a << ' '; cout << endl;
    for (auto &a: obj.getNewsFeed(2)) cout << a << ' '; cout << endl;
    obj.unfollow(1,2);
    for (auto &a: obj.getNewsFeed(1)) cout << a << ' '; cout << endl;
    for (auto &a: obj.getNewsFeed(2)) cout << a << ' '; cout << endl;

    return 0;
}
