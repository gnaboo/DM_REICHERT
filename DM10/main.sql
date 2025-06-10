
-- Exercice 90 : Le nom de la monnaie dont le symbole est "CHF".
SELECT nom_unite FROM Unites WHERE symbole = "CHF" ;
+--------------+
| nom_unite    |
+--------------+
| Franc suisse |
+--------------+


-- Exercice 91 : Le nombre de pièces ayant actuellement cours légal dans ma collection.
SELECT COUNT(*) FROM Pieces WHERE valable = 1;
+----------+
| COUNT(*) |
+----------+
|       80 |
+----------+


-- Exercice 92 : Le pays d’où provient la pièce ayant cours légal avec la plus grande valeur faciale (en cas
-- d’égalité, on acceptera une seule valeur mais on préfèrera l’ensemble des valeurs).
SELECT pays FROM Pieces WHERE valable AND
valeur = (SELECT MAX(valeur) FROM Pieces WHERE valable) GROUP BY pays;
+-------+
| pays  |
+-------+
| Japon |
+-------+


-- Exercice 93 : Le nom de l’unité monétaire dont j’ai le plus grand nombre de pièces au total (en comptant
-- les doublons autant de fois que nécessaire).
SELECT nom_unite FROM Pieces JOIN Unites on id_unite = unite GROUP BY nom_unite ORDER BY COUNT(nom_unite) DESC LIMIT 1;
-- Alternativement
SELECT u2.nom_unite FROM Pieces p2 JOIN Unites u2 ON u2.id_unite = p2.unite 
GROUP BY u2.nom_unite HAVING COUNT(*) = 
(SELECT MAX(total) FROM (SELECT COUNT(*) AS total 
FROM Pieces p JOIN Unites u ON u.id_unite = p.unite GROUP BY u.nom_unite) AS _);
+------------------+
| nom_unite        |
+------------------+
| Couronne danoise |
+------------------+



-- Exercice 94 : Le nombre total de cases de rangement occupées par au moins une pièce.
SELECT COUNT(*) FROM (SELECT * FROM Rangement GROUP BY valise, compartiment, rangee, colonne) as R1;
+----------+
| COUNT(*) |
+----------+
|      105 |
+----------+


-- Exercice 95 : Le plus grand nombre de pièces dans une même case de rangement.
SELECT MAX(nb_pieces) FROM (SELECT COUNT(*) as nb_pieces FROM Rangement GROUP BY valise, compartiment, rangee, colonne) as R1;
+----------------+
| MAX(nb_pieces) |
+----------------+
|              3 |
+----------------+

-- Exercice 96 : Le nom de l’unité monétaire ayant cours légal pour laquelle l’ensemble des pièces dont je
-- dispose a le plus de valeur en ramenant aux euros (comme des égalités sont improbables, on pourra ignorer
-- celles-ci).
SELECT nom_unite FROM Pieces p JOIN Unites u ON p.unite = u.id_unite JOIN Cours c ON u.id_unite = c.monnaie GROUP BY id_unite
ORDER BY SUM(euros) DESC LIMIT 1;
+--------------+
| nom_unite    |
+--------------+
| Franc suisse |
+--------------+

