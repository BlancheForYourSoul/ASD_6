#define MAX 40
#define size 10

typedef struct edge {
    int u, v, w;
} edge;

typedef struct edge_list {
    edge data[MAX];
    int c;
} edge_list;

edge_list elist;

int Graph[MAX][MAX];
edge_list spanlist;



void kruskalAlgo();
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2);
void sort();
void print();

//Kruskal Algoritm
void kruskalAlgo(){
    int belongs[MAX], a, b, check1, check2;
    elist.c = 0;

    printf("\n_______________\nAll edges:\n");
    for (a = 1; a < size; a++) {
        for (b = 0; b < a; b++) {
            if (Graph[a][b] != 0) {
                printf("#%d : %d - %d : %d\n",elist.c, a, b, Graph[a][b]);
                elist.data[elist.c].u = a;
                elist.data[elist.c].v = b;
                elist.data[elist.c].w = Graph[a][b];
                elist.c++;
            }
        }
    }

    sort();

    for (a = 0; a < size; a++) {
        belongs[a] = a;
    }

    spanlist.c = 0;

    for (a = 0; a < elist.c; a++) {

        check1 = find(belongs, elist.data[a].u);
        check2 = find(belongs, elist.data[a].v);

        if (check1 != check2) {
            spanlist.data[spanlist.c] = elist.data[a];
            spanlist.c++;
            applyUnion(belongs, check1, check2);
        }
    }
}

int find(int belongs[], int vertexno) {
    return (belongs[vertexno]);
}

void applyUnion(int belongs[], int c1, int c2) {
    int i;

    for (i = 0; i < size; i++) {
        if (belongs[i] == c1) {
            belongs[i] = c2;
        }
    }
}

// Sorting algo
void sort() {
    int i, j;
    edge temp;

    for (i = 1; i < elist.c; i++) {
        for (j = 0; j < elist.c - 1; j++) {
            if (elist.data[j].w > elist.data[j + 1].w) {
                temp = elist.data[j];
                elist.data[j] = elist.data[j + 1];
                elist.data[j + 1] = temp;
            }
        }
    }
}

// Printing the result
void print() {
    int i, cost = 0;

    printf("\n_______________\nUsed edges:\n");
    for (i = 0; i < spanlist.c; i++) {
        printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
        cost += spanlist.data[i].w;
    }

    printf("\nSpanning tree cost: %d", cost);
}
