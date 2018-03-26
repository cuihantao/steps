#ifndef STEPS_API_H
#define STEPS_API_H

#define EXPORT_STEPS __declspec( dllexport )
//#define EXPORT_STEPS ""

#include "header/power_system_database.h"
#include "header/toolkit/powerflow_solver/powerflow_solver.h"
#include "header/toolkit/dynamic_simulator/dynamic_simulator.h"

class STEPS_API_SEARCH_BUFFER
{
    public:
        vector<BUS*> buses;                            size_t bus_pointer;
        vector<GENERATOR*> generators;                 size_t generator_pointer;
        vector<PE_SOURCE*> pe_sources;                 size_t pe_source_pointer;
        vector<LOAD*> loads;                           size_t load_pointer;
        vector<FIXED_SHUNT*> fixed_shunts;             size_t fixed_shunt_pointer;
        vector<LINE*> lines;                           size_t line_pointer;
        vector<TRANSFORMER*> transformers;             size_t transformer_pointer;
        vector<HVDC*> hvdcs;                           size_t hvdc_pointer;
        vector<EQUIVALENT_DEVICE*> equivalent_devices; size_t equivalent_device_pointer;
        vector<AREA*> areas;                           size_t area_pointer;
        vector<ZONE*> zones;                           size_t zone_pointer;
        vector<OWNER*> owners;                         size_t owner_pointer;
};

