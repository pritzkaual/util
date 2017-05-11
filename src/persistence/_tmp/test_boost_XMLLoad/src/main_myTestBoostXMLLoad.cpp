/*
 * main_myTestBoostXMLLoad.cpp
 *
 *  Created on: 05.05.2017
 *      Author: Alexander P.
 */


#include "myTestBoostXMLLoad.hpp"


int main()
{
    try
    {
        testBoostXMLLoad::myTestBoostXMLLoad myObject;
        //myObject.load("_tmp/debug_settings.xml");
        //myObject.save("_tmp/debug_settings_out.xml");

        myObject.load("_tmp/uml.ecore");
        myObject.save("_tmp/uml_out.ecore");

        std::cout << "Success\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}
