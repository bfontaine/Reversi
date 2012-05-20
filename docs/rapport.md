% Projet LC4
% Baptiste Fontaine
% 20 mai 2012

Introduction
------------

Ce projet consistait en la réalisation d'un jeu d'Othello (ou Reversi) en C,
avec une interface textuelle et une intelligence artificielle.

Architecture
============

L'organisation du projet telle qu'elle était décrite dans l'énoncé n'a pas été
suivie, car il m'a semblé plus intéressant d'organiser le projet par moi-même.

Le code est divisé en fichiers `.c` et `.h`. Le code du programme est dans le
répertoire `src`, où l'on trouve `main.c`^[à chaque fois, s'il n'est pas
mentionné, le fichier `.h` correspondant est dans le même répertoire que le
`.c`], qui est le fichier principal (celui qui contient la fonction `main`),
et un fichier `utils.h` qui contient les principales instructions de
pré-processeur concernant les macros et les constantes pour les codes de retour
des fonctions. Ensuite, le sous-répertoire `src/game` contient les fichiers
`board.c` (qui contient toutes les fonctions relatives au plateau de jeu),
`board.h` (qui définie la structure utilisé pour modéliser un plateau de jeu),
`game.c` (qui contient les fonctions relatives au fonctionnement du jeu). Le
sous-répertoire `src/interfaces` contient les fichiers relatives aux interfaces
de jeu, et le sous-répertoire `src/ai` contient les fichiers relatifs à
l'intelligence artificielle.
Le répertoire `tests` contient les tests unitaires relatifs au code du projet.

Enfin, la racine du projet comporte un répertoire `docs`, où est situé le
présent rapport, un Makefile et un script Bash, `run_tests.sh`, qui permet de
lancer les tests unitaires.

Une fois compilé, le projet est un fichier binaire `othello`.


Organisation
============

J'ai réalisé ce projet seul, en le versionnant avec Git et en l'hébergeant
dans un dépôt privé Github^[Le dépôt est accessible à l'adresse suivante :
`https://github.com/bfontaine/Reversi`. Je le rendrais public un peu après l'heure
limite de rendu des projets.]. Pour détecter les fuites mémoires et les
problèmes de pointeurs en général, j'ai utilisé l'outil
[Valgrind](http://valgrind.org/docs/manual/mc-manual.html). De façon à pouvoir
automatiser les tests, j'ai écris des tests unitaires, ainsi qu'un script Bash
pour pouvoir les lancer facilement. Enfin, j'ai choisi d'écrire le code ansi que
les commentaires en anglais, car je considère que c'est une bonne habitude à
prendre pour faciliter la maintenance.


Tests
-----

Chaque fichier `F.c` est testé par un programme appelé `F_tests.c` situé dans le
répertoire `tests`, qui inclue le fichier `tests/tests_base.h`^[Ce fichier sert
uniquement à centraliser les `include` communs]. J'ai utilisé la macro `assert`
de C pour faire les tests. Le script `run_tests.sh` compile chaque fichier
`tests/*_tests.c`, et l'exécute, en affichant, à titre indicatif, le nombre
d'assertions du programme.

La partie de test fournie pour tester notre moteur de jeu est présente dans le fichier
`tests/game_test_WhiteWins_01.txt`. Le script de tests récupère le nom du
gagnant dans le nom du fichier, et teste si le programme `othello` trouve bien
le bon gagnant.


Compilation
-----------

La cible par défaut du Makefile est `othello`, qui compile l'ensemble du projet
en un fichier binaire `othello`. D'autres cibles sont possibles, comme `clean`,
qui supprime les fichiers temporaires, et `cleanall` qui supprime tous les
fichiers générés par `make` (fichiers `.o`) et les fichiers temporaires.

La compilation est effectuée avec GCC et les options suivantes :

- `-Wall` : active la majorité des avertissements
- `-Wextra` : active d'autres avertissements non inclus avec l'option précédente
- `-Wundef` : active les avertissements relatifs aux constantes de
  pré-processeur non initialisées (non inclu avec les deux options précédentes)
- `-Werror` : considère les avertissements comme des erreurs, et donc refuse de
  compiler s'il y a le moindre avertissement
- `-std=c89` : considère le code comme du C89 (demandé par l'énoncé du projet)

Interfaces
----------

L'interface textuelle du jeu a été en majorité écrite dans
`src/interfaces/text.c`. À l'origine, le but était de fournir plusieurs
interfaces (textuelle simple, textuelle améliorée, curses, éventuellement
graphique), mais le temps ne m'a pas permis d'en écrire d'autres. Toutes les
interfaces devaient implémenter les mêmes fonctions définies dans
`src/interfaces/interface.h`, ainsi, le choix de l'interface peut se faire à la
compilation, il n'y a pas besoin de toucher au code. L'interface textuelle se
comporte comme demandé dans l'énoncé du projet, sauf que l'affichage du plateau
du jeu se fait en utilisant les couleurs^[grâce à des codes pour le shell], mais
ceci peut être désactivé en mettant la valeur `0` à la constante
`BOARD_COLORS`^[située dans `src/utils.h`].

Architecture
------------

Le plateau de jeu est représenté par une simple structure comportant un seul
champ, qui est un tableau de `char`. Les cases vides sont représentées par `0`,
les cases blanches par `1` et les cases noires par `2`.

L'intelligence artificielle utilise un arbre de coups possibles. Elle est
représentée par un structure `ia`, qui comporte un tableau de coups possibles
pour le tour courant, chacun de ces coups étant lui-même un arbre de coups
possibles. Les coups sont représentés par une structure similaire à l'IA, mais,
pour faire des économies de mémoire, ils ne stockent que l'emplacement du coup,
et pas la position actuelle du plateau de jeu, qui est, elle, stockée dans la
structure `ia`, qui sert de racine à l'arbre. La logique liée à l'intelligence
artifielle est indépendante du programme principal; ainsi, l'IA est une sorte
d'interface spéciale : le programme principal ne fait que lui demander d'entrer
une commande, qui est toujours une commande relative aux coups.


Fonctionnalités
===============

Configuration
-------------

Le comportement du programme est très facilement configurable, puisque
pratiquement toutes les constantes sont centralisées dans le fichier
`src/utils.h`. Les options relatives à l'IA sont dans `src/ai/ai.h`.

Interface
---------

L'interface textuelle ne fournit que les commandes demandées dans l'énoncé du
projet. Elle gère les mauvaises commandes en affichant une erreur appropriée.

Intelligence Artificielle
-------------------------

L'intelligence artifielle peut être utilisée comme demandé dans l'énoncé du
projet, à savoir avec les options `--blanc` et `--noir`. Elle choisi ses coups
en fonction du nombre de points que ça peut lui rapporter, de la position du
coup (dans un coin, sur le côté ou au milieu), et en fonction des coups que peut
faire l'adversaire après.


Problèmes connus
================

Au moment du rendu du projet, la mise à jour du plateau de l'IA avec les coups
adverses ne fonctionnait pas correctement. Ainsi, le programme principal envoit
le coup adverse à l'IA pour qu'elle mette à jour son plateau de jeu courant,
mais cette fonctionnalité ne marche pas, ce qui fait qu'elle peut jouer les
2 ou 3 premiers coups d'une partie, mais ensuite elle tente de passer son coup
puisqu'elle ne voit pas de coup possible, le plateau de jeu n'étant pas à jour.

En dehors de ça, le projet compile sans erreur ni avertissement, et ne comporte
pas de fuites mémoires.
