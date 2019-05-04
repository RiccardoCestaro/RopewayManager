#include "invalidstringtoenumexception.h"

InvalidStringToEnumException::InvalidStringToEnumException() : error("Invalid String. Unable to assign to enum value"){
    std::cout << error <<std::endl;
}
