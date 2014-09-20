#ifndef GTE_H
#define GTE_H

#include <chrono>
#include "boost/circular_buffer.hpp"

// Gestionnaire de Temps d'Execution
class Execution_history
{
public:
    typedef std::chrono::milliseconds time;

private:
    // Moyenne mobile -- boost::circular_buffer
    boost::circular_buffer<time> last_execution_time_;
    boost::circular_buffer<time>::size_type buffer_size_;
    time average_;

public:
    Execution_history();

    void add_time(time);
    void calculate_moving_average();
    time get_last_time() const;
    time average() const;

    static time get_time();
};

#endif // GTE_H
