#include <iostream>
#include <vector>
 
using namespace std;
 
template <typename T>
struct Node {
  T val;
  Node<T> *next;
  Node(T _val) : val(_val), next(nullptr){}
};
 
template<typename T>
void printElement(Node<T> *element);
 
template<typename T>
void testList(T* (*generator)(int));

int* generateIntArray(int length);
float* generateFloatArray(int length);
double* generateDoubleArray(int length);
char* generateCharArray(int length);

double getArrMiddleValue(vector<int> arr);

template <typename T>
struct ListNode {
    Node<T> *first;
    Node<T> *last;
 
    ListNode() : first(nullptr), last(nullptr) {};
 
    bool isEmpty() {
        return first == nullptr;
    }
 
    void pushBack(T _val) {
        Node<T> *p = new Node<T>(_val);
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
 
        last->next = p;
        last = p;
    }
 
    void removeFirst() {
        if (isEmpty()) return;
        Node<T> *p = first;
        first = p->next;
        delete p;
    }

    void removeLast() {
        if (isEmpty()) return;
        if (first == last) {
            removeFirst();
            return;
        }
        Node<T> *p = first;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    void remove(T _val) {
        if (isEmpty()) return;
        if (first->val == _val) {
            removeFirst();
            return;
        }
        else if (last->val == _val) {
            removeLast();
            return;
        }
        Node<T> *slow = first;
        Node<T> *fast = first->next;
        while (fast && fast->val != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }

    void print() {
        if (isEmpty()) return;
        Node<T> *p = first;
        cout << "address: " << first << endl;
        while (p) {
            cout << "value: " << p->val << endl;
            cout << "address: " << p->next << endl;
            p = p->next;
        }
        
        cout << endl;
    }
 
    Node<T> *find(T _val) {
        Node<T> *p = first;
        while (p && p->val != _val) p = p->next;
            return (p && p->val == _val) ? p : nullptr;
    }

    Node<T> *operator[] (const int index) {
        if (isEmpty()) return nullptr;
        Node<T> *p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) return nullptr;
        }
        return p;
    }
};

template<typename T>
void searchElement(ListNode<T> *list);

template<typename T>
void addElement(ListNode<T> *list);

template<typename T>
void removeElement(ListNode<T> *list);

template<typename T>
void getElementByIndex(ListNode<T> list);
 
template<typename T>
ListNode<T> generateList(T* (*generator)(int), int length);

template<typename T>
void testRemoveSpeed(T* (*generator)(int));

template<typename T>
void testPushSpeed(T* (*generator)(int), T adding);

int main() {
    // testList(generateIntArray);
    cout << "adding speed test" << endl;
    testPushSpeed(generateIntArray, 10);
    cout << "removing speed test" << endl;
    testRemoveSpeed(generateIntArray);
}

const int DEFAULT_LENGTH = 10;
int MAX_ELEMENT = 500000;
int MIN_ELEMENT = 1;

template<typename T>
void testList(T* (*generator)(int)) {
    ListNode<T> list;
    T* data = generator(DEFAULT_LENGTH);
    for (int i = 0; i < DEFAULT_LENGTH; i++) {
        list.pushBack(data[i]);
    }

    while (1) {
        int command;

        cout << "Enter command: 0 - to print elements, 1 - to add element, 2 - to remove element, 3 - to search element, 4 - to find element by index" << endl;
        cin >> command;

        switch (command)
        {
        case 0:
            list.print();
            break;
        case 1:
            addElement(&list);
            break;
        case 2:
            removeElement(&list);
            break;
        case 3:
            searchElement(&list);
            break;
        case 4:
            getElementByIndex(list);
            break;
        default:
            cout << "unknown command";
            break;
        }
    }
}
 
template<typename T>
void printElement(Node<T> *element) {
    cout << "address: " << &element << endl;
    cout << "value: " << element->val << endl;
}

