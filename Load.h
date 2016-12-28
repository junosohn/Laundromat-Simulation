#ifndef LOAD_H
#define LOAD_H


class Load
{
    public:
        Load();
        Load(int);
        virtual ~Load();
        void set_load_id(int);
        void set_random_load_size(int);
        void set_is_finished(bool);
        int get_load_id();
        int get_random_load_size();
        bool is_finished();

    private:
        int load_id;
        int random_load_size;
        bool finished;
};

#endif // LOAD_H
