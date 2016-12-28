#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include "Load.h"

const int MAX_LOADS = 3;

using namespace std;

class Customer
{
    public:
        Customer();
        Customer(int, int);
        void set_customer_id(int);
        void set_arrival_time(int);
        void set_num_of_loads(int);
        void set_customer_served(bool);
        int get_customer_id();
        int get_arrival_time();
        int get_num_of_loads();
        int get_estimated_load_completion();
        bool get_customer_served();
        void set_load_array(int);
        Load* get_load(int);

        void set_end_time(int);
        int get_end_time();

    private:
        int customer_id;
        int arrival_time;
        int num_of_loads;
        int estimated_load_completion;
        Load loads[MAX_LOADS];
        bool customer_served;
        int end_time;

};

#endif // CUSTOMER_H
