template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) 
{ 
    this->length = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    }
    else {
        Node* curr = head;

        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = n;
    }

    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* prev = nullptr;

    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }

    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    this->head = nullptr;

    Node* tail = nullptr;
    Node* current = copyObj.head;

    while(current != nullptr)
    {
        Node* newNode = new Node(current->value);

        if(this->head == nullptr)
        {
            this->head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        this->length++;
        current = current->next;
    }
}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    
    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    if(position < 0 || position >= this->length)
    {
        throw string("Invalid index for insertion");
        return;
    }

    Node* previous = nullptr;
    Node* current = this->head;

    Node* newNode = new LinkedList<T>::Node(elem);
    
    for(int i = 0; i < position && current != nullptr; i++)
    {
        previous = current;
        current = current->next;
    }

    //We want to set previous->next to the current node, and set newNode->next to current

    if(previous != nullptr) //First verify that previous is valid
    {
        previous->next = newNode;
    }
    else //If it's not, we are inserting at element zero. Set head as newNode.
    {
        this->head = newNode;
    }

    newNode->next = current;
    this->length++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if(position < 0 || position >= this->length)
    {
        throw string("Invalid index for removal");
        return;
    }

    Node* previous = nullptr;
    Node* current = this->head;
    Node* next = nullptr;

    for(int i = 0; i < position && current != nullptr; i++)
    {
        previous = current;
        current = current->next;
    }

    if(current == nullptr) //Abort if the target is nullptr
    {
        throw string("Tried to remove a nullptr");
        return;
    }

    next = current->next; //Save reference to next node in line

    delete current;

    if(previous != nullptr)
    {
        previous->next = next; //Link previous to next to fill the hole made from deleting current
    }
    else
    {
        this->head = next; //If previous is nullptr, then we deleted the head of the list; Assign next to head.
    }

    this->length--;
}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
        return;
    }

    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
