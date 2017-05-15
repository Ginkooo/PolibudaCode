var IMG_WIDTH = IMG_HEIGHT = 100;

var books = [
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/84abb2131179143ceb2e165a86ef89e2,elemad.jpg',
		title: 'Elektronika dla małych i dużych',
		link: 'http://helion.pl/ksiazki/elektronika-dla-malych-i-duzych-od-przewodu-do-obwodu-oyvind-nydal-dahl,elemad.htm#format/e',
		description: 'Większość dzieciaków interesuje się fascynującym światem urządzeń elektrycznych. Obserwują, jak działa żarówka, zdalnie sterowany samochód czy odtwarzacz muzyki. Kiedy mały odkrywca postanawia sprawdzić, co one kryją w środku, często ofiarą tej niepohamowanej ciekawości pada jakiś gadżet. Warto pokazać najmłodszym, że elektronika najwięcej radości (i wiedzy!) daje wtedy, gdy zbuduje się coś własnymi rękoma! Właśnie konstruowanie coraz to bardziej skomplikowanych obwodów jest wyjątkowo wciągające i daje wielką satysfakcję.'
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/ce94a1828c605fe54ec6974b697bbcbb,mikjav.jpg',
		title: 'Mikrousługi w Javie. Poradnik eksperta',
		link: 'http://helion.pl/ksiazki/mikrouslugi-w-javie-poradnik-eksperta-sourabh-sharma,mikjav.htm',
		description: 'Niniejsza książka jest przeznaczona dla programistów Javy, którzy znają podstawowe pojęcia dotyczące mikrousług i chcą tworzyć funkcjonalne aplikacje biznesowe w tej technologii. Przedstawiono tu najważniejsze zasady realizacji dużych projektów, zaprezentowano ważne szczegóły dotyczące konfiguracji środowiska programistycznego i ciągłej integracji, które ułatwią wdrażanie mikrousług. Opisano zalety i sposoby wykorzystania biblioteki Spring Security. Przedstawiono dobre praktyki projektowania mikrousług, a także techniki ich debugowania, tak aby bez problemu można było zaprojektować i wdrożyć aplikację w środowisku korporacyjnym.',
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/cce76081c5c79abe2b80a93b1d32a5e5,pypod2.jpg',
		title: 'Python. Podstawy nauki o danych. Wydanie II',
		link: 'http://helion.pl/ksiazki/python-podstawy-nauki-o-danych-wydanie-ii-alberto-boschetti-luca-massaron,pypod2.htm',
		description: 'Niniejsza książka jest doskonałym wprowadzeniem do nauki o danych. Jej autorzy wskażą Ci prostą i szybką drogę do rozwiązywania różnych problemów z tego obszaru za pomocą Pythona oraz powiązanych z nim pakietów do analizy danych i uczenia maszynowego. Dzięki lekturze przejdziesz przez kolejne etapy modyfikowania i wstępnego przetwarzania danych, poznając przy tym podstawowe operacje związane z wczytywaniem danych, przekształcaniem ich, poprawianiem na potrzeby analiz, eksplorowaniem i przetwarzaniem. Poza podstawami opanujesz też zagadnienia uczenia maszynowego, w tym uczenia głębokiego, techniki analizy grafów oraz wizualizacji danych.',
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/77cf06aaf69c1a4c4fb5e8d98a8f131d,czykov.jpg',
		title: 'Czysty kod. Podręcznik dobrego programisty (ebook)',
		link: 'http://helion.pl/ksiazki/czysty-kod-podrecznik-dobrego-programisty-robert-c-martin,czykov.htm#format/e',
		description: 'W książce „Czysty kod. Podręcznik dobrego programisty” szczegółowo omówione zostały zasady, wzorce i najlepsze praktyki pisania czystego kodu. Podręcznik zawiera także kilka analiz przypadków o coraz większej złożoności, z których każda jest doskonałym ćwiczeniem porządkowania zanieczyszczonego bądź nieudanego kodu. Z tego podręcznika dowiesz się m.in., jak tworzyć dobre nazwy, obiekty i funkcje, a także jak tworzyć testy jednostkowe i korzystać z programowania sterowanego testami. Nauczysz się przekształcać kod zawierający problemy w taki, który jest solidny i efektywny.',
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/8e8419e52fe804796f95c780dbaa027d,angtia.jpg',
		title: 'Angular 2. Tworzenie interaktywnych aplikacji internetowych',
		link: 'http://helion.pl/ksiazki/angular-2-tworzenie-interaktywnych-aplikacji-internetowych-gion-kunz,angtia.htm',
		description: 'Niniejsza książka ma na celu nauczenie programistów tego nowego podejścia do programowania interaktywnych stron internetowych i równocześnie pokazanie najlepszych możliwości Angulara. Poza praktycznymi aspektami korzystania z tego frameworka największy nacisk położono na tworzenie interfejsów użytkownika bazujących na komponentach — wyjaśniono podstawowe koncepcje tego sposobu programowania i opisano, jak wykorzystać framework do tworzenia nowoczesnych, wydajnych i łatwych w utrzymaniu interfejsów użytkownika.',
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/4d23256c77cb2e3f384105706dcb9001,artd2v.jpg',
		title: 'Sztuka podstępu. Łamałem ludzi, nie hasła. Wydanie II',
		link: 'http://helion.pl/ksiazki/sztuka-podstepu-lamalem-ludzi-nie-hasla-wydanie-ii-kevin-d-mitnick-author-william-l-simon-autho,artd2v.htm',
		description: 'Zakup najdroższych technologii zabezpieczeń, karty biometryczne, intensywne szkolenia personelu, restrykcyjna polityka informacyjna czy wreszcie wynajęcie agencji ochrony - Kevin Mitnick udowodnił, że w świecie sieci i systemów poczucie bezpieczeństwa jest tylko iluzją. Ludzka naiwność, łatwowierność i ignorancja - oto najsłabsze ogniwa, wiodące do uzyskania poufnych informacji, tajnych kodów i haseł. Mitnick, obecnie najbardziej rozchwytywany ekspert w dziedzinie bezpieczeństwa komputerów, w swej niezwykłej książce przestrzega i pokazuje, jak łatwo można ominąć bariery systemów wartych miliony dolarów. Przedstawiając i analizując metody hakerów oparte na prawdziwych atakach, demonstruje, że tam, gdzie nie można znaleźć luk technicznych, zawsze skuteczne okazują się ludzkie słabości... A Ty? Jesteś w pełni świadomy narzędzi technologicznych i socjotechnicznych, które hakerzy mogą wykorzystać przeciwko Tobie?',
	},
	{
		src: 'https://static01.helion.com.pl/global/okladki/326x466/1d1890681eb5a1d64cff31a2a51c8f4c,autopy.jpg',
		title: 'Automatyzacja nudnych zadań z Pythonem. Nauka programowania',
		link: 'http://helion.pl/ksiazki/automatyzacja-nudnych-zadan-z-pythonem-nauka-programowania-al-sweigart,autopy.htm',
		description: 'Jeśli nie masz pojęcia o programowaniu, ale chcesz wykorzystać komputer do automatyzacji prostych, powtarzalnych operacji, trzymasz w ręku właściwą książkę. Podstawy programowania przedstawiono tu w sposób klarowny i zrozumiały, poszczególne działania wyjaśniono krok po kroku, a propozycje praktycznych projektów pozwalają na gruntowne przyswojenie materiału i poszerzenie wiedzy. Do nauki wykorzystano język Python, ponieważ jest on stosunkowo prosty, popularny, a przy tym wciąż rozwijany. Szybko przekonasz się, ile czasu i wysiłku można zaoszczędzić dzięki automatyzacji zadań za pomocą krótkich i łatwych programów!',
	},
];

