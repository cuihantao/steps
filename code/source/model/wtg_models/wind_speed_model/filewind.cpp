#include "header/model/wtg_models/wind_speed_model/filewind.h"
#include "header/basic/utility.h"

static vector<string> MODEL_VARIABLE_TABLE{ "GENERATOR MECHANICAL POWER IN PU", //0
                                            "GENERATOR MECHANICAL POWER IN MW",      //1
                                            "MECHANICAL POWER REFERENCE IN PU",      //2
                                            "GENERATOR ROTOR SPEED DEVIATION IN PU",     //3
                                            "STATE@GOVERNOR",     //4
                                            "STATE@TURBINE",       //5
                                            };//8

FILEWIND::FILEWIND()
{
    clear();
}

FILEWIND::~FILEWIND()
{
    clear();
}

void FILEWIND::clear()
{
    time.clear();
    wind_speed.clear();
    wind_direction.clear();

    current_time = INFINITE_THRESHOLD;
    current_wind_speed = 0.0;
    current_wind_direction = 0.0;
}

void FILEWIND::copy_from_const_model(const FILEWIND& model)
{
    clear();
}

FILEWIND::FILEWIND(const FILEWIND& model)
{
    copy_from_const_model(model);
}

FILEWIND& FILEWIND::operator=(const FILEWIND& model)
{
    if(this==&model)
        return *this;

    copy_from_const_model(model);

    return (*this);
}

string FILEWIND::get_model_name() const
{
    return "FILEWIND";
}


void FILEWIND::set_wind_speed_serial_file(string file)
{
    wind_speed_file = file;
}

string FILEWIND::get_wind_speed_serial_file() const
{
    return wind_speed_file;
}


double FILEWIND::get_double_data_with_index(size_t index) const
{
    return 0.0;
}

double FILEWIND::get_double_data_with_name(string par_name) const
{
    return 0.0;
}

void FILEWIND::set_double_data_with_index(size_t index, double value)
{
}

void FILEWIND::set_double_data_with_name(string par_name, double value)
{
}

bool FILEWIND::setup_model_with_steps_string(string data)
{
    return false;
}

bool FILEWIND::setup_model_with_psse_string(string data)
{
    bool is_successful = false;
    vector<string> dyrdata = split_string(data,",");
    if(dyrdata.size()<4)
        return is_successful;

    string model_name = get_string_data(dyrdata[1],"");
    if(model_name!=get_model_name())
        return is_successful;

    string file;
    file = get_string_data(dyrdata[3],"0.0");

    set_wind_speed_serial_file(file);

    is_successful = true;
    return is_successful;
}

bool FILEWIND::setup_model_with_bpa_string(string data)
{
    return false;
}


void FILEWIND::initialize()
{
    return;
}


void FILEWIND::load_wind_speed_from_file()
{
    string file = get_wind_speed_serial_file();
    ifstream fid(file);
    if(not fid.is_open())
        return;

    time.clear();
    wind_speed.clear();
    wind_direction.clear();

    string data;
    vector<string> datavec;
    fid>>data; // skip the head line
    while(true)
    {
        fid>>data;
        if(data.size()<3)
            break;
        data = trim_string(data);
        data = string2csv(data);
        datavec = split_string(data,",");
        if(datavec.size()<2)
            break;

        double t = get_double_data(datavec.front(),"0.0");
        datavec.erase(datavec.begin());

        double v = get_double_data(datavec.front(),"0.0");
        datavec.erase(datavec.begin());

        double direction = 0.0;
        if(datavec.size()>0)
        {
            direction = get_double_data(datavec.front(),"0.0");
            datavec.erase(datavec.begin());
        }

        time.push_back(t);
        wind_speed.push_back(v);
        wind_direction.push_back(direction);
    }
    fid.close();
}

void FILEWIND::run(DYNAMIC_MODE mode)
{
    ;
}

double FILEWIND::get_wind_speed_in_mps()
{
    if(time.size()==0)
        return 0.0;

    WT_GENERATOR* generator = get_wt_generator_pointer();
    double simulation_time = generator->get_dynamic_simulator_time_in_s();

    if(fabs(simulation_time-current_time)<FLOAT_EPSILON)
        return current_wind_speed;

    search_wind_data_at_simulation_time();

    return current_wind_speed;
}

