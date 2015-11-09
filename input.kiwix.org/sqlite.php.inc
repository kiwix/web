<?
function createOrOpenFeedbackDatabase() {
  try {
    $database = new SQLite3('input.kiwix.org.sqlite', 0666);
  } catch (Exception $e) {
    die($e->getMessage());
  }

  /* Try to create the table, do nothing if exist */
  $query = 'CREATE TABLE Feedbacks (Date TEXT, IP TEXT, Country TEXT, Message TEXT, Email TEXT, Language TEXT, Input TEXT, Version TEXT, Browser TEXT)';
  $database->exec($query);

  return $database;
}

function insertFeedbackToDatabase($date, $IP, $country, $message, $email, $language, $input, $version, $browser) {
  $database = createOrOpenFeedbackDatabase();

  $query =
    'INSERT INTO Feedbacks (Date, IP, Country, Message, Email, Language, Input, Version, Browser) ' .
    'VALUES ("'.$database->escapeString($date).'", "'.$database->escapeString($IP).'", "'.$database->escapeString($country).'", "'.$database->escapeString($message).'", "'.$database->escapeString($email).'", "'.$database->escapeString($language).'", "'.$database->escapeString($input).'", "'.$database->escapeString($version).'", "'.$database->escapeString($browser).'"); ';

    try {
      $database->exec($query);
    } catch (Exception $e) {
      die($e->getMessage());
    }
}

function exportFeedbackDatabaseToCSV() {
  $database = createOrOpenFeedbackDatabase();

  $query = "SELECT * FROM Feedbacks";
  $csv = "DATE\tIP\tCOUNTRY\tMESSAGE\tEMAIL\tLANGUAGE\tINPUT\tVERSION\tBROWSER\n";

  try {
    if ($result = $database->query($query)) {
      while ($row = $result->fetchArray()) {
        $message = str_replace("\t", " ", str_replace("\n", " ", str_replace("\r\n", " ", $row['Message'])));
        $csv .= "{$row['Date']}\t{$row['IP']}\t{$row['Country']}\t$message\t{$row['Email']}\t{$row['Language']}\t{$row['Input']}\t{$row['Version']}\t{$row['Browser']}\n";
      }
    }
  } catch (Exception $e) {
    die($e->getMessage());
  }

  return $csv;
}
?>