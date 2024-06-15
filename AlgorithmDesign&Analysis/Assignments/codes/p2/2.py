# Longest Common Subsequence (LCS).
# The following are some instances.
# a) X: xzyzzyx   Y: zxyyzxz
# b) X: MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD
#    Y: MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG

def lcs(x, y):
    x_len, y_len = len(x), len(y)
    # dp数组：X串前m个和Y串前n个的最长子序列
    dp = [[0 for _ in range(x_len+1)] for _ in range(y_len+1)]

    for i in range(1, x_len+1):
        for j in range(1, y_len+1):
            if x[i-1] == y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    return dp[x_len][y_len]


X_1 = "xzyzzyx"
Y_1 = "zxyyzxz"

X_2 = "MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD"
Y_2 = "MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG"

print(lcs(X_1, Y_1))
print(lcs(X_2, Y_2))
