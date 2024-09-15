## IOT Monitoring Simulator
    FRAISSE Tom

# Contexte Global

``
    But : Réaliser un simulateur permettant de modéliser un écosystème IOT spécialisé dans le monitoring de qualité de l'air 
``
# Attentes
 - Utilisation de C++ 17 et Compilateur g++ (MINGW)
 - Utilisation de Cmake
 - Capteurs
    - Capteurs de températures
    - Capteurs d'humidité
    - Capteurs de lumière
    - Capteurs sonores
 - Stockage des informations reçu sous forme de logs et/ou partagées dans une console

# Possibilité

- Créer interface graphique avec QTCreator ? 


# Caractéristiques techniques

PROCESSUS == CAPTEURS

 - Server
    - Capacité à stocker des informations sous formes de logs que l'on peut partager dans une console
    - Capacité à recevoir des informations des différents capteurs
    - gestion du temps interne de chaque capteur
   
Amelioration server : donner un rôle actif au server par exemple envoie de message selon la valeur de retour des capteurs
    ou monitoring de l'espace : donner des instructions en fonction des données reçus pour optimiser l'environnement de la pièce

 - Capteurs
    - un identifiant unique à chaques capteurs
    - un type par default ( via une string)
    - donnée pour la valeur du capteur
    - pointeur vers le Server dédié
    - un nom de capteurs -> logs personnalisés
 
    - Fonction update -> comportement dynamique du capteur executée par l'ordonnanceur suivant une base de temps prédefinis
    - Fonction execute -> met à jour la valeur mesurée par le capteur selon une certaine base de temps enhérente au capteur.
 puis l'envoie au serveur. (Simulation de la lecture d'une valeur par le capteur avec de l'aléatoire : lib random c++)
    - Génération de données de plusieurs types différents - en fonction du capteur
       -> Classe data Générique
    - les informations de chaques capteurs peuvent être transmises et récupérés à des intervales de temps différents 

 - Scheduler
   - Simule l'execution des capteurs
   - gère l'activation des processus sur un base de temps -> Simuler l'activation autonome des capteurs
   - Chaque processus gère son comportement selon son propre temps interne spécifique aux capteurs
    
   - Fonction simulation qui organise le sequencement de l'execution des processus -> permet au capteurs de récuperer les informations de mesure et de les retourner au serveur dédié