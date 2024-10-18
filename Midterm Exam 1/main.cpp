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
