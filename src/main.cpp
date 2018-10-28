#include <iostream>
#include "module.h"
#include "socket.hpp"
#include "trans_para.h"

int main(int argc, const char *argv[])
{
    Quantum::parse_string("CREATE TABLE Person.test(Id int,\n"
                          "LastName varchar(255),\n"
                          "FirstName varchar(255),\n"
                          "Address varchar(255),\n"
                          "City varchar(255)\n"
                          ");\n\n"
                          "INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees');");

    return 0;

}
