USE bank817;

# 创建一个函数，为所有存款账户增加1%的利息。
DELIMITER //
CREATE PROCEDURE AddInterestToAccounts()
BEGIN
    DECLARE done INT DEFAULT 0;
    DECLARE accountNumber VARCHAR(10);
    DECLARE oldBalance NUMERIC(12, 2);
    DECLARE newBalance NUMERIC(12, 2);
    -- 游标用来遍历存款账户
    DECLARE accountCursor CURSOR FOR
        SELECT account_number, balance FROM account817;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
    OPEN accountCursor;

    read_loop: LOOP
    -- 从游标中获取下一个账户号码
    FETCH accountCursor INTO accountNumber, oldBalance;
    -- 如果没有更多的账户，则退出循环
    IF done = 1 THEN
      LEAVE read_loop;
    END IF;
    -- 计算新余额，增加1%的利息
    SET newBalance = oldBalance * 1.01;
    -- 更新账户余额
    UPDATE account817 SET balance = newBalance WHERE account_number = accountNumber;
  END LOOP;

  CLOSE accountCursor;
END;
//
DELIMITER ;

-- 执行为所有存款账户增加1%的利息
CALL AddInterestToAccounts();
-- 查看执行结果
SELECT * FROM account817;


# 2、创建一个新表branch_total，用于存储各个支行的存款总额（表中有branch_name和total_balance两个属性）。
# 然后在这个表上，创建一个触发器，实现当有用户存款变动（包括增加、删除和更新）时，branch_total表中的存款总额跟着自动更新。
-- 创建表branch_total
CREATE TABLE branch_total (
  branch_name VARCHAR(30) PRIMARY KEY,
  total_balance DECIMAL(10, 2)
);
-- 插入数据
INSERT INTO branch_total (branch_name, total_balance)
    SELECT branch_name, SUM(balance) FROM account817 GROUP BY branch_name;

-- 触发器
DELIMITER //
CREATE TRIGGER updateBranchTotal AFTER INSERT ON account817
    FOR EACH ROW
    BEGIN
        -- 插入新存款账户时，更新存款总额
        INSERT INTO branch_total (branch_name, total_balance)
        VALUES (NEW.branch_name, NEW.balance)
        ON DUPLICATE KEY UPDATE total_balance = total_balance + NEW.balance;
    END; //

CREATE TRIGGER updateBranchTotalDelete AFTER DELETE ON account817
    FOR EACH ROW
    BEGIN
        -- 删除存款账户时，更新存款总额
       UPDATE branch_total
       SET total_balance = total_balance - OLD.balance
       WHERE branch_name = OLD.branch_name;
    END; //

CREATE TRIGGER updateBranchTotalUpdate AFTER UPDATE ON account817
    FOR EACH ROW
    BEGIN
        -- 更新存款账户时，更新存款总额
        UPDATE branch_total
        SET total_balance = total_balance - OLD.balance + NEW.balance
        WHERE branch_name = NEW.branch_name;
    END //
DELIMITER ;

-- 测试触发器

-- 插入一个新存款账户
INSERT INTO account817 VALUES ('A-777', 'Redwood', 1000);
SELECT * FROM branch_total;

-- 更新存款账户的余额
UPDATE account817 SET balance = 1500 WHERE account_number = 'A-777';
SELECT * FROM branch_total;

-- 删除一个存款账户
DELETE FROM account817 WHERE account_number = 'A-777';
SELECT * FROM branch_total;