#ifdef  __cplusplus
extern "C" {
#endif

void show_side_not_supported_for_device_with_api(string side, DEVICE_ID did, string api_func);
void show_parameter_not_supported_for_device_with_api(string par_name, DEVICE_ID did, string api_func);
void show_parameter_not_supported_with_api(string par_name, string api_func);
void show_device_not_exist_with_api(DEVICE_ID did, string api_func);

void show_parameter_not_supported_for_area_zone_owner_with_api(string par_name, size_t no, string api_func);
void show_area_zone_owner_not_exist_with_api(size_t no, string api_func);


void api_initialize_package();
size_t api_get_allowed_maximum_bus_number();
void api_set_allowed_maximum_bus_number(size_t max_bus);
size_t api_get_device_capacity(const char* device_type);
size_t api_get_area_capacity();
size_t api_get_zone_capacity();
size_t api_get_owner_capacity();
void api_set_device_capacity(const char* device_type, size_t cap);
void api_set_area_capacity(size_t cap);
void api_set_zone_capacity(size_t cap);
void api_set_owner_capacity(size_t cap);

void api_clear_package();
void api_terminate_package();
double api_get_package_float_data(char* parameter_name);
void api_set_package_float_data(char* parameter_name, double value);


void api_load_powerflow_data_from_file(char* file, char* file_type);
void api_save_powerflow_data_to_file(char* file, char* file_type);
void api_load_dynamic_data_from_file(char* file, char* file_type);
void api_save_dynamic_data_to_file(char* file, char* file_type);


void api_add_bus(size_t bus_number, char* bus_name, double base_voltage_in_kV);
void api_add_generator(size_t bus_number, char* identifier);
void api_add_pe_source(size_t bus_number, char* identifier);
void api_add_load(size_t bus_number, char* identifier);
void api_add_fixed_shunt(size_t bus_number, char* identifier);
void api_add_line(size_t sending_side_bus_number, size_t receiving_side_bus_number, char* identifier);
void api_add_hvdc(size_t rectifier_bus_number, size_t inverter_bus_number, char* identifier);
void api_add_transformer(size_t primary_side_bus_number, size_t secondary_side_bus_number, size_t tertiary_side_bus_number, char* identifier);
void api_add_equivalent_device(size_t bus_number, char* identifier);
void api_add_area(size_t area_number, char* area_name);
void api_add_zone(size_t zone_number, char* zone_name);
void api_add_owner(size_t owner_number, char* owner_name);

size_t api_get_device_count(const char* device_type);
size_t api_get_area_count();
size_t api_get_zone_count();
size_t api_get_owner_count();
void api_show_device_data(const char* device_type);

void api_initialize_bus_search(double vbase_kV_min, double vbase_kV_max, double v_pu_min, double v_pu_max, size_t area, size_t zone, size_t owner);
void api_initialize_all_bus_search();
size_t api_get_current_bus_number();
void api_goto_next_bus();

void api_initialize_device_search(const char* device_type, size_t bus);
size_t api_get_current_device_bus_number(const char* device_type, const char* side);
const char* api_get_current_device_identifier(const char* device_type);
void api_goto_next_device(const char* device_type);

void api_initialize_area_search();
size_t api_get_current_area_number();
void api_goto_next_area();

void api_initialize_zone_search();
size_t api_get_current_zone_number();
void api_goto_next_zone();

void api_initialize_owner_search();
size_t api_get_current_owner_number();
void api_goto_next_owner();

int api_get_bus_integer_data(size_t bus, char* parameter_name);
void api_set_bus_integer_data(size_t bus, char* parameter_name, int value);
double api_get_bus_float_data(size_t bus, char* parameter_name);
void api_set_bus_float_data(size_t bus, char* parameter_name, double value);
const char* api_get_bus_string_data(size_t bus, char* parameter_name);
void api_set_bus_string_data(size_t bus, char* parameter_name, char* value);
bool api_get_bus_boolean_data(size_t bus, char* parameter_name);
void api_set_bus_boolean_data(size_t bus, char* parameter_name, bool value);

int api_get_source_integer_data(size_t bus, char* identifier, char* parameter_name);
void api_set_source_integer_data(size_t bus, char* identifier, char* parameter_name, int value);
double api_get_source_float_data(size_t bus, char* identifier, char* parameter_name);
void api_set_source_float_data(size_t bus, char* identifier, char* parameter_name, double value);
const char* api_get_source_string_data(size_t bus, char* identifier, char* parameter_name);
void api_set_source_string_data(size_t bus, char* identifier, char* parameter_name, char* value);
bool api_get_source_boolean_data(size_t bus, char* identifier, char* parameter_name);
void api_set_source_boolean_data(size_t bus, char* identifier, char* parameter_name, bool value);

int api_get_load_integer_data(size_t bus, char* identifier, char* parameter_name);
void api_set_load_integer_data(size_t bus, char* identifier, char* parameter_name, int value);
double api_get_load_float_data(size_t bus, char* identifier, char* parameter_name);
void api_set_load_float_data(size_t bus, char* identifier, char* parameter_name, double value);
const char* api_get_load_string_data(size_t bus, char* identifier, char* parameter_name);
void api_set_load_string_data(size_t bus, char* identifier, char* parameter_name, char* value);
bool api_get_load_boolean_data(size_t bus, char* identifier, char* parameter_name);
void api_set_load_boolean_data(size_t bus, char* identifier, char* parameter_name, bool value);

int api_get_fixed_shunt_integer_data(size_t bus, char* identifier, char* parameter_name);
void api_set_fixed_shunt_integer_data(size_t bus, char* identifier, char* parameter_name, int value);
double api_get_fixed_shunt_float_data(size_t bus, char* identifier, char* parameter_name);
void api_set_fixed_shunt_float_data(size_t bus, char* identifier, char* parameter_name, double value);
const char* api_get_fixed_shunt_string_data(size_t bus, char* identifier, char* parameter_name);
void api_set_fixed_shunt_string_data(size_t bus, char* identifier, char* parameter_name, char* value);
bool api_get_fixed_shunt_boolean_data(size_t bus, char* identifier, char* parameter_name);
void api_set_fixed_shunt_boolean_data(size_t bus, char* identifier, char* parameter_name, bool value);

int api_get_line_integer_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name);
void api_set_line_integer_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name, int value);
double api_get_line_float_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name);
void api_set_line_float_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name, double value);
const char* api_get_line_string_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name);
void api_set_line_string_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name, char* value);
bool api_get_line_boolean_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name);
void api_set_line_boolean_data(size_t ibus, size_t jbus, char* identifier, char* parameter_name, bool value);

