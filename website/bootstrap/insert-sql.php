<?php
if (isset($_POST['plant_name'])) {
    echo insert();
    return;
}

if (isset($_POST['removeSubmit'])) {
    echo remove();
    return;
}

function insert() {
	include('./connect-sql.php');

	$plant_name = mysqli_real_escape_string($dbconn, $_REQUEST['plant_name']);
	$temperature = mysqli_real_escape_string($dbconn, $_REQUEST['temperature']);
	$light = mysqli_real_escape_string($dbconn, $_REQUEST['light']);
	$humidity = mysqli_real_escape_string($dbconn, $_REQUEST['humidity']);
	$soil_moisture = mysqli_real_escape_string($dbconn, $_REQUEST['soil_moisture']);

	$dbcheckplantname = "SELECT * FROM `settings` WHERE plantname = '$plant_name' ";

	$dbcheckIDexist = "SELECT * FROM `settings` WHERE lastmodified = '0'";

	$dbcheckrownumbers = "SELECT * FROM `settings`";
	$dbcheckrownumbersquery = mysqli_num_rows(mysqli_query($dbconn, $dbcheckrownumbers));

	$t = time();

	if (mysqli_num_rows(mysqli_query($dbconn, $dbcheckplantname))) {
		//plantname exists
	    $dbsend = "UPDATE settings SET lastmodified = '$t', temperature = '$temperature', light = '$light', humidity = '$humidity', soilmoisture = '$soil_moisture' WHERE plantname = '$plant_name'";
		echo "plantname exists <br>";
	} else {
		//plantname doesnt exist
		echo "plantname doesnt exist <br>";
		if (mysqli_num_rows(mysqli_query($dbconn, $dbcheckIDexist))) {
			//ID exists
			$dbsend = "UPDATE settings SET plantname = '$plant_name', lastmodified = '$t', temperature = '$temperature', light = '$light', humidity = '$humidity', soilmoisture = '$soil_moisture' WHERE lastmodified = '0' LIMIT 1";
			echo "ID exists <br>";
		}
		else {
			$dbsend = "INSERT INTO settings (ID, lastmodified, plantname, temperature, light, humidity, soilmoisture) VALUES ('$dbcheckrownumbersquery', '$t', '$plant_name', '$temperature', '$light', '$humidity', '$soil_moisture')";
			echo "ID doesnt exist <br>";
		}
	}

	if(mysqli_query($dbconn, $dbsend)){
	    echo "Records added/edited successfully.";
	} else {
	    echo "ERROR: Could not execute $dbsend. " . mysqli_error($dbconn);
	}
	mysqli_close($dbconn);
}

function remove() {
	include('./connect-sql.php');

	$plant_name = mysqli_real_escape_string($dbconn, $_REQUEST['removePlantname']);

	$dbcheckplantname = "SELECT * FROM `settings`";
	mysqli_query($dbconn, $dbcheckplantname);

	$dbclear = "UPDATE settings SET plantname = '', lastmodified = 'NULL', temperature = '', light = '', humidity = '', soilmoisture = '' WHERE plantname = '$plant_name' ";

	if(mysqli_query($dbconn, $dbclear)) {
        echo "Records cleared successfully.";
    } else {
        echo "ERROR: Could not execute $dbclear. " . mysqli_error($dbconn);
    }
    mysqli_close($dbconn);	
}
	
?>