// Forward declaration of specialSort API.
// bool specialSort(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> a;
        for(int i=0;i<N;i++){
            a.push_back(i+1);
        }
        for (int i=1;i<N;i++){
            int temp = a[i]; 
            int left = 0;
            int right = i - 1;
            int mid = 0;
            while (left <= right) {
                mid = (left + right) / 2;
                if (compare(temp,a[mid])) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            for (int j = i - 1; j >= left; j--) {
                a[j + 1] = a[j];
            }
            if (left != i) {
                a[left] = temp;
            }
        }
        return a;
    }
};