function random_books(count) {
	ret = [];
	for(var i=0; i<count; i++) {
		var rand = Math.floor(Math.random() * books.length);
		var book = books[rand];
		if(ret.indexOf(book) != -1) {
			i--;
			continue;
		}
		ret.push(book);
	}
	return ret;
}

function smallerize() {
	$(this).find('.title').slideUp();
}

function biggerize() {
	$(this).find('.title').slideDown();
	$(this).children().css('position', 'relative');
	$(this).children().css('margin', '5px auto');
}

function put_books(books) {
	var suggested = $('#suggested');
	var html = '';
	html += '<ul>';
	for(var i=0; i<books.length; i++) {
		html += '<li class="suggestion" onclick="window.location.href=\'' + books[i].link + '\';">';
		html += '<img height="300" src="' + books[i].src + '" alt="' + books[i].title + '">';
		html += '<h3 class="title">' + books[i].title + '</h3>';
		html += '</li>';
	}
	html += '</ul>';
	suggested.append(html);
	$('.suggestion').mouseenter(biggerize).mouseleave(smallerize);
}

function count_cart() {
	var cart = localStorage['cart'] || '[]';
	var cart = JSON.parse(cart);
	var count = cart.length;
	$('#itemcount').html(count);
}

function initIndex() {
	var suggestion = $('#suggested');
	var books_to_preview = random_books(5);
	put_books(books_to_preview);
	count_cart();
}

