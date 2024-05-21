# Labs-8
1.Да се имплементира апстрактна класа Hero за која се чува:
име - низа од знаци од максимум 40 знаци
attack damage - децимален број
attack speed - децимален број
ability power - децимален број
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за херојот и виртуелна функција float power() која ја враќа моќта на херојот.

Потребно е да се имплементира класите LegendaryHero и SuperHero кои што ќе наследуваат од класата Hero.

За класата LegendaryHero дополнително се чуваат:

hiddenPowers - број на скриени моќи (цел број)
Функцијата power() се пресметува со формулата (0.4*attack damage*hiddenPowers)+(0.25*attack speed*hiddenPowers)+(0.35*ability power*hiddenPowers)

Функцијата displayInfo() печати во формат:

LegendaryHero: [име] 

Number of hidden powers: [hiddenPowers]

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]

За класата SuperHero дополнително се чуваат:

isShapeshifter - bool
Функцијата power() се пресметува со формулата attack damage+attack speed+ability power. Доколку е shapeshifter, тогаш неговата моќ се зголемува за два пати.

Функцијата displayInfo() печати во формат:

SuperHero: [име] 

Shapeshifter: [Yes/No]

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]


Потребно е да се имплементира класата LegendarySuperHero која што ќе наследува од класите LegendaryHero и SuperHero.

Моќта е пресметана на следниот начин: (моќта на LegendaryHero + моќта на SuperHero)/2

Функцијата displayInfo() печати во формат:

LegendarySuperHero: [име] 

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]


Да се направи глобална функција Hero *mostPowerfulLegendaryHero(Hero **heroes, int n) што ќе врати покажувач до најмоќниот легендарен херој.


input:  
0
4
1
Hero1 130 70 40 3
0
Hero2 60 84 21 1
1
Hero3 120 32 60 2
0
Hero4 200 310 540 1

result:
LegendaryHero: Hero1
Number of hidden powers: 3
Attack damage: 130
Attack speed: 70
Ability power: 40
Power: 250.5


2.  Да се имплементира класа Athlete за која се чува:
name (низа од карактери)
age (int)
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадениот атлетичар.

Потребно е да се имплементираат класите Runner и Jumper кои што ќе наследуваат од класата Athlete.

За класата Runner дополнително се чуваат:

speed - брзина на играчот(double)
Функцијата displayInfo() ја вклучува и брзината.

За класата Jumper дополнително се чуваат:

height- висина на скокачот (double)
Функцијата displayInfo() ја вклучува и висината.


Потребно е да се имплементира класата AllRoundAthlete која што ќе наследува од класите Runner и Jumper.

За класата AllRoundAthlete дополнително се чува:

stamina - стамина на AllRound играчот(int)

Функцијата displayInfo() печати вклучувајќи го и нивото на стамина.

Да се направи глобална функцијаAthlete* findAthleteWithMaxValue(Athlete** athletes, int n) - најголема вредност за тркачите се одредува според брзина, додека кај скокачите според висина, треба да се најде играчот кој ќе има најголема вредност и да се врати покажувач кон него.


input:
0
4
1
Kirca 24 9.4
0
Stamena 19 1.65
1
Ema 21 6.9
0
Jocka 22 1.8

result:
Athlete: Kirca
Age: 24
Speed: 9.4 mph
