#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>

#include "simulationtraits.h"

std::string char2hex( char dec );
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);
std::string send_request(std::string request);
std::string stringify(double x);
std::string stringify(int x);
std::string stringify(simulation_traits::node_id_type x);
std::chrono::milliseconds get_time();

#endif // UTILS_H
