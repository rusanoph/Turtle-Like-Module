//---For-Turtle-module-realization-21.04.2021---
//--------------------STACK---------------------
typedef struct {
    int MAX;    // Top of stack
    int tos;    // Current stack element index
    TDrawer *stack; // Array of stack elements
} Tstack_Drawer;

void InitDrawerStack(Tstack_Drawer *obj, int tos, int MAX)
{   // Setter
    obj->tos = tos;
    obj->MAX = MAX;
    obj->stack = (TDrawer*)malloc(sizeof(TDrawer) * MAX);
}

void push_Drawer(Tstack_Drawer *stackD, TDrawer *d)
{
    if (stackD->tos >= stackD->MAX)
    {
        printf("Stack Overflow!");
        return;
    }
    // Add current statement of object d
    // and increment stack index
    setD(&stackD->stack[stackD->tos], d);
    stackD->tos += 1;
}

void pop_Drawer(Tstack_Drawer *stackD, TDrawer *obj)
{
    stackD->tos -= 1;
    if (stackD->tos < 0)
    {   // If stack is empty return it index
        // to last position
        printf("Stack is empty!");
        stackD->tos += 1;
    }
    setD(obj, &stackD->stack[stackD->tos]);

}
//--------------------STACK---------------------