int api_get_transformer_integer_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name);
void api_set_transformer_integer_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name, int value);
double api_get_transformer_float_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name);
void api_set_transformer_float_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name, double value);
const char* api_get_transformer_string_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name);
void api_set_transformer_string_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name, char* value);
bool api_get_transformer_boolean_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name);
void api_set_transformer_boolean_data(size_t ibus, size_t jbus, size_t kbus, char* identifier, char* side, char* parameter_name, bool value);

int api_get_hvdc_integer_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name);
void api_set_hvdc_integer_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name, int value);
double api_get_hvdc_float_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name);
void api_set_hvdc_float_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name, double value);
const char* api_get_hvdc_string_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name);
void api_set_hvdc_string_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name, char* value);
bool api_get_hvdc_boolean_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name);
void api_set_hvdc_boolean_data(size_t ibus, size_t jbus, char* identifier, char* side, char* parameter_name, bool value);

int api_get_euivalent_device_integer_data(size_t bus, char* identifier, char* parameter_name);
void api_set_equivalent_device_integer_data(size_t bus, char* identifier, char* parameter_name, int value);
double api_get_euivalent_device_float_data(size_t bus, char* identifier, char* parameter_name);
void api_set_equivalent_device_float_data(size_t bus, char* identifier, char* parameter_name, double value);
const char* api_get_euivalent_device_string_data(size_t bus, char* identifier, char* parameter_name);
void api_set_equivalent_device_string_data(size_t bus, char* identifier, char* parameter_name, char* value);
bool api_get_euivalent_device_boolean_data(size_t bus, char* identifier, char* parameter_name);
void api_set_equivalent_device_boolean_data(size_t bus, char* identifier, char* parameter_name, bool value);

int api_get_area_integer_data(size_t area, char* parameter_name);
void api_set_area_integer_data(size_t area, char* parameter_name, int value);
double api_get_area_float_data(size_t area, char* parameter_name);
void api_set_area_float_data(size_t area, char* parameter_name, double value);
const char* api_get_area_string_data(size_t area, char* parameter_name);
void api_set_area_string_data(size_t area, char* parameter_name, char* value);
bool api_get_area_boolean_data(size_t area, char* parameter_name);
void api_set_area_boolean_data(size_t area, char* parameter_name, bool value);

int api_get_zone_integer_data(size_t zone, char* parameter_name);
void api_set_zone_integer_data(size_t zone, char* parameter_name, int value);
double api_get_zone_float_data(size_t zone, char* parameter_name);
void api_set_zone_float_data(size_t zone, char* parameter_name, double value);
const char* api_get_zone_string_data(size_t zone, char* parameter_name);
void api_set_zone_string_data(size_t zone, char* parameter_name, char* value);
bool api_get_zone_boolean_data(size_t zone, char* parameter_name);
void api_set_zone_boolean_data(size_t zone, char* parameter_name, bool value);

int api_get_owner_integer_data(size_t owner, char* parameter_name);
void api_set_owner_integer_data(size_t owner, char* parameter_name, int value);
double api_get_owner_float_data(size_t owner, char* parameter_name);
void api_set_owner_float_data(size_t owner, char* parameter_name, double value);
const char* api_get_owner_string_data(size_t owner, char* parameter_name);
void api_set_owner_string_data(size_t owner, char* parameter_name, char* value);
bool api_get_owner_boolean_data(size_t owner, char* parameter_name);
void api_set_owner_boolean_data(size_t owner, char* parameter_name, bool value);

int api_get_generator_related_model_integer_parameter(size_t bus, char* identifier, char* model_type, char* model_name, char* parameter_name);
void api_set_generator_related_model_integer_parameter(size_t bus, char* identifier, char* model_type, char* model_name, char* parameter_name, int value);
double api_get_generator_related_model_float_parameter(size_t bus, char* identifier, char* model_type, char* model_name, char* parameter_name);
void api_set_generator_related_model_float_parameter(size_t bus, char* identifier, char* model_type, char* model_name, char* parameter_name, double value);
const char* api_get_generator_related_model_name(size_t bus, char* identifier, char* model_type);




void api_initialize_powerflow_solver();


