#ifndef AUTOLOCK_H
#define AUTOLOCK_H
//pris de http://h-deb.clg.qc.ca/Sujets/Client-Serveur/Mutex-Autoverrou.html

#include <mutex>
#include <string>

class Autolock
{
   std::mutex &mutex_;
public:
   Autolock(std::mutex &m) throw()
      : mutex_(m)
   {
       mutex_.lock();
   }
   ~Autolock() throw()
      { mutex_.unlock(); }
};

#endif // AUTOVERROU_H
