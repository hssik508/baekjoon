#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* prev;
    Node* next;
};

class List
{
private:
    Node* head;
    Node* tail;
public:
    List()
    {
        head=nullptr;
    }
    void addfront(int data)
    {
        if (head==nullptr)
        {
            Node* newNode = new Node;
            newNode->data=data;
            newNode->prev=nullptr;
            newNode->next=nullptr;
            head = newNode;
            tail = newNode;
        }
        else
        {
            Node* newNode = new Node;
            newNode->data=data;
            newNode->next=head;
            
        }
    }
};



int main()
{

}