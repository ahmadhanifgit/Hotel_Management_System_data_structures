#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ===============================
// Customer Structure (Singly Linked List)
// ===============================
struct Customer {
    string name;
    string cnic;
    string phone;
    int roomNumber;
    int daysStayed;
    Customer* next;
};

// ===============================
// Room Structure (Binary Search Tree Node)
// ===============================
struct Room {
    int roomNumber;
    bool isAvailable;
    float pricePerDay;
    Room* left;
    Room* right;
};

// ===============================
// Staff Structure (Doubly Linked List)
// ===============================
struct Staff {
    string name;
    string role;
    Staff* next;
    Staff* prev;
};

class StaffList {
    Staff* head;
public:
    StaffList() : head(nullptr) {}

    // Destructor to free memory
    ~StaffList() {
        Staff* current = head;
        while (current) {
            Staff* next = current->next;
            delete current;
            current = next;
        }
    }

    void addStaff() {
        string name, role;
        cout << "Enter staff name: ";
        getline(cin >> ws, name);
        cout << "Enter staff role: ";
        getline(cin >> ws, role);
        Staff* newStaff = new Staff{name, role, nullptr, nullptr};
        if (!head) head = newStaff;
        else {
            newStaff->next = head;
            head->prev = newStaff;
            head = newStaff;
        }
        cout << "Staff member added.\n";
    }

    void displayStaff() {
        Staff* temp = head;
        if (!temp) {
            cout << "No staff records.\n";
            return;
        }
        cout << "\n--- Staff List ---\n";
        while (temp) {
            cout << "Name: " << temp->name << " | Role: " << temp->role << endl;
            temp = temp->next;
        }
    }
};

// ===============================
// Feedback Queue (Singly Linked List)
// ===============================
struct Feedback {
    string customerName;
    string message;
    Feedback* next;
};

class FeedbackQueue {
    Feedback* front;
    Feedback* rear;
public:
    FeedbackQueue() : front(nullptr), rear(nullptr) {}

    // Destructor to free memory
    ~FeedbackQueue() {
        Feedback* current = front;
        while (current) {
            Feedback* next = current->next;
            delete current;
            current = next;
        }
    }

    void addFeedback() {
        string name, msg;
        cout << "Enter your name: ";
        getline(cin >> ws, name);
        cout << "Enter your feedback or complaint: ";
        getline(cin >> ws, msg);
        Feedback* newFeedback = new Feedback{name, msg, nullptr};
        if (!rear) front = rear = newFeedback;
        else {
            rear->next = newFeedback;
            rear = newFeedback;
        }
        cout << "Feedback recorded.\n";
    }

    void showFeedback() {
        Feedback* temp = front;
        if (!temp) {
            cout << "No feedback available.\n";
            return;
        }
        cout << "\n--- Feedback & Complaints ---\n";
        while (temp) {
            cout << "Customer: " << temp->customerName << " | Message: " << temp->message << endl;
            temp = temp->next;
        }
    }
};

// ===============================
// Check-in Stack (Singly Linked List)
// ===============================
struct CheckNode {
    string name;
    int room;
    CheckNode* next;
};

class CheckStack {
    CheckNode* top;
public:
    CheckStack() : top(nullptr) {}

