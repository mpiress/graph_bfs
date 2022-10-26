#include "bfs.h"


//// procs FILA

Fila* FFVazia(){
  Fila *f = (Fila*) malloc(sizeof(Fila));
  f->head = NULL;
  f->tail = NULL;
  return f;
}

void Queue(Fila *f, int vertex){
  Item *d = (Item *) malloc (sizeof(Item));
  d->data = vertex;
  d->prox = NULL;

  if(f->head == NULL){
    f->head = d;
    f->tail = d;
  }else{
    f->tail->prox = d;
    f->tail = d;
  }

  f->size ++;
}

Item* Dequeue(Fila *f){
  Item *aux;

  if(f->head == NULL)
    return NULL;

  aux = f->head;
  f->head = f->head->prox;
  f->size --;

  return aux;
}

//// fim procs FILA

// procs para tratar com grafos 

Vertex VertexInitialize(int value){
  Vertex v = malloc (sizeof(Vertex));
  v->value = value;
  v->prox  = NULL;
  return v;
}

Graph GraphInitialize(int V){
  Graph G = malloc (sizeof(Graph));
  G->V = V;
  G->E = 0;
  G->adj = malloc(V * sizeof(Vertex));

  for(int v=0; v<V; v++)
    G->adj[v] = VertexInitialize(v);

  return G;
}

void GraphInsertEdge(Graph G, Vertex v1, Vertex v2){
  Vertex v = G->adj[v1->value];
  
  while(v->prox != NULL){
    if (v->value == v2->value)
      return;
    v = v->prox;
  }

  v->prox = VertexInitialize(v2->value);
  G->E ++;
}

void ImprimeGraph(Graph G){
  Vertex aux;

  for(int v=0; v<G->V; v++){
    aux = G->adj[v];

    while(aux->prox != NULL){
      printf(" %d -> ", aux->value);
      aux = aux->prox;
    }

    printf(" %d ", aux->value);
    printf("\n");
  }
  
}

// fim procs para tratar com grafos
void BFS(Graph G, Vertex s){
  Fila *f = FFVazia();
  int cor[G->V]; //0 Branco, 1 Cinza, 2 Preto
  int d[G->V];
  int pi[G->V]; // -1 == NULL
  
  for(int i=0; i<G->V; i++)
    if(i != s->value){
      cor[i] = 0;
      d[i]   = -1; //infinito
      pi[i]  = -1; // ? não tem pai ainda
    }

  cor[s->value] = 1;
  d[s->value]   = 0;
  pi[s->value]  = -1;

  Queue(f, s->value);

  while (f->size > 0){
    Item *u = Dequeue(f);
    for(Vertex v = G->adj[u->data]; v != NULL; v=v->prox){
      if(cor[v->value] == 0){
        cor[v->value] = 1;
        d[v->value]   = d[u->data] + 1;
        pi[v->value]  = u->data;
        Queue(f, v->value);
      }
    }

    cor[u->data] = 2;
    printf("Vertex:%d Antecessor:%d\n", u->data, pi[u->data]);
  }
}



