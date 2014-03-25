#ifndef AUTOVERROU_H
#define AUTOVERROU_H
//pris de http://h-deb.clg.qc.ca/Sujets/Client-Serveur/Mutex-Autoverrou.html
#include <mutex>
#include <string>
class Autoverrou
{
   std::mutex &mutex_;
public:
   Autoverrou(std::mutex &m) throw()
      : mutex_(m)
   {
       mutex_.lock();
   }
   ~Autoverrou() throw()
      { mutex_.unlock(); }
};

#endif // AUTOVERROU_H
