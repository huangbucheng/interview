#include <iostream>
#include <vector>

void print(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/*
 * 将一个连续区间翻转
 */
void reverse_range(std::vector<int>& arr, int s, int e) {
    int size = arr.size();
    if ((s > e) || (e > size)) {
        return;
    }

    int len = e-s+1;
    for (int i = 0; i < len/2; i++) {
        std::swap(arr[s+i], arr[e-i]);
    }
}

/*
 * 将2个区间连接起来翻转
 */
void reverse_apart_range(std::vector<int>& arr, int s1, int e1, int s2, int e2) {
    int size = arr.size();
    if (((s1 > e1) || (e1 > size)) || ((s2 > e2) || (e2 > size))) {
        return;
    }

    int len1 = e1 - s1 + 1;
    int len2 = e2 - s2 + 1;
    for (int i = 0; i < (len1 + len2)/2; i++) {
        int s_idx = i < len1 ? s1 + i : s2 + i - len1;
        int e_idx = i < len2 ? e2 - i : e1 - i + len2;
        std::swap(arr[s_idx], arr[e_idx]);
    }
}

void swap_range(std::vector<int>& arr, int s1, int e1, int s2, int e2) {
    int size = arr.size();
    if ((s1 < s2 && e1 >= s2) || (s1 > s2 && e2 >= s1)) {
        // 不允许交叉
        return;
    }

    if (s1 > s2) {
        s1 = s1 + s2;
        s2 = s1 - s2;
        s1 = s1 - s2;

        e1 = e1 + e2;
        e2 = e1 - e2;
        e1 = e1 - e2;
    }

    int len1 = e1 - s1 + 1;
    int len2 = e2 - s2 + 1;

    print(arr);
    // swap s1-e1
    reverse_range(arr, s1, e1);
    // swap s2-e2
    reverse_range(arr, s2, e2);

    // s1-e1 与 s2-e2连接翻转
    reverse_apart_range(arr, s1, e1, s2, e2);

    if ((len1 == len2) || (s2 - e1 == 1)) { return; }
    if (len1 < len2) {
        swap_range(arr, e1+1, s2-1, s2, s2+len2-len1-1);
    } else if (len1 > len2) {
        swap_range(arr, s1+len2, e1, e1+1, s2-1);
    }
}

int main() {
    int s_list[9] = {1,2,3,4,8,5,7,6,9};
    std::vector<int> arr(s_list, s_list+9);
    std::cout << "---------------------" << std::endl;
    std::cout << "[2,3] <-> [5,7]" << std::endl;
    swap_range(arr, 2, 3, 5, 7);
    print(arr);
    std::cout << "---------------------" << std::endl;
    std::cout << "[0,3] <-> [4,8]" << std::endl;
    swap_range(arr, 0, 3, 4, 8);
    print(arr);
    std::cout << "---------------------" << std::endl;
    std::cout << "[2,3] <-> [7,7]" << std::endl;
    swap_range(arr, 2, 3, 7, 7);
    print(arr);
    std::cout << "---------------------" << std::endl;
    std::cout << "[2,2] <-> [5,7]" << std::endl;
    swap_range(arr, 2, 2, 5, 7);
    print(arr);
}
