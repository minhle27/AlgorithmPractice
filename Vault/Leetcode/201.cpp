class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        for (int i = 31; i >= 0; i--) {
            unsigned int mask = 1 << i;
            if ((right & mask) != (left & mask)) {
                return right & ~((1LL << (i + 1)) - 1);
            }
        }
        return right;
    }
};
