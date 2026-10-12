# get_next_line

`get_next_line` est un projet 42 qui consiste à lire un fichier ligne par ligne, en ne gardant en mémoire que le strict nécessaire entre deux appels, il reprend le comportement de get_line.

## Objectif

Le but est d'implémenter une fonction capable de :

- lire depuis un descripteur de fichier
- retourner une ligne complète à chaque appel
- conserver le reste du texte pour l'appel suivant
- gérer correctement la fin de fichier et les erreurs

## Fichiers

- `get_next_line.c` : implémentation principale de `get_next_line`
- `get_next_line_utils.c` : fonctions utilitaires de manipulation de chaînes
- `get_next_line.h` : prototype de la fonction et constantes du projet

## Fonction attendue

La fonction principale suit cette forme :

```c
char *get_next_line(int fd);
```

Elle retourne :

- une ligne lue depuis le fichier, avec le `\n` s'il est présent
- `NULL` à la fin du fichier ou en cas d'erreur

```bash
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1000000
```

Tu peux adapter `BUFFER_SIZE` selon tes besoins ou les contraintes du sujet.

## Utilisation

Exemple simple :

```c
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

## Comportement

Le projet s'appuie sur :

- une zone de stockage intermédiaire entre les appels
- la recherche du premier saut de ligne
- l'extraction de la ligne retournée
- la conservation du reste pour l'appel suivant
