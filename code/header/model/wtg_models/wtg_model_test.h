#ifndef WTG_MODEL_TEST_H
#define WTG_MODEL_TEST_H


#include <cstdlib>
#include <cstring>
#include <iostream>

#ifdef _MSC_VER
	#pragma warning (disable: 4290)
#endif

#include "thirdparty/cpptest/cpptest.h"

#include "header/power_system_database.h"

using namespace std;

class WTG_MODEL_TEST : public Test::Suite
{
    public:
        WTG_MODEL_TEST();
        POWER_SYSTEM_DATABASE* get_test_power_system_database();
        WT_GENERATOR* get_test_wt_generator();
    protected:
        virtual void setup();
        virtual void tear_down();
    private:
        POWER_SYSTEM_DATABASE* psdb;
};

#endif//WTG_MODEL_TEST_H