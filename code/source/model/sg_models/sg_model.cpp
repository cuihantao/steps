#include "header/model/sg_models/sg_model.h"
#include "header/basic/utility.h"
#include "header/power_system_database.h"
#include "header/STEPS.h"
SG_MODEL::SG_MODEL()
{
    set_allowed_device_type_CAN_ONLY_BE_CALLED_BY_SPECIFIC_MODEL_CONSTRUCTOR("GENERATOR");
    busptr = NULL;
}

SG_MODEL::~SG_MODEL()
{
    ;
}

GENERATOR* SG_MODEL::get_generator_pointer() const
{
    return (GENERATOR*) get_device_pointer();
}

void SG_MODEL::set_bus_pointer()
{
    STEPS& toolkit = get_toolkit(__PRETTY_FUNCTION__);
    POWER_SYSTEM_DATABASE& psdb = toolkit.get_power_system_database();

    GENERATOR* generator = get_generator_pointer();
    size_t bus = generator->get_generator_bus();

    busptr = psdb.get_bus(bus);
    if(busptr==NULL)
    {
        ostringstream osstream;
        osstream<<"Warning. No bus pointer is set for "<<get_model_name()<<" model of "<<generator->get_device_name()<<"\n"
                <<"Check model data.";
        toolkit.show_information_with_leading_time_stamp(osstream);
    }
}

BUS* SG_MODEL::get_bus_pointer() const
{
    return busptr;
}

double SG_MODEL::get_mbase_in_MVA() const
{
    GENERATOR* gen = get_generator_pointer();
    if(gen!=NULL)
        return gen->get_mbase_in_MVA();
    else
        return 0.0;
}

double SG_MODEL::get_bus_base_frequency_in_Hz()
{
    BUS* busptr =  get_bus_pointer();
    if(busptr!=NULL)
        return busptr->get_base_frequency_in_Hz();
    else
    {
        set_bus_pointer();
        if(get_bus_pointer()!=NULL)
            return get_bus_base_frequency_in_Hz();
        else
            return 0.0;
    }
}

complex<double> SG_MODEL::get_terminal_complex_voltage_in_pu()
{
    BUS* busptr =  get_bus_pointer();
    if(busptr!=NULL)
        return busptr->get_complex_voltage_in_pu();
    else
    {
        set_bus_pointer();
        if(get_bus_pointer()!=NULL)
            return get_terminal_complex_voltage_in_pu();
        else
            return 0.0;
    }
}

double SG_MODEL::get_terminal_voltage_in_pu()
{
    BUS* busptr =  get_bus_pointer();
    if(busptr!=NULL)
        return busptr->get_voltage_in_pu();
    else
    {
        set_bus_pointer();
        if(get_bus_pointer()!=NULL)
            return get_terminal_voltage_in_pu();
        else
            return 0.0;
    }
}
