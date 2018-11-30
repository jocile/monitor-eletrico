<?php
//Conexão com o banco de dados
$mysqli = new mysqli('localhost', 'root', 'SENHA', 'teste');
if ($mysqli->connect_error) {
    die('Erro de conexão: (' . $mysqli->connect_errno . ')');
}
date_default_timezone_set('America/Sao_Paulo');
?>
