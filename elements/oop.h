#ifndef OOP_H
#define OOP_H

#include <list>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

class OOP
{
public:
    OOP();

    //------------hash table
    template<typename T, typename V>
    class HashMap {
        vector<list<pair<T,V> > > arr;
        int arrLen=100;
        int hashCode(T & t) {
            return hash<T>(t) % arr.size();
        }
    public:
        HashMap() : arr(arrLen) {}

        bool insert(const pair<T, V> & x) {
            int index = hashCode(x.first);
            list<pair<T, V> > t = arr[index];
            for (auto i=t.begin(); i != t.end(); i++) {
                if (i->first==x.first)
                    return false;
            }
            t.push_back(x);
            return true;
        }

        pair<T, V> get(T & key) {
            int index = hashCode(key);
            auto t = arr[index];
            for (auto itr = t.begin(); itr != t.end(); itr++) {
                if (itr->first == key)
                    return *itr;
            }
            return t.end();
        }

    };

    // find the missing number in 4billion integers (nonnegative) with 10 MB memory
    // 4 billion = 2^32 integers
    // 10 MB = 2^20*8=2^23 MB = 2^21 integers (4B integer)
    // rangeSize = bitSize > 2^32/2^21 = 2^11, choose 2^12;
    // chunkSize = 2^32 / 2^12 = 2^20;
    // or choose bitsize = 2^12, rangSize=2^20
    int findMissNumber(fstream &fs);

    string tail(const string &filename, int numLine);
    //-----------chat room---

    // simple system in a single machine, big memory, limited memory with big disk storage, caching
    // distribute system: parallel processing, distribute data, failure tolerancy (duplicate), caching update, data sync
    // webserver, database, caching
    // data storage: file, DB, json/xml, bloom bile, balance memory/DB
    // lantency: network bandwidth, processing time, caching (LRU, least recently used), parallel, single/multiple machines,

    struct Community {
        string name;
        int ID;
//        vector<FBNode> members;
    };

    template<typename T>
    struct Item {
        ~Item(){}
        string name;
        string category;
        int id;
        vector<T> getFeatures(){}
    };

    struct User {
        string name;
        int userID;
        string address;
        int registrationTime;
        string password;
        string profileImage;
        string private_checkup;
        vector<Item<string> > purchaseHistory;
    };

    struct Documentation : public Item<string> {
        string author;
        int publishTime;
        vector<string> getFeatures() {
            // scan the doc to return list of word with high TF.IDF scores
            return vector<string>();
        }
    };

    struct Movie : public Item<string> {
        string name;
        int publishTime;
        string director;
        vector<string> actors;
        string genre;

        vector<string> getFeatures() {
            return vector<string>();
        }
    };

    struct PC : public Item<int> {
        int specifications;
        vector<int> getFeatures() {
            return vector<int>();
        }
    };

    struct FBNode {
        User userprofile;
        vector<shared_ptr<FBNode> > friends;
        vector<shared_ptr<FBNode> > requests;
        vector<shared_ptr<FBNode> > news;

        vector<string> poster;

        vector<shared_ptr<Community> > groups;

        vector<string> photos;
    };

    class Recommendation {
        vector<vector<double> > utility;

        int JacardDistance;
        int cosineDistance;

        vector<User> users; // define user based on purchase/read/review
        vector<Item<string> > items; // define items by the features: doc->words of high TF.IDF, movie->director/actor/year/genre/rating, product->normalizeParams/rating/
        unordered_map<string, User> tableUsers;
        unordered_map<string, User> tableItem;

        unordered_map<string, vector<User> > similarUsers;
        unordered_map<string, vector<Item<string> > > similarItems;

        // collaborativeFiltering()
        // user-based: compute similary between the pair of users: user is defined by purchase/review/read/otherbehavior, use
        // item-based: compute similarity between the pair of items: for each item of user purchase, for each user of purchased the item: for each item of that user

        // Clustering(): due to the spasity of the matrix, cluter the users and items to make reliable measurement: hierarchical clustering and k-mean (centriol/clustriol based), LSH to build buckets;

    public:
        string recommend(const User &user){}
        string recommend(const Item<string> &item){}
        void addUpdateUser(const User &user){}
        void addUpdateItem(const Item<string> &item){}
        void deleteUser(const User &user){}
        void deleteItem(const Item<string> &item){}

    };

    class Advertise {
        unordered_map<string, vector<Item<string> > > keyAds_bids; // online-greedy
        unordered_map<string, vector<Item<string> > > keyAds_budgetBalance;
        unordered_map<string, vector<Item<string> > > keyAds_distribution; // rarest_word go first

