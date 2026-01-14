#pragma once
#include "double_ll.h"
#include <unordered_map>
#include <utility>
#include <stdexcept>
#include <iostream>

template <typename K, typename V>
class LRUCache {
private:
    std::size_t capacity_;
    std::unordered_map<K, std::pair<V, Node<K>*>> map_;
    LinkedList<K> list_;

public:
    explicit LRUCache(std::size_t capacity = 50) : capacity_(capacity) {
        if (capacity_ == 0) throw std::invalid_argument("Capacity must be > 0");
    }

    bool contains(const K& key) const {
        return map_.find(key) != map_.end();
    }

    V* get(const K& key) {
        auto it = map_.find(key);
        if (it == map_.end()) return nullptr;

        std::cout << "Found value: " << it->second.first << " in the map!" << std::endl;
        list_.move_to_front(it->second.second);
        return &it->second.first;
    }

    void put(const K& key, const V& value) {
        auto it = map_.find(key);

        if (it != map_.end()) {
            it->second.first = value;
            list_.move_to_front(it->second.second);
            return;
        }

        if (map_.size() >= capacity_) {
            K evicted_key = list_.pop();
            std::cout << "Evicted key: " << evicted_key << " from the map!" << std::endl;
            map_.erase(evicted_key);
        }

        std::cout << "Added value: " << value << " to the map!" << std::endl;
        Node<K>* node = list_.push_front(key);
        map_.emplace(key, std::make_pair(value, node));
    }

    std::size_t size() const { return map_.size(); }
    std::size_t capacity() const { return capacity_; }
};
