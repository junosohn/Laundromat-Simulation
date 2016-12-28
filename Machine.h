#ifndef MACHINE_H
#define MACHINE_H
#include "Load.h"
#include <iostream>
#include <fstream>

using namespace std;

class Machine
{
    public:
        enum MachineType {Dryer, Washer};
        Machine();
        Machine(MachineType, int);
        void set_machine_id(int);
        void set_time_in(int);
        void set_machine_empty(bool);
        int get_machine_id();
        int get_time_in();
        bool get_machine_empty();
        void load_machine(Load *, int);
        bool check_load_done(int);
        Load* remove_load();


    private:
        int machine_id;
        int time_in;
        bool machine_empty;
        MachineType type;
        Load* load;
};

#endif // MACHINE_H