double FILEWIND::get_wind_direction_in_deg()
{
    if(time.size()==0)
        return 0.0;

    WT_GENERATOR* generator = get_wt_generator_pointer();
    double simulation_time = generator->get_dynamic_simulator_time_in_s();

    if(fabs(simulation_time-current_time)<FLOAT_EPSILON)
        return current_wind_direction;

    search_wind_data_at_simulation_time();

    return current_wind_direction;
}

double FILEWIND::get_wind_speed_in_pu()
{
    WT_GENERATOR* generator = get_wt_generator_pointer();
    if(generator==NULL)
        return 0.0;

    WT_AERODYNAMIC_MODEL* aero_model = generator->get_wt_aerodynamic_model();
    if(aero_model==NULL)
        return 0.0;

    double vwind = get_wind_speed_in_mps();
    return vwind/aero_model->get_nominal_wind_speed_in_mps();
}

void FILEWIND::search_wind_data_at_simulation_time()
{
    WT_GENERATOR* generator = get_wt_generator_pointer();
    double simulation_time = generator->get_dynamic_simulator_time_in_s();

    current_time = simulation_time;

    size_t n = time.size();
    double time_min = time[0];
    double time_max = time[n-1];

    if(current_time<=time_min)
    {
        current_wind_speed = wind_speed[0];
        current_wind_direction = wind_direction[0];
    }
    else
    {
        if(current_time>=time_max)
        {
            current_wind_speed = wind_speed[n-1];
            current_wind_direction = wind_direction[n-1];
        }
        else
        {
            size_t previous_index = 0, next_index = n-1;
            size_t previous_time = time[previous_index], next_time = time[next_index];
            while(true)
            {
                size_t temp_index = ((previous_index+next_index)>>1);
                double temp_time = time[temp_index];
                if(fabs(temp_time-current_time)<FLOAT_EPSILON)
                {
                    current_wind_speed = wind_speed[temp_index];
                    current_wind_direction = wind_direction[temp_index];
                    break;
                }
                else
                {
                    if(temp_time>current_time)
                    {
                        next_index = temp_index;
                        next_time = time[next_index];
                    }
                    else
                    {
                        previous_index = temp_index;
                        previous_time = time[previous_index];
                    }
                    if(next_index-previous_index==1)
                    {
                        double slope;
                        slope = (wind_speed[next_index]-wind_speed[previous_index])/(time[next_index]-time[previous_index]);
                        current_wind_speed = wind_speed[previous_index]+slope*(current_time-time[previous_index]);

                        slope = (wind_direction[next_index]-wind_direction[previous_index])/(time[next_index]-time[previous_index]);
                        current_wind_direction = wind_direction[previous_index]+slope*(current_time-time[previous_index]);
                        break;
                    }
                }
            }
        }
    }
}


void FILEWIND::check()
{
    ;
}


void FILEWIND::report()
{
    show_information_with_leading_time_stamp(get_standard_model_string());
}

void FILEWIND::save()
{
    ;
}

string FILEWIND::get_standard_model_string() const
{
    ostringstream sstream;
    WT_GENERATOR* gen = get_wt_generator_pointer();
    size_t bus = gen->get_generator_bus();
    string identifier= gen->get_identifier();
    string file = get_wind_speed_serial_file();

    sstream<<setw(8)<<bus<<", "
      <<"'"<<get_model_name()<<"', "
      <<"'"<<identifier<<"', "
      <<"'"<<file<<"'"
      <<"  /";
    return sstream.str();
}


size_t FILEWIND::get_variable_index_from_variable_name(string var_name)
{
    return 0;
}

string FILEWIND::get_variable_name_from_variable_index(size_t var_index)
{
    return "";
}

double FILEWIND::get_variable_with_index(size_t var_index)
{
    return 0.0;
}

double FILEWIND::get_variable_with_name(string var_name)
{
    return 0.0;
}

string FILEWIND::get_dynamic_data_in_psse_format() const
{
    return get_standard_model_string();
}

string FILEWIND::get_dynamic_data_in_bpa_format() const
{
    return get_standard_model_string();
}

string FILEWIND::get_dynamic_data_in_steps_format() const
{
    return get_standard_model_string();
}