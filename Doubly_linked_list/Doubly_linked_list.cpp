
#include <iostream>
using namespace std;

struct element {
    int data;
    element* next, * prev;
};

class list {
    element* head, * tail;
    int size;
public:
    list() {
        head = tail = nullptr;
        size = 0;
    }

    list(int size) {
        for (int i = 0; i < size; i++)
        {
            add_head(rand() % 101 - 50);
        }
    }

    list(const list& obj) {
        head = tail = nullptr;
        size = 0;
        *this = obj;
    }

    void add_head(int value) {
        element* new_element = new element;
        new_element->data = value;
        new_element->next = new_element->prev = nullptr;

        if (!size) {
            head = tail = new_element;
        }
        else {
            new_element->next = head;
            head->prev = new_element;
            head = new_element;
            new_element = nullptr;
        }
        size++;

    }

    void add_tail(int value) {
        element* new_element = new element;
        new_element->data = value;
        new_element->next = new_element->prev = nullptr;

        if (!size) {
            head = tail = new_element;
        }
        else {
            new_element->prev = tail;
            tail->next = new_element;
            tail = new_element;
            new_element = nullptr;
        }
        size++;
    }

    void print()const {
        cout << "Size: " << size << '\n';
        cout << string(100, '-') << "\n";

        element* tmp = head;
        while (tmp) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }

        cout << "\n" << string(100, '-') << "\n";
    }


    void add_position(int pos, int value) {
        element* tmp = new element;
        tmp->data = value;
        tmp->prev = tmp->next = nullptr;

        if (pos > size) {
            return;
        }

        if (!pos) {
            add_head(value);
        }
        else if (pos == size) {
            add_tail(value);
        }
        else {
            element* ptr1 = head;
            int i = 0;
            while (i++ < pos - 1) {
                ptr1 = ptr1->next;
            }

            element* ptr2 = ptr1->next;
            tmp->prev = ptr1;
            tmp->next = ptr2;

            ptr1->next = tmp;
            ptr2->prev = tmp;
            size++;
        }
    }

    void delete_head() {
        if (!size) {
            return;
        }

        element* tmp = head;
        head = head->next;
        if (size != 1) {
            head->prev = nullptr;
        }
        delete tmp;
        size--;
    }

    void delete_tail() {
        if (!size) {
            return;
        }
        element* tmp = tail;
        tail = tail->prev;
        if (size != 1) {
            tail->next = nullptr;
        }

        delete tmp;
        size--;
        if (!size) {
            head = nullptr;
        }
    }

    void delete_pos(int pos) {
        if (pos > size) {
            return;
        }

        if (!pos) {
            delete_head();
        }
        else {
            element* ptr = head;
            int i = 0;
            while (i++ < pos - 1) {
                ptr = ptr->next;
            }
            element* temp = ptr->next;
            ptr->next = ptr->next->next;
            ptr->prev = ptr->next->prev;

            delete temp;
            size--;
        }
    }

    int search(int value) {
        int pos = 0;
        element* ptr = head;

        while (ptr->data != value) {
            pos++;
            ptr = ptr->next;
            if (pos == size) {
                return -1;
            }
        }
        return pos;
    }

    int search_replace(int value, int new_value) {
        int count = 0;
        element* ptr = head;

        while (ptr != nullptr) {
            if (ptr->data == value) {
                ptr->data = new_value;
                count++;
            }
            ptr = ptr->next;
        }
        return count;
    }

    void delete_search(int value) {
        element* ptr = head;

        while (ptr != nullptr) {
            if (ptr->data == value) {
                element* tmp = ptr;
                ptr = ptr->next;
                if (tmp->prev != nullptr) {
                    tmp->prev->next = tmp->next;
                }
                else {
                    head = tmp->next;
                }

                if (tmp->next != nullptr) {
                    tmp->next->prev = tmp->prev;
                }
                else {
                    tail = tmp->prev;
                }
                delete tmp;
                size--;
            }
            else {
                ptr = ptr->next;
            }
        }
    }

    void reverse() {
        element* next_el = nullptr;
        element* current_el = head;
        element* prev_el = nullptr;

        tail = head;

        while (current_el != nullptr) {
            next_el = current_el->next;
            current_el->next = prev_el;
            current_el->prev = next_el;
            prev_el = current_el;
            current_el = next_el;
        }
        head = prev_el;
    }

    void clear() {
        while (head) {
            delete_head();
        }
    }

    list& operator=(const list& other) {
        if (this == &other) {
            return *this;
        }

        delete head;
        delete tail;
        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;

        return *this;
    }

    int& operator[](int index)const {
        element* number = head;
        for (int i = 0; i < size; i++) {
            if (i == index) {
                return number->data;
            }
            number = number->next;
        }
        return number->data;
    }


    ~list() {
        clear();
    }
};



int menu() {
    int choice;
    cout << "0 - EXIT\n";
    cout << "1 - ADD HEAD\n";
    cout << "2 - ADD TAIL\n";
    cout << "3 - ADD POSITION\n";
    cout << "4 - DELETE HEAD\n";
    cout << "5 - DELETE TAIL\n";
    cout << "6 - DELETE POSITION\n";
    cout << "7 - SEARCH ELEMENT\n";
    cout << "8 - REPLACE ELEMENT\n";
    cout << "9 - CLEAR LIST\n";
    cout << "10 - REVERSE\n";

    cout << "Enter choice: ";
    cin >> choice;
    return choice;

}


int main()
{
    srand(time(NULL));

    int size;
    cout << "Enter size: ";
    cin >> size;

    list l(size);

    while (true) {
        system("cls");
        l.print();
        int choice = menu();


        if (!choice) break;
        int number, pos, new_number, plug;
        switch (choice) {
        case 1:
            cout << "Enter number: ";
            cin >> number;
            l.add_head(number);
            break;
        case 2:
            cout << "Enter number: ";
            cin >> number;
            l.add_tail(number);
            break;
        case 3:
            cout << "Enter position: ";
            cin >> pos;
            cout << "Enter number: ";
            cin >> number;
            l.add_position(pos, number);
            break;
        case 4:
            l.delete_head();
            break;
        case 5:
            l.delete_tail();
            break;
        case 6:
            cout << "Enter pos: ";
            cin >> pos;
            l.delete_pos(pos);
            break;
        case 7:
            cout << "Enter number: ";
            cin >> number;
            cout << l.search(number);
            cin >> plug;
            break;
        case 8:
            cout << "Enter number: ";
            cin >> number;
            cout << "Enter new_number: ";
            cin >> new_number;
            l.search_replace(number, new_number);
            break;
        case 9:
            l.clear();
            break;
        case 10:
            l.reverse();
            break;
        }
    }


    cout << "\n\n\n";
    return 0;
}
