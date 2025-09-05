#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HotelSystem {
public:
    virtual void showStatus() = 0; 
};


class RoomManager : public HotelSystem {
public:
    struct Room {
        int num;
        string type;
        bool available;
    };

    Room rooms[5];
    int roomCount = 0;

    void addRoom() {
        if (roomCount >= 5) {
            cout << "Max rooms reached!\n";
            return;
        }
        cout << "Room number: ";
        cin >> rooms[roomCount].num;
        cout << "Type (S/D): ";
        cin >> rooms[roomCount].type;
        rooms[roomCount].available = true;
        roomCount++;
        cout << "Room added!\n";
    }

    void showRooms() {
        cout << "\n=== Rooms ===\n";
        for (int i = 0; i < roomCount; i++) {
            cout << rooms[i].num << " - " << rooms[i].type
                 << (rooms[i].available ? " [Available]" : " [Booked]") << endl;
        }
    }

    bool isRoomAvailable(int roomNum) {
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].num == roomNum) {
                return rooms[i].available;
            }
        }
        return false;
    }

    void bookRoom(int roomNum) {
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].num == roomNum) {
                rooms[i].available = false;
                break;
            }
        }
    }

 
    void showStatus() override {
        showRooms();
    }
};


class BookingManager : public HotelSystem {
public:
    struct Booking {
        string guest;
        int room;
        string date;
    };

    Booking bookings[5];
    int bookCount = 0;

    void addBooking(string guest, int room, string date) {
        if (bookCount >= 5) {
            cout << "Max bookings reached!\n";
            return;
        }
        bookings[bookCount].guest = guest;
        bookings[bookCount].room = room;
        bookings[bookCount].date = date;
        bookCount++;
        cout << "Booking successful!\n";
    }

    void showBookings() {
        cout << "\n=== Bookings ===\n";
        for (int i = 0; i < bookCount; i++) {
            cout << bookings[i].guest << " - Room "
                 << bookings[i].room << " (" << bookings[i].date << ")\n";
        }
    }

   
    void showStatus() override {
        showBookings();
    }
};


class FileManager {
public:
    void saveData(RoomManager& rm, BookingManager& bm) {
        ofstream file("data.txt");
        file << rm.roomCount << endl;
        for (int i = 0; i < rm.roomCount; i++) {
            file << rm.rooms[i].num << " " << rm.rooms[i].type
                 << " " << rm.rooms[i].available << endl;
        }
        file << bm.bookCount << endl;
        for (int i = 0; i < bm.bookCount; i++) {
            file << bm.bookings[i].guest << " " << bm.bookings[i].room
                 << " " << bm.bookings[i].date << endl;
        }
        cout << "Data saved!\n";
    }

    void loadData(RoomManager& rm, BookingManager& bm) {
        ifstream file("data.txt");
        if (file) {
            file >> rm.roomCount;
            for (int i = 0; i < rm.roomCount; i++) {
                file >> rm.rooms[i].num >> rm.rooms[i].type >> rm.rooms[i].available;
            }
            file >> bm.bookCount;
            for (int i = 0; i < bm.bookCount; i++) {
                file >> bm.bookings[i].guest >> bm.bookings[i].room >> bm.bookings[i].date;
            }
            cout << "Data loaded!\n";
        } else {
            cout << "No saved data found!\n";
        }
    }
};


int main() {
    RoomManager rm;
    BookingManager bm;
    FileManager fm;
    HotelSystem* systems[2] = { &rm, &bm }; 
    int choice;

    while (true) {
        cout << "\n1. Add Room\n2. Book Room\n3. Show Status\n4. Save Data\n5. Load Data\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rm.addRoom();
                break;
            case 2: {
                string guest, date;
                int room;
                cin.ignore(); 
                cout << "Guest name: ";
                getline(cin, guest);
                cout << "Room number: ";
                cin >> room;
                cin.ignore(); 
                cout << "Date: ";
                getline(cin, date);

                if (rm.isRoomAvailable(room)) {
                    rm.bookRoom(room);
                    bm.addBooking(guest, room, date);
                } else {
                    cout << "Room not available or invalid!\n";
                }
                break;
            }
            case 3:
                for (int i = 0; i < 2; i++) {
                    systems[i]->showStatus();
                }
                break;
            case 4:
                fm.saveData(rm, bm);
                break;
            case 5:
                fm.loadData(rm, bm);
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