function list_books() {
	var i = 0;
	ret = '<div class="container-fluid">';
	ret += '<div class="row">';
	while(i<books.length) {
		ret += '<div class="book col-md-6">';
		ret += '<h3 class="bigtitle">' + books[i].title + '</h3>';
		ret += '<div class="bookexpand">';
		ret += '<img src="' + books[i].src + '" alt="' + books[i].title + '">';
		ret += '<p class="description">' + books[i].description + '</p>';
		ret += '<div class="btn btn-primary btn-md" onclick="window.location.href=\'' + books[i].link + '\'">Kup u wydawcy</div>';
		ret += '<div class="btn btn-primary btn-md" onclick="add_to_cart(\'' + books[i].title + '\')">Dodaj do koszyka</div>';
		ret += '</div>';
		ret += '</div>';
		i++;
	}
	ret += '</div>';
	ret += '</div>';
	return ret;
}

function initShop() {
	$('#booklist').append(list_books);
	$('.bigtitle').click((event) => {
		var event = $(event.target);
		var target = event.next('.bookexpand');
		target.slideToggle("slow");
	});
	count_cart();
}

function increase_item_count() {
	$('#itemcount').html(Number($('#itemcount').html()) + 1);
}

function add_to_cart(name) {
	var cart = localStorage['cart'] || '[]';
	var cart = JSON.parse(cart);
	cart.push(name);
	localStorage['cart'] = JSON.stringify(cart);
	increase_item_count();
}

function find_src(name) {
	var index = books.findIndex((book) => book.title == name);
	return books[index].src;
}

function populate_cartlist() {
	var cartlist = $('#cartlist');
	var cart = localStorage['cart'] || '[]';
	var cart = JSON.parse(cart);
	var html = '';
	for(var i=0; i<cart.length; i++) {
		html += '<div class="media cartitem">';
		html += '<div class="media-left">';
		html += '<div class="itemdelete glyphicon glyphicon-remove" onclick="delete_item(this,\'' + cart[i] + '\')"></div>';
		html += '</div>';
		html += '<div class="media-body">';
		html += '<h4>' + cart[i] + '</span>';
		html += '<img class="thumbnail" src="' + find_src(cart[i]) + '" alt="Obraz" width="50" height="50">';
		html += '</div>';
		html += '</div>';
	}
	cartlist.append(html);
}

function zerotraile(num) {
	if(num > 9) {
		return String(num);
	}
	var num = String(num);
	return '0' + num;
}

function set_min_date() {
	var datefield = $('#date');
	var date = new Date();
	date.setDate(date.getDate() + 3);
	var day = zerotraile(date.getDate());
	var month = zerotraile(date.getMonth() + 1);
	var year = date.getFullYear();
	datefield.attr('min', [year, month, day].join('-'));
}

function initCart() {
	count_cart();
	populate_cartlist();
}

function delete_cart() {
	localStorage['cart'] = '[]';
}

function delete_item(element, name) {
	var cart = JSON.parse(localStorage['cart'] || '[]')
	var index = cart.indexOf(name);
	if(index > -1) {
		cart.splice(index, 1);
	}
	localStorage['cart'] = JSON.stringify(cart);
	count_cart();
	$(element).parent().parent().remove();
}

function initOrder() {
	count_cart();
	set_min_date();
	var orderlist = $('#orderlist');
	var cart = JSON.parse(localStorage['cart'] || '[]')
	html = '';
	for(var i=0; i<cart.length; i++) {
		html += '<li>';
		html += cart[i];
		html += '</li>';
	}
	orderlist.append(html);
}
