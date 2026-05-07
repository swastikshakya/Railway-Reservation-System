#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

class Railway
{
private:
    int trainNo;
    char trainName[50];
    char source[50];
    char destination[50];
    char passengerName[50];
    int age;
    char gender[10];
    int seatNo;
    char coach[10];
    long long mobile;
    float fare;
    int pnr;
    char journeyDate[20];
    char bookingStatus[20];

public:
    void addTrain();
    void showTrain();
    void bookTicket();
    void showTicket();
    void saveTicket();
    void displayAllTickets();
    int getSeatNo();
    int getPNR();
    char* getPassengerName();
    void searchTicket();
};

void Railway::addTrain()
{
    cout << "\nEnter Train Number: ";
    cin >> trainNo;

    cin.ignore();

    cout << "Enter Train Name: ";
    cin.getline(trainName, 50);

    cout << "Enter Source: ";
    cin.getline(source, 50);

    cout << "Enter Destination: ";
    cin.getline(destination, 50);

    ofstream trainFile("trains.dat", ios::binary | ios::app);
    trainFile.write((char*)this, sizeof(*this));
    trainFile.close();

    cout << "\nTrain Added Successfully!\n";
}

void Railway::showTrain()
{
    cout << "\nTrain No       : " << trainNo;
    cout << "\nTrain Name     : " << trainName;
    cout << "\nSource         : " << source;
    cout << "\nDestination    : " << destination;
    cout << "\n----------------------------------";
}

void Railway::bookTicket()
{
    cout << "\nEnter Train Number: ";
    cin >> trainNo;

    cin.ignore();

    cout << "Enter Passenger Name: ";
    cin.getline(passengerName, 50);

    cout << "Enter Age: ";
    cin >> age;

    cin.ignore();

    cout << "Enter Gender: ";
    cin.getline(gender, 10);

    cout << "Enter Mobile Number: ";
    cin >> mobile;

    cout << "Enter Seat Number: ";
    cin >> seatNo;

    cin.ignore();

    cout << "Enter Coach Type (AC/Sleeper): ";
    cin.getline(coach, 10);

    cout << "Enter Journey Date: ";
    cin.getline(journeyDate, 20);

    pnr = 1000 + seatNo + trainNo;

    if(strcmp(coach, "AC") == 0)
        fare = 1500;
    else
        fare = 800;

    strcpy(bookingStatus, "CONFIRMED");

    cout << "\nTicket Booked Successfully!";
    cout << "\nGenerated PNR: " << pnr;
}

void Railway::showTicket()
{
    cout << "\n=========== TICKET ===========";
    cout << "\nPNR Number      : " << pnr;
    cout << "\nTrain Number    : " << trainNo;
    cout << "\nPassenger Name  : " << passengerName;
    cout << "\nAge             : " << age;
    cout << "\nGender          : " << gender;
    cout << "\nMobile          : " << mobile;
    cout << "\nSeat Number     : " << seatNo;
    cout << "\nCoach           : " << coach;
    cout << "\nJourney Date    : " << journeyDate;
    cout << "\nFare            : " << fare;
    cout << "\nBooking Status  : " << bookingStatus;
    cout << "\n================================\n";
}

void Railway::saveTicket()
{
    ofstream file("tickets.dat", ios::binary | ios::app);

    file.write((char*)this, sizeof(*this));

    file.close();
}

void Railway::displayAllTickets()
{
    ifstream file("tickets.dat", ios::binary);

    Railway r;

    while(file.read((char*)&r, sizeof(r)))
    {
        r.showTicket();
    }

    file.close();
}

int Railway::getSeatNo()
{
    return seatNo;
}

int Railway::getPNR()
{
    return pnr;
}

char* Railway::getPassengerName()
{
    return passengerName;
}

void Railway::searchTicket()
{
    int searchPNR;
    bool found = false;

    cout << "\nEnter PNR Number: ";
    cin >> searchPNR;

    ifstream file("tickets.dat", ios::binary);

    Railway r;

    while(file.read((char*)&r, sizeof(r)))
    {
        if(r.getPNR() == searchPNR)
        {
            r.showTicket();
            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nTicket Not Found!\n";
}

void cancelTicket()
{
    int seat;
    bool found = false;

    cout << "\nEnter Seat Number to Cancel: ";
    cin >> seat;

    Railway r;

    ifstream file("tickets.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while(file.read((char*)&r, sizeof(r)))
    {
        if(r.getSeatNo() != seat)
        {
            temp.write((char*)&r, sizeof(r));
        }
        else
        {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("tickets.dat");
    rename("temp.dat", "tickets.dat");

    if(found)
        cout << "\nTicket Cancelled Successfully!\n";
    else
        cout << "\nSeat Not Found!\n";
}

void displayTrainList()
{
    ifstream file("trains.dat", ios::binary);

    Railway r;

    while(file.read((char*)&r, sizeof(r)))
    {
        r.showTrain();
    }

    file.close();
}

int main()
{
    Railway r;

    int choice;
    char password[20];

    cout << "\n===== LOGIN SYSTEM =====";

    cout << "\nEnter Admin Password: ";
    cin >> password;

    if(strcmp(password, "admin123") != 0)
    {
        cout << "\nWrong Password!";
        return 0;
    }

    do
    {
        cout << "\n\n====== RAILWAY RESERVATION SYSTEM ======";

        cout << "\n1. Add Train";
        cout << "\n2. Show Train List";
        cout << "\n3. Book Ticket";
        cout << "\n4. Show All Tickets";
        cout << "\n5. Search Ticket by PNR";
        cout << "\n6. Cancel Ticket";
        cout << "\n7. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            r.addTrain();
            break;

        case 2:
            displayTrainList();
            break;

        case 3:
            r.bookTicket();
            r.saveTicket();
            break;

        case 4:
            r.displayAllTickets();
            break;

        case 5:
            r.searchTicket();
            break;

        case 6:
            cancelTicket();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while(choice != 7);

    return 0;
}
