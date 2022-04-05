#ifndef  EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
using namespace std;

class Exceptions : public exception {
public:

	Exceptions(const char* msg) : exception(msg){}
};
#endif  

