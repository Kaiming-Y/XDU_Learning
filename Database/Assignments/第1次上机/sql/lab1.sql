CREATE DATABASE BANK817;
SHOW DATABASES;
USE BANK817;
SHOW TABLES;

CREATE TABLE BRANCH817(
    branch_name varchar(30) NOT NULL,
    branch_city varchar(30),
    assets numeric(12, 2),
    PRIMARY KEY (branch_name),
    CONSTRAINT chk_assets CHECK ( assets>=0 )
);
CREATE TABLE CUSTOMER817(
    customer_name varchar(30) NOT NULL,
    customer_street varchar(30),
    customer_city varchar(30),
    PRIMARY KEY (customer_name)
);
CREATE TABLE ACCOUNT817(
    account_number varchar(10),
    branch_name varchar(30) NOT NULL,
    balance numeric(12, 2),
    PRIMARY KEY (account_number),
    FOREIGN KEY (branch_name) REFERENCES BRANCH817(branch_name),
    CONSTRAINT chk_balance CHECK ( balance>=0 )
);
CREATE TABLE LOAN817(
    loan_number varchar(10),
    branch_name varchar(30) NOT NULL,
    amount numeric(12, 2),
    PRIMARY KEY (loan_number),
    FOREIGN KEY (branch_name) REFERENCES BRANCH817(branch_name),
    CONSTRAINT chk_amount CHECK ( amount>=0 )
);
CREATE TABLE DEPOSITOR817(
    customer_name varchar(30),
    account_number varchar(10),
    FOREIGN KEY (customer_name) REFERENCES CUSTOMER817(customer_name),
    FOREIGN KEY (account_number) REFERENCES ACCOUNT817(account_number)
);
CREATE TABLE BORROWER817(
    customer_name varchar(30) NOT NULL,
    loan_number varchar(10),
    FOREIGN KEY (customer_name) REFERENCES CUSTOMER817(customer_name),
    FOREIGN KEY (loan_number) REFERENCES LOAN817(loan_number)
);

SHOW TABLES;
DESC CUSTOMER817;
DESC ACCOUNT817;
DESC BORROWER817;
DESC LOAN817;
DESC BRANCH817;
DESC DEPOSITOR817;

# BRANCH817必须在ACCOUNT817之前创建，因为account表中有有一个外键在branch表中
INSERT INTO BRANCH817 VALUES ('Brighton','Brooklyn',7100000), ('Downtown','Brooklyn',9000000),
                             ('Mianus','Horseneck',400000), ('North Town','Rye',3700000),
                             ('Perryridge','Horseneck',1700000), ('Pownal','Bennington',300000),
                             ('Redwood','Palo Alto',2100000), ('Round Hill','Horseneck',8000000);
INSERT INTO CUSTOMER817 VALUES ('Adams','Spring','Pittsfield'), ('Brooks','Senator','Brooklyn'),
                               ('Curry','North','Rye'), ('Glenn','Sand Hill','Woodside'),
                               ('Green','Walnut','Stamford'), ('Hayes','Main','Harrison'),
                               ('Johnson','Alma','Palo Alto'), ('Jones','Main','Harrison'),
                               ('Lindsay','Park','Pittsfield'), ('Smith','North','Rye'),
                               ('Turner','Putnam','Stamford'), ('Williams','Nassau','Princeton');
INSERT INTO ACCOUNT817 VALUES ('A-101','Downtown',500), ('A-102','Perryridge',400), ('A-201','Brighton',900),
                              ('A-215','Mianus',700), ('A-217','Brighton',750), ('A-222','Redwood',700),
                              ('A-305','Round Hill', 350);
INSERT INTO LOAN817 VALUES ('L-11','Round Hill',900), ('L-14','Downtown',1500), ('L-15','Perryridge',1500),
                           ('L-16','Perryridge',1300), ('L-17','Downtown',1000), ('L-23','Redwood',2000),
                           ('L-93', 'Mianus', 500);
INSERT INTO DEPOSITOR817 VALUES ('Hayes','A-102'), ('Johnson','A-101'), ('Johnson','A-201'), ('Jones','A-217'),
                                ('Lindsay','A-222'), ('Smith','A-215'), ('Turner','A-305');
INSERT INTO BORROWER817 VALUES ('Adams','L-16'), ('Curry','L-93'), ('Hayes','L-15'),('Jones','L-17'),
                               ('Smith','L-11'), ('Smith','L-23'), ('Williams','L-17');
# ('Jackson','L-14')这条数据无法插入，因为CUSTOMER817这张表中没有customer_name='Jackson'

