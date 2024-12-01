/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#define DEBUG(x) { cout << #x << " = " << (x) << endl; }
#define sz(x) int((x).size())
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> v;
        ListNode* tmp = head;
        while (tmp != nullptr) {
            v.push_back(tmp);
            tmp = tmp->next;
        }
        int id = sz(v);
        for (int i = 0; i < id - 1 - i; i++) {
            v[i]->next = v[id - 1 - i];
            if (id - 1 - i > i + 1) {
                v[id - 1 - i]->next = v[i + 1];
                v[id - 2 - i]->next = nullptr;
            }
        }
    }
};
