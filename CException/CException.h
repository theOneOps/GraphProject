//
// Created by Billy on 06/03/2024.
//


#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <string>

#define denominator_equals_zero 0

using namespace std;


/**********************************************************
*  Class : CExeption
* *********************************************************
* ROLE : management any exception errors of the program
* *********************************************************
* VERSION: 1.0
* AUTHORS: Selly Bill-Gate MEDEWOU
          Jeremie YANG
* DATE: DD/MM/YYYY
* *********************************************************
* EXTERNES InCLUSIONS
*/
class CException
{
private:
    int uiExval;
    string Exmessage;
    string filename;
    int line;
public:
    /**
     *******************************************************************************
     * CException
     * *****************************************************************************
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Create an arc by default (done by the compiler)
     *******************************************************************************
    */
    CException();

    /**
     *******************************************************************************
     * CException
     * *****************************************************************************
    * Entries : int id : the number of the exception, string message : the message of the exception,
    *   the string file : the file that raised the exception, int line : the line on witch the exception have been thrown from
    * Needs : None
    * Returns : void
    * Leads :  Create an Exception which attributs equels to the parameters's values
     *******************************************************************************
    */
    CException(int id, string message, string file, int line);

    /**
    *******************************************************************************
    * CEXModifyValue
    * *****************************************************************************
    * Entries : the entry value of the Exception
    * Needs : None
    * Returns : void
    * Leads : modify the current value of the exception by the parameter's value
    *******************************************************************************
    */
    void CEXModifyValue(int uiP);

    /**
    *******************************************************************************
    * CEXReadValue
    * *****************************************************************************
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : Return the uiExval's value of the exception
    *******************************************************************************
    */
    [[nodiscard]] int CEXReadValue()const;


    /*
    * ********************************************
    * CEXModifyMessage
    * ********************************************
    * Entries : string : the newValue of message's attribute
    * Needs : None
    * Returns : None
    * Leads : changes the value of the message's attribute
    */
    void CEXModifyMessage(const string& message);

    /*
    * *****************************************************************************
    * CEXReadMessage
    * *****************************************************************************
    * Entries : None
    * Needs : None
    * Returns : void
    * Leads : print the message's attribute content
    */
    void CEXReadMessage() const;
};


#endif //TP2_EXCEPTION_HPP
