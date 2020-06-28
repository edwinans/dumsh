# Parties implementé
Tout les fonctionnalite sont implementé dans le cadre du projet:
- `cd` , `exit` , `>1` et `>2` .
- En l'absence de redirection de sortie, dumsh affichera la sortie standard en vert et la sortie erreur en rouge. 
- La sortie standard et l'erreur standard sont a priori entremêlées (ls -R >1 fic).
- Toutes les lectures/écritures sont réalisées en bas niveau (sauf en mode debogage fonction print_args).

## Choix d'implementation

#### Navigation:
La navigation dans le DUMSH ce fait avec des appelle de fonction `getcwd` pour recupere le chemin absolu et `chdir` pour naviguer avec un `cédérom` (la seule différence avec le bash et la commande `cd` sans arg qui dans notre cas nous deplace vers la root `/` a la place de`~`).

#### Couleur:
Pour gérer les bonnes couleurs j'ai implementer plusieurs fonctions avec quelque MACRO afin de les appeler dans le nécessaire (`print_out` en vert , `print_err` en rouge et `print_blue` en bleu).
la seule difficulté était le cas de couleur sans redirection pour cela je redirige la STDERR vers un fichier temporaire "tmp" qui serait à la fin supprimer ensuite j'affiche d'abbord la STDOUT de la commande en vert et après on affiche le contenu de fichier Tmp sur STDERR et en rouge.

#### Interface continue:
Pour bien implementer la partie "L'invite du shell dans ce cas ne devra pas revenir avant la fin de l'affichage" on utilise les fonctions:
`fork` , `execvp`, `wait` .
Pour pouvoir attendre la fin de l'execution d'une commande externe avant de re-afficher l'interface du DUMSH. (voir le grand `switch(fork())` dans `exec_line`).

#### annexe:

- Affichage du chemin cours apres l'utilisation de `cd` dans l'interface.

- Implementation d'un propre spliter qui ignore tout type d'espace (Space characters en C).

- Utilisation des fonction de bas-niveau (`read`, `write`, `close`...) pour tout le projet sans appelle a la fonction `system`.

- Un seul buffeur (`buf`) de taille `BUFZ=1024` dans tout le code.






