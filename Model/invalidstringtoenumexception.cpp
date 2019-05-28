#include "invalidstringtoenumexception.h"

/**
 * @brief InvalidStringToEnumException::InvalidStringToEnumException
 *
 * Costruttore della classe InvalidStringToEnumException
 */
InvalidStringToEnumException::InvalidStringToEnumException() : error("Invalid String. Unable to assign to enum value"){
    std::cout << error <<std::endl;
}
