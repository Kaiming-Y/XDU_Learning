USE BANK817;

# 1 创建一个视图branch_detail，能够显示所有支行的存款客户数量、存款总额、贷款客户数量、贷款总额
CREATE VIEW branch_detail AS
    SELECT b.branch_name,
           COUNT(d.customer_name) AS deposit_customer_count,
           SUM(a.balance) AS deposit_total_balance,
           COUNT(bo.customer_name) AS loan_customer_count,
           SUM(l.amount) AS loan_total_amount
    FROM branch817 b
    LEFT JOIN account817 a ON b.branch_name = a.branch_name
    LEFT JOIN depositor817 d ON a.account_number = d.account_number
    LEFT JOIN loan817 l ON b.branch_name = l.branch_name
    LEFT JOIN borrower817 bo ON l.loan_number = bo.loan_number
    GROUP BY b.branch_name;
SELECT * FROM branch_detail;


# 2 在account的account_number属性上建立索引，并在account表里插入大量元组，比较有无索引在查询速度上的区别
DROP PROCEDURE IF EXISTS InsertMultipleAccounts;
-- 插入大量元组的过程
DELIMITER //
CREATE PROCEDURE InsertMultipleAccounts(IN num_rows INT)
BEGIN
    DECLARE i INT;
    DECLARE new_account_number VARCHAR(10);
    SET i = 1;
    SET new_account_number = '';
    WHILE i <= num_rows DO
        SET new_account_number = CONCAT('A-', LPAD(100 + FLOOR(RAND() * 99900), 5, '0'));
        IF NOT EXISTS (SELECT 'Exist' FROM account817 WHERE account_number = new_account_number) THEN
            INSERT INTO account817 (account_number, branch_name, balance)
            SELECT
                 new_account_number, -- account_number
                ELT(1 + FLOOR(RAND() * 7), 'Brighton', 'Downtown', 'Mianus', 'North Town', 'Perryridge', 'Pownal', 'Redwood', 'Round Hill'),-- branch_name
                FLOOR(RAND() * 100) * 10; -- balance
            SET i = i + 1;
        END IF;
    END WHILE;
END//
DELIMITER ;

-- 插入大量数据
CALL InsertMultipleAccounts(100000);
# SELECT * FROM account817 WHERE account_number = 'A-99099';
-- 创建索引
CREATE INDEX amount_number_index ON account817(account_number);
-- 查询数据
SELECT * FROM account817 WHERE branch_name = 'Brighton';
-- 删除索引
DROP INDEX amount_number_index ON account817;
-- 查询数据
SELECT * FROM account817 WHERE branch_name = 'Brighton';


# 3 创建角色银行经理branch_manager，银行经理具有插入、删除和更新branch表的权限
-- 创建银行经理角色
CREATE ROLE branch_manager;
-- 授予插入权限
GRANT INSERT ON bank817.branch817 TO branch_manager;
-- 授予删除权限
GRANT DELETE ON bank817.branch817 TO branch_manager;
-- 授予更新权限
GRANT UPDATE ON bank817.branch817 TO branch_manager;
-- 查询权限
SHOW GRANTS FOR branch_manager;