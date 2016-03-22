#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //Para idioma pt-br
#include <point.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivo;
    int lin, col;
    char **maze;
    Point p;
    int i, j;
    arquivo = fopen("labirinto.txt", "r");
    if(arquivo == NULL)
        printf("Erro ao carregar o labirinto, arquivo não pode ser aberto.");
    else {
        fscanf(arquivo, "%i %i", &lin, &col);
        printf("%i", col);

        maze=(char **) malloc(lin*sizeof(char *));    //ALOCAÇÃO DINÂMICA DA MATRIZ
        for(i=0;i<10;i++)
            maze[i]=(char *) malloc(col*sizeof(char));

        for(i=0; i<lin; i++)
        {
            fscanf(arquivo, "%s", maze[i]);
        }

        for(i = 0; i<lin; i++) {
            for(j=0; j<col; j++)
                printf("%c  ", maze[i][j]);
            printf("\n");
        }
    }

    free(maze);
    fclose(arquivo);

    system("Pause");
}
