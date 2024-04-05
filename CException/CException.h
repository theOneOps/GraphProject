//
// Created by Billy on 19/03/2024.
//


#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <string>

using namespace std;

/**********************************************************
*  Class : CExeption
* *********************************************************
* ROLE : management of any exception errors of the program
* *********************************************************
* VERSION: 1.0
* AUTHORS: Selly Bill-Gate MEDEWOU
          Jeremie YANG
* DATE: 19/03/2024
* *********************************************************
* EXTERNES InCLUSIONS
*/
class CException
{
private:
    // the value (id) of the exception
    int uiExval;
    //the message value of the exception
    string Exmessage;
    // the file's where the message's coming from
    string filename;
    // the line where the exception's coming from
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
    CException(int id, string message, string file, const int line);

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


#endif //EXCEPTION_HPP
