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

Point pop(Pilha p1);
int push(Pilha *p1, Point w);
Point searchEntry(int l, int c, char m[][c]);

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivo;
    int lin, col;
    char **maze;
    Point pos;
    Pilha ways;
    int i, j;
    arquivo = fopen("labirinto.txt", "r");
    if(arquivo == NULL)
        printf("Erro ao carregar o labirinto, arquivo n�o pode ser aberto.");
    else {
        fscanf(arquivo, "%i %i", &lin, &col);
        printf("%i", col);

        char (*maze)[col] = (char(*)[col]) malloc(sizeof(char)*lin*col);

        for(i=0; i<lin; i++)
        {
            fscanf(arquivo, "%s", maze[i]);
        }

        pos = searchEntry(lin, col, maze);

        if(pos.x == -1 && pos.y == -1)
            printf("\nN�o h� entrada para esse labirinto, imposs�vel continuar");
        else {
            push(&ways, pos);
        }
    }

    free(maze);
    fclose(arquivo);

    system("Pause");
    return 0;
}

//Functions
Point pop(Pilha p1) {
    Point r;
    if(p1.topo == 0) {
        r.x = -1;
        r.y = -1;
    }
    else {
        r.x = p1.p[p1.topo].x;
        r.y = p1.p[p1.topo].y;
        p1.topo--;
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

