#include <iostream>

template<typename keyBased, typename dataType>
class BinTree // Двоичное дерево
{
    private:

        template<typename keyBased, typename dataType>
        class Node // Узел дерева
        {
            public:

                keyBased key; // Ключ (Дерево сортируются по ключу, данные могут быть любыми)
                dataType data; // Данные
                Node* left; // Адрес левого потомка
                Node* right; // Адрес правого потомка

                /////////// Node

                Node(keyBased key = keyBased(), dataType data = dataType(), Node *left = nullptr, Node *right = nullptr) // Конструктор класса Node
                {
                    this->key = key;
                    this->data = data;
                    this->left = left;
                    this->right = right;
                }
        };

        unsigned int currentSize; // Текущий размер списка (количество элементов в дереве)
        Node<keyBased, dataType> *root; //Корень дерева (Узел, который не имеет родителей)

        /////////// errorBinTree

        void errorBinTree(unsigned int codeExit) // Вывод ошибки
        {
            switch (codeExit)
            {
            case 2: std::cout << std::endl << "Binary tree Underflow" << std::endl; break;
            case 3: std::cout << std::endl << "Binary tree is empty" << std::endl; break;
            case 4: std::cout << std::endl << "Key is not found" << std::endl; break;
            }
            exit(1);
        }

        /////////// subPush

        void subPush(keyBased key, dataType data, Node<keyBased, dataType> *currentNode) // Рекурсивная функция добавления следующего узла
        {
            if (root == nullptr) // Если добавляется первый узел дерева
            {
                root = new Node<keyBased, dataType>(key, data);
            }
            else // Если же в списке есть узлы
            {
                if (key < currentNode->key) // Если значение ключа меньше, чем значение ключа текущего узла
                {
                    if (currentNode->left == nullptr) // Если текущий элемент не имеет левого потомка, то создается такой потомок
                    {
                        currentNode->left = new Node<keyBased, dataType>(key, data);
                    }
                    else
                    {
                        subPush(key, data, currentNode->left); // Рекурсивный вызов функции для левых потомков
                    }
                }
                else
                {
                    if (currentNode->right == nullptr) // Если текущий элемент не имеет правого потомка, то создается такой потомок
                    {
                        currentNode->right = new Node<keyBased, dataType>(key, data);
                    }
                    else
                    {
                        subPush(key, data, currentNode->right); // Рекурсивный вызов функции для правых потомков
                    }
                }
            }
        }

        /////////// subPrint

        //Note: Описание этой функции представлено чуть ниже, перед функцией subSearch, т.к. она содержит меньше команд для вывода сообщений на экран

        bool cheakOne = true;
        bool cheakTwo = true;
        bool cheakLeft = true;
        bool cheakRight = true;
        void subPrint(Node<keyBased, dataType> *currentNode)
        {
            if (currentSize != 0)
            {
                if (currentNode)
                {
                    if (cheakOne)
                    {
                        std::cout << std::endl << "The root of tree (key : data): ";
                        cheakOne = false;
                    }
                    std::cout << currentNode->key << " : " << currentNode->data << std::endl;
                    if (cheakTwo)
                    {
                        std::cout << std::endl << "The tree has " << currentSize - 1 << " descendants." << std::endl;
                        cheakTwo = false;
                    }

                    if (currentNode->left != nullptr)
                    {
                        if (cheakLeft)
                        {
                            std::cout << std::endl << "The elements of left branch (key : data): " << std::endl;
                            cheakLeft = false;
                        }
                        subPrint(currentNode->left);
                    }
                    if (currentNode->right != nullptr)
                    {
                        if (cheakRight)
                        {
                            std::cout << std::endl << "The elements of right branch (key : data): " << std::endl;
                            cheakRight = false;
                        }
                        subPrint(currentNode->right);
                    }
                }
            }
            else
            {
                errorBinTree(3);
            }
        }

        //void subPrint(Node<dataType> *currentNode) // Рекурсивная функция вывода всех элементов дерева
        //{
        //  if (currentSize != 0)
        //  {
        //      if (currentNode) // Если указатель примет значение nullptr, то программа завершится
        //      {
        //      std::cout << currentNode->key << " : " << currentNode->data << std::endl; // Вывод сообщения в формате key : data
        //      if (currentNode->left != nullptr) // Если существует левый потомок
        //      {
        //          subPrint(currentNode->left); // Рекурсивный вызов функции для левых потомков
        //      }
        //      if (currentNode->right != nullptr) // Если существует правый потомок
        //      {
        //          subPrint(currentNode->right); // Рекурсивный вызов функции для правых потомков
        //      }
        //  }
        //  else // Если дерево пустое, то выводить нечего - ошибка "Binary tree is empty"
        //  {
        //      errorBinTree(3);
        //  }
        //}

