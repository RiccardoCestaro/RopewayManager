#ifndef INVALIDSTRINGTOENUMEXCEPTION_H
#define INVALIDSTRINGTOENUMEXCEPTION_H

#include <iostream>

/**
 * @brief The InvalidStringToEnumException class
 *
 * classe di eccezioni, sollevate durante la costruzione
 * di oggetti nei quali il valore con il quale si vuole
 * costruire dovrebbe uguagliarne un altro
 */
class InvalidStringToEnumException{
    std::string error;
public:
    InvalidStringToEnumException();
};

#endif // INVALIDSTRINGTOENUMEXCEPTION_H
