#include <iostream>

/*
 * 排列组合
 */
 
void swap(int* src, int* dst) {
    int tmp = *src;
    *src = *dst;
    *dst = tmp;
}

void permutation_all(int s_list[], int left, int size) {
    if (left == size) {
        std::cout << "[LIST]";
        for (int i=0; i<size; i++) {
            std::cout << s_list[i] << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (int i=left; i<size; i++) {
        swap(&s_list[left], &s_list[i]);
        permutation_all(s_list, i+1, size);
        swap(&s_list[left], &s_list[i]);
    }
}

int main() {
    int s_list[5];
    for (int i = 0; i < 5; i++) {
        s_list[i] = i+1;
    }

    permutation_all(s_list, 0, 5);
}