template<typename T>
void searchElement(ListNode<T> *list) {
    T searched;
    cout << "Input searched value" << endl;
    cin >> searched;

    if (list->find(searched)) {
        printElement(list->find(searched));
    } else {
        cout << "not element found" << endl;
    }
}

template<typename T>
void addElement(ListNode<T> *list) {
    T newValue;
    cout << "Input new value" << endl;
    cin >> newValue;

    list->pushBack(newValue);
}

template<typename T>
void removeElement(ListNode<T> *list) {
    T removingValue;
    cout << "Input removing value" << endl;
    cin >> removingValue;

    list->remove(removingValue);
}

template<typename T>
void getElementByIndex(ListNode<T> list) {
    int index;
    cout << "Input searched index" << endl;
    cin >> index;

    if (list[index]) {
        printElement(list[index]);
    } else {
        cout << "not element found" << endl;
    }
}

int* generateIntArray(int length) {
    int* array = new int[length];
 
    for (int i = 0; i < length; i++) {
        array[i] = MIN_ELEMENT + rand() % MAX_ELEMENT;
    }
 
    return array;
}
 
float* generateFloatArray(int length) {
    float* array = new float[length];
 
    for (int i = 0; i < length; i++) {
        array[i] = (MIN_ELEMENT + rand() % MAX_ELEMENT) * 0.01;
    }
 
    return array;
}
 
double* generateDoubleArray(int length) {
    double* array = new double[length];
 
    for (int i = 0; i < length; i++) {
        array[i] = (MIN_ELEMENT + rand() % MAX_ELEMENT) * 0.01;
    }
 
    return array;
}
 
char* generateCharArray(int length) {
    char* array = new char[length];
 
    for (int i = 0; i < length; i++) {
        array[i] = 'a' + rand()%26;
    }
 
    return array;
}

const int ONE_SIZE_ITERATIONS = 10;

double getArrMiddleValue(vector<int> arr) {
    double sum = 0;
    int length = arr.size();

    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }

    return sum / length;
}

template<typename T>
void testPushSpeed(T* (*generator)(int), T adding) {
    vector<int> sizes = {1000, 2000, 5000, 10000, 20000};
    vector<double> times;

    for (int i = 0; i < sizes.size(); i++) {
        vector<int> sizeTimes;
        for (int j = 0; j < ONE_SIZE_ITERATIONS; j++) {
            ListNode<T> list = generateList(generator, sizes[i]);

            unsigned int start_time =  clock();
            list.pushBack(adding);
            unsigned int end_time = clock();
            sizeTimes.push_back(end_time - start_time);
        }
        times.push_back(getArrMiddleValue(sizeTimes));
    }

    for (int i = 0; i < sizes.size(); i++) {
        cout << sizes[i] << " - " << times[i] << endl;
    }
}

template<typename T>
void testRemoveSpeed(T* (*generator)(int)) {
    vector<int> sizes = {1000, 2000, 5000, 10000, 20000};
    vector<double> times;

    for (int i = 0; i < sizes.size(); i++) {
        vector<int> sizeTimes;
        for (int j = 0; j < ONE_SIZE_ITERATIONS; j++) {
            ListNode<T> list = generateList(generator, sizes[i]);
            int randomIndex = rand()%sizes[i];
            Node<T> *element = list[randomIndex];

            unsigned int start_time =  clock();
            list.remove(element->val);
            unsigned int end_time = clock();
            sizeTimes.push_back(end_time - start_time);
        }
        times.push_back(getArrMiddleValue(sizeTimes));
    }

    for (int i = 0; i < sizes.size(); i++) {
        cout << sizes[i] << " - " << times[i] << endl;
    }
}

template<typename T>
ListNode<T> generateList(T* (*generator)(int), int length) {
    ListNode<T> list;
    T* data = generator(length);

    for (int i = 0; i < length; i++) {
        list.pushBack(data[i]);
    }

    return list;
}