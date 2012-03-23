1;2802;0c<?
function createOrOpenFeedbackDatabase() {
  try {
    $database = new SQLiteDatabase('input.kiwix.org.sqlite', 0666, $error);
  } catch(Exception $e) {
    die($error);
  }

  /* Try to create the table, do nothing if exist */
  $query = 'CREATE TABLE Feedbacks (Date TEXT, IP TEXT, Country TEXT, Message TEXT, Language TEXT, Input TEXT, Version TEXT, Browser TEXT)';
  $database->queryExec($query, $error);

  return $database;
}

function insertFeedbackToDatabase($date, $IP, $country, $message, $language, $input, $version, $browser) {
  $database = createOrOpenFeedbackDatabase();

  $query =
    'INSERT INTO Feedbacks (Date, IP, Country, Message, Language, Input, Version, Browser) ' .
    'VALUES ("'.sqlite_escape_string($date).'", "'.sqlite_escape_string($IP).'", "'.sqlite_escape_string($country).'", "'.sqlite_escape_string($message).'", "'.sqlite_escape_string($language).'", "'.sqlite_escape_string($input).'", "'.sqlite_escape_string($version).'", "'.sqlite_escape_string($browser).'"); ';

  if(!$database->queryExec($query, $error)) {
    die($error);
  }
}

function exportFeedbackDatabaseToCSV() {
  $database = createOrOpenFeedbackDatabase();

  $query = "SELECT * FROM Feedbacks";
  $csv = "DATE\tIP\tCOUNTRY\tMESSAGE\tLANGUAGE\tINPUT\tVERSION\tBROWSER\n";

  if ($result = $database->query($query, SQLITE_BOTH, $error)) {
    while ($row = $result->fetch()) {
      $message = str_replace("\t", " ", str_replace("\n", " ", str_replace("\r\n", " ", $row['Message'])));
      $csv .= "{$row['Date']}\t{$row['IP']}\t{$row['Country']}\t$message\t{$row['Language']}\t{$row['Input']}\t{$row['Version']}\t{$row['Browser']}\n";
    }
  } else {
    die($error);
  }

  return $csv;
}
?>