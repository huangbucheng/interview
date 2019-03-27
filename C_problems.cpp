// 第一题：在一个二叉树中找到所有节点的内容包含某子串的节点，并使用快速排序方法找到顺序为第n位的节点值。排序规则如下：子串出现的次数，如果次数一样则按字符数排序，如果字符数一样则按ascii排序。

#include <string>
#include <vector>
#include <iostream>

struct TNode {
    struct TNode* left;
    struct TNode* right;
    std::string val;
};

typedef std::vector<struct TNode*> TNodeList;

bool bContains(struct TNode* node, const std::string & substr) {
    std::size_t idx = node->val.find(substr);
    return idx != std::string::npos;
}

void findNodes(struct TNode* head, const std::string & substr, TNodeList& result) {
    if (!head) {return;}

    if (bContains(head, substr)) {
        result.push_back(head);
    }
    findNodes(head->left, substr, result);
    findNodes(head->right, substr, result);
}

std::string val_list[10] = {
    "ushq", "usus", "hskd", "iwkd", "irws",
    "ushq", "usus", "husd", "itkd", "inos",
};

void makeTree(struct TNode* head, int seq, int max) {
    if (!head) {return;}
    if (max == 0) {return;}

    head->left = NULL;
    head->right = NULL;
    head->val = val_list[seq % 10];
    if (max <= 1) {return;}

    head->left = new(struct TNode);
    makeTree(head->left, seq+1, max/2);
    if (max <= 2) {return;}

    head->right = new(struct TNode);
    makeTree(head->right, seq+max/2+1, max/2 + max%2);
    return;
}

int substrCount(std::string s_str, const std::string & substr) {
    int count = 0;
    std::size_t idx = s_str.find(substr);
    while (idx != std::string::npos) {
        count++;
        idx = s_str.find(substr, idx+substr.size());
    }
    return count;
}

// left < right -> -1; left == right -> 0; else False
int bCompare(struct TNode* left, struct TNode* right, const std::string & substr) {
    int l_count = substrCount(left->val, substr);
    int r_count = substrCount(right->val, substr);
    if (l_count != r_count) {
        if (l_count < r_count) {
            return -1;
        } else {
            return 1;
        }
    }

    if (left->val.size() != right->val.size()) {
        if (left->val.size() < right->val.size()) {
            return -1;
        } else {
            return 1;
        }
    }

    return left->val.compare(right->val);
}

void quick_sort(TNodeList& s_list, int left, int right, const std::string & substr) {
    if (left >= right) {return;}

    int left_s = left;
    int right_e = right;
    struct TNode* privot = s_list[left];
    while (left < right) {
        while (right > left) {
            int bRes = bCompare(s_list[right], privot, substr);
            if (bRes <= 0) {
                s_list[left++] = s_list[right];
                break;
            }
            right--;
        }
        while (left < right) {
            int bRes = bCompare(s_list[left], privot, substr);
            if (bRes > 0) {
                s_list[right++] = s_list[left];
                break;
            }
            left++;
        }
    }
    s_list[left] = privot;

    quick_sort(s_list, left_s, left-1, substr);
    quick_sort(s_list, right+1, right_e, substr);
}

void trvalTree(struct TNode* head) {
    if (!head) {return;}
    trvalTree(head->left);
    std::cout << head->val << std::endl;
    trvalTree(head->right);
}

int main() {
    struct TNode head;
    makeTree(&head, 0, 20);
    // trvalTree(&head);

    TNodeList results;
    findNodes(&head, "us", results);
    quick_sort(results, 0, results.size()-1, "us");
    for (int i = 0; i < results.size(); i++) {
        std::cout << i << ": " << results[i]->val << std::endl;
    }
}
