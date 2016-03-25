#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //Para idioma pt-br

#define FALSE 0
#define TRUE 1
typedef int bool;

#define MAZE_WALL 'p'
#define MAZE_IN 'e'
#define MAZE_OUT 's'
#define MAZE_WAY 'b'

struct point{
    int x;
    int y;
};
typedef struct point Point;

struct stack{
    Point *p;
    int topo;
};
typedef struct stack Stack;

struct boolPos {
    int left;
    int bottom;
    int right;
    int top;
};
typedef struct boolPos BoolPos;

// Stack
Stack* createStack(int size);
bool pop(Stack *p1, Point *point);
void push(Stack *p1, Point w);
void deinitStack(Stack *s);

// Helpers
bool searchEntry(int l, int c, char m[][c], Point *point);
void checkPositions(BoolPos *s, Point *c, int lin, int col, char maze[][col]);

int main() {
    setlocale(LC_ALL, "Portuguese");
    int lin, col;
    Point pos;
    Stack *ways;
    BoolPos currentSituation;
    int i, j;

    FILE *arquivo;
    arquivo = fopen("labirinto.txt", "r");

    if(arquivo == NULL) {
        printf("Erro ao carregar o labirinto, arquivo não pode ser aberto.");
        return 0;
    }

    fscanf(arquivo, "%i %i", &lin, &col);
    printf("Labirinto %i x %i\n\n", lin, col);

    // Alocate +1 to acomodate the \0 at end of final line
    char (*maze)[col] = (char(*)[col]) malloc((sizeof(char)*lin*col) + 1);

    for(i=0; i<lin; i++) {
        fscanf(arquivo, "%s", maze[i]);
    }

    if (searchEntry(lin, col, maze, &pos) == FALSE) {
        printf("\nNão há entrada para esse labirinto, impossível continuar");
        return 0;
    }

    ways = createStack(lin * col);
    push(ways, pos);

    while(maze[pos.x][pos.y] != MAZE_OUT) {
        checkPositions(&currentSituation, &pos, lin, col, maze);

        if(maze[pos.x][pos.y] == MAZE_WAY) {
            maze[pos.x][pos.y] = 'v'; //Move
        }

        printf("\nTentativa: %i x %i", pos.x, pos.y);

        if(currentSituation.left == 0 && currentSituation.bottom == 0 && currentSituation.right == 0 && currentSituation.top == 0) {
            if (pop(ways, &pos) == FALSE) {
                printf("Entrada encontrada não leva para uma saída!\n");
                return 0;
            }
        } else {
            push(ways, pos);
        }
    }

    printf("\n\nLabirinto descoberto com sucesso!\nO caminho é:\n\n");

    while(pop(ways, &pos) == TRUE) {
        printf("%iº passo: %i x %i\n", ways->topo +1, pos.x, pos.y);
    }

    deinitStack(ways);
    printf("\n\n");

    free(maze);
    fclose(arquivo);

    system("Pause");
    return 0;
}

// Stack Functions
Stack* createStack(int size) {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s->p = (Point*) malloc(sizeof(Point) * size);
    s->topo = 0;

    return s;
}

bool pop(Stack *p1, Point *point) {
    if(p1->topo == 0) {
        return FALSE;
    }

    p1->topo--;
    point->x = p1->p[p1->topo].x;
    point->y = p1->p[p1->topo].y;

    return TRUE;
}

void push(Stack *p1, Point w) {
    p1->p[p1->topo].x = w.x;
    p1->p[p1->topo].y = w.y;
    p1->topo++;
}

void deinitStack(Stack *s) {
    free(s->p);
    free(s);
}

// Helpers
bool searchEntry(int l, int c, char m[][c], Point *point) {
    int i, j;
    bool found = FALSE;
    char current;

    for(i=0; i<l; i++) {
        for(j=0; j<c; j++) {
            current = m[i][j];

            if(current == MAZE_IN && found == FALSE) {
                point->x = i;
                point->y = j;
                found = TRUE;
                printf("%c", toupper(current));
            } else {
                switch (current) {
                    case MAZE_WALL:
                        printf("#");
                        break;
                    case MAZE_OUT:
                        printf("S");
                        break;
                    case MAZE_IN:
                        printf("e");
                        break;
                    default:
                        printf(" ");
                        m[i][j] = MAZE_WAY;
                        break;
                }
            }
        }
        printf("\n");
    }

    return found;
}

void checkPositions(BoolPos *s, Point *c, int lin, int col, char maze[][col]){
    s->left = 0;
    s->bottom = 0;
    s->right = 0;
    s ->top = 0;

    if((c->y + 1 <= lin) && (maze[c->x][c->y+1] == MAZE_WAY || maze[c->x][c->y+1] == MAZE_OUT )) {
        s->left = 1;
        c->y += 1;
        return;
    }
    if((c->x + 1 <= col) && (maze[c->x +1][c->y] == MAZE_WAY|| maze[c->x+1][c->y] == MAZE_OUT)) {
        s->bottom = 1;
        c->x += 1;
        return;
    }
    if((c->y - 1 >= 0) && (maze[c->x][c->y-1] == MAZE_WAY || maze[c->x][c->y-1] == MAZE_OUT)) {
        s->right = 1;
        c->y -= 1;
        return;
    }
    if((c->x -1 >= 0) && (maze[c->x-1][c->y] == MAZE_WAY) || maze[c->x-1][c->y] == MAZE_OUT) {
        s->top = 1;
        c->x -= 1;
    }
}
