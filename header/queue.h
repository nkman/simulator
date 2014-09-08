#ifndef _HEADER_QUEUE_H
#define _HEADER_QUEUE_H

struct Node{
    Process P;
    struct Node* next;
};
typedef struct Node node;


struct queue{
       node* front;
       node* back;      
};


void initialise(struct queue *q)
{
  (*q).front=(*q).back=0;
}
 
  
void enqueue(struct queue *q, Process a)
{  
   node* p = (node*)malloc(sizeof(node));
   p->next=0;
   p->P=a;
   
   if((*q).front==0) {(*q).front=(*q).back=p;return;}
   
   if((*q).front==(*q).back) {
                     (*q).front=p;
                     (*q).back->next=p;
                     return ; 
                   }

   (*q).front->next=p;
   (*q).front=p;
   return ;
}


Process* dequeue(struct queue *q)
{    
   Process* p=0;

   if((*q).front==0) {return 0;}
   
   if((*q).front==(*q).back) {
                     p=&((*q).front->P);      
                     (*q).front=(*q).back=0;
                     return p; 
                   }

    p=&((*q).back->P);
    (*q).back=(*q).back->next;
   return p;
}

/*
void Print(struct queue *q)
{ 
   if((*q).front==0){printf("Empty\n");
   return; }

   node* p=(*q).back;
   while(p)
   {
   	printf("%d ",p->P);
   	p=p->next;
   }printf("\n");
}*/

#endif /* _HEADER_QUEUE_H */