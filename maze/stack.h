#ifdef STACK
#define STACK

#define QTD 100

typedef struct {
    Point p[QTD];
    int topo;
} Pilha;

Point pop();
int push(int x, int y);

#endif
