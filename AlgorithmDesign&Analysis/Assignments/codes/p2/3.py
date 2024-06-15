# Longest Common Substring.
# The following are some instances.
# a) X: xzyzzyx   Y: zxyyzxz
# b) X: MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD
#    Y: MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG

def longest_common_substring(x, y):
    x_len, y_len = len(x), len(y)
    # dp数组：X串以第m个和Y串第n个为结尾的最长子串长度
    dp = [[0 for _ in range(x_len+1)] for _ in range(y_len+1)]
    max_len = 0

    for i in range(1, x_len+1):
        for j in range(1, y_len+1):
            if x[i-1] == y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
                if dp[i][j] > max_len:
                    max_len = dp[i][j]
            else:
                dp[i][j] = 0

    return max_len


X_1 = "xzyzzyx"
Y_1 = "zxyyzxz"

X_2 = "MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD"
Y_2 = "MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG"

print(longest_common_substring(X_1, Y_1))
print(longest_common_substring(X_2, Y_2))
