#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Base Room Class
class Room
{
protected:
    int roomNumber;
    double pricePerNight;
    bool isAvailable;
    string roomType;

public:
    Room(int number, double price, string type)
        : roomNumber(number), pricePerNight(price), isAvailable(true), roomType(type) {}

    virtual double calculateCost(int nights)
    {
        return pricePerNight * nights;
    }

    virtual void displayInfo()
    {
        cout << "Room " << roomNumber << " | " << roomType
             << " | ₹" << pricePerNight << "/night | "
             << (isAvailable ? "Available" : "Occupied") << endl;
    }

    // Getters
    int getRoomNumber() { return roomNumber; }
    double getPrice() { return pricePerNight; }
    bool getAvailability() { return isAvailable; }
    string getRoomType() { return roomType; }

    // Setters
    void bookRoom() { isAvailable = false; }
    void vacateRoom() { isAvailable = true; }
};

// Inherited Room Types
class StandardRoom : public Room
{
public:
    StandardRoom(int number) : Room(number, 100.0, "Standard") {}

    double calculateCost(int nights) override
    {
        return pricePerNight * nights; // No extra charges
    }
};

class DeluxeRoom : public Room
{
public:
    DeluxeRoom(int number) : Room(number, 200.0, "Deluxe") {}

    double calculateCost(int nights) override
    {
        return pricePerNight * nights; // Base price
    }
};

class Suite : public Room
{
public:
    Suite(int number) : Room(number, 350.0, "Suite") {}

    double calculateCost(int nights) override
    {
        // Suite includes breakfast - add small service fee
        return (pricePerNight * nights) + (20 * nights);
    }
};

// Guest Class
class Guest
{
private:
    string name;
    string phone;
    string email;
    int guestId;

public:
    Guest(int id, string gName, string gPhone, string gEmail)
        : guestId(id), name(gName), phone(gPhone), email(gEmail) {}

    void displayInfo()
    {
        cout << "Guest ID: " << guestId << " | " << name
             << " | " << phone << " | " << email << endl;
    }

    string getName() { return name; }
    int getGuestId() { return guestId; }
};

// Reservation Class
class Reservation
{
private:
    int reservationId;
    Guest *guest;
    Room *room;
    string checkInDate;
    string checkOutDate;
    int totalNights;
    double totalCost;

public:
    Reservation(int id, Guest *g, Room *r, string inDate, string outDate, int nights)
        : reservationId(id), guest(g), room(r), checkInDate(inDate),
          checkOutDate(outDate), totalNights(nights)
    {
        totalCost = room->calculateCost(totalNights);
        room->bookRoom();
    }

    void displayReservation()
    {
        cout << "\n=== Reservation Details ===" << endl;
        cout << "Reservation ID: " << reservationId << endl;
        guest->displayInfo();
        room->displayInfo();
        cout << "Check-in: " << checkInDate << " | Check-out: " << checkOutDate << endl;
        cout << "Total Nights: " << totalNights << " | Total Cost: ₹" << totalCost << endl;
    }

    Room *getRoom() { return room; }
    Guest *getGuest() { return guest; }
    double getCost() { return totalCost; }
};

// Main Hotel Management Class
class Hotel
{
private:
    string hotelName;
    vector<Room *> rooms;
    vector<Guest *> guests;
    vector<Reservation *> reservations;
    int nextGuestId;
    int nextReservationId;

public:
    Hotel(string name) : hotelName(name), nextGuestId(1), nextReservationId(1)
    {
        initializeRooms();
    }

    ~Hotel()
    {
        // Cleanup memory
        for (auto room : rooms)
            delete room;
        for (auto guest : guests)
            delete guest;
        for (auto res : reservations)
            delete res;
    }

    void initializeRooms()
    {
        // Create some sample rooms
        for (int i = 101; i <= 103; i++)
        {
            rooms.push_back(new StandardRoom(i));
        }
        for (int i = 201; i <= 204; i++)
        {
            rooms.push_back(new DeluxeRoom(i));
        }
        for (int i = 301; i <= 305; i++)
        {
            rooms.push_back(new Suite(i));
        }
        cout << "Initialized " << rooms.size() << " rooms!" << endl;
    }

