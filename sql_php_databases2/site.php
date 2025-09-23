<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Insurance Covers</title>
</head>

<body>
<?php
	class insur_db extends SQLite3 {
		function __construct() {
			$this->open("insurance.db");
		}
	}
	$db = new insur_db();

?>
	<h2>Step 9</h2>
	<table border="solid">
	<tr>
		<th>Cover Number</th>
		<th>Description</th>
		<th>Yearly Cost</th>
		<th>Minimum Valid Months</th>
	</tr>
<?php

	$res = $db->query("SELECT * FROM insurance_covers");
	while ($row = $res->fetchArray(SQLITE3_ASSOC)) {
		echo "<tr>";
		echo "<td>" . $row['cover_no'] . "</td>";
		echo "<td>" . $row['desc'] . "</td>";
		echo "<td>" . $row['yearly_cost'] . "</td>";
		echo "<td>" . $row['min_valid_months'] . "</td>";
		echo "</tr>";
	}
?>
	</table>

	<hr>
	<h2>Step 10</h2>
	<p><form method="post">
	<select name="product">
		<option value=""></option>
<?php
	while ($row = $res->fetchArray(SQLITE3_ASSOC)) {
		echo "<option value=\"" . $row['cover_no'] . "\">" .
		    $row['desc'] . "</option>";
	}
?>
	</select>
	<input type="submit" name="submit"/>
	</form></p>

	<table border="solid">
	<tr>
		<th>Full Name</th>
		<th>Address</th>
		<th>Phone Number</th>
		<th>VAT Number</th>
		<th>Tax Office</th>
	</tr>
<?php
	if (isset($_POST['submit'], $_POST['product']) && $_POST['product'] != "") {
		$res = $db->query("
			SELECT DISTINCT full_name, address, tel, vat_no, tax_office
			FROM customers
			INNER JOIN contracts USING(vat_no)
			INNER JOIN insurance_covers USING(cover_no)
			WHERE cover_no = " . $_POST['product']);

		while ($row = $res->fetchArray(SQLITE3_ASSOC)) {
			echo "<tr>";
			echo "<td>" . $row['full_name'] . "</td>";
			echo "<td>" . $row['address'] . "</td>";
			echo "<td>" . $row['tel'] . "</td>";
			echo "<td>" . $row['vat_no'] . "</td>";
			echo "<td>" . $row['tax_office'] . "</td>";
			echo "</tr>";
		}
	}
?>
	</table>
<?php
	$db->close();
?>
</body>
</html>
