#ifndef TEST_CMD_H
#define TEST_CMD_H

#define TEST_MAGIC 'x'
#define TEST_MAX_NR 3

#define RW_CLEAR _IO(TEST_MAGIC,1)
#define READ_OLD _IO(TEST_MAGIC,2)
#define READ_NEW _IO(TEST_MAGIC,3)

#endif
