#include "LaundromatDay.h"
#include "Machine.h"
#include "Customer.h"
#include "Load.h"
#include "LoadQueue.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

LaundromatDay::LaundromatDay()
{

}

LaundromatDay::LaundromatDay(int c_p_h, int washers, int dryers, int days)
{
    cust_per_hour = c_p_h;
    num_washers = washers;
    num_dryers = dryers;
    num_days = days;
    day_count = 0;
    init_machine_arrays();
    num_finished_customers = 0;
    customer_wait_count=0;
}

LaundromatDay::~LaundromatDay()
{
    //dtor
}

/** Getters and Setters **/

void LaundromatDay::set_num_finished_customers()
{
    num_finished_customers = 0;
}

int LaundromatDay::get_num_finished_customers()
{
    return num_finished_customers;
}

void LaundromatDay::set_customer_wait_count()
{
    customer_wait_count = 0;
}

int LaundromatDay::get_customer_wait_count()
{
    return customer_wait_count;
}

void LaundromatDay::set_cust_per_hour(int c_p_h)
{
    cust_per_hour = c_p_h;
}
void LaundromatDay::set_num_washers(int n_w)
{
    num_washers = n_w;
}
void LaundromatDay::set_num_dryers(int n_d)
{
    num_dryers = n_d;
}
void LaundromatDay::set_customers_served(int c_s)
{
    customers_served = c_s;
}

int LaundromatDay::get_cust_per_hour()
{
    return cust_per_hour;
}

int LaundromatDay::get_num_washers()
{
    return num_washers;
}

int LaundromatDay::get_num_dryers()
{
    return num_dryers;
}

int LaundromatDay::get_customers_served()
{
    return customers_served;
}

/** Class Function **/

void LaundromatDay::output_file(ofstream& log)
{
    log.open("output.txt");
    if(log.fail())
    {
        cout << "Output file error!";
        exit(1);
    }
}

void LaundromatDay::simulate_day()
{
    //output_file(log_book);
    customers_served = 0;
    c_time = 0;
    cout << "***************************************************" << endl;
    cout << "Day " << day_count << ": \n";
    cout << "***************************************************" << endl << endl;

    //When day has expired, continue the day until the queues are empty.
    while(c_time < MAX_MINUTES || !check_all_customers_served())
    {
        if(c_time < MAX_MINUTES)
        {
            if(customer_arrival())
                create_customer();
        }

        check_machines_loads();
        check_queues();
        check_customer_finished();
        c_time++;

    }
    day_count++;
}

//randomizes customer arrival
bool LaundromatDay::customer_arrival()
{
    return((cust_per_hour/60.0*100) > (rand()%100+1));
}

//Create a customer with the current time as arrival time and the ID.
//Place the customers loads into the washQ.
void LaundromatDay::create_customer()
{
    customers[customers_served] = Customer(customers_served, c_time);

    for(int i = 0; i < customers[customers_served].get_num_of_loads(); i++)
    {
        washQ.push_load(customers[customers_served].get_load(i));
    }

    /** REVAMP COUT **/
    cout << "Time " << c_time << ": Customer " << customers_served << " with "
             << customers[customers_served].get_num_of_loads() << " loads arrived." << endl;

    customers_served++;
}

//Initialize the washers and dryers into their respective arrays.
void LaundromatDay::init_machine_arrays()
{
    for(int i = 0; i < num_washers; i++)
    {
        washer[i] = Machine(Machine::Washer, i);
    }

    for(int i = 0; i < num_dryers; i++)
    {
        dryer[i] = Machine(Machine::Dryer, i);
    }
}

//Checks each customer for loads that are finished (if they aren't already finished)
void LaundromatDay::check_customer_finished()
{
    bool finished;

    for(int i = 0; i < customers_served; i++)
    {
        if(!customers[i].get_customer_served())
        {
            finished = true;
            for(int j = 0; j < customers[i].get_num_of_loads(); j++)
            {
                if(!customers[i].get_load(j)->is_finished())
                {
                    finished = false;
                }
            }

            if(finished)
            {
                customers[i].set_customer_served(true);
                customers[i].set_end_time(c_time);
                num_finished_customers++;
                /** REVAMP COUT **/
                cout << "Time " << c_time << ": Customer " << i << " is finished." << endl;
                if( ((c_time - customers[i].get_arrival_time()) - (30 + customers[i].get_estimated_load_completion())) != 0)
                {
                    customer_wait_count++;
                }
            }
        }

    }
}

//Checks each queue and moves the load into the machines from the appropriate queue.
void LaundromatDay::check_queues()
{
    //Checking Wash Queue
    //-1 is used if a machine is not available.
    while(!washQ.queue_empty() && (get_empty_machine(washer, num_washers) != -1))
    {
        //Loading first free washer with the first load off the washQ.
        /** REVAMP COUT **/
        cout << "Time " << c_time << ": ";
        washer[get_empty_machine(washer, num_washers)].load_machine(washQ.pop_load(), c_time);
    }

    //Checking Dry Queue
    while(!dryQ.queue_empty() && (get_empty_machine(dryer, num_dryers) != -1))
    {
        //Loading first free washer with the first load off the washQ.
        /** REVAMP COUT **/
        cout << "Time " << c_time << ": ";
        dryer[get_empty_machine(dryer, num_dryers)].load_machine(dryQ.pop_load(), c_time);
    }
}

//Check if loads in machines are done for that machine. If the loads are
//marked as completely done do nothing, if not move to dryer queue.
void LaundromatDay::check_machines_loads()
{
    for(int i = 0; i < num_washers; i++)
    {
        if(washer[i].check_load_done(c_time))
        {
            cout << "Time " << c_time;
            dryQ.push_load(washer[i].remove_load());
            cout << " done washing." << endl;
        }
    }

    for(int i = 0; i < num_dryers; i++)
    {
        if(dryer[i].check_load_done(c_time))
        {
            cout << "Time " << c_time;
            dryer[i].remove_load();
            cout << " done drying." << endl;
        }
    }
}

//Returns the index of the machine that is available
int LaundromatDay::get_empty_machine(Machine machines[], int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(machines[i].get_machine_empty())
        {
            return i;
        }
    }
    //If no machines are found  then -1 will be returned(signifying false).
    return -1;
}

//Checks all of machines to determine if they are collectively empty.
bool LaundromatDay::check_all_customers_served()
{
    for(int i = 0; i < customers_served; i++)
    {
        if(!customers[i].get_customer_served())
        {
            return false;
        }
    }
    return true;
}

void LaundromatDay::final_output_message(int w_c, int n_d)
{
    cout << endl << "# OF DAYS CUSTOMERS HAD TO WAIT: " << w_c << " OUT OF " << n_d << endl;
    cout << "PRECENTAGE OF DAYS WITH WAIT: " << (double)w_c/n_d*100 << "%" << endl;
}

void LaundromatDay::end_of_day_results()
{
    cout << endl;
    for(int i=0; i<num_finished_customers; i++)
        cout << "Customer " << i << " arrived at " << customers[i].get_arrival_time() << " done at "
                 << customers[i].get_end_time() << " should have been " <<  (customers[i].get_arrival_time()+30 + customers[i].get_estimated_load_completion())
                 << ". Customer waited: "
                 << (customers[i].get_end_time() - customers[i].get_arrival_time()) - (30 + customers[i].get_estimated_load_completion())
                 << " minutes." << endl;
}

