#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class Stack
{
public:
    int max_height;
    T *base;
    int top = 0;

    Stack(int set_max_height)
    {
        this->max_height = set_max_height;
        this->base = (T *)calloc(max_height, sizeof(T));
        this->top = 0;
    }

    void push(T pushed)
    {
        if (top >= max_height)
        {
            cout << "Stack is full" << endl;
            return;
        }

        else
        {
            this->base[top] = pushed;
            top += 1;
        }
    }

    void pop()
    {
        if (top == 0)
        {
            cout << "Stack is empty" << endl;
            return;
        }

        this->base[top] = 0;
        top -= 1;
    }

    void print(T *stack_base)
    {
        for (int i = 0; i < top; i++)
        {
            cout << stack_base[i] << " ";
        }
        cout << endl;
    }
};

template <class U>
class Queue
{
public:
    int max_height;
    U *base;
    int front = 0;
    int rear = 0;
    int count = 0;

    Queue(int set_max_height)
    {
        this->max_height = set_max_height;
        this->base = (U *)calloc(set_max_height, sizeof(U));
    }

    void enqueue(U pushed)
    {
        if (this->count >= this->max_height)
        {
            cout << "Queue is full" << endl;
            return;
        }

        else
        {

            this->base[rear] = pushed;
            this->rear += 1;
            this->count += 1;
        }
    }

    void dequeue()
    {

        if (this->count <= 0)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        this->base[front] = 0;

        for (int i = 0; i < this->count; i++)
        {
            this->base[i] = this->base[i + 1];
        }

        this->front += 1;
        this->count -= 1;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << this->base[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Stack<int> stack(4);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.print(stack.base);
    stack.pop();
    stack.print(stack.base);

    Stack<char> stack2(4);
    stack2.push('a');
    stack2.push('b');
    stack2.push('c');
    stack2.push('d');
    stack2.print(stack2.base);
    stack2.pop();
    stack2.print(stack2.base);

    Queue<int> queue(4);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.print();
    queue.dequeue();
    queue.print();

    Queue<char> queue2(4);
    queue2.enqueue('a');
    queue2.enqueue('b');
    queue2.enqueue('c');
    queue2.enqueue('d');
    queue2.print();
    queue2.dequeue();
    queue2.print();
    
    return 0;
}
