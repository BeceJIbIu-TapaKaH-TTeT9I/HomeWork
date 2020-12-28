#include <iostream>

template <typename dataType>
class Stack // Стэк, реализованный на основе динамического массива
{
    private:
        
        unsigned int maxSizeStack; // Максимально возможный размер массива/стэка, задается в начале
        unsigned int numberTopStack; // Номер элемента на веришне стэка (+ 1 = кол-во элементов в стеке)
        dataType *arrayStack; // Указатель для динамического массива

        /////////// errorStack

        void errorStack(unsigned int codeExit) // Вывод ошибки
        {
            switch (codeExit)
            {
                case 1: std::cout << std::endl << "Stack Overflow" << std::endl; break;
                case 2: std::cout << std::endl << "Stack Underflow" << std::endl; break; 
                case 3: std::cout << std::endl << "Stack is empty" << std::endl; break; // По факту, пустой стэк - это не ошибка, если не убирать из него элементы
            }
            exit(1);
        }

    public:

        /////////// Stack

        Stack(const unsigned int inSize) // Конструктор класса Stack
        {
            maxSizeStack = inSize; // Задание максимально возможного размера стэка
            numberTopStack = 0;
            arrayStack = new dataType[inSize]; // Выделение памяти под стэк
        }

        /////////// push

        void push(const dataType newElementStack) // Добавление элемента на вершину стэка, если в массиве есть место
        {
            if (numberTopStack + 1 <= maxSizeStack) // Проверка на наличие места в массиве
            {
                arrayStack[numberTopStack] = newElementStack;
                numberTopStack++;
            }
            else // элемент некуда, стэк заполнен - ошибка "Stack Overflow"
            {
                errorStack(1);
            }
        }

        /////////// pop

        void pop() // Удаление элемента с вершины стэка, если в нем есть хотя бы 1 элемент
        {
            if (numberTopStack >= 1) // Проверка на наличие элементов в стэке
            {
                numberTopStack--;
            }
            else // удалять элемент неоткуда, т.к. стэк пуст - ошибка "Stack Underflow"
            {
                errorStack(2);
            }
        }

        /////////// size

        unsigned int size() // Вывод количества элементов стэка
        {
            return numberTopStack;
        }

        /////////// top

        dataType top() // Вывод элемента на вершине стэка, если в нем есть хотя бы 1 элемент
        {
            if (numberTopStack == 0) // Если стэк пуст, то выводить нечего - ошибка "Stack is empty"
            {
                errorStack(3);
            }
            else
            {
                return arrayStack[numberTopStack - 1];
            }
        }

        /////////// print

        void print() // Вывод всех элементов стэка, если в нем есть хотя бы 1 элемент
        {
            if (numberTopStack == 0) // Если стэк пуст, то выводить нечего - ошибка "Stack is empty"
            {
                errorStack(3);
            }
            else
            {
                std::cout << std::endl << "The stack consists of " << numberTopStack << " elements:" << std::endl;
                for (unsigned int i = 0; i < numberTopStack; i++)
                {
                    std::cout << arrayStack[i] << std::endl;
                }
            }
        }

        /////////// clear

        void clear() // Очитка памяти от массива/стэка
        {
            std::cout << std::endl << "Clearing the stack..." << std::endl;
            delete arrayStack;
            numberTopStack = 0;
            std::cout << std::endl << "The stack consists of " << numberTopStack << " elements." << std::endl;
        }
};

 int main()
{
    Stack<int> stack(10);

    std::cout << "The stack consists of " << stack.size() << " elements." << std::endl;

    stack.push(0);
    stack.push(-20);
    stack.push(300);
    stack.push(5);

    stack.print();

    stack.pop();
    stack.pop();

    stack.print();

    std::cout << std::endl << "Element at the top of the stack: " << stack.top() << std::endl;

    stack.clear();

    stack.pop();

    return 0;
}
