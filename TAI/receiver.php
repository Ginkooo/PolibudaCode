<!doctype html>
<html>
<head>
</head>
<body>
    <?php
        var_dump($_REQUEST);
        echo "<h2>Dane odebrane z formularza:</h2>";
        if (isset($_REQUEST['surname']) && $_REQUEST['surname']) {
            $surname= htmlspecialchars(trim($_REQUEST['surname']));
            echo "Nazwisko: $surname<br>";
        }
        if (isset($_REQUEST['age']) && $_REQUEST['age']) {
            $age= htmlspecialchars(trim($_REQUEST['surname']));
            echo "Wiek: $age<br>";
        }
        if (isset($_REQUEST['country']) && $_REQUEST['country']) {
            $country = htmlspecialchars(trim($_REQUEST['country']));
            echo "Kraj: $country<br>";
        }
        if (isset($_REQUEST['email']) && $_REQUEST['email']) {
            $email= htmlspecialchars(trim($_REQUEST['email']));
            echo "Email: $email<br>";
        }
        if (isset($_REQUEST['language']) && $_REQUEST['language']) {
            $surname= htmlspecialchars(trim($_REQUEST['surname']));
            echo "Język: $surname<br>";
        }
        ?>
<body>
</html>