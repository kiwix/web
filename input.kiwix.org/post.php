<?
    mb_internal_encoding("UTF-8");
    include 'sqlite.php.inc';

    $headers = apache_request_headers();
    if (array_key_exists('X-Forwarded-For', $headers)){
      $ip = $headers['X-Forwarded-For'];
    } else {
      $ip = $_SERVER["REMOTE_ADDR"];
    }

    $country = geoip_country_name_by_name($ip) == "" ? "unknown country" : geoip_country_name_by_name($ip);
    $input = $_POST["input"];
    $message = $_POST["message"];
    $email = $_POST["email"];
    $version = $_POST["version"];
    $browser = $_SERVER['HTTP_USER_AGENT'];
    $language = $_SERVER["HTTP_ACCEPT_LANGUAGE"];

    $to = "feedback@kiwix.org";
    $from = "Kiwix Feedback System <feedback@www.kiwix.org>";
    $subject = "Kiwix Feedback from $country ($ip)";
    $headers = "From: $from\r\n";
    $headers .= "Content-Type: text/plain; charset=utf-8\r\n";
    $headers .= "Content-Transfer-Encoding: 8bit\r\n";

    $content  = "MESSAGE\n==================================================\n";
    $content .= "$message\n\n";
    $content .= "\nADDITIONAL INFORMATIONS\n==================================================\n";
    $content .= "Email:         $email\n";
    $content .= "Input:         $input\n";
    $content .= "Version:       $version\n";	
    $content .= "IP:            $ip\n";	
    $content .= "Location:      $country\n";
    $content .= "Browser - OS:  $browser\n";
    $content .= "Browser lang.: $language\n";

    if (strlen($message)>4 && 
        strpos($message, "link=http") === false && 
	strpos($message, "href=") === false && 
	strpos($message, "[link]") === false) {
      mail($to, $subject, $content, $headers);
      insertFeedbackToDatabase(date("Y-m-d H:i:s"), $ip, $country, $message, $email, $language, $input, $version, $browser);
    }

    header("Location: /thanks.html");
    exit();
?> 