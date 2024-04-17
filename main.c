#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h" // Include function.h if used

int main() {
  Node* head = NULL; // Initialize empty list
  
  int count = 0;
  int choice, chc, hargaTiket, gerbong;
  char name[50], kelas[50], namaDel[50];

  while (1) {
    printf("\nMenu:\n");
    printf("1. Add Passenger\n");
    printf("2. Sort Passenger\n");
    printf("3. Display Passenger List\n");
    printf("4. Delete Passenger\n");
    printf("5. Sort By Class\n");
    printf("6. Exit Program\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) { // Check for valid integer input
      printf("Invalid input! Please enter a number.\n");
      scanf("%*[^\n]"); // Clear invalid input from buffer
      continue;
    }

    switch (choice) {
      case 1:
        printf("Enter Passenger's Name: ");
        if (scanf(" %s", name) != 1) { // Check for successful name input with size limit
          printf("Invalid input! Please enter a name within 50 characters.\n");
          scanf("%*[^\n]"); // Clear invalid input from buffer
          continue;
        }

        printf("Enter Ticket's Price: ");
        if (scanf("%d", &hargaTiket) != 1) { // Check for valid integer input
          printf("Invalid input! Please enter a number for ticket price.\n");
          scanf("%*[^\n]"); // Clear invalid input from buffer
          continue;
        }

        printf("Enter Passenger's Class (Eksekutif or Bisnis): ");
        if (scanf(" %s", kelas) != 1) { // Check for successful class input with size limit
          printf("Invalid input! Please enter a class.\n");
          scanf("%*[^\n]"); // Clear invalid input from buffer
          continue;
        }

        printf("Enter Passenger's Seat Number: ");
        if (scanf("%d", &gerbong) != 1) { // Check for valid integer input
          printf("Invalid input! Please enter a number for seat number.\n");
          scanf("%*[^\n]"); // Clear invalid input from buffer
          continue;
        }

        Node* newNode = createNode(name, hargaTiket, gerbong, kelas);
        if (newNode != NULL) { // Check if node creation was successful
          insertNode(&head, newNode); // Insert at the end
        } else {
          printf("Failed to create new node!\n");
        }
        system("cls"); // Assuming system("cls") is for clearing the screen
        break;
      case 2:
        while (newNode != NULL) {
            count++;
            newNode = newNode->next;
        }
        
        // Call the bubbleSort function to sort the list
        bubbleSort(&head, count);

        // Print the sorted list
        printf("\nSorted List:\n");
        displayList(head);
        break;
      case 3:
        displayList(head);
        break;
      case 4:
        printf("Enter Passenger's Name for deletion: ");
        scanf("%s", namaDel);
        deleteNode(&head, namaDel);
        break;
      case 5:
        printf("1. Display Sorted Eksekutif Passengers\n");
        printf("2. Display Sorted Bisnis Passengers\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        Node* eksekutifHead;
        Node* bisnisHead;
        head = divideList(head, &eksekutifHead, &bisnisHead);
        if (scanf("%d", &chc) != 1) {
            printf("Invalid input! Please enter a number.\n");
            scanf("%*[^\n]"); // Clear invalid input from buffer
            continue;
        }

        switch(chc) {
            case 1:
                displaySortedClassList(eksekutifHead, "Eksekutif");
                break;
            case 2:
                displaySortedClassList(bisnisHead, "Bisnis");
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
            }
            break;
      case 6:
        printf("Exiting...\n");
        exit(0);
      default:
        printf("Invalid choice!\n");
    }
  }
}
