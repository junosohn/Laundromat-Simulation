#ifndef LOADQUEUE_H
#define LOADQUEUE_H
#include "Load.h"

class LoadQueue
{
    public:
        LoadQueue();
        virtual ~LoadQueue();
        struct Node
        {
            Load *data;
            Node *link;
        };
        void push_load(Load*);
        Load* pop_load();
        bool queue_empty();
    private:
        Node* head;
};

#endif // LOADQUEUE_H
