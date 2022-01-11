-- -- sqlite3
PRAGMA foreign_keys = ON;
.schema
.header on
.mode column

-- Part 1
CREATE TABLE insurance_covers (
	cover_no INT(2) NOT NULL,
	desc VARCHAR,
	yearly_cost INT(2) NOT NULL,
	min_valid_months INT(2) NOT NULL,
	PRIMARY KEY(cover_no)
);

CREATE TABLE customers (
	full_name VARCHAR,
	address VARCHAR,
	tel VARCHAR,
	vat_no VARCHAR,
	tax_office VARCHAR,
	PRIMARY KEY(vat_no)
);

CREATE TABLE contracts (
	cover_no INT(2) NOT NULL,
	vat_no VARCHAR,
	start_date DATE,
	expire_date DATE,
	FOREIGN KEY(vat_no) REFERENCES customers(vat_no),
	FOREIGN KEY(cover_no) REFERENCES insurance_covers(cover_no)
);

-- Part 2
INSERT INTO insurance_covers VALUES
	(1, "Health Insurance", 200, 12),
	(2, "Critical Illness Cover", 100, 12),
	(3, "Home Insurance", 150, 24),
	(4, "Car Insurance", 120, 12);

INSERT INTO customers VALUES
	("Foo Bar", "Nice Street 4", "2101234567", "123456789", "Peristeri"),
	("Bob Baz", "Bad Avenue", "2113216549", "321654987", "Acharnes");

INSERT INTO contracts VALUES
	(1, "123456789", "2021-03-02", "2022-03-02"),
	(2, "123456789", "2020-12-01", "2021-12-01"),
	(3, "321654987", "2020-05-10", "2022-05-10"),
	(3, "123456789", "2020-07-11", "2022-07-11");

-- Part 3: diagram.png

-- Part 4
CREATE VIEW info AS
	SELECT full_name "Customer name",
	desc AS "Coverage",
	vat_no as "VAT number",
	start_date AS "Start date",
	expire_date AS "Expiration date"
	FROM customers
	INNER JOIN contracts USING (vat_no),
	insurance_covers USING(cover_no)
	ORDER BY full_name;

CREATE VIEW updatable_info AS
	SELECT full_name, vat_no, address, tel, tax_office
	FROM customers
	ORDER BY full_name;

SELECT * from info;

-- Part 5
SELECT insurance_covers.desc AS "Contract",
	count(contracts.cover_no) AS "Number of contracts"
	FROM contracts
	INNER JOIN insurance_covers USING(cover_no)
	GROUP BY contracts.cover_no;

-- Make this a view so we can make things easier later.
CREATE VIEW total_cost_info AS
	SELECT full_name AS "Customer",
	sum(yearly_cost) AS "Total contract cost"
	FROM contracts
	INNER JOIN insurance_covers USING (cover_no)
	INNER JOIN customers USING (vat_no)
	GROUP BY vat_no
	ORDER BY sum(yearly_cost) desc;

SELECT * from total_cost_info;

-- Part 6
CREATE TRIGGER cost_of_contracts AFTER INSERT ON insurance_covers
BEGIN
	UPDATE customers SET total = (SELECT sum(yearly_cost) FROM insurance_covers) + new.yearly_cost
	WHERE customers.vat_no = new.vat_no;
END;

INSERT INTO contracts VALUES (4, "123456789", "2022-05-10", "2023-05-10");
SELECT * from total_cost_info;

-- Part 7 (SQLite doesn't have CREATE FUNCTION so this part is commented out)
-- DELIMETER //
-- CREATE FUNCTION contract_duration(start DATE, end DATE)
-- RETURNS INT
-- DETERMINISTIC
-- BEGIN
-- 	RETURN datediff(end, start);
-- END //
-- DELIMETER ;
-- 
-- Test function.
-- SELECT contract_duration(
-- 	SELECT start_date FROM contracts WHERE vat_no = "123456789",
-- 	SELECT expire_date FROM contracts WHERE vat_no = "123456789"
-- );


-- Part 8 (SQLite doesn't have procedures either)
-- DELIMETER //
-- CREATE PROCEDURE active_contracts(vat_no_arg VARCHAR, date_arg DATE)
-- BEGIN
-- 	DECLARE start_row INT DEFAULT 0;
-- 	DECLARE end_row INT DEFAULT 0;
-- 	DECLARE p_vat_no VARCHAR,
-- 	DECLARE p_cover_no INT,
-- 	DECLARE p_start_date DATE,
-- 	DECLARE p_end_date DATE,
-- 	DECLARE contr_count INT DEFAULT 0;
-- 	DECLARE COST INT;
-- 	DECLARE pending_cost INT DEFAULT 0;
-- 	DECLARE contr_ptr CURSOR FOR SELECT * FROM contracts;
-- 	
-- 	SET start_row := 0;
-- 	SELECT count(*) FROM contracts INTO end_row;
-- 	OPEN contr_ptr;
-- 	WHILE (start_row < end_row) DO
-- 		FETCH contr_ptr INTO p_vat_no, p_cover_no, p_start_date, p_end_date;
-- 		SELECT yearly_cost FROM insurance_covers WHERE cover_no = p_cover_no INTO cost;
-- 
-- 		IF (p_vat_no = vat_no_arg AND date_arg >= p_start_date AND date_arg <= p_end_date) THEN
-- 			SET contr_count := contr_count + 1;
-- 			SET pending_cost := pending_cost + cost;
-- 		END IF;
-- 		SET start_row := start_row + 1;
-- 	END WHILE;
-- 	SELECT contr_count AS "Active contracts", pending_cost/12 AS "Contract cost per month";
-- END //
-- DELIMETER ;
-- 
-- Test procedure.
-- CALL active_contracts("123456789", "2021-10-10");