    // Destructor to free memory
    ~CheckStack() {
        CheckNode* current = top;
        while (current) {
            CheckNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void checkIn(string name, int room) {
        CheckNode* newNode = new CheckNode{name, room, top};
        top = newNode;
        cout << "Guest checked in.\n";
    }

    void checkOut() {
        if (!top) {
            cout << "No guests to check out.\n";
            return;
        }
        cout << "Guest checked out: " << top->name << " (Room: " << top->room << ")\n";
        CheckNode* temp = top;
        top = top->next;
        delete temp;
    }

    void showLastCheckIn() {
        if (top)
            cout << "Last Check-In: " << top->name << " | Room: " << top->room << endl;
        else
            cout << "No check-ins yet.\n";
    }
};

// ===============================
// Room Binary Search Tree
// ===============================
class RoomBST {
    Room* root;

    // Helper function for inserting a room
    Room* insert(Room* node, int number, float price) {
        if (!node) return new Room{number, true, price, nullptr, nullptr};
        if (number < node->roomNumber) node->left = insert(node->left, number, price);
        else if (number > node->roomNumber) node->right = insert(node->right, number, price);
        return node;
    }

    // Helper function for searching a room
    Room* search(Room* node, int number) {
        if (!node || node->roomNumber == number) return node;
        if (number < node->roomNumber) return search(node->left, number);
        return search(node->right, number);
    }

    // Helper function for in-order traversal (displaying rooms)
    void displayInOrder(Room* node) {
        if (!node) return;
        displayInOrder(node->left);
        cout << "Room No: " << node->roomNumber << " | Status: " << (node->isAvailable ? "Available" : "Booked")
             << " | Price/Day: Rs." << fixed << setprecision(2) << node->pricePerDay << endl;
        displayInOrder(node->right);
    }

    // Helper function for deleting the BST
    void deleteTree(Room* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    RoomBST() : root(nullptr) {}

    // Destructor to free memory
    ~RoomBST() {
        deleteTree(root);
    }

    void addRoom(int number, float price) {
        if (getRoom(number)) {
            cout << "Room " << number << " already exists.\n";
            return;
        }
        root = insert(root, number, price);
        cout << "Room " << number << " added successfully.\n";
    }

    Room* getRoom(int number) {
        return search(root, number);
    }

    void markRoomBooked(int number) {
        Room* room = getRoom(number);
        if (room) room->isAvailable = false;
    }

    void markRoomFree(int number) {
        Room* room = getRoom(number);
        if (room) room->isAvailable = true;
    }

    void displayAllRooms() {
        if (!root) {
            cout << "No rooms added yet.\n";
            return;
        }
        cout << "\n--- All Hotel Rooms ---\n";
        displayInOrder(root);
    }
};

// ===============================
// Customer Linked List
// ===============================
class CustomerList {
    Customer* head;
public:
    CustomerList() : head(nullptr) {}

    // Destructor to free memory
    ~CustomerList() {
        Customer* current = head;
        while (current) {
            Customer* next = current->next;
            delete current;
            current = next;
        }
    }

    void bookRoom(RoomBST& rooms, CheckStack& checkIns) {
        string name, cnic, phone;
        int roomNo, days;
        cout << "Enter Name: ";
        getline(cin >> ws, name);
        cout << "Enter CNIC: ";
        getline(cin >> ws, cnic);
        cout << "Enter Phone: ";
        getline(cin >> ws, phone);
        cout << "Enter Room Number to Book: ";
        cin >> roomNo;
        cout << "Enter Number of Days: ";
        cin >> days;

        Room* room = rooms.getRoom(roomNo);
        if (!room) {
            cout << "Room does not exist.\n";
            return;
        }
        if (!room->isAvailable) {
            cout << "Room is already booked.\n";
            return;
        }

        Customer* newCust = new Customer{name, cnic, phone, roomNo, days, nullptr};
        newCust->next = head;
        head = newCust;
        rooms.markRoomBooked(roomNo);
        checkIns.checkIn(name, roomNo);

        cout << "Room successfully booked!\n";
    }

    void showCustomers() {
        Customer* temp = head;
        if (!temp) {
            cout << "No bookings yet.\n";
            return;
        }
        cout << "\n--- All Booked Customers ---\n";
        while (temp) {
            cout << "Name: " << temp->name << " | CNIC: " << temp->cnic << " | Phone: " << temp->phone
                 << " | Room: " << temp->roomNumber << " | Days: " << temp->daysStayed << endl;
            temp = temp->next;
        }
    }

    void deleteBooking(RoomBST& rooms) {
        string cnic;
        cout << "Enter CNIC to delete booking: ";
        getline(cin >> ws, cnic);
        Customer* temp = head;
        Customer* prev = nullptr;

        while (temp && temp->cnic != cnic) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Booking not found.\n";
            return;
        }

        rooms.markRoomFree(temp->roomNumber);

        if (!prev) head = temp->next;
        else prev->next = temp->next;

        delete temp;
        cout << "Booking deleted and room is now available.\n";
    }

    void generateBill(RoomBST& rooms) {
        string cnic;
        cout << "Enter CNIC for billing: ";
        getline(cin >> ws, cnic);
        Customer* temp = head;
        while (temp && temp->cnic != cnic) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "No customer found with this CNIC.\n";
            return;
        }
        Room* room = rooms.getRoom(temp->roomNumber);
        if (!room) { // Should not happen if room was valid during booking
            cout << "Error: Room details not found for this booking.\n";
            return;
        }
        float total = temp->daysStayed * room->pricePerDay;
        cout << "\n--- Invoice ---\n";
        cout << "Name: " << temp->name << endl;
        cout << "Room: " << temp->roomNumber << endl;
        cout << "Days: " << temp->daysStayed << endl;
        cout << "Rate: Rs. " << room->pricePerDay << "/day" << endl;
        cout << "Total Amount: Rs. " << fixed << setprecision(2) << total << endl;
    }
};

// ===============================
// Event Structure (Singly Linked List)
// ===============================
struct Event {
    string eventName;
    string eventType; // e.g., "Wedding Hall", "Party"
    string customerName;
    int numberOfGuests;
    string date; // Consider a more robust date type for a real system
    float price;
    Event* next;
};

class EventList {
    Event* head;
public:
    EventList() : head(nullptr) {}

    // Destructor to free memory
    ~EventList() {
        Event* current = head;
        while (current) {
            Event* next = current->next;
            delete current;
            current = next;
        }
    }

