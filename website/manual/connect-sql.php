<?php

	$dbconn = mysqli_connect("localhost", "root", "", "plantcare");
	if ($dbconn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
?>