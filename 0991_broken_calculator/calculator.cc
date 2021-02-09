class Solution {
public:
    int brokenCalc(int X, int Y) {
        int step = 0;
        while (X < Y) {
            Y = Y & 1 ? Y + 1 : Y / 2;
            step++;
        }
        step += X - Y;
        return step;
    }
};
