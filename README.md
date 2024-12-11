(EL YOUBI MONCEF - 2G2TD1TP2 - TP1 - Prog Sys)

Compte Rendu de TP : Ensea in the Shell 

1. Affichage du message de bienvenue et du prompt
Ce que j’ai fait :
Lors du lancement du shell, un message de bienvenue s'affiche avec le prompt enseash %. Ce prompt invite l'utilisateur à entrer une commande.

Difficultés rencontrées et solution :
La mise en place du prompt a été simple, mais il a fallu veiller à ce qu’il soit rafraîchi après chaque exécution de commande. L’utilisation d’une boucle while(1) avec un break lorsque l'utilisateur entre le mot "exit" a permis de relancer automatiquement la demande de commande à chaque fois.
On utilise bien la fonction read() pour lire l’entrée de l’utilisateur en allouant de la mémoire dans le buffer et en crééant un tableau de 128 octets pour stocker l'entrée de l'utilisateur. 
On s'assure aussi d'enlever le saut de ligne (\n) qui est ajouté automatiquement à la fin de la chaîne lorsque l'utilisateur appuie sur "Entrée" pour ne pas fausser l'exécution de fonctions comme execvp qui attend une chaîne correctement formatée. On le remplace par un caractère de fin de chaîne (\0). Cela garantit que la commande est proprement terminée et prête à être interprétée sans inclure de caractères indésirables.

2. Exécution des commandes simples
Ce que j’ai fait :
J’ai implémenté la gestion de commandes simples en utilisant fork pour créer un processus fils et execvp pour exécuter les commandes entrées par l’utilisateur.

Difficultés rencontrées et solution :
L’une des premières difficultés rencontrées a été la gestion des erreurs dans execvp et le traitement des commandes non valides. De plus, il fallait s'assurer que le processus parent attendait la fin du processus fils pour revenir au prompt.
J’ai utilisé la fonction waitpid pour synchroniser l’exécution et attendre que le processus fils se termine. Pour gérer les erreurs d’exécution, j’ai intégré des vérifications après l'appel à execvp pour afficher des messages d'erreur appropriés si la commande échouait.

3. Gestion de la sortie avec exit et <Ctrl>+D
Ce que j’ai fait :
J’ai programmé la gestion de la commande exit et du signal de fin d’entrée (Ctrl+D) pour permettre de quitter proprement le shell avec un message de sortie.

Difficultés rencontrées et solution :
J'ai ensuite utilisé la fonction strcmp pour comparer la commande entrée avec la chaîne "exit". Si une correspondance est trouvée, le programme affiche un message de sortie grâce à write, puis sort proprement de la boucle avec un break.
J'ai également pris en compte le cas où l'utilisateur appuie sur <ctrl>+d, signalé par un retour négatif ou nul de la fonction read (n <= 0). Cela permet de quitter le shell de manière intuitive sans comportement inattendu

4. Affichage du code de sortie ou signal
Ce que j’ai fait :
J’ai implémenté l’affichage du code de sortie de la commande précédente directement dans le prompt sous la forme enseash [exit:0] % ou enseash [sign:9] % pour signaler l’arrêt anormal d’un processus.

Difficultés rencontrées et solution :
Il y a eu une difficulté à correctement récupérer le signal retourné par le processus. J'ai crée un fichier c "crash_program" qui alloué de la mémoire à un endroit non autorisé pour réaliser un segfault et récupérer le signal d'arrêt anormal du processus.
J’ai utilisé WEXITSTATUS(status) et WTERMSIG(status) sur la variable status retournée par waitpid pour obtenir respectivement le code de sortie et le signal d’arrêt. Ces informations ont été affichées après l'exécution de chaque commande.

5. Mesure du temps d'exécution
Ce que j’ai fait :
J’ai mesuré le temps d’exécution des commandes en utilisant clock_gettime avant et après l’appel à execvp, et j'ai affiché ce temps dans le prompt sous la forme enseash [exit:0|10ms] %.

Difficultés rencontrées et solution :
Mesurer le temps d’exécution d’une commande en intégrant la gestion des signaux et du retour du code de sortie a été un challenge afin d’utiliser correctement clock_gettime pour obtenir une mesure précise en millisecondes.
J’ai utilisé clock_gettime(CLOCK_MONOTONIC, &start) avant l'exécution de la commande et clock_gettime(CLOCK_MONOTONIC, &end) après. La différence entre ces deux timestamps m’a permis d’obtenir le temps écoulé en millisecondes. Le résultat était ensuite intégré et affiché dans la console.

6. Exécution de commandes complexes avec arguments
Ce que j’ai fait :
J’ai géré l’exécution de commandes avec des arguments en utilisant strtok pour diviser la chaîne de commande en tokens (arguments) avant de les passer à execvp.

Difficultés rencontrées et solution :
Le traitement des arguments a nécessité une bonne gestion de la mémoire et des erreurs possibles lors de la tokenisation des entrées. Il fallait s'assurer que la commande était bien formatée.
J’ai utilisé la fonction strtok pour découper la commande entrée en token en fonction des espaces, qui sont ensuite stockés dans le tableau d'arguments args qui est à son tour passé à execvp pour executer la commande. J'ai également ajouté des vérifications pour garantir que l'entrée était correcte avant l'exécution.

7. Gestion des redirections > et <
Ce que j’ai fait :
J’ai implémenté la gestion des redirections de flux > (sortie) et < (entrée) à l’aide de deux sous-fonctions. Ces fonctions recherchent respectivement les opérateurs > et < dans la commande, s'assurent qu'un fichier est bien spécifié après ces opérateurs, puis utilisent la fonction freopen pour rediriger stdout ou stdin vers le fichier approprié.

Difficultés rencontrées et solution :
Une difficulté concernait l'utilisation de freopen pour rediriger les flux. Par exemple, une erreur de fichier manquant provoquait l'échec de la redirection, générant un message d'erreur via perror.
Enfin, il fallait supprimer les opérateurs > et < ainsi que les noms de fichiers dans la liste des arguments pour éviter que ces éléments ne soient transmis à execvp. J'ai résolu cela en remplaçant les positions des opérateurs et des fichiers par NULL, ce qui garantit que seules les commandes et arguments valides sont exécutés (args[i] = NULL)

8. Gestion des pipes |
Ce que j’ai fait :
J’ai créé une fonction dédiée pour gérer les pipes. Il a fallu créer deux processus enfants créés avec fork() pour exécuter respectivement la commande de gauche et celle de droite.
Le premier processus redirige sa sortie standard (stdout) vers l'extrémité d'écriture du pipe grâce à dup2(), tandis que le second redirige son entrée standard (stdin) vers l'extrémité de lecture du pipe. 

Difficultés rencontrées et solution :
Une difficulté majeure a été de bien gérer les fermetures des extrémités inutilisées du pipe dans chaque processus pour éviter les blocages. J'ai aussi ajouté des messages d'erreurs appropriés afin de traiter le cas de commandes invalides ou d'arguments manquants.
Enfin, on synchronise les processus via waitpid pour garantir que les deux commandes s'exécutent correctement avant de retourner le contrôle à l'utilisateur.


Conclusion :
Ce TP m’a permis de renforcer mes compétences en gestion des processus, en particulier pour la manipulation des pipes, des redirections et la gestion des processus fils et pères. Les principales difficultés étaient liées à la gestion des descripteurs de fichiers et à la synchronisation des processus. La fonction strtok pour exécuter des commandes complexes avec plusieurs arguments était aussi un enjeu à relever. Grâce à une approche modulaire, j’ai pu structurer le code en sous-fichiers et résoudre ces problèmes de manière efficace.
