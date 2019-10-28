<?php
	include('./connect-sql.php');
	//$dbcheckID = "SELECT * FROM `settings` WHERE plantname = '$plant_name'";
	$plant_name = mysqli_real_escape_string($dbconn, $_REQUEST['plant_name']);
	$temperature = mysqli_real_escape_string($dbconn, $_REQUEST['temperature']);
	$light = mysqli_real_escape_string($dbconn, $_REQUEST['light']);
	$humidity = mysqli_real_escape_string($dbconn, $_REQUEST['humidity']);
	$soil_moisture = mysqli_real_escape_string($dbconn, $_REQUEST['soil_moisture']);

	$dbcheckplantname = "SELECT * FROM `settings` WHERE plantname = '$plant_name'";
	$t = time();
	if (mysqli_num_rows(mysqli_query($dbconn, $dbcheckplantname))) {
      //plant exists
		$dbsend = "UPDATE settings SET lastmodified = '$t', temperature = '$temperature', light = '$light', humidity = '$humidity', soilmoisture = '$soil_moisture' WHERE plantname = '$plant_name'";
    } else {
      //plant doesnt exist
		$dbsend = "INSERT INTO settings (lastmodified, plantname, temperature, light, humidity, soilmoisture) VALUES ('$t', '$plant_name', '$temperature', '$light', '$humidity', '$soil_moisture')";
    }

	if(mysqli_query($dbconn, $dbsend)){
		echo "Records added successfully.";
	} else {
		echo "ERROR: Could not execute $dbsend. " . mysqli_error($dbconn);
	}
	mysqli_close($dbconn);
?>