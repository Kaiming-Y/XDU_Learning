# 回溯法解决8-皇后问题

n = 8
board = [None] * n
cnt = 0


def can_put(row: int, column: int) -> bool:
    for i in range(row):
        if board[i] == column or abs(row - i) == abs(column - board[i]):
            return False
    return True


def find_n_queen(row: int):
    global cnt

    if row == n:
        cnt += 1
        return

    for col in range(n):
        if can_put(row, col):
            board[row] = col
            find_n_queen(row + 1)
            board[row] = None  # 回溯


find_n_queen(0)
print("解的总数：", cnt)