        /////////// subSearch

        //Note: Функция недоработана

        dataType subSearch(keyBased key, Node<keyBased, dataType> *currentNode) // Рекурсивная функция поиска узла по ключу
        {
            if (key == currentNode->key) // Если ключи совпали, то выводится данные из узла
            {
                return currentNode->data;
            }
            else if (key < currentNode->key) // Если значение ключа меньше, чем значение ключа текущего элемента 
            {
                subSearch(key, currentNode->left); // Рекурсивный вызов функции для левых потомков
            }
            else // Если значение ключа больше, чем значение ключа текущего элемента
            {
                subSearch(key, currentNode->right); // Рекурсивный вызов функции для правых потомков
            }
        }

        /////////// subPopKey

        bool keyFoundPop = false; // Переменная для контроля совпадения ключей

        void subPopKey(keyBased key, Node<keyBased, dataType> *currentNode) // Рекурсивная функция удаления по ключу
        {
            if (currentSize != 0)
            {
                if (currentNode) // Если указатель примет значение nullptr, то программа завершится
                {
                    if (key == currentNode->key) // Если ключи совпали, то очищаются данные узла
                    {
                        currentNode->data = dataType();
                        keyFoundPop = true;
                    }
                    else if (key < currentNode->key) // Если значение ключа меньше, чем значение ключа текущего элемента 
                    {
                        subPopKey(key, currentNode->left); // Рекурсивный вызов функции для левых потомков
                    }
                    else // Если значение ключа больше, чем значение ключа текущего элемента 
                    {
                        subPopKey(key, currentNode->right); // Рекурсивный вызов функции для правых потомков
                    } 
                }
            }
            else
            {
                errorBinTree(2); // Если дерево пустое, то убирать нечего - ошибка "Binary tree Underflow"
            }
        }

        /////////// subClear

        void subClear(Node<keyBased, dataType> *currentNode) // Рекурсивная функция очистки памяти от дерева
        {
            if (currentSize == 0) // Если дерево пустое, то очищать нечего - ошибка "Binary tree is empty"
            {
                errorBinTree(3); 
            }
            else
            {
                if (currentNode) // Если указатель примет значение nullptr, то программа завершится с ошибкой Binary tree is empty
                {
                    subClear(currentNode->left); // Рекурсивная очистка левых помков
                    subClear(currentNode->right); // Рекурсивная очистка правых помков
                    delete currentNode; // Удаление узла
                }
            }
        }

    public:

        /////////// BinTree

        BinTree() // Конструктор класса BinTree
        {
            root = nullptr;
            currentSize = 0;
        }

        /////////// push

        void push(keyBased key, dataType data) // Добавление следующего элемента/узла дерева
        {
            subPush(key, data, root); // Рекурсивная функция добавления следующего узла
            currentSize++; // Увеличение размера дерева на 1
        }

        /////////// print

        void print() // Вывод всех элементов дерева
        {
            subPrint(root); // Рекурсивная функция вывода всех элементов дерева
        }

        /////////// search

        dataType search(keyBased key) // Поиск узла по ключу
        {
            return subSearch(key, root); // Рекурсивная функция поиска узла по ключу
        }

        /////////// popKey

        void popKey(keyBased key) // Удаление элемента по ключу
        {
            subPopKey(key, root); // Рекурсивная функция удаления по ключу
            if (keyFoundPop == false) // Если ключи не совпали, то ошибка "Key is not found"
            {
                errorBinTree(4);
            }
        }

        /////////// clear

        void clear() // Очистка памяти от дерева
        {
            std::cout << std::endl << "Clearing the binare tree..." << std::endl;
            subClear(root); // Рекурсивная функция очистки памяти от дерева
            currentSize = 0; // Текущий размер дерева = 0
            std::cout << std::endl << "The binare tree consists of " << currentSize << " elements." << std::endl;
        }
};


int main()
{
    BinTree<int, char> binTree;


    binTree.push(0, 'A');
    binTree.push(-1, 'B');
    binTree.push(-2, 'C');
    binTree.push(1, 'D');
    binTree.push(2, 'E');

    int key = -2;

    std::cout << "The descendant with a key " << key << " has data " << binTree.search(key) << std::endl;

    binTree.popKey(key);

    std::cout << std::endl << "The descendant with a key " << key << " has data " << binTree.search(key) << std::endl;

    binTree.print();

    binTree.clear();

    binTree.print();
}
