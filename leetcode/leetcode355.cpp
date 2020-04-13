// 设计一个推特
# include "leetcode.h"


class Twitter {
private:
    static int twitterTime;  // 每条推特的时间不同，使用静态变量储存
    map<int, set<int>> user_twitter;  // 使用map构造用户到推特的映射
    map<int, set<int>> user_follow;   // 用户关注的情况
public:
    /** Initialize your data structure here. */
    Twitter() {

    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        user_twitter[userId].insert(tweetId);  // 为用户添加一条推特
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        user_follow[followerId].insert(followeeId);  // 添加一个关注
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        // 将followeeId从关注列表中移除即可
        map<int, set<int>>::iterator it = user_follow.find(followerId);
        if(it != user_follow.end()){
            set<int>::iterator iter = user_follow[followerId].find(followeeId);
            if(iter != user_follow[followerId].end()){
                user_follow[followerId].erase(iter);
            }
        }
    }
};

int Twitter::twitterTime = 0;  // 初始化静态变量


/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */