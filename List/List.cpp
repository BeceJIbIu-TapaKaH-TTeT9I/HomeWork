#include <iostream>

template<typename dataType>
class List // Односвязный список
{
    private:

		template<typename dataType>
		class  Node // Элемент/узел списка
		{
			public:

				Node *next; // Адрес следующего элемента, если элемент последний в списке, то указатель = nullptr
				dataType data; // Данные текущего элемента

				/////////// Node

				Node(dataType data = dataType(), Node *next = nullptr) // Конструктор класса Node
				{
					this->data = data;
					this->next = next;
				}
		};

		unsigned int currentSize; // Текущий размер списка (количество элементов в списке)
		Node<dataType> *oneElement; // 1 элемент/узел списка

		/////////// errorList

		void errorList(unsigned int codeExit) // Вывод ошибки
		{
			switch (codeExit)
			{
			case 2: std::cout << std::endl << "List Underflow" << std::endl; break;
			case 3: std::cout << std::endl << "List is empty" << std::endl; break; // По факту, пустой список - это не ошибка, если не убирать из него узлы
			}
			exit(1);
		}

	public:

		/////////// List

		List() // Конструктор класса List
		{
			currentSize = 0;
			oneElement = nullptr;
		}

		/////////// push

		void push(dataType data) // Добавление следующего элемента/узла списка
		{
			if (oneElement == nullptr) // Если добавляется первый узел списка
			{
				oneElement = new Node<dataType>(data);
			}
			else // Если же в списке есть узлы
			{
				Node<dataType> *current = oneElement; // Создание временной переменной типа Node
				while (current->next != nullptr) // Поиск узла, адрес которого = nullptr, т.к. этот узел является последним в списке
				{
					current = current->next;
				}
				current->next = new Node<dataType>(data); // Создание нового элемента и присвоение адреса нового элемента опследнему next последнего элемента (сейчас это current->next) 
			}
			currentSize++; // Увеличение размера списка на 1
		}

		/////////// size

		unsigned int size() // Вывод количества элементов списка
		{
			return currentSize;
		}

		/////////// print

		void print() // Вывод всех элементов списка
		{
			if (currentSize == 0) // Если список пуст, то выводить нечего - ошибка "Stack is empty"
			{
				errorList(3);
			}
			else
			{
				std::cout << std::endl << "The list consists of " << currentSize << " elements:" << std::endl;
				Node<dataType>* current = oneElement; // Создание временной переменной типа Node
				while (current != nullptr) // Цикл не закончится, пока не будет найден элемент, next, которого = nullptr, т.е. последний элемент списка
				{
					std::cout << current->data << std::endl;
					current = current->next; // Присвоение указателю адреса следующего элемента
				}
			}
		}

		/////////// popFront

		void popFront() // Удаление элемента из начала списка, т.к. это удалять именно этот элемент проще и быстрее
		{
			if (currentSize >= 1) // Проверка на наличие элементов в списке
			{
				Node<dataType>* tmpFront = oneElement; // Создание временной переменной типа Node
				oneElement = oneElement->next; // Сохранение адреса следующего элемента, чтобы не потерять всю цепочку узлов
				delete tmpFront; // Удаление первого элемента
				currentSize--; //Уменьшение размера списка на 1
			}
			else
			{
				errorList(2);
			}
		}

		/////////// clear

		void clear() // Очитка памяти от списка
		{
			std::cout << std::endl << "Clearing the list..." << std::endl;
			while (currentSize) // Переменная currentSize имеет тип данных unsigned int, соответсвенно, когда она станет < 0, цикл завершится
			{
				popFront();
			}
			std::cout << std::endl << "The list consists of " << currentSize << " elements." << std::endl;
		}
};

int main()
{
	List<int> list;

	std::cout << "The list consists of " << list.size() << " elements." << std::endl;

	list.push(0);
	list.push(10);
	list.push(-10);
	list.push(20);
	list.push(100);
	
	list.print();

	list.popFront();
	list.popFront();
	list.popFront();

	list.print();

	list.clear();

	list.popFront();

	return 0;
}
