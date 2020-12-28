#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int min = 0, max = height.size() - 1;
        int area_max = 0;
        while (min < max) {
            int area = (max - min) * (height[min] < height[max] ? height[min] : height[max]);
            area_max = area > area_max ? area : area_max;
            if (height[min] < height[max]) {
                min++;
            } else {
                max--;
            }
        }
        return area_max; 
    }
};