    void showAvailableRooms()
    {
        cout << "\n=== Available Rooms ===" << endl;
        bool found = false;
        for (auto room : rooms)
        {
            if (room->getAvailability())
            {
                room->displayInfo();
                found = true;
            }
        }
        if (!found)
        {
            cout << "🚫 No available rooms found!" << endl;
        }
    }

    void showAllRooms()
    {
        cout << "\n=== All Rooms ===" << endl;
        for (auto room : rooms)
        {
            room->displayInfo();
        }
    }

    Guest *registerGuest()
    {
        string name, phone, email;

        cout << "\n=== Guest Registration ===" << endl;
        cout << "Enter guest name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter phone: ";
        getline(cin, phone);
        cout << "Enter email: ";
        getline(cin, email);

        Guest *newGuest = new Guest(nextGuestId++, name, phone, email);
        guests.push_back(newGuest);

        cout << "✅ Guest registered successfully!" << endl;
        newGuest->displayInfo();
        return newGuest;
    }

    void makeReservation()
    {
        if (guests.empty())
        {
            cout << "⚠️ Please register a guest first!" << endl;
            return;
        }

        showAvailableRooms();
        int roomNumber, nights;
        string checkIn, checkOut;

        cout << "\nEnter room number to book: ";
        cin >> roomNumber;

        Room *selectedRoom = nullptr;
        for (auto room : rooms)
        {
            if (room->getRoomNumber() == roomNumber && room->getAvailability())
            {
                selectedRoom = room;
                break;
            }
        }

        if (!selectedRoom)
        {
            cout << "🚫 Room not available or invalid room number!" << endl;
            return;
        }

        cout << "Enter check-in date (DD/MM/YYYY): ";
        cin >> checkIn;
        cout << "Enter check-out date (DD/MM/YYYY): ";
        cin >> checkOut;
        cout << "Enter number of nights: ";
        cin >> nights;

        // Show latest guest or let user choose
        Guest *guest = guests.back();
        cout << "Booking for guest: ";
        guest->displayInfo();

        Reservation *newReservation = new Reservation(nextReservationId++, guest,
                                                      selectedRoom, checkIn, checkOut, nights);
        reservations.push_back(newReservation);

        cout << "\nReservation successful!" << endl;
        newReservation->displayReservation();
    }

    void checkOut()
    {
        if (reservations.empty())
        {
            cout << "♻️ No active reservations!" << endl;
            return;
        }

        showAllReservations();
        int resId;
        cout << "Enter reservation ID to check out: ";
        cin >> resId;

        for (auto it = reservations.begin(); it != reservations.end(); ++it)
        {
            if (true)
            { // In real system, check if reservation matches ID
                cout << "\n=== Checking Out ===" << endl;
                (*it)->displayReservation();
                (*it)->getRoom()->vacateRoom();
                cout << "Room " << (*it)->getRoom()->getRoomNumber() << " is now available." << endl;
                delete *it;
                reservations.erase(it);
                return;
            }
        }
        cout << "🚫 Reservation ID not found!" << endl;
    }

    void showAllReservations()
    {
        if (reservations.empty())
        {
            cout << "🚫 No reservations found!" << endl;
            return;
        }

        cout << "\n=== All Reservations ===" << endl;
        for (auto res : reservations)
        {
            res->displayReservation();
        }
    }

    void showMenu()
    {
        cout << "\n"
             << string(50, '=') << endl;
        cout << "    🏨 " << hotelName << " MANAGEMENT SYSTEM" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Show All Rooms" << endl;
        cout << "2. Show Available Rooms" << endl;
        cout << "3. Register New Guest" << endl;
        cout << "4. Make Reservation" << endl;
        cout << "5. Show All Reservations" << endl;
        cout << "6. Check Out" << endl;
        cout << "7. Exit" << endl;
        cout << string(50, '=') << endl;
        cout << "Choose option (1-7): ";
    }
};

// Main function
int main()
{
    Hotel hotel("EVEREST HOTEL");
    int choice;

    do
    {
        hotel.showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            hotel.showAllRooms();
            break;
        case 2:
            hotel.showAvailableRooms();
            break;
        case 3:
            hotel.registerGuest();
            break;
        case 4:
            hotel.makeReservation();
            break;
        case 5:
            hotel.showAllReservations();
            break;
        case 6:
            hotel.checkOut();
            break;
        case 7:
            cout << "Thank you for using Hotel Management System!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}