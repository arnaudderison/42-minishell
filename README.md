```
 ___      ___   __    _____  ___    __      ________  __    __   
|"  \    /"  | |" \  (\"   \|"  \  |" \    /"       )/" |  | "\  
 \   \  //   | ||  | |.\\   \    | ||  |  (:   \___/(:  (__)  :) 
 /\\  \/.    | |:  | |: \.   \\  | |:  |   \___  \   \/      \/  
|: \.        | |.  | |.  \    \. | |.  |    __/  \\  //  __  \\  
|.  \    /:  | /\  |\|    \    \ | /\  |\  /" \   :)(:  (  )  :) 
|___|\__/|___|(__\_|_)\___|\____\)(__\_|_)(_______/  \__|  |__/

par des minishtres pour des minishtres

```
```
message a plach: ssh-keygen -t ed25519 -C "your_email@example.com"
```
😳 [Plachard](https://github.com/Lopine)

🔦 [Aderison](https://github.com/arnaudderison)

# Tokenisation

### 1. **Structure d'un token**
Chaque token doit contenir des informations importantes comme le type de token (commande, argument, redirection, etc.) et la valeur littérale. Une structure simple en C pourrait ressembler à ceci :

```c
typedef enum {
    TOKEN_COMMAND,
    TOKEN_ARGUMENT,
    TOKEN_PIPE,
    TOKEN_REDIRECTION_INPUT,
    TOKEN_REDIRECTION_OUTPUT,
    TOKEN_REDIRECTION_APPEND,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_END
} TokenType;

typedef struct s_token {
    TokenType type;        // Type de token (commande, argument, etc.)
    char *value;           // Valeur du token (texte littéral)
    struct s_token *next;  // Pointeur vers le prochain token (pour une liste chaînée)
} t_token;
```

Cette structure te permet de stocker le type de chaque token ainsi que sa valeur associée. Tu peux ajouter un pointeur vers le token suivant pour une gestion en liste chaînée.

### 2. **Liste chaînée pour stocker les tokens**
Une liste chaînée est idéale pour stocker les tokens, car elle permet de facilement ajouter des éléments au fur et à mesure que tu les trouves pendant l'analyse de la ligne de commande. Voici une structure pour gérer cette liste :

```c
typedef struct s_token_list {
    t_token *head;   // Pointeur vers le premier token
    t_token *tail;   // Pointeur vers le dernier token pour ajouter rapidement
} t_token_list;
```

#### Avantages :
- **Ajout facile** : Ajouter des tokens à la liste est simple, surtout si tu gardes un pointeur vers le dernier élément (la `tail`).
- **Parcours linéaire** : Facile à parcourir pour ensuite traiter ou exécuter les commandes.

#### Fonction pour ajouter un token à la liste :
```c
void add_token(t_token_list *list, TokenType type, char *value) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return; // Gestion des erreurs de malloc
    new_token->type = type;
    new_token->value = strdup(value);
    new_token->next = NULL;

    if (list->head == NULL) {
        list->head = new_token;
        list->tail = new_token;
    } else {
        list->tail->next = new_token;
        list->tail = new_token;
    }
}
```

### 3. **Tableau dynamique pour les arguments**
Pour gérer les arguments d'une commande spécifique, tu peux utiliser un tableau dynamique (comme un tableau de pointeurs `char**` en C). Cela te permet de stocker chaque argument d'une commande de manière contiguë en mémoire, ce qui facilite l'exécution via `execvp()` ou d'autres fonctions.

Tu peux regrouper ces arguments avec la commande sous une structure qui représentera chaque "commande" complète, incluant ses arguments et éventuellement ses redirections.

```c
typedef struct s_command {
    char **argv;        // Tableau dynamique d'arguments (argv[0] = commande)
    char *input_file;   // Fichier pour redirection d'input (<)
    char *output_file;  // Fichier pour redirection d'output (>)
    int append_output;  // 1 si c'est une redirection avec ">>"
} t_command;
```

### 4. **Structure globale pour le parsing**
Une fois que tu as tous les tokens, tu peux les convertir en structures de commandes plus complexes, comme des pipelines ou des séquences de commandes avec des opérateurs logiques (comme `&&`, `||`, etc.).

Voici une structure pour gérer des pipelines de commandes :

```c
typedef struct s_pipeline {
    t_command **commands;  // Tableau de pointeurs vers des commandes (pipeline)
    int num_commands;      // Nombre de commandes dans le pipeline
    struct s_pipeline *next;  // Pointeur vers le pipeline suivant (pour les ; et &&)
} t_pipeline;
```

### 5. **Exemple d'utilisation**
Tu pourrais avoir une fonction qui convertit ta liste de tokens en une série de commandes ou de pipelines à exécuter :

1. **Étape de tokenisation** : Analyse la ligne de commande en tokens et crée une liste chaînée de tokens.
2. **Étape de parsing** : Parcours la liste de tokens pour créer des structures de commandes ou de pipelines.
3. **Étape d'exécution** : Utilise les structures de commandes/pipelines pour invoquer `fork()`, `exec()` et gérer les redirections.

### Conclusion
Voici un aperçu des structures principales pour gérer la tokenisation dans **minishell** :
- **t_token** : Représente un token individuel.
- **t_token_list** : Liste chaînée de tokens.
- **t_command** : Représente une commande avec ses arguments et ses redirections.
- **t_pipeline** : Gère un pipeline de commandes.

Ces structures te permettront de bien gérer l'analyse syntaxique des commandes et leur exécution dans ton minishell.
# Shources
[Medium](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

[GitBook](https://42-cursus.gitbook.io/guide/rank-03/minishell)

