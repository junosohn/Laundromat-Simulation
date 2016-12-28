#include "LoadQueue.h"
#include <cstddef>
#include <iostream>

using namespace std;

LoadQueue::LoadQueue()
{
    head = NULL;
}

LoadQueue::~LoadQueue()
{
    //dtor
}

// Create a new node and cycle through the current nodes to find
// a node that is null. Insert the node in the empty spot.
void LoadQueue::push_load(Load* load)
{
    Node* current_node = head;
    Node* new_node = new Node;
    new_node->data = load;
    new_node->link = NULL;

    if(queue_empty())
    {
        head = new_node;
    }
    else
    {
        while(current_node->link != NULL)
        {
            current_node = current_node->link;
        }

        current_node->link = new_node;
    }

}

Load* LoadQueue::pop_load()
{
    if(queue_empty())
    {
        //cout << "Queue is empty" << endl;
        return NULL;
    }

    Load* load_temp = head->data;
    Node* node_temp = head;
    head = node_temp->link;
    delete node_temp;
    return load_temp;
}

bool LoadQueue::queue_empty()
{
    if(head == NULL)
    {
        return true;
    }
    return false;
}
