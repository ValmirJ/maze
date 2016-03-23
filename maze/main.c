#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //Para idioma pt-br

#define QTD 100

struct point{
    int x;
    int y;
};
typedef struct point Point;

struct pilha{
    Point p[QTD];
    int topo;
};
typedef struct pilha Pilha;

struct boolPos {
    int left;
    int bottom;
    int right;
    int top;
};
typedef struct boolPos BoolPos;


Point pop(Pilha *p1);
int push(Pilha *p1, Point w);
Point searchEntry(int l, int c, char m[][c]);
void checkPositions(BoolPos *s, Point c, int lin, int col, char maze[][col]);

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivo;
    int lin, col;
    char **maze;
    Point pos;
    Pilha ways;
    ways.topo = 0;
    BoolPos currentSituation;
    int i, j;
    arquivo = fopen("labirinto.txt", "r");
    if(arquivo == NULL)
        printf("Erro ao carregar o labirinto, arquivo não pode ser aberto.");
    else {
        fscanf(arquivo, "%i %i", &lin, &col);
        printf("Labirinto %i x %i\n\n", lin, col);

        char (*maze)[col] = (char(*)[col]) malloc(sizeof(char)*lin*col);

        for(i=0; i<lin; i++)
        {
            fscanf(arquivo, "%s", maze[i]);
        }

        pos = searchEntry(lin, col, maze);

        if(pos.x == -1 && pos.y == -1)
            printf("\nNão há entrada para esse labirinto, impossível continuar");
        else {
            push(&ways, pos);
        }
        pos = pop(&ways);
        printf("%i x %i", pos.x, pos.y);
    }

    free(maze);
    fclose(arquivo);

    system("Pause");
    return 0;
}

//Functions
Point pop(Pilha *p1) {
    Point r;

    if(p1->topo == 0) {
        r.x = -1;
        r.y = -1;
    }
    else {
        p1->topo--;
        r.x = p1->p[p1->topo].x;
        r.y = p1->p[p1->topo].y;
    }
    return r;
}
int push(Pilha *p1, Point w) {
    if(p1->topo == QTD)
        return 0;
    p1->p[p1->topo].x = w.x;
    p1->p[p1->topo].y = w.y;
    p1->topo++;
    return 1;
}

Point searchEntry(int l, int c, char m[][c]) {
    Point e;
    int i, j;
    e.x = -1;
    e.y = -1;
    for(i=0; i<l; i++) {
        for(j=0; j<c; j++)
        {
            printf("%c ", m[i][j]);

            if(m[i][j] == 'e') {
                e.x = i;
                e.y = j;
            }
        }
        printf("\n");
    }
    return e;
}

void checkPositions(BoolPos *s, Point c, int lin, int col, char maze[][col]){
    s->left = 0;
    s->bottom = 0;
    s->right = 0;
    s ->top = 0;
    if(c.y + 1 <= lin && maze[c.x][c.y+1] == " ")
        //empilha e marca um 'V' de visitado
        ;
}

