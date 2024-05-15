# Max Sum.
# The following is an instance.
# a) (-2，11，-4，13，-5，-2)

def max_subarray_sum(array):
    # dp数组：当前元素结尾的最大子序列和
    dp = [0 for _ in range(len(array))]
    dp[0] = array[0]

    for i in range(1, len(array)):
        if dp[i-1] < 0:
            dp[i] = array[i]
        else:
            dp[i] = array[i] + dp[i-1]

    return max(dp)


a = [-2, 11, -4, 13, -5, -2]

print(max_subarray_sum(a))
