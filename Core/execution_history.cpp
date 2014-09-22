#include <algorithm>
#include <chrono>
#include "execution_history.h"

Execution_history::Execution_history()
    //: buffer_size_(10)
{
    // Moyenne sera sur taille_buffer_ donnees
    //last_execution_time_ = boost::circular_buffer<time>(buffer_size_);
}

Execution_history::time Execution_history::average() const
{
    return average_;
}

Execution_history::time Execution_history::get_time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}

void Execution_history::calculate_moving_average()
{
    //time avg_time;
    //std::for_each(last_execution_time_.begin(), last_execution_time_.end(), [&](time tmp){avg_time += tmp;});
    //average_ =  avg_time / last_execution_time_.size();
}

Execution_history::time Execution_history::get_last_time() const
{
    //return last_execution_time_.back();
}

void Execution_history::add_time(time nouveau)
{
    //last_execution_time_.push_back(nouveau);
}