    public:
        void addAd(){}
        void updateAd(){}
        void deleteAd(){}

    };

    class Search {
        unordered_map<string, vector<string> > matchingResults; //ranked list,
                                // website sorted by PageRank,
                                // spelling is sorted by editdistance and keyboard layout/phonic_model/userHistory
                                // article is sorted by popularity, latest release
                                // book/merchandise is sorted by rating/price/popularity
                                // movie is sorted by rating/popularity/genre
        void stemming(){}
        void crawler(){}
        void PageRank(){}

    public:
        void query(){}
        void review(){}
    };

    class FB {
        vector<FBNode> people;

    public:
        void search(); // people, item(movie, music, book, product), return rankedList;
        void recommendation(); // doc/message, book, music, movie, product,
        void adwords();      // for advertiser;

    };

    class TwitterNode {
        User user;
        vector<shared_ptr<TwitterNode> > followings;
        vector<shared_ptr<TwitterNode> > followers;
        vector<string> notification;
        vector<string> messages;
        vector<string> discover;
        Recommendation recom_server;
        Advertise ad_server;
    public:
        void retwitter(){}
    };

    void elevatorSystem();
    void FBNewsFeed(); //
    void Twitter(){} // directed graph
    void FBFriendSuggest(){} // unitility matrix, collaborative filtering
    void FBPostSuggest(){}
    void FBFindPlacesAndCheckin(){} // find nearby place based on friends' recommendation, checkins and likes
                                // share with checkin / tag friends /reserve_restaurant
    void partyTickingSystem(){} // list, and hashtable

    struct FourSquareUserNode {
        string name;
        string location;
        vector<int> privacySetting;
        bool checkin;
        string currentLocation(){} // GPS
        vector<User> importFromFB;
    };
    struct Store {
        string name;
        string address;
        int rating;
        int visitors;
        vector<string> comments;
        string map_direction;
        vector<Store> neigbors;
        vector<Store> nextStores;

    };

    void FourSquare(){} // behavious pattern recognition: sequence of sight seeing, social graph, location map graph, store/sights/art/coffe/book/nightlife, recently opened, promotion(ads), recommendation

    struct Auction {
        string itemName;
        string description;
        int basePrice;
        vector<User> bidders;
        int currentPrice;
        int duetime;
        vector<string> comments;
    };

    struct paypalBuyer {
        string name;

    };

    struct paypalSeller {
        string name;

    };

    void Paypal(){} //
    void ebayAuction(){}

    struct Company {
        string name;
        string description;
        int currentprice;
        vector<int> history;
        vector<string> news;
        vector<int> fundamentals;
        vector<Company> competitors;
        vector<User> management;
        vector<int> analysis;
    };

    void stockUpdateSystem(){}

    struct dropboxUser {

    };

    void dropbox(){}
    void searchqueryWithMultipleMachines(); // queue for short_query, long_query at the coordinator server, memcached server, data distributed with hashcode and load balance, replication for fault tolerance
    void trieScalability(){}
    void bloomfilter(){} // reduce the memory usage with accepted false positive rate. bit array with multiple hash functions to set the bits
    void FBOldestFriends(){}

    void googleNews(){} // topics, top stories/recent,weather, world/US/NewYork, politics/Business/techology/entertainment/science/sport/health
    void youtube(){} // recommendation->(recently)watched/review/friends/similar_users/popular, features->genre/directors/authors/actors/movie_tag/keyword, movie ads
                    // TV shows, action/adventure, children/family, classic, comedy, documentation, drama, faith/spiritual, sports, music, romance, foreign, thriller/horror, sci-fi/fantansy
    void meetingSchedule(){} // restaurantReservation(), userManager, tableManager, add/update/delete, onlineGreedy/distributionManage/priorityUsers,
    void FBPublishGetNewFeedFunctions(){}
    void FBFriendsOnLine(){} // UserOnlineFlag
    void twitterPostMessageGetMessage(){} //
    void phoneBook(){}
    void goolecom(){} // page ranking, storage and retrieval, spell checking/suggest, ads,recommendation. sterming
    void amazonRecommendationEngine(){}
    void gmail(){} // authentication, distributed database/replication, mobile/PC interface, spam detection/tag

    //Machine learning is not a new technology at Facebook: they use it to place adverts, rank news feed items and suggest friends for their users
    //   Read more at: http://phys.org/news/2013-12-facebook-machine.html#jCp
    // Targeted advertising from supermarkets, movie recommendations from Netflix and book suggestions from Amazon are all driven by machine learning models which predict human behaviour


};

#endif // OOP_H
