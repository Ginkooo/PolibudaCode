<!DOCTYPE html>

<?php

function print_form() {
    print('
<form  action="/receiver.php" method="POST">
    <p>Formularz zamówienia:</p><br>
    <label for="surname">Nazwisko:</label>
    <input type="text" id="surname" name="surname"><br>
    <label for="age">Wiek:</label>
    <input type="text" id="age" name="age"><br>

    <label for="country">Państwo:</label>
    <select name="country">
        <option value="poland">Poland</option>
        <option value="germany">Germany</option>
        <option value="france">France</option>
    </select>

    <br>

    <label for="email">Email:</label>
    <input type="email" id="email" name="email">
    <p>Zamawiam tutorial z języka:</p>
    <input type="checkbox" name="lang[]" id="c++" value="cpp">
    <label for="c++">C++</label>
    <input type="checkbox" name="lang[]" id="python" value="python">
    <label for="python">Python</label>
    <input type="checkbox" name="lang[]" id="java" value="java">
    <label for="java">java</label>
    <p>Sposób zapłaty:</p>
    <input type="radio" name="payment_type" value="EUROCARD">
    <label for="EUROCARD">EUROCARD</label>
    <input type="radio" name="payment_type" value="VISA">
    <label for="VISA">VISA</label>
    <input type="radio" name="payment_type" value="BANK_TRANSFER">
    <label for="bank_transfer">Przelew bankowy:</label>
    <br>
    <button name="action" value="send" type="submit">Wyślij</button>
    <button name="action" value="add" type="submit">Dodaj</button>
    <button name="action" value="show" type="submit">Pokaż</button>
    <button name="action" value="java" type="submit">Java</button>
    <button name="action" value="python" type="submit">Python</button>
    <button name="action" value="cpp" type="submit">Cpp</button>
</form>
');
}
?>

<html>
<head>
<link href="css/styles.css" rel="stylesheet">
</head>
<body>
<div class="center">
<?php 
    print_form();
?>
</div>
</body>
</html>