#include<string>

struct User
{
    std::string university;
    int userID;
    std::string userName;
    int numberTweets;
    int friendsCount;
    int followersCount;
    std::string createdAt;

    User(std::string university, int userID, std::string userName, int numberTweets, int friendsCount, int followersCount, std::string createdAt)
        : university(university), userID(userID), userName(userName), numberTweets(numberTweets), friendsCount(friendsCount), followersCount(followersCount), createdAt(createdAt) {}
    User() {university = ""; userID = 0; userName = ""; numberTweets = 0; friendsCount = 0; followersCount = 0; createdAt = "";}
};
