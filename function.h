  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>


  typedef struct Node {
    char name[50];
    int hargaTiket;
    int noGerbong;
    char kelas[50];
    struct Node* next;
  } Node;

  // Function prototypes
  Node* createNode(char name[], int hargaTiket, int noGerbong, char kelas[]);
  void insertSorted(Node** head, Node* newNode);
  void displayList(Node* head);
  void swapNodes(Node* a, Node* b);

  // Create a new node with allocated memory
  Node* createNode(char name[], int hargaTiket, int noGerbong, char kelas[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
      printf("Memory allocation failed!\n");
      return NULL;
    }
    strcpy(newNode->name, name);
    newNode->hargaTiket = hargaTiket;
    newNode->noGerbong = noGerbong;

    if (strcasecmp(kelas, "Eksekutif") != 0 && strcasecmp(kelas, "Bisnis") != 0){
      printf("Invalid Class! Please enter 'Eksekutif' or 'Bisnis'.\n");
      return NULL; // Indicate error
    }
    strcpy(newNode->kelas, kelas);
    newNode->next = NULL;
    return newNode;
  }


  // Insert a new node in sorted order based on hargaTiket (descending)
  void insertNode(Node** head, Node* newNode) {
    // If the list is empty, make the new node the head
    if (*head == NULL) {
      *head = newNode;
      return;
    }

    // Traverse the list to find the last node
    Node* current = *head;
    while (current->next != NULL) {
      current = current->next;
    }

    // Insert the new node at the end
    current->next = newNode;
    newNode->next = NULL;
  }

  // Display the linked list
  void displayList(Node* head) {
      if (head == NULL) {
          printf("No Passenger Available!\n");
          return;
      }

      int rank = 1;
      Node* temp = head;

      // Header row with formatting
      printf("| %3s | %-*s | %-*s | %5s | %5s |\n", "Rank", 20, "Name", 19, "Class", "Ticket Price", "Seat Number");
      printf("---------------------------------------------------------------------------------\n"); // Adjusted separator for better alignment

      while (temp != NULL) {
          printf("| %3d | %-*s | %-*s | %10d | %10d |\n", rank++, 20, temp->name, 20, temp->kelas, temp->hargaTiket, temp ->noGerbong);
          temp = temp->next;
      }
  }



  // Swap data between two nodes
  void swapNodes(Node* a, Node* b) {
    char tempName[20];
    int tempHarga;
    strcpy(tempName, a->name);
    tempHarga= a->hargaTiket;
    strcpy(a->name, b->name);
    a->hargaTiket = b->hargaTiket;
    strcpy(b->name, tempName);
    b->hargaTiket = tempHarga;
  }

/*Function to swap the nodes */
struct Node* swap(struct Node* ptr1, struct Node* ptr2)
{
    struct Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

/* Function to sort the list */
void bubbleSort(struct Node** head, int count)
{
    struct Node** h;
    int i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            struct Node* p1 = *h;
            struct Node* p2 = p1->next;

            if (p1->hargaTiket < p2->hargaTiket) {

                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}


  void deleteNode(Node** head, char name[]) {
    // Check for empty list
    if (*head == NULL) {
      printf("List is empty. No node to delete.\n");
      return;
    }

    // Check if head node needs to be deleted
    if (strcmp( (*head)->name, name ) == 0) {
      Node* temp = *head;
      *head = (*head)->next;
      free(temp);
      return;
    }

    // Traverse the list to find the node to delete
    Node* current = *head;
    Node* prev = NULL;
    while (current != NULL && strcmp(current->name, name) != 0) {
      prev = current;
      current = current->next;
    }

    // Node not found
    if (current == NULL) {
      printf("Passenger '%s' not found in the list.\n", name);
      return;
    }

    // Delete the node
    prev->next = current->next;
    free(current);
  }


// Function to divide the linked list based on class
Node* divideList(Node* head, Node** eksekutifHead, Node** bisnisHead) {
  Node* current = head;
  Node* prevEksekutif = NULL;
  Node* prevBisnis = NULL;
  *eksekutifHead = NULL;
  *bisnisHead = NULL;

  while (current != NULL) {
    Node* next = current->next;

    if (strcasecmp(current->kelas, "Eksekutif") == 0) {
      if (*eksekutifHead == NULL) {
        *eksekutifHead = current;
      } else {
        prevEksekutif->next = current;
      }
      prevEksekutif = current;
    } else if (strcasecmp(current->kelas, "Bisnis") == 0) {
      if (*bisnisHead == NULL) {
        *bisnisHead = current;
      } else {
        prevBisnis->next = current;
      }
      prevBisnis = current;
    } else {
      printf("Invalid class found in list! Skipping node.\n");
      // You can choose to handle invalid classes differently here (e.g., remove the node)
    }

    current->next = NULL; // Detach node from original list
    current = next;
  }

  // Set the last node's next pointer in each separated list to NULL
  if (prevEksekutif != NULL) {
    prevEksekutif->next = NULL;
  }
  if (prevBisnis != NULL) {
    prevBisnis->next = NULL;
  }

  return head; // Return the original head (now empty)
}

int countPassengers(Node* head) {
  int count = 0;
  Node* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}
// Function to display a sorted list based on class
void displaySortedClassList(Node* head, char class[]) {
  if (head == NULL) {
    printf("No passengers of class '%s' found.\n", class);
    return;
  }

  bubbleSort(&head, countPassengers(head)); // Sort the separated list
  displayList(head);
}
