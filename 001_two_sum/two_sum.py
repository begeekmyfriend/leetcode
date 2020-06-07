class Solution:
    def twoSum(self, nums, target):
        h = {}
        for i, n in enumerate(nums):
            other = target - n
            if other not in h:
                h[n] = i
            else:
                return [h[other], i]

print(Solution().twoSum([-1, -2, -3, -4, -5], -8))
