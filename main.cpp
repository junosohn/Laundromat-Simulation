/*

VCC CMPT 1020 - Assignment 2

Laundromat Simulation

This program simulates: 1. A laundromat for a high
number of days, using a defined number of machines
and randomly generated average rate of customers per hour,
to find the optimal rate of customers per hour so that none
have to wait for their loads.
2. A laundromat for several days, with a set rate of customers
per hour, and an increasing number of machines, to find the minimum
number of machines needed so that no customers have to wait to
pick up their loads.

Authors: Junho Sohn, Tom Dorval, Eleanor Kim.
Date: 02/23/16   

*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include "LaundromatDay.h"

using namespace std;
int get_choice();
void intro_msg();

const int TEST = 0;
const int SCENARIO1 = 1;
const int SCENARIO2 = 2;
const int QUIT = 3;

int main()
{
    intro_msg();
    srand (time(NULL));
    int choice,cust_hour,num_w,num_d,num_days,wait_count;

    do
    {
        choice = get_choice();
        switch (choice)
        {

        case TEST:
        {
            system("CLS");
            wait_count=0;
            cout << "TEST: User inputs." << endl << endl;
            cout << "ENTER # DAYS YOU WANT TO SIMULATE: ";
            cin >> num_days;
            cout << "ENTER # OF CUSTOMERS PER HOUR: ";
            cin >> cust_hour;
            cout << "ENTER # OF WASHERS: ";
            cin >> num_w;
            cout << "ENTER # OF DRYERS: ";
            cin >> num_d;
            LaundromatDay laundromat(cust_hour, num_w, num_d, num_days);
            for (int i = 0; i < num_days; i++)
            {
                laundromat.simulate_day();
                laundromat.end_of_day_results();
                if(laundromat.get_customer_wait_count() > 0)
                    wait_count++;
                //resetting values to 0
                laundromat.set_customer_wait_count();
                laundromat.set_num_finished_customers();
            }

            laundromat.final_output_message(wait_count, num_days);
            break;
        }

        case SCENARIO1: //Simulates laundromat with set number of machines and variable customer/hour rate.
        {
            system("CLS");
            num_w = 12,num_d = 12;
            wait_count=0;
            cout << "SCENARIO 1: Number of washers and dryers = 12." << endl << endl;
            cout << "ENTER # DAYS YOU WANT TO SIMULATE: ";
            cin >> num_days;
            cout << "ENTER # OF CUSTOMERS PER HOUR: ";
            cin >> cust_hour;
            LaundromatDay laundromat(cust_hour, num_w, num_d, num_days);
            for (int i = 0; i < num_days; i++)
            {
                laundromat.simulate_day();
                laundromat.end_of_day_results();
                if(laundromat.get_customer_wait_count() > 0)
                    wait_count++;
                //resetting values to 0
                laundromat.set_customer_wait_count();
                laundromat.set_num_finished_customers();
            }

            laundromat.final_output_message(wait_count, num_days);
            break;
        }

        case SCENARIO2: //Simulates laundromat with set customers/hour rate and variable number of machines
        {
            system("CLS");
            cust_hour=6;
            wait_count=0;
            cout << "SCENARIO 2: Average number of customers = 6." << endl << endl;
            cout << "ENTER # DAYS YOU WANT TO SIMULATE: ";
            cin >> num_days;
            cout << "ENTER # OF WASHERS: ";
            cin >> num_w;
            cout << "ENTER # OF DRYERS: ";
            cin >> num_d;
            LaundromatDay laundromat(cust_hour, num_w, num_d, num_days);

            for (int i = 0; i < num_days; i++)
            {
                laundromat.simulate_day();
                laundromat.end_of_day_results();
                if(laundromat.get_customer_wait_count() > 0)
                    wait_count++;
                //resetting values to 0
                laundromat.set_customer_wait_count();
                laundromat.set_num_finished_customers();
            }

            laundromat.final_output_message(wait_count, num_days);
            break;
        }

        default:
            if (choice != QUIT)
                cout << endl <<"That is NOT a valid test case.  Try again..." <<endl;
            break;

        }  // end switch

    }
    while (choice != QUIT);

    cout << "Finishing the program." << endl;
    return 0;
}

// Gets the user input for options.
int get_choice()
{
    int choice;

    cout << "Select which option you want by entering its number: " << endl;
    cout << " " << endl;

    cout << TEST << "  TEST" << endl;
    cout << SCENARIO1 << "  SCENARIO 1" << endl;
    cout << SCENARIO2 << "  SCENARIO 2" << endl;
    cout << QUIT << "  EXIT" << endl << endl;

    cin >> choice;
    cout << endl;
    return choice;
}

// Intro message to the program.
void intro_msg()
{
    cout << "*********************************" << endl;
    cout << "*                               *" << endl;
    cout << "*   LAUNDROMAT SIMULATOR 9000   *" << endl;
    cout << "*                               *" << endl;
    cout << "*********************************" << endl << endl;
}
