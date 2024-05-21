1.Дадени ви се класите User и SocialNetwork. 

Во класата User се чуваат информации за корисничко име, возраст и број на пријатели во рамки на некоја социјална мрежа.

Во класата SocialNetwork се чува листа на членови (објекти од класата User) и големина на листата.

Да се дополни почетниот код со следните работи:

Да се спречи додавање на корисник со веќепостоечко корисничко име преку фрлање исклучок од тип UserAlreadyExistsException. Справете се со исклучокот на потребното место. 
Да се додаде променлива за лимитот на дозволени пријатели на еден корисник (цел број). Променливата да важи за сите корисници (објекти од класа User) и истата да може да се менува преку методот setLimit. Иницијално променливата да има вредност 3.
Да се фрли исклучок од тип UserNotFoundException во методот friendRequest доколку firstUsername или secondUsername не се кориснички имиња на корисници во социјалната мрежа. Справете се со исклучокот на потребното место. 
Да се спречи зголемување на бројот на пријатели на некој корисник (над дозволениот лимит) со исклучок од тип FriendsLimitExceededException. Справете се со исклучокот на потребното место.

input:
5
stefan.andonov 19
vlatko.spasev 20
marko.petrov 21
dimitar.kitanovski 22
ema.pandilova 18
0
0
0

result:
Registration of users
Users:
Username: stefan.andonov Age: 19 # of friends: 0
Username: vlatko.spasev Age: 20 # of friends: 0
Username: marko.petrov Age: 21 # of friends: 0
Username: dimitar.kitanovski Age: 22 # of friends: 0
Username: ema.pandilova Age: 18 # of friends: 0

Friend requests
Users:
Username: stefan.andonov Age: 19 # of friends: 0
Username: vlatko.spasev Age: 20 # of friends: 0
Username: marko.petrov Age: 21 # of friends: 0
Username: dimitar.kitanovski Age: 22 # of friends: 0
Username: ema.pandilova Age: 18 # of friends: 0

CHANGE STATIC VALUE
Users:
Username: stefan.andonov Age: 19 # of friends: 0
Username: vlatko.spasev Age: 20 # of friends: 0
Username: marko.petrov Age: 21 # of friends: 0
Username: dimitar.kitanovski Age: 22 # of friends: 0
Username: ema.pandilova Age: 18 # of friends: 0


2.Да се имплементира класа Flight во која се чува:

кодот на летот(низа од најмногу 40 знаци)
градот на заминување(низа од најмногу 100 знаци)
градот на пристигнување(низа од најмногу 100 знаци)
цена на лет(децимален број)
цена на багаж(децимален број)
За оваа класа да се имплементираат следните методи:

функција calculateTotalPrice() што ја враќа збир од цената на летот и цената на багажот
функција displayInfo() за печатење на летот во формат:
[ Код Од До Цена]

Да се имплементира класа EconomyFlight во која покрај основните информации за летот дополнително се чува:

број на седиште(низа од најмногу 4 карактери)
Во оваа класа да се препокрие соодветно функцијата calculateTotalPrice() така што на основната цена на летот ќе се пресмета LOYALTY_DISCOUNT што е статичка променлива во класата која изнесува 20% попуст. Дополнително доколку првата буква од кодот на седиштето е C или F цената на летот се зголемува 30% затоа што седиштето е до прозорецот. Доколку при пресметувањето на цената првата буква од кодот на седиштето не е A, B, C, D, E, F да се фрли исклучок InvalidSeatNumberException кој ќе ја печати пораката "Invalid Seat Number Exception". LOYALTY_DISCOUNT е статичка променлива и може да ја промени само авио компанијата. 

Соодветно во класата исто така да се препокрие функцијата displayInfo која ќе печати во формат:

[ Код Од До Седиште

Total price: Вкупната Цена ]

Дополнително во класите да се имплементираат соодветно сите потребни работи.

input:
1
5
W775 Skopje Vienna 120 50 C25
G667 Rome Paris 100 25 A18
A556 Istanbul Amsterdam 200 0 B05
S449 Skopje Berlin 80 45 E14
K119 Porto Madrid 95 30 F18

result:
===== Testiranje na klasite ======
W775 Skopje-Vienna C25
Total Price: $176.8
G667 Rome-Paris A18
Total Price: $100
A556 Istanbul-Amsterdam B05
Total Price: $160
S449 Skopje-Berlin E14
Total Price: $100
K119 Porto-Madrid F18
Total Price: $130


3.Да се напише програма која што од датотека со име "text.txt" ќе ги одреди и ќе ги испечати на стандарден излез:

релативната фреквенција на сите мали букви
релативната фреквенција на сите големи букви
Релативната фреквенција на даден(и) карактер(и) се пресметува како количник на вкупното појавување на тој/тие карактер/и со вкупниот број на карактери во текстот (да се игнорираат празните места и специјалните знаци).

Да не се менува функцијата writeToFile().

input:
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse efficitur tempus enim, id imperdiet nisl rhoncus et. Nunc aliquam suscipit ex eget tincidunt. Nullam finibus ipsum congue, tempus quam et, condimentum diam. MAECENAS COMMODO est NIBH, ac condimentum neque ultrices in. Donec varius lectus nibh. Praesent quis turpis quis purus venenatis condimentum id molestie erat. In viverra dignissim congue. Sed sit amet malesuada metus, ut egestas massa. Vivamus pretium, dui at hendrerit pharetra, nunc augue dignissim lorem, in suscipit tortor ligula quis tellus. Sed porttitor enim non faucibus facilisis. Phasellus accumsan tincidunt est, quis imperdiet mauris commodo vel. Aliquam erat volutpat. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Vestibulum vestibulum massa suscipit quam mollis, quis hendrerit quam tempor. In feugiat viverra condimentum. Donec volutpat est enim, ut malesuada libero pulvinar vel. In hac habitasse.#

result:
0.0455
0.9545


