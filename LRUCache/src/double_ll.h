#pragma once
#include <cstddef>

template <typename T>
struct Node {
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;

    explicit Node(const T& d) : data(d) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head_ = nullptr; 
    Node<T>* tail_ = nullptr;

public:
    LinkedList() = default;

    ~LinkedList() {
        Node<T>* cur = head_;
        while (cur) {
            Node<T>* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    Node<T>* head() const { return head_; }
    Node<T>* tail() const { return tail_; }

    Node<T>* push_front(const T& data) {
        Node<T>* node = new Node<T>(data);
        node->next = head_;
        node->prev = nullptr;

        if (head_) head_->prev = node;
        head_ = node;

        if (!tail_) tail_ = node; 
        return node;
    }

    void detach(Node<T>* node) {
        if (!node) return;

        if (node->prev) node->prev->next = node->next;
        else head_ = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail_ = node->prev;

        node->next = nullptr;
        node->prev = nullptr;
    }

    void move_to_front(Node<T>* node) {
        if (!node || node == head_) return;
        detach(node);

        node->next = head_;
        node->prev = nullptr;
        if (head_) head_->prev = node;
        head_ = node;
    }

    T pop() {
        Node<T>* node = tail_;
        T out = node->data;
        detach(node);
        delete node;
        return out;
    }

    bool empty() const { return head_ == nullptr; }
    std::size_t size() const {
        std::size_t n = 0;
        for (auto* p = head_; p; p = p->next) ++n;
        return n;
    }
};
