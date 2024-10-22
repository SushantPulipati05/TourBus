#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>  

using namespace std;

class TourBus {
    int bid;
    char destination[200];
    char time[50];
    int max_seats;
    int booked;
    int fare;

public:
    TourBus() {
        bid = 0;
        max_seats = 50;
        booked = 0;
        fare = 0;
        strcpy(time, "9:10am");
        strcpy(destination, "");
    }

    void input();
    void show() const;
    void display();
    int getid() {
        return bid;
    }
    void book() {
        if (booked < max_seats) {
            booked++;
        } else {
            cout << "All seats are booked!" << endl;
        }
    }
    char* getDestination() {
        return destination;
    }
    char* getTime() {
        return time;
    }
    int getBooked() {
        return booked;
    }
    int getMax() {
        return max_seats;
    }
    int getFare() {
        return fare;
    }
};

class Ticket {
    char name[50];
    TourBus bus;

public:
    void generate(const char cname[], const TourBus& tb) {
        strcpy(name, cname);
        bus = tb;
    }
    void display() const {
        cout << "Customer Name: " << name << endl;
        cout << "Details of Bus: " << endl;
        bus.show();
    }
    const char* getName() const {  
        return name;
    }
};

void TourBus::input() {
    cout << "Enter bus id: ";
    cin >> bid;
    cout << "Enter bus destination: ";
    cin.ignore();  
    cin.getline(destination, sizeof(destination));
    cout << "Enter time of bus: ";
    cin.getline(time, sizeof(time));
    cout << "Enter fare of the bus: ";
    cin >> fare;
}

void TourBus::display() {
    cout << bid << "\t" << destination << "\t" << time << "\t" << max_seats << "\t" << booked << "\t" << fare << "\n";
}

void TourBus::show() const{
    cout << "Bus Id: " << bid << endl;
    cout << "Destination: " << destination << endl;
    cout << "Time: " << time << endl;
    cout << "No. of seats remaining: " << max_seats - booked << endl;
}

int main() {
    int ch;
    fstream F, G;
    TourBus b;

    
    int id, chk;
    char dest[70], cname[50];
    Ticket t;

    do {
        system("CLS"); 
        cout << "Press 1 - Add a New Tour Bus" << endl;
        cout << "Press 2 - Show Selected Bus" << endl;
        cout << "Press 3 - Display All Buses" << endl;
        cout << "Press 4 - Delete a Bus" << endl;
        cout << "Press 5 - Book a ticket " << endl;
        cout << "Press 6 - Display Booked Tickets " << endl;
        cout << "Press 7 - Delete a booked ticket " << endl;
        cout << "Press 8 - Exit" << endl; 
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            F.open("tour.dat", ios::app | ios::binary);
            if (!F) {
                cout << "Can't open file for writing." << endl;
                system("pause");
                break;
            }
            b.input();
            F.write(reinterpret_cast<char*>(&b), sizeof(b));
            F.close();
            cout << "Bus added Successfully " << endl;
            system("pause");
            break;

        case 2:
            chk = 0;
            cout << "Enter the bus id to be displayed: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            if (!F) {
                cout << "Can't open file for reading." << endl;
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (b.getid() == id) {
                        b.show();
                        chk = 1;
                        break;
                    }
                }
                if (chk == 0)
                    cout << "Bus not Found" << endl;
            }
            F.close();
            system("pause");
            break;

        case 3:
            F.open("tour.dat", ios::in | ios::binary);
            if (!F) {
                cout << "Can't open file for reading." << endl;
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    b.display();
                }
            }
            F.close();
            cout << "Press a key to continue ";
            system("pause");
            break;

        case 4:
            chk = 0;
            cout << "Enter the bus id to be deleted: ";
            cin >> id;
            F.open("tour.dat", ios::in | ios::binary);
            G.open("temp.dat", ios::out | ios::binary);
            if (!F) {
                cout << "Can't open source file for reading." << endl;
            } else if (!G) {
                cout << "Can't open temporary file for writing." << endl;
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (b.getid() != id) {
                        G.write(reinterpret_cast<char*>(&b), sizeof(b));
                    } else {
                        b.show();
                        chk = 1;
                    }
                }
                if (chk == 0)
                    cout << "Bus not Found" << endl;
                else
                    cout << "Bus Deleted " << endl;
            }
            F.close();
            G.close();
            remove("tour.dat");
            rename("temp.dat", "tour.dat");
            system("pause");
            break;

        case 5:
            chk = 0;
            cout << "Enter the destination: ";
            cin.ignore();
            cin.getline(dest, sizeof(dest));
            F.open("tour.dat", ios::in | ios::out | ios::binary);
            if (!F) {
                cout << "Can't open file for reading/writing." << endl;
            } else {
                while (F.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                    if (strcmp(b.getDestination(), dest) == 0) {
                        b.show();
                        chk = 1;
                        cout << "Enter the customer name: ";
                        cin.getline(cname, sizeof(cname));
                        b.book();
                        t.generate(cname, b);
                        G.open("tickets.dat", ios::app | ios::binary);
                        if (G) {
                            G.write(reinterpret_cast<char*>(&t), sizeof(t));
                            G.close();
                        } else {
                            cout << "Can't open tickets file for writing." << endl;
                        }
                        F.seekp(static_cast<std::streampos>(F.tellg()) - static_cast<std::streamoff>(sizeof(b)), ios::beg);
                        F.write(reinterpret_cast<char*>(&b), sizeof(b));
                        cout << "Ticket booked" << endl;
                        system("pause");
                        break;
                    }
                }
                if (chk == 0)
                    cout << "No Bus Found" << endl;
            }
            F.close();
            break;

        case 6:
            cout << "Booked Tickets " << endl;
            G.open("tickets.dat", ios::in | ios::binary);
            if (!G) {
                cout << "Can't open tickets file for reading." << endl;
            } else {
                while (G.read(reinterpret_cast<char*>(&t), sizeof(t))) {
                    t.display();
                }
            }
            G.close();
            cout << "Press a key to continue ";
            system("pause");
            break;

        case 7:
            chk = 0;
            cout << "Enter the customer name to delete the ticket: ";
            cin.ignore();  
            cin.getline(cname, sizeof(cname));
            G.open("tickets.dat", ios::in | ios::binary);
            fstream tempFile;
            tempFile.open("temp.dat", ios::out | ios::binary);

            if (!G) {
                cout << "Can't open tickets file for reading." << endl;
            } else if (!tempFile) {
                cout << "Can't open temporary file for writing." << endl;
            } else {
                while (G.read(reinterpret_cast<char*>(&t), sizeof(t))) {
                    if (strcmp(t.getName(), cname) != 0) {
                        tempFile.write(reinterpret_cast<char*>(&t), sizeof(t));
                    } else {
                        cout << "Ticket for " << cname << " deleted." << endl;
                        chk = 1;
                    }
                }
                if (chk == 0) {
                    cout << "No ticket found for customer " << cname << endl;
                }
            }
            G.close();
            tempFile.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            system("pause");
            break;

        }
    } while (ch != 8);

    return 0;
}
