#include "Customer.h"
#include <time.h>
#include <cstdlib>
#include <cstddef>
#include <iostream>

using namespace std;

Customer::Customer() //: max_length(420)
{
}

Customer::Customer(int id, int time)
{
    customer_id = id;
    arrival_time = time;
    num_of_loads = rand() % 3 + 1;
    customer_served = false;
    set_load_array(num_of_loads);
    end_time = 0;
}

/** Getters and Setters **/

void Customer::set_customer_id(int id)
{
    customer_id = id;
}

void Customer::set_arrival_time(int time)
{
    arrival_time = time;
}

void Customer::set_num_of_loads(int number)
{
    num_of_loads = number;
}

void Customer::set_customer_served(bool served)
{
    customer_served = served;
}

int Customer::get_customer_id()
{
    return customer_id;
}

int Customer::get_arrival_time()
{
    return arrival_time;
}

int Customer::get_num_of_loads()
{
    return num_of_loads;
}

int Customer::get_estimated_load_completion()
{
    return estimated_load_completion;
}

bool Customer::get_customer_served()
{
    return customer_served;
}

void Customer::set_end_time(int endtime)
{
    end_time = endtime;
}

int Customer::get_end_time()
{
    return end_time;
}

/** Setup Functions **/

// Sets our Load array with the randomly generated # of loads, tracks the
//Highest load time of the loads.
void Customer::set_load_array(int num)
{
    int highest = 0;
    for(int i = 0; i < num; i++)
    {
        loads[i] = Load(customer_id);
        if ((loads[i].get_random_load_size()) > highest)
        {
            highest = loads[i].get_random_load_size();
        }
    }
    estimated_load_completion = highest;
}

//Used to access load of laundry, parameter used is the index.
Load* Customer::get_load(int index)
{
    return &loads[index];
}