size_t api_get_powerflow_solver_integer_parameter(char* parameter_name);
void api_set_powerflow_solver_integer_parameter(char* parameter_name, int value);
double api_get_powerflow_solver_float_parameter(char* parameter_name);
void api_set_powerflow_solver_float_parameter(char* parameter_name, double value);
bool api_get_powerflow_solver_boolean_parameter(char* parameter_name);
void api_set_powerflow_solver_boolean_parameter(char* parameter_name, bool value);

void api_solve_powerflow(char* method);
bool api_is_powerflow_converged();
void api_show_powerflow_result();
void api_save_powerflow_result(char* file);
void api_save_network_matrix(char* file);



size_t api_get_dynamic_simulator_integer_parameter(char* parameter_name);
void api_set_dynamic_simulator_integer_parameter(char* parameter_name, int value);
double api_get_dynamic_simulator_float_parameter(char* parameter_name);
void api_set_dynamic_simulator_float_parameter(char* parameter_name, double value);
const char* api_get_dynamic_simulator_string_parameter(char* parameter_name);
void api_set_dynamic_simulator_string_parameter(char* parameter_name, char* value);
bool api_get_dynamic_simulator_boolean_parameter(char* parameter_name);
void api_set_dynamic_simulator_boolean_parameter(char* parameter_name, bool value);
void api_set_dynamic_simulator_output_file(char* file);
const char* api_get_dynamic_simulator_output_file();

void api_set_dynamic_simulation_time_step(double value);
double api_get_dynamic_simulation_time_step();

void api_prepare_meters();
void api_prepare_bus_related_meters();
void api_prepare_generator_related_meters();
void api_prepare_load_related_meters();
void api_prepare_line_related_meters();
void api_prepare_hvdc_related_meters();
void api_prepare_equivalent_device_related_meters();

void api_start_dynamic_simulation();
void api_stop_dynamic_simulation();
void api_run_simulation_to_time(double t_end);
void api_run_a_step();
void api_update_with_event();

void api_set_bus_fault(size_t bus, char* fault_type, double fault_G, double fault_B);
void api_clear_bus_fault(size_t bus, char* fault_type);
void api_trip_bus(size_t bus);

void api_set_line_fault(size_t ibus, size_t jbus, char* identifier, char* fault_type, double fault_location, double fault_G, double fault_B);
void api_clear_line_fault(size_t ibus, size_t jbus, char* identifier, char* fault_type, double fault_location);
void api_trip_line(size_t ibus, size_t jbus, char* identifier);
void api_trip_line_breaker(size_t ibus, size_t jbus, char* identifier);
void api_close_line(size_t ibus, size_t jbus, char* identifier);
void api_close_line_breaker(size_t ibus, size_t jbus, char* identifier);

void api_trip_transformer(size_t ibus, size_t jbus, size_t kbus, char* identifier);
void api_trip_transformer_breaker(size_t ibus, size_t jbus, size_t kbus, char* identifier);
void api_close_transformer(size_t ibus, size_t jbus, size_t kbus, char* identifier);
void api_close_transformer_breaker(size_t ibus, size_t jbus, size_t kbus, char* identifier);

void api_trip_generator(size_t bus, char* identifier);
void api_shed_generator(size_t bus, char* identifier, double percent);

void api_trip_load(size_t bus, char* identifier);
void api_close_load(size_t bus, char* identifier);
void api_scale_load(size_t bus, char* identifier, double percent);
void api_scale_all_loads(double percent);

void api_manually_bypass_hvdc(size_t ibus, size_t jbus, char* identifier);
void api_manually_unbypass_hvdc(size_t ibus, size_t jbus, char* identifier);
void api_manually_block_hvdc(size_t ibus, size_t jbus, char* identifier);
void api_manually_unblock_hvdc(size_t ibus, size_t jbus, char* identifier);

double api_get_generator_voltage_reference_in_pu(size_t bus, char* identifier);
double api_get_generator_power_reference_in_MW(size_t bus, char* identifier);

void api_set_generator_voltage_reference_in_pu(size_t bus, char* identifier, double value);
void api_set_generator_power_reference_in_MW(size_t bus, char* identifier, double value);

#ifdef  __cplusplus
}
#endif

#endif // STEPS_API_H
