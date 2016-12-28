#include "Machine.h"
#include <cstdlib>
#include <cstddef>
//#include <fstream>

using namespace std;

Machine::Machine()
{
}

Machine::Machine(MachineType machine_type, int id)
{
    type = machine_type;
    machine_id = id;
    machine_empty = true;
}

/** Getters and Setters **/

void Machine::set_machine_id(int id)
{
    machine_id = id;
}

void Machine::set_time_in(int time)
{
    time_in = time;
}

void Machine::set_machine_empty(bool mempty)
{
    machine_empty = mempty;
}

int Machine::get_machine_id()
{
    return machine_id;
}

int Machine::get_time_in()
{
    return time_in;
}

bool Machine::get_machine_empty()
{
    return machine_empty;
}

/** Class Functions **/

//Loads the machine with a load of laundry and the current time.
void Machine::load_machine(Load *laundry_load, int time)
{
    machine_empty = false;
    load = laundry_load;
    time_in = time;

    /// REVAMP COUT ///
    cout << "Putting load belonging to customer " << load->get_load_id()
    << " in ";

    if(type == Washer)
        cout << "washer";

    else
        cout << "dryer";

    cout << " " << machine_id << " for ";

    if(type == Washer)
        cout << "30 minutes" << endl;

    else
        cout << load->get_random_load_size() << " minutes" << endl;

}

//Checks if a load of laundry is done.
bool Machine::check_load_done(int time)
{
    if(machine_empty)
    {
        return false;
    }
    int load_time;
    if(type == Machine::Washer)
    {
        load_time = 30;
    }
    else
    {
        load_time = load->get_random_load_size();
    }

    if((time_in + load_time) == time)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//If the load is done, remove the load from the machine, set
//the machine to empty
Load* Machine::remove_load()
{
    //Setting the entire load as done (can be picked up).
    if(type == Machine::Dryer)
    {
        load->set_is_finished(true);
    }

    Load* temp = load;
    load = NULL;
    machine_empty = true;

    /** REVAMP COUT */
    cout << ": Load belonging to customer " << temp->get_load_id();

    return temp;
}

