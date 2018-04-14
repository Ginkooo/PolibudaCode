#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace std;

class Semafor {
    public:
        Semafor(int _count);
        void signal();
        bool wait_try();
        int get_value() const;
    private:
        int resource_counter;
        mutex counter_mutex;
        condition_variable condition_different_than_zero;
};
