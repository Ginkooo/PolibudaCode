<!DOCTYPE html>
<html>
<head>
<link href="css/styles.css" rel="stylesheet">
</head>
<body>
<div class="center">
<p>Przykładowy formularz HTML:</p>
<form  action="/receiver.php" method="POST">
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
    <input type="checkbox" name="lang[]" id="c++">
    <label for="c++">C++</label>
    <input type="checkbox" name="lang[]" id="Python">
    <label for="python">Python</label>
    <input type="checkbox" name="lang[]" id="Java">
    <label for="java">java</label>
    <p>Sposób zapłaty:</p>
    <input type="radio" name="EUROCARD">
    <label for="EUROCARD">EUROCARD</label>
    <input type="radio" name="VISA">
    <label for="VISA">VISA</label>
    <input type="radio" name="bank_transfer">
    <label for="bank_transfer">Przelew bankowy:</label>
    <br>
    <input type="submit" id="send" name="send" value="Wyślij">
    <input type="button" id="cancel" name="cancel" value="Anuluj">
</form>
</div>
</body>
</html>