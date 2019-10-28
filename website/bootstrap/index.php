<!doctype html>
<html lang="nl">
<head>
	<!-- 
		Bootstrap docs: https://getbootstrap.com/docs/4.3/ 
		Bootstrap beginner guide: https://websitesetup.org/bootstrap-tutorial-for-beginners/
		Bootstrap sidebar guide: https://bootstrapious.com/p/bootstrap-sidebar
		-->

	<!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <!-- Bootstrap CSS -->
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
	
	<link rel="stylesheet" href="css/style.css">

	<title>Data from PlantCare db</title>
	<description> </description>
</head>
<!-- https://www.youtube.com/watch?v=HtTG5Kf_mTA 
	Copy the data to another external server: https://docs.microsoft.com/en-us/sql/relational-databases/replication/replication-tutorials?redirectedfrom=MSDN&view=sql-server-ver15	
	Color palette : https://coolors.co/151526-204c39-527755-87a330-a1c349
-->
<body>
	<script type="text/javascript" src="./scripts/script.js"></script>
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
	<!-- Optional bootstrap JS -->
	<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
	<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
</body>
</html>
