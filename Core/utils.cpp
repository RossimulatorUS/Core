#include <sstream>
#include <curl/curl.h>

#include "utils.h"

using std::string;

// From https://code.google.com/p/twitcurl/source/browse/trunk/libtwitcurl/urlencode.cpp?r=47
string char2hex( char dec )
{
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48 in ascii
    if (10<= dig1 && dig1<=15) dig1+=65-10; //A,65 in ascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=65-10;

    string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
    ((string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}

string send_request(string request)
{
    CURL *curl;
    string response;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

string stringify(double x)
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}

string stringify(int x)
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}


string stringify(size_t x)
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}

string stringify(simulation_traits::node_id_type x)
{
    std::ostringstream ss;
    ss << x;
    return ss.str();
}

std::chrono::milliseconds get_time()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
}
