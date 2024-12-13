#include <iostream>
using namespace std;

// Function to check if a seat is available
inline int check_seats_availability(int row, int col, int** teater, int* seatsinrow) {
    if (row < 0 || row >= seatsinrow[0] || col < 0 || col >= seatsinrow[row]) {
        cout << "Invalid seat selection!" << endl;
        return;
    }
 
    if (teater[row][col] == 0)
    {
        return 0;  // if empty
    }

    else
    {
        return 1; // if not empty
    }
    
}

// Function to book a seat
void book_seat(int row, int col, int** teater, int* seatsinrow) {
    if (check_seats_availability(row, col, teater, seatsinrow) == 0) {
        teater[row][col] = 1;  // Mark the seat as booked
        cout << "Seat booked successfully!" << endl;
    }
    else  if(check_seats_availability(row, col, teater, seatsinrow) == 1)
    {
        cout << "Sorry, this seat is already occupied " << endl;
    }
}

// Function to cancel a booking
void cancel_seat(int row, int col, int** teater, int* seatsinrow) {
    if (check_seats_availability(row, col, teater, seatsinrow) == 1)
    {
        teater[row][col] = 0;  // Mark the seat as available
        cout << "Seat canceled successfully!" << endl;
    }
    else if(check_seats_availability(row, col, teater, seatsinrow) == 0)
    {
        cout << "No booking found for this seat." << endl;
    }
}

// Function to view the seating arrangement
void view_seats(int rows, int** teater, int* seatsinrow) {
    cout << "Seating arrangement:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < seatsinrow[i]; j++) {
            cout << (teater[i][j] == 0 ? "E " : "B ");  // E for empty, B for booked
        }
        cout << endl;
    }
}

int main() {
    int rows;

    // Input the number of rows
    cout << "Enter the number of rows in the theater: ";
    cin >> rows;

    // Dynamically allocate memory for the seating arrangement
    int** teater = new int* [rows];
    int* seatsinrow = new int[rows];

    // Input the number of seats for each row and initialize to 0 (empty)
    for (int i = 0; i < rows; i++) {
        cout << "Enter the number of seats for row " << i + 1 << ": ";
        cin >> seatsinrow[i];
        teater[i] = new int[seatsinrow[i]];  // Allocate memory for each row

        // Initialize seats to 0 (empty)
        for (int j = 0; j < seatsinrow[i]; j++) {
            teater[i][j] = 0;
        }
    }

    // Main menu
    int option;
    do {
        cout << "\nMenu: \n";
        cout << "1. Book a seat\n";
        cout << "2. Cancel a booking\n";
        cout << "3. View seating arrangement\n";
        cout << "4. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
        case 1:
        {
            int row, col;
            cout << "Enter row number (0-based index): ";
            cin >> row;
            cout << "Enter column number (0-based index): ";
            cin >> col;
            book_seat(row, col, teater, seatsinrow);
            break;
        }
        case 2:
        {
            int row, col;
            cout << "Enter row number (0-based index): ";
            cin >> row;
            cout << "Enter column number (0-based index): ";
            cin >> col;
            cancel_seat(row, col, teater, seatsinrow);
            break;
        }
        case 3:
            view_seats(rows, teater, seatsinrow);
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option! Please try again.\n";
            break;
        }
    }
    while (option != 4);

    // Clean up dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        delete[] teater[i];  // Free each row's memory
    }
    delete[] teater;  // Free the array of rows
    delete[] seatsinrow;  // Free the seatsinrow array

    return 0;
}
