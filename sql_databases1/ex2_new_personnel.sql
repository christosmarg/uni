CREATE TABLE DEPT (
	DEPTNO INT(2) NOT NULL,
	DNAME VARCHAR,
	LOC VARCHAR,
	PRIMARY KEY(DEPTNO)
);

CREATE TABLE EMP (
	EMPNO INT(2) NOT NULL,
	ENAME VARCHAR,
	JOB VARCHAR,
	HIREDATE DATE,
	MGR INT(2),
	SAL FLOAT(7,2),
	COMM FLOAT(7,2),
	DEPTNO INT(2) NOT NULL,
	PRIMARY KEY(EMPNO),
	FOREIGN KEY(DEPTNO) REFERENCES DEPT(DEPTNO)
);

CREATE TABLE PROJ (
	PROJ_CODE INT(3) NOT NULL,
	DESCRIPTION VARCHAR,
	PRIMARY KEY(PROJ_CODE)
);

CREATE TABLE ASSIGN (
	EMPNO INT(2) NOT NULL,
	PROJ_CODE INT(3),
	A_TIME INT(3),
	PRIMARY KEY(EMPNO, PROJ_CODE),
	FOREIGN KEY(EMPNO) REFERENCES EMP(EMPNO),
	FOREIGN KEY(PROJ_CODE) REFERENCES PROJ(PROJ_CODE)
);

INSERT INTO DEPT VALUES
	(10, 'ACCOUNTING', 'ATHENS'),
	(20, 'SALES', 'LONDON'),
	(30, 'RESEARCH', 'ATHENS'),
	(40, 'PAYROLL', 'LONDON');

INSERT INTO EMP VALUES
	(10, 'CODD', 'ANALYST', '1989-01-01', 15, 3000, NULL, 10),
	(15, 'ELMASRI', 'ANALYST', '1995-05-02', 15, 1200, 150, 10),
	(20, 'NAVATHE', 'SALESMAN', '1977-07-07', 20, 2000, NULL, 20),
	(30, 'DATE', 'PROGRAMMER', '2004-05-04', 15, 1800, 200, 10);

INSERT INTO PROJ VALUES
	(100, 'PAYROLL'),
	(200, 'PERSONELL'),
	(300, 'SALES');

INSERT INTO ASSIGN VALUES
	(10, 100, 40),
	(10, 200, 60),
	(15, 100, 100),
	(20, 200, 100),
	(30, 100, 100);

-- Using SQLite3 syntax
.header on
.mode column

-- Question 1
SELECT 
	ENAME,
	SAL AS "ΜΙΣΘΟΣ", 
	COMM AS "ΠΡΟΜΗΘΕΙΑ",
	IFNULL(ROUND(COMM * 100 / SAL, 1) || "%", "0.00%") AS "ΠΟΣΟΣΤΟ"
	FROM EMP;

-- Question 2
SELECT 
	ENAME AS "ΕΠΩΝΥΜΟ", 
	SAL AS "ΜΗΝΙΑΙΕΣ ΑΠΟΔΟΧΕΣ",
	strftime("%Y", "now") - strftime("%Y", HIREDATE) AS "ПРОΥΠΗΡΕΣΙΑ"
	FROM EMP;

-- Question 3
SELECT 
	ENAME AS "ΕΠΩΝΥΜΟ",
	JOB AS "ΘΕΣΗ",
	HIREDATE AS "ΠΡΟΣΛΗΨΗ"
	FROM EMP
	WHERE strftime("%d", HIREDATE)  <= "05";

-- Question 4
SELECT 
	ENAME AS "ΕΠΩΝΥΜΟ"
	FROM EMP
	INNER JOIN DEPT ON
		DEPT.DEPTNO = EMP.DEPTNO AND
		DEPT.DNAME = "ACCOUNTING";

-- Question 5
SELECT 
	ENAME AS "ΕΠΩΝΥΜΟ",
	MAX(
		(strftime("%Y", "now") - strftime("%Y", HIREDATE)) *
		 12 * SAL
	) AS "ΣΥΝΟΛΙΚΟΣ ΜΙΣΘΟΣ"
	FROM EMP;

 
-- Output

-- Question 1:
-- ENAME    ΜΙΣΘΟΣ  ΠΡΟΜΗΘΕΙΑ  ΠΟΣΟΣΤΟ
-- -------  ------  ---------  -------
-- CODD     3000.0             0.00%
-- ELMASRI  1200.0  150.0      12.5%
-- NAVATHE  2000.0             0.00%
-- DATE     1800.0  200.0      11.1%

-- Question 2:
-- ΕΠΩΝΥΜΟ  ΜΗΝΙΑΙΕΣ ΑΠΟΔΟΧΕΣ  ПРОΥΠΗΡΕΣΙΑ
-- -------  -----------------  -----------
-- CODD     3000.0             32
-- ELMASRI  1200.0             26
-- NAVATHE  2000.0             44
-- DATE     1800.0             17

-- Question 3:
-- ΕΠΩΝΥΜΟ  ΘΕΣΗ        ΠΡΟΣΛΗΨΗ
-- -------  ----------  ----------
-- CODD     ANALYST     1989-01-01
-- ELMASRI  ANALYST     1995-05-02
-- DATE     PROGRAMMER  2004-05-04

-- Question 4:
-- ΕΠΩΝΥΜΟ
-- -------
-- CODD
-- ELMASRI
-- DATE

-- Question 5:
-- ΕΠΩΝΥΜΟ  ΣΥΝΟΛΙΚΟΣ ΜΙΣΘΟΣ
-- -------  ----------------
-- CODD     1152000.0
