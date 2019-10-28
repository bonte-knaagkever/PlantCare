<?php

	include('./connect-sql.php');
	$dbsensordata = "SELECT * FROM `sensordata` ORDER BY `sensordata`.`date` DESC LIMIT 20";
	$dbsensordataquery = mysqli_query($dbconn, $dbsensordata);

	echo "<table>";
	echo "<tr><th>Datum</th><th>Temperatuur</th><th>Licht</th><th>Luchtvochtigheid</th><th>Bodemvochtigheid</th></tr>";	

	while ($row = mysqli_fetch_array($dbsensordataquery, MYSQLI_ASSOC)) { 
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

	$dbsettings = "SELECT * FROM `settings`";
	$dbsettingsquery = mysqli_query($dbconn, $dbsettings);

	echo "<table>";
	echo "<tr><th>ID</th><th>Plant naam</th><th>Temperatuur</th><th>licht</th><th>Luchtvochtigheid</th><th>Bodemvochtigheid</th></tr>";	

	while ($row = mysqli_fetch_array($dbsettingsquery, MYSQLI_ASSOC)) { 
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
<form action="insert-sql.php" id="insertform" method="post">
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
    <input type="submit">
</form>

<!--dropdown with data to php https://stackoverflow.com/questions/12276735/how-to-insert-a-data-in-php-mysql-from-a-drop-down -->
<form action="insert-sql.php" name="removeForm" method="post">
	Plant verwijderen:
	<select name="removePlantname" required> <!--onchange="confirmremoval()"-->
		<option disabled selected value="">- selecteer plant -</option>
		<?php
			include('./connect-sql.php');
			$dbplantnames = "SELECT plantname FROM `settings` where plantname <> ''";
			$dbplantnamesquery = mysqli_query($dbconn, $dbplantnames);

			while ($plantname = mysqli_fetch_array($dbplantnamesquery, MYSQLI_ASSOC)) {
				echo "<option value=".$plantname['plantname'].">".$plantname['plantname']."</option>";
			}

			mysqli_close($dbconn);
		?>
	</select>
	<input type="submit" name="removeSubmit">
</form>

<script>
	function confirmremoval() {
		var e = document.getElementById("removePlantname");
		var removeplant = e.options[e.selectedIndex].text;
		if (removeplant != e.options[e.selectedIndex = 0].text) {
			if (confirm("Are you sure to remove '" + removeplant + "'?")) {
				window.location = "./insert-sql.php"
				//location.reload(); 
				//sendremoval(e.options[e.selectedIndex].text);
			}
		} 
	}
</script> 

<!-- formSubmit without leaving the page https://stackoverflow.com/questions/2954961/execute-php-without-leaving-page -->