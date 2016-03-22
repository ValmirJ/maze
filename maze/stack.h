#ifdef STACK
#include "point.h"
#define STACK

#define QTD 100

typedef struct {
    Point p[QTD];
    int topo;
} Pilha;

Point pop() {
    Point r;
    if(topo == 0) {
        r.x = -1;
        r.y = -1;
    }
    else {
        r.x = p[topo].x;
        r.y = p[topo].y;
        topo--;
    }
    return r;
}
int push(int x, int y) {
    if(topo == QTD-1)
        return 0;
    p[topo].x = x;
    p[topo].y = y;
    return 1;
}

#endif
