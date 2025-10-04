class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = 0;
        int j = 0;
        while (i < m || j < n) {
            if (j == n || i < m && nums1[i] <= nums2[j]) {
                nums1[(m + i + j) % (m + n)] = nums1[i];
                i++;
            } else {
                nums1[(m + i + j) % (m + n)] = nums2[j];
                j++;
            }
        }
        int k = 0;
        for (int i = m; i < m + n; i++) {
            nums2[k++] = nums1[i];
        }
        for (int i = m - 1; i >= 0; i--) {
            nums1[i + n] = nums1[i];
        }
        for (int i = 0; i < n; i++) {
            nums1[i] = nums2[i];
        }
    }
};
