#include <bits/stdc++.h>

using namespace std;

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
class LRUCache {
public:
    LRUCache(int capacity) {
        cap_ = capacity;
    }

    int get(int key) {
        if (ht_.count(key) == 0) {
            return -1;
        }

        int value = (*ht_[key]).second;
        if (li_.front().first != key) {
            li_.erase(ht_[key]);
            li_.push_front(make_pair(key, value));
            ht_[key] = li_.begin(); // iterator failure
        }

        return value;
    }

    void put(int key, int value) {
        if (cap_ <= 0) {
            return;
        }

        if (ht_.count(key) == 0) {
            li_.erase(ht_[key]);
        } else {
            if (li_.size() == cap_) {
                auto lru = li_.back();
                li_.pop_back();
                ht_.erase(lru.first);
            }
        }
        li_.push_front(make_pair(key, value));
        ht_[key] = li_.begin(); // iterator failure
    }

private:
    int cap_;
    list<pair<int, int>> li_;
    unordered_map<int, list<pair<int, int>>::iterator> ht_;
};
