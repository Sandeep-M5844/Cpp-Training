#include<iostream>
#include<queue>
#include<vector>
#include<thread>
using namespace std;

class vehicle
{
public:
    string vech_no;
    int veh_type;
    int entry_time;
    int exit_time;
    double parking_fee;

public:
    vehicle(string vno, int vtype, int entry_time)
    {
        vech_no = vno;
        veh_type = vtype;
        this->entry_time = entry_time;
        exit_time = -1;
        parking_fee = 0;
    }

    void calculateParkingFee()
    {
        // 1-> 20rs 2->10rs ->0->0rs
        if(veh_type == 0)
        {
            return;
        }
        int duration = exit_time - entry_time;  // Duration in minutes
        if (veh_type == 1)  // cars vehicle
        {
            parking_fee = duration * 20.0 / 60.0; 
        }
        else if(veh_type == 2)  // bike vehicles
        {
            parking_fee = duration * 10.0 / 60.0;  // $10 per hour
        }
    }
};

class parking
{
private:
    queue<vehicle*> waiting_queue;  
    int basement;
    int parking_slots;
    double total_revenue;
    vector<vector<vehicle*>> parking_area; 
    queue<vehicle*> entry_parking_queue;    
    queue<vehicle*> exit_parking_queue;    
    vector<vehicle*> emergency_vehicles;

public:
    parking()
    {
        cout << "Enter number of basements available in the parking lot: " << endl;
        cin >> basement;
        cout << "Enter the number of parking slots available: " << endl;
        cin >> parking_slots;

        // Initialize parking area with nullptr
        parking_area.resize(basement, vector<vehicle*>(parking_slots, nullptr));
        total_revenue = 0;
    }

    int get_current_time()
    {
        time_t now = time(0);
        return static_cast<int>(now / 60);  // Return time in minutes 
    }

    void parking_entry()
    {
        string vehicle_number = "";
        int vehicle_type;

        cout << "Enter vehicle number: " << endl;
        cin >> vehicle_number;

        cout << "Enter vehicle type (1 for 4 weller, 2 for 2 weeler,0 emergency ): ";
        cin >> vehicle_type;

        int current_time = get_current_time();

        vehicle* new_Vehicle_data = new vehicle(vehicle_number, vehicle_type, current_time);

        if (vehicle_type == 0)
        {
            emergency_vehicles.push_back(new_Vehicle_data);
            cout << "Emergency vehicle " << vehicle_number << " added to the emergency parking space." << endl;
        }
        else
        {
            entry_parking_queue.push(new_Vehicle_data);
        }

        process_parking();
    }

    void process_parking()
    {
        if (!entry_parking_queue.empty())
        {
            vehicle* new_vehicle_entry = entry_parking_queue.front();
            entry_parking_queue.pop();

            bool parked = false;
            for (int i = 0; i < basement; ++i)
            {
                for (int j = 0; j < parking_slots; ++j)
                {
                    if (parking_area[i][j] == nullptr)
                    {
                        parking_area[i][j] = new_vehicle_entry;

                        cout << "Vehicle " << new_vehicle_entry->vech_no << " is parked in Basement " << i + 1 
                            << ", Slot " << j + 1 << endl;
                        parked = true;
                        break; 
                    }
                }

                if (parked)
                {
                    break;
                }
            }

            if (!parked)
            {
                cout << "Parking lot is full, adding vehicle " 
                    << new_vehicle_entry->vech_no << " to the waiting queue" << endl;
                waiting_queue.push(new_vehicle_entry);
            }
        }
    }

    void parking_exit()
    {
        string vehicle_number;
        cout << "Enter vehicle number for exit: ";
        cin >> vehicle_number;

        bool found = false;

        for (auto it = emergency_vehicles.begin(); it != emergency_vehicles.end(); ++it)
        {
            if ((*it)->vech_no == vehicle_number)
            {
                cout << "Emergency vehicle " << vehicle_number << " has exited." << endl;
                delete* it;  
                emergency_vehicles.erase(it); 
                found = true;
                break;
            }
        }

        if (!found)
        {
            for (int i = 0; i < basement; ++i)
            {
                for (int j = 0; j < parking_slots; ++j)
                {
                    if (parking_area[i][j] != nullptr && parking_area[i][j]->vech_no == vehicle_number)
                    {
                        int current_time = get_current_time();
                        parking_area[i][j]->exit_time = current_time;
                        parking_area[i][j]->calculateParkingFee();  // Calculate the parking fee
                        total_revenue += parking_area[i][j]->parking_fee;
                        cout << "Vehicle " << vehicle_number << " has exited from Basement "
                            << i + 1 << ", Slot " << j + 1 << endl;
                        cout << "Parking Fee: $" << parking_area[i][j]->parking_fee << endl;
                            
                        delete parking_area[i][j];
                        parking_area[i][j] = nullptr;
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }

            if (!found)
            {
                cout << "Vehicle not found in the parking lot" << endl;
            }
            else
            {
               
                if (!waiting_queue.empty())
                {
                    vehicle* next_vehicle = waiting_queue.front();
                    waiting_queue.pop();
                    cout << "Parking slot is now free, parking next waiting vehicle: "
                        << next_vehicle->vech_no << endl;
                    entry_parking_queue.push(next_vehicle);
                    process_parking();
                }
            }
        }
    }

    void systemReport()
    {
        int total_no_of_cars_parked = 0;
        int parking_space_left = 0;
        int total_no_of_cars_in_waiting_queue = waiting_queue.size();
        int total_no_of_emergency_vehicles = emergency_vehicles.size();

        for (int i = 0; i < basement; ++i)
        {
            for (int j = 0; j < parking_slots; ++j)
            {
                if (parking_area[i][j] != nullptr)
                {
                    total_no_of_cars_parked++;
                }
            }
        }

        for (int i = 0; i < basement; ++i)
        {
            for (int j = 0; j < parking_slots; ++j)
            {
                if (parking_area[i][j] == nullptr)
                {
                    parking_space_left++;
                }
            }
        }

        cout << endl << "System Report: " << endl;
        cout << "Total number of vehicles parked (Normal): " << total_no_of_cars_parked << endl;
        cout << "Parking spaces left: " << parking_space_left << endl;
        cout << "Total number of vehicles in waiting queue: " << total_no_of_cars_in_waiting_queue << endl;
        cout << "Total number of emergency vehicles in the parking lot: " << total_no_of_emergency_vehicles << endl;
        cout << "Total revenue generated: $" << total_revenue << endl;

    }

    void displayParkingSpace()
    {
        cout << "Current Parking Space Status:"<<endl;
        for (int i = 0; i < basement; ++i)
        {
            cout << "Basement " << i + 1 << ": ";
            for (int j = 0; j < parking_slots; ++j)
            {
                if (parking_area[i][j] == nullptr)
                {
                    cout << "[Empty] ";
                }
                else
                {
                    cout << "[" << parking_area[i][j]->vech_no << "] ";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    parking p;

    while (true) {
        int choice;
        cout << "\nParking Management System"<<endl;
        cout << "1. Vehicle Entry"<<endl;
        cout << "2. Vehicle Exit"<<endl;
        cout << "3. Show Parking Report"<<endl;
        cout << "4. Show Parking Space"<<endl;
        cout << "5. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            p.parking_entry();
            this_thread::sleep_for(chrono::seconds(2));  // Sleep for 2 seconds
            break;
        case 2:
            p.parking_exit();
            break;
        case 3:
            p.systemReport();
            break;
        case 4:
            p.displayParkingSpace();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}