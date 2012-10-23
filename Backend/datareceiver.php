<?php
include("Class.MySQLDatabase.php");

$db = new MySQL();

if(!$db->Connect()) { die("MySQL died a horrible death"); }

$outTemp = (isset($_POST['outtemp'])) ? $_POST['outtemp'] : "null";
$inTemp = (isset($_POST['intemp'])) ? $_POST['intemp'] : "null";
$outHum = (isset($_POST['outhum'])) ? $_POST['outhum'] : "null";
$inHum = (isset($_POST['inhum'])) ? $_POST['inhum'] : "null";
$barPress = (isset($_POST['barpress'])) ? $_POST['barpress'] : "null";
$windDir = (isset($_POST['winddir'])) ? $_POST['winddir'] : "null";
$windSpeed = (isset($_POST['windspeed'])) ? $_POST['windspeed'] : "null";
$rainAmount = (isset($_POST['rainamount'])) ? $_POST['rainamount'] : "null";
$soilMoisture = (isset($_POST['soilmois'])) ? $_POST['soilmois'] : "null";

$stID = 1;

$sql = "INSERT INTO Station_Data VALUES (null, null, $outTemp, $inTemp, $outHum, $inHum, $barPress, $windDir, $windSpeed, $rainAmount, $soilMoisture, $stID);";

$db->ExecuteSQL($sql);

echo $db->getLastError();
?>