<html>
<head>
	<link rel="stylesheet" href="css/style.css">
	<!--<link rel="stylesheet" href="https://unpkg.com/purecss@1.0.1/build/pure-min.css" integrity="sha384-oAOxQR6DkCoMliIh8yFnu25d7Eq/PHS21PClpwjOTeU2jRSq11vu66rf90/cZr47" crossorigin="anonymous">-->
	<title>Data from PlantCare db</title>
	<description></description>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
</head>
<script type="text/javascript" src="./scripts/script.js"></script>
<!-- https://www.youtube.com/watch?v=HtTG5Kf_mTA 
	Copy the data to another external server: https://docs.microsoft.com/en-us/sql/relational-databases/replication/replication-tutorials?redirectedfrom=MSDN&view=sql-server-ver15	
	Color palette : https://coolors.co/151526-204c39-527755-87a330-a1c349
-->
<body>
	<div class="wrapper">
		<header class="main-header">
			<?php
				include('./header.php');
			?>
		</header>
		
		<aside class="main-sidebar">
			<section>
				<?php
					include('./sidebar.php');
				?>
			</section>
		</aside>
		
		<div class="main-content">
			<section>
				<?php
					include('./content.php');
				?>
			</section>
		</div>
	
		<footer class="main-footer">
			<?php
				include('./footer.php');
			?>
		</footer>

		<!-- http://form.guide/php-form/php-form-select.html	https://www.geeksforgeeks.org/php-mysqli_num_rows-function/ -->
		<!--<p>How many rows of data to display?
		<select type="submit" name="selectorRows" id = "selectorRows">
			<option value="25">25</option>
			<option value="50">50</option>
			<option value="100">100</option>
			<option value="250">250</option>
			<option value="500">500</option>
		</select>
		</p>-->

	</div>
</body>
</html>
