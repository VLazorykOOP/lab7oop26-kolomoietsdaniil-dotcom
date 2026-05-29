#include <iostream>
#include <cstring>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Task 1

template <typename T>
int searchLast(T arr[], int size, T key) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

template <>
int searchLast<const char*>(const char* arr[], int size, const char* key) {
    for (int i = size - 1; i >= 0; i--) {
        if (strcmp(arr[i], key) == 0) {
            return i;
        }
    }
    return -1;
}

// Task 2

template <typename T>
void insertionsort(T arr[], int size) {
    for (int i = 1; i < size; i++) {
        T point = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > point) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = point;
	}
}

template <>
void insertionsort<const char*>(const char* arr[], int size) {
    for (int i = 1; i < size; i++) {
        const char* point = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], point) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = point;

    }
}

// Task 3

template <typename T>
class MyArray {
private:
    int size;
    T* arr;
public:
    MyArray(int s) : size(s) {
        arr = new T[size];
    }

    ~MyArray() {
        delete[] arr;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds!" << endl;
            exit(1);
        }
        return arr[index];
    }

    MyArray& operator=(const MyArray& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        size = other.size;
        arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    MyArray& operator+=(const T& item) {
        size = size + 1;
        T* newArr = new T[size];
        for (int i = 0; i < size - 1; i++) {
            newArr[i] = arr[i];
        }
        newArr[size - 1] = item;
        delete[] arr;
        arr = newArr;
        return *this;
    }

    MyArray operator+(const T& item) const {
        MyArray result(*this);
        result += item;
        return result;
    }

    MyArray& operator-=(const T& item) {
        int indexforRemoval = -1;
        for (int i = size - 1; i >= 0; i--) {
            if (arr[i] == item) {
                indexforRemoval = i;
                break;
            }
        }

        if (indexforRemoval != -1) {
            T* newArr = new T[size - 1];
            for (int i = 0, j = 0; i < size; i++) {
                if (i != indexforRemoval) {
                    newArr[j++] = arr[i];
                }
            }
            delete[] arr;
            arr = newArr;
            size--;
        }
        else {
            cout << "Item not found in the array!" << endl;
        }
        return *this;
    }

    MyArray operator-(const T& item) const {
        MyArray result(*this);
        result -= item;
        return result;
    }

    void display() const {
        cout << "MyArray contents: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void create() {
        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

};

// Task 4

template <typename T>
struct Node {
    T data;
    Node<T>* next;
	Node<T>* prev;

};

template <typename T>
class ListManager {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    ListManager() : head(nullptr), tail(nullptr) {}
    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            newNode->prev = nullptr;
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~ListManager() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    class Iterator {
    private:
        Node<T>* current; 
    public:
        Iterator(Node<T>* node) : current(node) {}

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next; 
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        T& operator*() {
            return current->data;
        }
    };


    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int main_choice;
    do {
        cout << "\n=== Lab 7 ===\n";
        cout << "1. Task (Template Sequential Search)\n";
        cout << "2. Task (Template Insertion Sort)\n";
        cout << "3. Task (MyArray Class)\n";
        cout << "4. Task (List Iterator)\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> main_choice;

        switch (main_choice) {
        case 1: {
            int search_choice;
            do {
                cout << "\nChoose the action\n";
                cout << "1. Search for an integer\n";
                cout << "2. Search for a char*\n";
                cout << "0. Back to main menu\n";
                cout << "Your choice: ";
                cin >> search_choice;

                switch (search_choice) {
                case 1: {
                    int size;
                    cout << "Enter the size of the integer array: ";
                    cin >> size;
                    int* int_arr = new int[size];

                    cout << "Enter the elements of the integer array:\n";
                    for (int i = 0; i < size; i++) {
                        cin >> int_arr[i];
                    }

                    int key;
                    cout << "Enter the integer to search for: ";
                    cin >> key;

                    int lastIndex = searchLast(int_arr, size, key);
                    if (lastIndex != -1) {
                        cout << "The last occurrence of " << key << " is at index " << lastIndex << ".\n";
                    }
                    else {
                        cout << key << " not found in the array.\n";
                    }

                    delete[] int_arr;
                    break;
                }

                case 2: {
                    int size;
                    cout << "Enter the size of the string array: ";
                    cin >> size;

                    const char** str_arr = new const char* [size];

                    cout << "Enter the elements of the string array (words):\n";
                    for (int i = 0; i < size; i++) {
                        char buffer[100];
                        cin >> buffer;

                        // Виділяємо пам'ять під точний розмір слова і копіюємо його туди
                        char* word = new char[strlen(buffer) + 1];
                        strcpy_s(word, strlen(buffer) + 1, buffer);
                        str_arr[i] = word;
                    }

                    char key[100];
                    cout << "Enter the string to search for: ";
                    cin >> key;


                    int lastIndex = searchLast(str_arr, size, (const char*)key);

                    if (lastIndex != -1) {
                        cout << "The last occurrence of '" << key << "' is at index " << lastIndex << ".\n";
                    }
                    else {
                        cout << "'" << key << "' not found in the array.\n";
                    }


                    for (int i = 0; i < size; i++) {
                        delete[] str_arr[i];
                    }
                    delete[] str_arr;

                    break;
                }

                case 0:
                    cout << "Back to main menu...\n";
                    break;
                }

            } while (search_choice != 0);

            break;
        }

        case 2: {
            int sort_choice;
            do {
                cout << "\nChoose the action\n";
                cout << "1. Sort an integer array\n";
                cout << "2. Sort a string array\n";
                cout << "0. Back to main menu\n";
                cout << "Your choice: ";
                cin >> sort_choice;
                switch (sort_choice) {

                case 1: {
                    int size;
                    cout << "Enter the size of the integer array: ";
                    cin >> size;
                    int* int_arr = new int[size];
                    cout << "Enter the elements of the integer array:\n";
                    for (int i = 0; i < size; i++) {
                        cin >> int_arr[i];
                    }
                    cout << "Array before sorting:\n";
                    for (int i = 0; i < size; i++) {
                        cout << int_arr[i] << " ";
						
                    }
                    cout << endl;

                    insertionsort(int_arr, size);
                    cout << "Sorted integer array:\n";
                    for (int i = 0; i < size; i++) {
                        cout << int_arr[i] << " ";
                    }
                    cout << endl;
                    delete[] int_arr;
                    break;
                }
                case 2: {
                    int size;
                    cout << "Enter the size of the string array: ";
                    cin >> size;
                    const char** str_arr = new const char* [size];
                    cout << "Enter the elements of the string array (words):\n";
                    for (int i = 0; i < size; i++) {
                        char buffer[100];
                        cin >> buffer;
                        char* word = new char[strlen(buffer) + 1];
                        strcpy_s(word, strlen(buffer) + 1, buffer);
                        str_arr[i] = word;
                    }
                    cout << "Array before sorting:\n";
                    for (int i = 0; i < size; i++) {
                        cout << str_arr[i] << " ";
                    }
                    cout << endl;
                    insertionsort(str_arr, size);
                    cout << "Sorted string array:\n";
                    for (int i = 0; i < size; i++) {
                        cout << str_arr[i] << " ";
                    }
                    cout << endl;

                    for (int i = 0; i < size; i++) {
                        delete[] str_arr[i];
                    }
                    delete[] str_arr;
                    break;
                }

                case 0:
                    cout << "Back to main menu...\n";
                    break;
                }
            } while (sort_choice != 0);

            break;
        }

        case 3: {
            MyArray<int> ar(3);
            int class_choice;
            do {
                cout << "\nChoose the action\n";
                cout << "1. Create MyArray of integers\n";
                cout << "2. Display MyArray of integers\n";
                cout << "3. Add an element to MyArray of integers\n";
                cout << "4. Remove an element from MyArray of integers\n";
                cout << "0. Back to main menu\n";
                cin >> class_choice;
                switch (class_choice) {
                case 1: {
                    ar.create();
                    break;
                }
                case 2: {
                    ar.display();
                    break;
                }
                case 3: {
                    int element;
                    cout << "Enter the integer to add: ";
                    cin >> element;
                    ar += element;
                    break;
                }
                case 4: {
                    int element;
                    cout << "Enter the integer to remove: ";
                    cin >> element;
                    ar -= element;
                    break;
                }
                case 0:
                    cout << "Back to main menu...\n";
                    break;
                }

            } while (class_choice != 0);

            break;
        }

        case 4: {
            ListManager<int> myList;
            myList.push_back(10);
            myList.push_back(20);
            myList.push_back(30);
            int it_choice;
            do {
                cout << "\nChoose the action\n";
                cout << "1. Test task\n";
                cout << "0. Back to main menu\n";
                cin >> it_choice;
                switch (it_choice) {
                case 1: {
                    cout << "List contents via Iterator: ";
                    for (ListManager<int>::Iterator it = myList.begin(); it != myList.end(); ++it) {
                        cout << *it << " ";
                    }
                    cout << endl;
                    break;
                }
                case 0:
                    cout << "Back to main menu...\n";
                    break;
                }
            } while (it_choice != 0);

            break; 
        }

        case 0:
            cout << "Exiting...\n";
            break;

        } 
    } while (main_choice != 0);

    return 0;
}