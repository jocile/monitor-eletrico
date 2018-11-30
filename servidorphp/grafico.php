<!DOCTYPE html>
<html lang="en">
<head>
  <title>Gráfico de Corrente - ESP8266 + PHP + MYSQL</title>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <meta http-equiv='refresh' content='60' URL=''>    
  <!-- CSS -->
  <link rel="stylesheet" type="text/css" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <!-- JS -->
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
  <!-- Google Chart -->  
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
</head>
<body>
<?php
//Inclui a conexão com o BD
include 'api/conn.php';
//Faz o SELECT da tabela, usando Prepared Statements.
$sql = "SELECT data, hora, corrente FROM eletrico";
$stmt = $mysqli->prepare($sql);
$stmt->execute();
$stmt->bind_result($data, $hora, $temp);
$stmt->store_result();
//Cria o array primário
$dados = array();
//Laço dos dados
 while ($ln = $stmt->fetch()){
//Cria o array secundário, onde estarão os dados.
    $temp_hora = array();
$temp_hora[] = ((string) $hora);
    $temp_hora[] = ((float) $temp);
//Recebe no array principal, os dados.
    $dados[] = ($temp_hora);
}
//Trasforma os dados em JSON
  $jsonTable = json_encode($dados);
//echo $jsonTable;
?>
<h3 align="center">ESP8266 + MYSQL + PHP + GOOGLE CHART - V2</h3>
<!-- Div do Gráfico -->
<div class="container" style="height: 300px; width: 100%" id="chart_div"></div>
<br><br>
</body>
<script>
//Script do Google que define o TIPO do gráfico
google.charts.load('current', {packages: ['corechart', 'line']});
google.charts.setOnLoadCallback(drawBackgroundColor);
//Define o tipo de coluna e o nome
function drawBackgroundColor() {
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Horario');
      data.addColumn('number', 'Corrente (I)');
    
      //Captura os dados em JSON e monta o gráfico, de acordo com os dados.
      data.addRows( <?php echo $jsonTable ?>);
//Opções do gráfico:  
      var options = {
        hAxis: {
          title: 'Hora'
        },
        vAxis: {
          title: 'Corrente'
        },
        backgroundColor: '#f1f8e9'
      };
//Criação do Gráfico 
      var chart = new google.visualization.LineChart(document.getElementById('chart_div'));
      chart.draw(data, options);
    }
</script>
</html>
