<?
include 'sqlite.php.inc';
$csv = exportFeedbackDatabaseToCSV();

header("Content-type: application/octet-stream");
header("Content-Disposition: attachment; filename=feedbacks.csv");
header("Pragma: no-cache");
header("Expires: 0");
header("Content-Transfer-Encoding: binary"); 
header("Cache-Control: no-cache, must-revalidate");
print "$csv\n";

?>