<?php

	include('./connect-sql.php');
	$dbgetsensordata = "SELECT * FROM `sensordata` ORDER BY `sensordata`.`date` DESC LIMIT 20";
	$dbsensordata = mysqli_query($dbconn, $dbgetsensordata);

	echo "<table>";
	echo "<tr><th>Datum</th><th>Temperatuur</th><th>Licht</th><th>Luchtvochtigheid</th><th>Bodemvochtigheid</th></tr>";	

	//for ($k = 0; $k < $rows; $k++){ 
	//    $row = mysqli_fetch_assoc($dbdata);
	//    echo "<tr><td>";
	//    echo $row['date'];
	//    echo "</td><td>";
	//    echo $row['temperature'];
	//    echo "</td><td>";
	//    echo $row['light'];
	//    echo "</td><td>";
	//    echo $row['humidity'];
	//    echo "</td><td>";
	//    echo $row['soilmoisture'];
	//    echo "</td></tr>";
	//}

	while ($row = mysqli_fetch_array($dbsensordata, MYSQLI_ASSOC)) { 
		echo "<tr><td>";
		echo $row['date'];
		echo "</td><td>";
		echo $row['temperature'];
		echo "</td><td>";
		echo $row['light'];
		echo "</td><td>";
		echo $row['humidity'];
		echo "</td><td>";
		echo $row['soilmoisture'];
		echo "</td></tr>";
	}
	echo "</table>";

	$dbgetsettings = "SELECT * FROM `settings`";
	$dbsettings = mysqli_query($dbconn, $dbgetsettings);

	echo "<table>";
	echo "<tr><th>ID</th><th>Plant naam</th><th>Temperatuur</th><th>licht</th><th>Luchtvochtigheid</th><th>Bodemvochtigheid</th></tr>";	

	//for ($k = 0; $k < $rows; $k++){ 
	//    $row = mysqli_fetch_assoc($dbdata);
	//    echo "<tr><td>";
	//    echo $row['date'];
	//    echo "</td><td>";
	//    echo $row['temperature'];
	//    echo "</td><td>";
	//    echo $row['light'];
	//    echo "</td><td>";
	//    echo $row['humidity'];
	//    echo "</td><td>";
	//    echo $row['soilmoisture'];
	//    echo "</td></tr>";
	//}

	while ($row = mysqli_fetch_array($dbsettings, MYSQLI_ASSOC)) { 
		echo "<tr><td>";
		echo $row['ID'];
		echo "</td><td>";
		echo $row['plantname'];
		echo "</td><td>";
		echo $row['temperature'];
		echo "</td><td>";
		echo $row['light'];
		echo "</td><td>";
		echo $row['humidity'];
		echo "</td><td>";
		echo $row['soilmoisture'];
		echo "</td></tr>";
	}
	echo "</table>";

	mysqli_close($dbconn);

?>

<!-- https://www.tutorialrepublic.com/php-tutorial/php-mysql-insert-query.php-->
<form action="insert-sql.php" method="post">
	<p><strong>Een plant toevoegen:</strong></p>
    <p>
        <label for="plantname">Plant naam:</label>
        <input type="text" name="plant_name" id="plantname" required>
    </p>
    <p>
        <label for="temperature">Gewenste temperatuur (graden C):</label>
        <input type="text" name="temperature" id="temperature" required>
    </p>
    <p>
        <label for="light">Gewenste hoeveelheid licht (0-1023):</label>
        <input type="text" name="light" id="light" required>
    </p>
	    <p>
        <label for="humidity">Gewenste luchtvochtigheid (%):</label>
        <input type="text" name="humidity" id="humidity" required>
    </p>
	    <p>
        <label for="soilmoisture">Gewenste bodemvochtigheid (pF):</label>
        <input type="text" name="soil_moisture" id="soilmoisture" required>
    </p>
    <input type="submit" value="Submit">
</form>

<!--formSubmit without leaving the page https://stackoverflow.com/questions/2954961/execute-php-without-leaving-page-->