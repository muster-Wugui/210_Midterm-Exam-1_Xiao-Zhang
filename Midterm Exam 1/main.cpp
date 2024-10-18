//
//  main.cpp
//  Midterm Exam 1
//
//  Created by Xiao Zhang on 10/18/24.
//

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        // This is a constructor to set data and pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;  // use data to store value
            prev = p;     // to set prev pointer
            next = n;     // to set next pointer
        }
    };
    
    Node* head;  // This is a pointer which is the start of the list
    Node* tail;  // This is a pointer which is the end of the list
    
public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // Initialize empty list
    
    // This function aim to insert value in a specific position
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);  // Create new node
        if (!head) {  // If list is empty, set new node as both head and tail
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        // Move to the given position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {  // Print warning when the position exceeds the list size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        // Insert new node between temp and the next node
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;  // Update tail if inserted at the end
        temp->next = newNode;
    }
    // Delete the first node with the given value
    void delete_val(int value) {
        if (!head) return;  // If list is empty, nothing to delete
        Node* temp = head;
        // Search for the node with the matching value
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp) return;  // Can't find the value
        // Adjust pointers to remove the node
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;  // Update head if first node is deleted
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;  // Update tail if last node is deleted
        delete temp;
    }
    
    // Delete node at a given position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        if (pos == 1) {  // Delete first node
            pop_front();
            return;
        }
        Node* temp = head;
        // Move to the specific position
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            temp = temp->next;
        }
        if (!temp->next) {  // If it's the last node, use pop_back
            pop_back();
            return;
        }
        // Remove the node
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
    
    // Add a node at the end of the list
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;  // If list is empty
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;  // Update tail
        }
    }
    
    // Add a node at the front of the list
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;  // If list is empty
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;  // Update head
        }
    }
    
    // Remove the first node
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;  // List becomes empty
        delete temp;
    }
    
    // Remove the last node
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;  // List becomes empty
        delete temp;
    }
    // Method to print every other element
    void every_other_element() {
        Node* temp = head;  // Start from head
        bool flag = false;  // use a flag variable to tag the skipping elements
        while (temp) {
            if (!flag){
                cout << temp->data << " ";  // Print if not skipping
            }
            flag = !flag;  // Change the flag
        }
        cout << endl;
    }

    // Print all elements in order
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Print all elements in reverse order
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // Destructor to free the memory
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);
    myList.push_back(5);

    cout << "Original elements: ";
    myList.print();  // This should print: 1 2 3 4 5

    cout << "Every other element: ";
    myList.every_other_element();  // This should print: 1 3 5

    myList.delete_val(3);
    cout << "Elements after deleting 3: ";
    myList.print();  // This should print: 1 2 4 5

    return 0;
}