MariaDB [sql-mp2i-dm]> SELECT *, SUM(valeur), SUM(valeur)*euros FROM Pieces JOIN Cours ON unite = monnaie JOIN Unites ON unite = id_unite WHERE valable GROUP BY unite;
+----------+--------------------------+--------+-------+-------+---------+---------+------------+----------+---------+-------------------------+----------------------+------------------------+
| id_piece | pays                     | valeur | unite | annee | valable | monnaie | euros      | id_unite | symbole | nom_unite               | SUM(valeur)          | SUM(valeur)*euros      |
+----------+--------------------------+--------+-------+-------+---------+---------+------------+----------+---------+-------------------------+----------------------+------------------------+
|       76 | Danemark                 |   0.05 |     7 |  1986 |       1 |       7 |   0.134399 |        7 | DKK     | Couronne danoise        |   109.05000000074506 |     14.656210604410171 |
|       89 | NorvÃ¨ge                 |      1 |     8 |  2006 |       1 |       8 |  0.0884225 |        8 | NOK     | Couronne norvÃ©gienne   |                   76 |      6.720109969377518 |
|       95 | SuÃ¨de                   |      1 |     9 |  2000 |       1 |       9 |  0.0876615 |        9 | SEK     | Couronne suÃ©doise      |                   24 |     2.1038759350776672 |
|       42 | Pologne                  |   0.01 |    10 |  2015 |       1 |      10 |   0.213843 |       10 | PLN     | ZÅ‚oty                  |    8.880000004544854 |      1.898925866860481 |
|       34 | Chine                    |    0.1 |    11 |  1991 |       1 |      11 |   0.135779 |       11 | CNY     | Yuan                    |  0.10000000149011612 |   0.013577899539141347 |
|       65 | Japon                    |      1 |    12 |  2004 |       1 |      12 | 0.00696267 |       12 | JPY     | Yen                     |                  666 |      4.637138228863478 |
|       31 | IsraÃ«l                  |   0.01 |    13 |  1980 |       1 |      13 |   0.261931 |       13 | ILS     | Shekel                  |  0.16000000201165676 |     0.0419089608693225 |
|       14 | Ã‰tats-Unis              |   0.01 |    15 |  1994 |       1 |      15 |   0.940315 |       15 | USD     | Dollar amÃ©ricain       | 0.009999999776482582 |   0.009403149871457739 |
|       23 | Canada                   |   0.01 |    16 |  2005 |       1 |      16 |   0.679914 |       16 | CAD     | Dollar canadien         |    4.509999999776483 |      3.066412129250188 |
|        8 | Argentine                |    0.1 |    19 |  1993 |       1 |      19 | 0.00468589 |       19 | ARS     | Peso argentin           |   0.8500000014901161 |   0.003983006447085574 |
|       11 | Royaume-Uni              |      1 |    20 |  1983 |       1 |      20 |    1.13177 |       20 | GBP     | Livre sterling          |                    1 |     1.1317700147628784 |
|       26 | Guyana                   |   0.05 |    21 |  1991 |       1 |      21 | 0.00448028 |       21 | GYD     | Dollar guyanien         |  0.05000000074505806 | 0.00022401400244256853 |
|       41 | Australie                |      1 |    22 |  1986 |       1 |      22 |   0.618729 |       22 | AUD     | Dollar australien       |                    1 |     0.6187289953231812 |
|       38 | RÃ©publique tchÃ¨que     |      2 |    23 |  2004 |       1 |      23 |  0.0423205 |       23 | CZK     | Couronne tchÃ¨que       |                  155 |      6.559677664190531 |
|       40 | Mexique                  |    0.5 |    24 |  2005 |       1 |      24 |  0.0508579 |       24 | MXN     | Peso mexicain           |                  0.5 |   0.025428950786590576 |
|       51 | Maroc                    |     10 |    25 |  1995 |       1 |      25 |  0.0903067 |       25 | MAD     | Dirham marocain         |                   10 |     0.9030669927597046 |
|       52 | AlgÃ©rie                 |     10 |    26 |  1981 |       1 |      26 | 0.00685076 |       26 | DZD     | Dinar algÃ©rien         |                   30 |    0.20552279893308878 |
|       54 | Tunisie                  |   0.02 |    27 |  1996 |       1 |      27 |   0.301448 |       27 | TND     | Dinar tunisien          | 0.019999999552965164 |   0.006028959616371399 |
|       57 | ThaÃ¯lande               |     10 |    28 |  2004 |       1 |      28 |  0.0270129 |       28 | THB     | Baht thaÃ¯landais       |                   10 |       0.27012899518013 |
|       58 | Afrique du Sud           |      5 |    29 |  2005 |       1 |      29 |  0.0513349 |       29 | ZAR     | Rand sud-africain       |                    5 |    0.25667449459433556 |
|       59 | Suisse                   |   0.05 |    30 |  1983 |       1 |      30 |    1.02147 |       30 | CHF     | Franc suisse            |    8.350000005215406 |      8.529274093471683 |
+----------+--------------------------+--------+-------+-------+---------+---------+------------+----------+---------+-------------------------+----------------------+------------------------+


SELECT nom_unite FROM Pieces JOIN Cours ON unite = monnaie JOIN Unites ON unite = id_unite WHERE valable GROUP BY unite ORDER BY SUM(valeur)*euros DESC LIMIT 1;
+------------------+
| nom_unite        |
+------------------+
| Couronne danoise |
+------------------+





-- Exercice 97 : Le nombre d’unités monétaires dont le cours n’est pas précisé.
SELECT COUNT(*) FROM (SELECT * FROM Unites EXCEPT (SELECT id_unite, symbole, nom_unite FROM Unites JOIN Cours ON id_unite = monnaie)) as R1;
+----------+
| COUNT(*) |
+----------+
|        9 |
+----------+


-- Exercice 98 : Le nombre total d’emplacements des compartiments en admettant que toutes les valises
-- contiennent au moins une pièce et aient le même nombre de compartiments, que chaque compartiment ait le
-- même nombre de rangées et qu’au moins une pièce figure dans la dernière rangée d’un compartiment, et que
-- chaque rangée ait le même nombre de colonnes et qu’au moins une pièce figure dans la dernière colonne d’une
-- rangée.
SELECT MAX(compartiment)*MAX(valise)*MAX(rangee)*MAX(colonne) FROM Rangement;
+--------------------------------------------------------+
| MAX(compartiment)*MAX(valise)*MAX(rangee)*MAX(colonne) |
+--------------------------------------------------------+
|                                                    231 |
+--------------------------------------------------------+

-- Exercice 99 : Le nombre d’emplacements vides sous les mêmes conditions que pour l’exercice précédent.
SELECT MAX(compartiment)*MAX(valise)*MAX(rangee)*MAX(colonne) - (SELECT COUNT(*) FROM (SELECT * FROM Rangement GROUP BY valise, compartiment, rangee, colonne) as R1) as nb FROM Rangement;
+------+
| nb   |
+------+
|  126 |
+------+





























































90 : Franc suisse
91 : 80
92 : Japon
93 : Couronne danoise
94 : 105
95 : 3
96 : Couronne danoise
97 : 9
98 : 231
99 : 126