SELECT * FROM BRANCH817;
SELECT * FROM CUSTOMER817;
SELECT * FROM ACCOUNT817;
SELECT * FROM ACCOUNT817 WHERE account_number LIKE 'A-___';
SELECT * FROM LOAN817;
SELECT * FROM DEPOSITOR817;
SELECT * FROM BORROWER817;


CREATE DATABASE employee_lab1;
SHOW DATABASES;
USE employee_lab1;

CREATE TABLE employee (
    employee_name varchar(30) NOT NULL,
    street varchar(30),
    city varchar(10),
    PRIMARY KEY (employee_name)
);
CREATE TABLE company (
    company_name varchar(30) NOT NULL,
    city varchar(10),
    PRIMARY KEY (company_name)
);
CREATE TABLE works (
    employee_name varchar(30) NOT NULL,
    company_name varchar(30) NOT NULL,
    salary numeric(12, 2),
    PRIMARY KEY (employee_name),
    FOREIGN KEY (company_name) REFERENCES company(company_name),
    CONSTRAINT chk_salary CHECK ( salary>=0 )
);
CREATE TABLE managers (
    employee_name varchar(30) NOT NULL,
    manager_name varchar(30),
    PRIMARY KEY (employee_name)
);
SHOW TABLES;

INSERT INTO employee VALUES ('Adams','Spring','Pittsfield'), ('Brooks','Senator','Brooklyn'),
                            ('Curry','North','Brooklyn'), ('Jones','Main','Harrison'),
                            ('Green','Walnut','Stamford'), ('Hayes','Main','Harrison'),
                            ('Lindsay','Park','Pittsfield'), ('Turner','Putnam','Stamford');
INSERT INTO company VALUES ('First Bank Corporation','Brooklyn'), ('Small Bank Corporation','Pittsfield'),
                           ('Second Bank Corporation','Harrison'), ('Great Bank Corporation','Pittsfield'),
                           ('Big Bank Corporation','Pittsfield');
INSERT INTO works VALUES ('Adams','First Bank Corporation',120000), ('Brooks','Small Bank Corporation',20000),
                         ('Curry','Small Bank Corporation',8000), ('Green','First Bank Corporation',50000),
                         ('Jones','Second Bank Corporation',110000), ('Hayes','First Bank Corporation',9000),
                         ('Lindsay','Small Bank Corporation',100000), ('Turner','First Bank Corporation',60000);
INSERT INTO managers VALUES ('Adams','James'), ('Brooks','Curry'), ('Curry','Jones'), ('Green','James'),
                            ('Jones','Hayes'), ('Lindsay','Petter'), ('Hayes','Petter'), ('Turner','James');


# 3.9
# a
SELECT e.employee_name,e.city FROM employee e JOIN works w ON e.employee_name = w.employee_name WHERE w.company_name='First Bank Corporation';
# b
SELECT e.employee_name,e.street,e.city FROM employee e WHERE e.employee_name IN (
    SELECT w.employee_name FROM works w WHERE w.company_name = 'First Bank Corporation' AND w.salary > 10000
    );
# c
SELECT * FROM employee e WHERE e.employee_name IN (
    SELECT w.employee_name FROM works AS w WHERE w.company_name != 'First Bank Corporation'
    );
# d
SELECT e.employee_name,w.salary FROM employee e JOIN works w ON e.employee_name = w.employee_name WHERE w.salary>(
    SELECT MAX(salary) FROM works WHERE company_name='Small Bank Corporation'
);
# e
SELECT * FROM company WHERE city IN (
    SELECT city FROM company WHERE company_name = 'Small Bank Corporation'
);
# f
SELECT company_name,COUNT(employee_name) AS count_employee FROM works GROUP BY company_name ORDER BY count_employee DESC LIMIT 1;
# g
SELECT company_name,AVG(salary) AS avg_salary FROM works GROUP BY company_name HAVING avg_salary > (
    SELECT AVG(salary) FROM works WHERE company_name = 'First Bank Corporation'
);


# 3.10
# a
UPDATE employee SET city = 'Newtown' WHERE employee_name = 'Jones';
SELECT * FROM employee;
# b
UPDATE works SET salary = CASE
    WHEN salary <= 100000 AND employee_name IN (SELECT manager_name FROM managers) THEN salary * 1.10
    WHEN salary > 100000 AND employee_name IN (SELECT manager_name FROM managers) THEN salary * 1.03
    ELSE salary END
WHERE company_name = 'First Bank Corporation';
SELECT * FROM works;