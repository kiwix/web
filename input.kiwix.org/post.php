<?
    $ip = $_SERVER['REMOTE_ADDR'];
    $country = geoip_country_name_by_name($ip) == "" ? "unknown country" : geoip_country_name_by_name($ip);
    $input = $_POST["input"];
    $message = $_POST["message"];
    $version = $_POST["version"];
    $browser = $_SERVER['HTTP_USER_AGENT'];
    $language = $_SERVER["HTTP_ACCEPT_LANGUAGE"];

    $to = "feedback@kiwix.org";
    $from = "Kiwix Feedback System <feedback@www.kiwix.org>";
    $subject = "Kiwix Feedback from $country ($ip)";
    $headers = "From: $from\r\n";
    $headers .= "Content-type: text/plain\r\n";

    $content  = "MESSAGE\n==================================================\n";
    $content .= "$message\n\n";
    $content .= "\nADDITIONAL INFORMATIONS\n==================================================\n";
    $content .= "Input:         $input\n";
    $content .= "Version:       $version\n";	
    $content .= "IP:            $ip\n";	
    $content .= "Location:      $country\n";
    $content .= "Browser - OS:  $browser\n";
    $content .= "Browser lang.: $language\n";

    mail($to, $subject, $content, $headers);

    header("Location: /thanks.html");
    exit();
?> 