<?php
	//Incluimos o código de conexão ao BD
	include 'conn.php';
	//Variável responsável por guardar o valor enviado pelo ESP8266
	$temp = $_GET['irms'];
	//Captura a Data e Hora do SERVIDOR (onde está hospedada sua página):
	$hora = date('H:i:s');
	$data = date('Y-m-d');
	//Insere no Banco de Dados, usando Prepared Statements.
	$sql = "INSERT INTO eletrico (data, hora, corrente)  VALUES (?, ?, ?)";
	$stmt = $mysqli->prepare($sql);
	$stmt->bind_param('ssd', $data, $hora, $irms);
	$stmt->execute();
	echo 'Dados gravados com sucesso!';
?>