    void addEvent() {
        string name, type, custName, date;
        int guests;
        float eventPrice;

        cout << "Enter Event Name (e.g., 'Grand Wedding', 'Birthday Party'): ";
        getline(cin >> ws, name);
        cout << "Enter Event Type (e.g., 'Wedding Hall', 'Party'): ";
        getline(cin >> ws, type);
        cout << "Enter Customer Name for Event: ";
        getline(cin >> ws, custName);
        cout << "Enter Number of Guests: ";
        cin >> guests;
        cin.ignore(); // Consume the newline character after cin >> guests
        cout << "Enter Event Date (DD-MM-YYYY): ";
        getline(cin >> ws, date);
        cout << "Enter Event Price: Rs.";
        cin >> eventPrice;
        cin.ignore(); // Consume the newline character

        // Check for more than 100 guests
        if (guests <= 100) {
            cout << "Events for more than 100 guests are prioritized in this module. For smaller events, please use room bookings.\n";
            return;
        }

        Event* newEvent = new Event{name, type, custName, guests, date, eventPrice, nullptr};
        newEvent->next = head;
        head = newEvent;

        cout << "Event '" << name << "' booked successfully for " << guests << " guests!\n";
    }

    void displayAllEvents() {
        Event* temp = head;
        if (!temp) {
            cout << "No events booked yet.\n";
            return;
        }
        cout << "\n--- All Booked Events ---\n";
        while (temp) {
            cout << "Event Name: " << temp->eventName
                 << " | Type: " << temp->eventType
                 << " | Customer: " << temp->customerName
                 << " | Guests: " << temp->numberOfGuests
                 << " | Date: " << temp->date
                 << " | Price: Rs." << fixed << setprecision(2) << temp->price << endl;
            temp = temp->next;
        }
    }

    // You could add a deleteEvent function here similar to deleteBooking
    // based on event name or customer name if needed.
};

// ===============================
// Main Program
// ===============================
int main() {
    RoomBST hotelRooms;
    CustomerList hotelCustomers;
    FeedbackQueue feedbacks;
    StaffList staff;
    CheckStack checkIns;
    EventList hotelEvents; // New EventList object

    int choice;

    // Initial hardcoded rooms
    hotelRooms.addRoom(101, 3500);
    hotelRooms.addRoom(102, 4000);
    hotelRooms.addRoom(103, 5000);
    hotelRooms.addRoom(201, 5500);

    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Book Room\n2. View All Rooms\n3. View All Customers\n4. Cancel Booking\n5. Generate Bill\n";
        cout << "6. Add Feedback\n7. View Feedback\n8. Add Staff\n9. View Staff\n10. View Last Check-In\n11. Check-Out Guest\n";
        cout << "12. Add New Room\n";
        cout << "13. Book Event (Wedding Hall/Party)\n14. View All Events\n"; // New Event options
        cout << "0. Exit\nEnter choice: ";
        cin >> choice;
        // cin.ignore() is used after numerical input (like cin >> choice, cin >> roomNum, cin >> price, cin >> days, cin >> guests, cin >> eventPrice)
        // to consume the leftover newline character, preventing issues with subsequent getline() calls.
        if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 &&
            choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11 &&
            choice != 12 && choice != 13 && choice != 14) {
            // Only consume if not a choice that immediately uses getline
            // For general safety, it's often better to just use cin.ignore() after every cin >> int/float.
            // However, specific scenarios with getline() require careful handling.
            // The existing `cin.ignore()` after each relevant `cin` in the methods is more robust.
            // This `cin.ignore()` here is a fallback for the main menu choice.
             cin.ignore();
        }


        switch (choice) {
            case 1: hotelCustomers.bookRoom(hotelRooms, checkIns); break;
            case 2: hotelRooms.displayAllRooms(); break;
            case 3: hotelCustomers.showCustomers(); break;
            case 4: hotelCustomers.deleteBooking(hotelRooms); break;
            case 5: hotelCustomers.generateBill(hotelRooms); break;
            case 6: feedbacks.addFeedback(); break;
            case 7: feedbacks.showFeedback(); break;
            case 8: staff.addStaff(); break;
            case 9: staff.displayStaff(); break;
            case 10: checkIns.showLastCheckIn(); break;
            case 11: checkIns.checkOut(); break;
            case 12: {
                int roomNum;
                float price;
                cout << "Enter Room Number: ";
                cin >> roomNum;
                cout << "Enter Price per Day: ";
                cin >> price;
                hotelRooms.addRoom(roomNum, price);
                // Ensure to consume the newline after the last numerical input
                cin.ignore();
                break;
            }
            case 13: hotelEvents.addEvent(); break; // Call addEvent for booking events
            case 14: hotelEvents.displayAllEvents(); break; // Call displayAllEvents
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
