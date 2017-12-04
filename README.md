# Pong
Présentation : 

Pong est un jeu concu par Nolan Bushnell et développé par Allan Alcorn en 1972 et qui as a
a la fois lancer la société atari et introduit le jeu video au grand public.

Il s'agit d'une simulation de tenis de table (d'ou son nom) jouable a 1 ou 2 joueurs.

L'écran est séparé en 3 zones, la zone de jeu situé sur la partie centrale de l'écran et
les 2 zones de but défendues par les joueurs situés aux extrimitées gauche et droite de l'écran.

La zone de jeu est séparés des zone de but par des racettes.

Chaque joueur peut déplacer verticalement une racette.

La balle opère un déplacement réctiligne et uniforme dans une direction jusqu'a rencontrer un 
obstacle (une raquette ou une extrimité de l'écran), quand cela se produit, la balle rebondit sur 
cet obstacle.

Lorsque la balle passe dans une zone de but, l'adversaire du joueur défendant ce but marque un point,
la balle est alors déplacée dans la zone de jeu.

Le but est de marquer le plus de points.


Fonctionement Général bloc par bloc du programme : 

Au demarage du programme, toutes les variables sont initialisées.
Le programme vérifie s'il y a des valeures entrées en parramètres et si oui, si celles entrés
peuvent ètres interprétés.
Le programme vérifie si le gestionaire graphique ainsi que son extention textuelle ont bien 
été initialisés.
Le programme initialise les variables SDL ainsi que l'emplacement des objets sur l'écran.

Le programme entre alors dans la boucle de jeu.
Le programme va vérifier si le jeu a été réinitialisé, le cas est chéant, le programme va se 
mettre en pause pour que le ou les joueurs puissent prendre le temps de se positioner.
Le programme va vérifier les colisions entre la balle et les racettes, si colision il y a, la
l'orientation de la balle sera changée. Si la balle entre en colision avec la racette, le programme
va vérifier l'emplacement de la colision sur la racette et changer l'angle de la balle en fonction
Le programme va ensuite vérifier les évènements, a savoir si une touche est préssée et changer la 
position de la raquette en fonction.
Le programme va mettre a jour les variables SDL et attendre 12ms avant de passer a la frame suivante

Options : 

[] : Lancement du jeu en mode local, le premier joueur utilise les touches [z] et [s] et
le second joueur utilise les touches [up] et [down]

[-ia] : Lance le jeu en mode locale, le joueur utilise les touches [z] et [s] et l'autre joueur
est simulé par l'ordinageur

[-multi] [add] [token] : NON IMPLEMENTE | Le jeu va tenter de se connecter a l'adresse du serveur entrée
en parrametres, s'il y arrive, deux joueurs ayant entrer le mème token vont jouer ensemble.

Conception de la mise en réseau : 

Le serveur possede une matrice de 3 * x dont seul la première colonne est remplie par des identifients
uniques générés automatiquement.
Le serveur est en attente de la récéption d'un paquet.
Lorsqu'un joueur tente de se connecter, il dois entrer deux parrametres, l'adresse du serveur et un token, 
si le joueur n'entre pas ce dernier parrametre, le serveur lui en atribuera un automatiquement.
Un paquet contenant le token est envoyé au serveur, si le client n'a pas entrer de token, 
la veleur 0 est envoyée dans le paquet.
Le serveur place l'adresse du client dans l'une des deux colones de la matrice ou la première colonne
correspond au token envoyé dans le paquet ou générer par le serveur.
si les deux colonne sont remplie, le serveur lance un thread qui sera charger d'établire la communication 
entre les deux joueurs.
si un client envoie un signal d'extinction sans que la partie ai commancer, celui ci va envoyer un paquet
contenant la valeur -1, le serveur va ensuite parcourir la matrice et enlever l'adresse du client correspondant

La partie peut commancer.

lorsque le client appuie sur les touches [z] et [s], il va a la fois changer le positionement de sa racette
mais aussi envoyer cette valeure au serveur, celui ci va envoyer cette valeure a son adversaire.
lorsqu'un client recois un paquet, celui ci va déclancher un évènement qui va modifier le positionement 
de la seconde raquette et l'afficher lors de la frame suivente.
une communicaiton réseau ne prenant qu'entre 1 et 20ms, l'affichage n'aura que quelques frames de retard.
le score est calculé en retard.

Lorsqu'un joueur envoie un signal d'extinction, il envoie un paquet au serveur qui va envoyer un paquet
au second client lui indiquant la fin de la partie, le serveur va mettre libérer les adresse présentes
dans la matrice et mettre fin a son processus.
