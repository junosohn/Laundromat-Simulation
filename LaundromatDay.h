#ifndef LAUNDROMATDAY_H
#define LAUNDROMATDAY_H
#include "Machine.h"
#include "Customer.h"
#include "LoadQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int MAX_CUSTOMERS = 420;
const int MAX_NUM_WASHERS = 100;
const int MAX_NUM_DRYERS = 100;
const int MAX_MINUTES = 420;

using namespace std;

class LaundromatDay
{
public:
    LaundromatDay();
    LaundromatDay(int, int, int, int);
    ~LaundromatDay();

    void set_cust_per_hour(int);
    void set_num_washers(int);
    void set_num_dryers(int);
    void set_customers_served(int);
    int get_cust_per_hour();
    int get_num_washers();
    int get_num_dryers();
    int get_customers_served();
    void simulate_day();
    bool customer_arrival();
    void create_customer();
    void init_machine_arrays();
    void check_customer_finished();
    void check_queues();
    void check_machines_loads();
    int get_empty_machine(Machine[], int);
    bool check_all_customers_served();
    void print_results();
    int get_customer_wait_count();
    void set_customer_wait_count();
    int get_num_finished_customers();
    void set_num_finished_customers();

    void final_output_message(int,int);
    void end_of_day_results();
    void output_file(ofstream& log);


private:
    int cust_per_hour;   // number of customers per hour
    int num_washers;      // total number of washing machines
    int num_dryers;      // total number of dryers;
    int customers_served; // total number of customers served
    int c_time;          // current time in the simulation
    int day_count;      //keep track of the number of days
    int num_days;       //number of days to run simulation
    int num_finished_customers; //number of customers that have picked up their loads
    LoadQueue washQ;     // washing queue
    LoadQueue dryQ;      // drying queue
    ofstream log_book;  //log file

    Customer customers[MAX_CUSTOMERS];   //array of customers
    Machine washer[MAX_NUM_WASHERS];    //array of washers
    Machine dryer[MAX_NUM_DRYERS];       //array of dryers

    int customer_wait_count;
};

#endif // LAUNDROMATDAY_H
