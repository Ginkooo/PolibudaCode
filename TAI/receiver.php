<!doctype html>
<html>
<head>
</head>
<body>
    <?php

    $filename = 'db.csv';

    function write_header($f) {
        fwrite($f, "surname|age|country|email|languages|payment_type\n");
    }

    function show($filename) {
        if (!file_exists($filename)) {
            die("Plik nie istnieje, stwóżże do najpierw poprzed dodanie jakiś danych przez funkcję dodaj!");
        }

        $f = fopen($filename, 'r');

        while($line = fgetcsv($f, $delimiter='|')) {
            print(implode("\t", $line));
            print("\n");
        }

        fclose($f);
    }
    
    function add_record($filename) {
    foreach($_REQUEST as $key=>$value) {
        $$key = $value;
    }
        if (!file_exists($filename)) {
            $f = fopen($filename, 'w');
            write_header($f);
            fclose($f);
        }
        $lang = implode(',', $lang);
        $f = fopen($filename, 'a');
        fwrite($f, "$surname|$age|$country|$email|$lang|$payment_type\n");
        fclose($f);
    }

    foreach($_REQUEST as $key=>$value) {
        $$key = $value;
    }


    switch($_REQUEST['action']) {
        case 'add':
            echo "Zapisywanie informacji do pliku";
            add_record($filename);
        break;
        case 'show':
            show($filename);
        break;
    }
        ?>
<body>
</html>