#include <iostream>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;

class LFUCache {
    typedef struct LFU {
        int key_;
        int value_;
        int freq_;
        LFU(int key, int value, int freq) : key_(key), value_(value), freq_(freq) {};
    } LFU;

public:
    LFUCache(int capacity) {
        cap_ = capacity;
    }

    int get(int key) {
        if (key_map_.count(key) == 0) {
            return -1;
        }

        freq_incr(key);
        return (*key_map_[key])->value_;
    }

    void put(int key, int value) {
        if (cap_ <= 0) {
            return;
        }

        if (key_map_.count(key) == 0) {
            freq_incr(key);
            (*key_map_[key])->value_ = value;
        } else {
            if (key_map_.size() == cap_) {
                // squeeze minimum frequency
                auto& li = freq_map_.begin()->second;
                key_map_.erase(li.back()->key_);
                li.pop_back();
            }

            _freq_incr(key, value, 0);
        }
    }

private:
    void freq_incr(int key) {
        int value = (*key_map_[key])->value_;
        int freq = (*key_map_[key])->freq_;

        // list.erase + freq_map.erase
        auto& li = freq_map_[freq];
        li.erase(key_map_[key]);
        if (li.empty()) {
            freq_map_.erase(freq);
        }

        _freq_incr(key, value, freq);
    }

    void _freq_incr(int key, int value, int freq) {
        if (freq_map_.count(freq + 1) == 0) {
            freq_map_[freq + 1] = li_;
        }

        auto& li = freq_map_[freq + 1];
        li.push_front(new LFU(key, value, freq + 1));
        key_map_[key] = li.begin();
    }

    void freq_map_show() {
        cout << "freq map show:" << endl;
        for (auto it : freq_map_) {
            cout << it.first << ": ";
            for (auto lfu : it.second)
                cout << lfu->key_ << " ";
            cout << "\t";
        }
        cout << endl;
    }

    int cap_;
    list<LFU *> li_;
    map<int, decltype(li_)> freq_map_;
    unordered_map<int, decltype(li_)::iterator> key_map_;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    LFUCache *lfu = new LFUCache(2);
    lfu->put(1, 1);
    cout << "put 1 1" << endl;
    lfu->put(2, 2);
    cout << "put 2 2" << endl;
    cout << "get " << lfu->get(1) << endl;      // return 1
    lfu->put(3, 3);   // evicts key 2
    cout << "put 3 3" << endl;
    //lfu->get(2);      // return -1 (not found)
    cout << "get " << lfu->get(2) << endl;
    //lfu->get(3);      // return 3
    cout << "get " << lfu->get(3) << endl;
    lfu->put(4, 4);   // evicts key 1.
    cout << "put 4 4" << endl;
    //lfu->get(1);      // return -1 (not found)
    cout << "get " << lfu->get(1) << endl;
    //lfu->get(3);      // return 3
    cout << "get " << lfu->get(3) << endl;
    //lfu->get(4);      // return 4
    cout << "get " << lfu->get(4) << endl;
    return 0;
}
