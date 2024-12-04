#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())

struct Node {
    int val;
    int key;
    Node* next;
    Node* prev;
    Node(int val, int key) : val { val }, key { key }, next { nullptr }, prev { nullptr } {}
};

struct Queue {
    Node* head { new Node(-1, -1) };
    Node* tail { new Node(-1, -1) };

    Queue() {
        head->next = tail;
        tail->prev = head;
    }

    void enqueue(Node* node) {
        Node* lastNode = tail->prev;
        lastNode->next = node;
        node->prev = lastNode;
        node->next = tail;
        tail->prev = node;
    }

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    Node* top() {
        return head->next;
    }
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, Node*> store;
    Queue* q = new Queue;

    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (store.count(key) == 0) return -1;
        Node* node = store[key];
        q->remove(node);
        q->enqueue(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (store.count(key) > 0) {
            Node* cur = store[key];
            cur->val = value;
            q->remove(cur);
            q->enqueue(cur);
        } else {
            if (sz(store) == capacity) {
                Node* LRUnode = q->top();
                store.erase(LRUnode->key);
                q->remove(LRUnode);
            }
            Node* cur = new Node(value, key);
            store[key] = cur;
            q->enqueue(cur);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
