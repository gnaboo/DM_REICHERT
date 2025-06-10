
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
SELECT nom_unite FROM Pieces JOIN Cours ON unite = monnaie JOIN Unites ON unite = id_unite
WHERE valable GROUP BY unite ORDER BY SUM(valeur)*euros DESC LIMIT 1;
+------------------+
| nom_unite        |
+------------------+
| Couronne danoise |
+------------------+





-- Exercice 97 : Le nombre d’unités monétaires dont le cours n’est pas précisé.
SELECT COUNT(*) FROM (SELECT * FROM Unites 
EXCEPT (SELECT id_unite, symbole, nom_unite FROM Unites JOIN Cours ON id_unite = monnaie)) as R1;
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
SELECT MAX(compartiment)*MAX(valise)*MAX(rangee)*MAX(colonne) - 
(SELECT COUNT(*) FROM (SELECT * FROM Rangement GROUP BY valise, compartiment, rangee, colonne) as R1) as nb FROM Rangement;
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





