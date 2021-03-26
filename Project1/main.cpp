
using namespace std;


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "version.h"


bool correctProtocol(char input[], int &position, string &protocol);
bool correctDomain(char input[], int &position, string &domain, string &host);
bool correctPort(char input[], int &position, string &port);
bool correctFilePath(char input[], int &position, string &filePath);
bool correctFileType(char input[], int &position, string &fileType);
void correctParameters(char input[], int &position, string &parameters);



int main() 
{ 

    string inputString,                         // The address the user inputs
           protocol = "",                       // Contains the protocol type
           domain = "",                         // Contains the domain
           hostname = "",
           port = "",
           filePath = "",
           fileType = "",
           parameters = "";

    int position = 0;                           // Keeps track of where the program is on the address

    bool validProtocol = false,
         validDomain = false,
         validPort = false,
         portExists = false,
         validFilePath = false,
         validFileType = false,
         parametersExists = false;

    version();

    // Asks the user for the address
    cout << "Enter an address: ";
    cin >> inputString;

    // Create a char array for the inputed address
    char stringToChar[inputString.length()];

    // Turn the inputted address into the char array
    for (int i = 0; i < inputString.length(); i++)
        stringToChar[i] = inputString[i];

    stringToChar[inputString.length()] = '\0';

    // Checks if protocol is valid or not
    validProtocol = correctProtocol(stringToChar, position, protocol);

    // Checks if the domain is valid
    validDomain = correctDomain(stringToChar, position, domain, hostname);

    // If the port exists then check if it is valid
    if (stringToChar[position] == ':')
    {
        portExists = true;
        validPort = correctPort(stringToChar, position, port);
    }

    // If a port doesnt exists then move on to checking the file path
    validFilePath = correctFilePath(stringToChar, position, filePath);
    validFileType = correctFileType(stringToChar, position, fileType);
    
    // If the parameters exists then read it in
    if (stringToChar[position] == '?')
    {
        parametersExists = true;
        correctParameters(stringToChar, position, parameters);
    }

    // Formatting
    cout << left;

    if (validDomain && validFilePath && validFileType && validProtocol)
    {
        cout << left;
        cout << setw(14) << "Protocol:"   << protocol   << endl;
        cout << setw(14) << "Domain:"     << hostname   << endl;
        
        if (portExists && validPort)
            cout << setw(14) << "Port:"       << port       << endl;

        cout << setw(14) << "File Path:"  << filePath   << endl;

        if (parametersExists)
            cout << setw(14) << "Parameters:" << parameters << endl;
    }


    else
    {
        cout << "Invalid URL with following erroneous components:\n\n";

        if (!validProtocol)
            cout << setw(14) << "Protocol:"   << protocol << " is not a valid protocol."  << endl;

        if (!validDomain)
            cout << setw(14) << "Domain:" << domain << " is an invalid domain name." << endl;

        if (portExists && !validPort)
            cout << setw(14) << "Port:" << "port number must be between 1 and 65535." << endl;
        
        if (!validFileType)
            cout << setw(14) << fileType << " is not a valid file type." << endl;
    }
    


    system("pause");

    return 0;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: 
 * Descr:    
 * 
 * Input:    
 * Return:   bool
 * *******************************************************/
bool correctProtocol(char input[], int &position, string &protocol)
{

    // Gettting the protocols from the user input.
    for (; input[position] != ':'; position++)
        protocol += input[position];

    // If it uses the correct protocols then return true
    if (protocol == "http" || protocol == "https" || protocol == "ftp" || protocol == "ftps")
        return true;
    
    return false;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: 
 * Descr:    
 * 
 * Input:    
 * Return:   bool
 * *******************************************************/
bool correctDomain(char input[], int &position, string &domain, string &host)
{
    // Makes sure that all the parts are there
    int decimalCount = 0;

    // Moves the position up 3 to get rid of the "://"
    position += 3;

    // Read in the host name
    for (; input[position] != '/' && input[position] != ':' && input[position] != '\0'; position++)
    {
        // Keeps track of the number of decimals to make sure all the parts are there
        if (input[position] == '.')
            decimalCount++;
        
        if (decimalCount == 2 && input[position] != '.')
            domain += input[position];

        host += input[position];
    }
    
    if (decimalCount == 2 && (domain == "edu" || domain == "com" || domain == "biz" || domain == "gov"))
        return true;

    return false;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: correctPort
 * Descr:    Checks if the current 
 * 
 * Input:    char input[], int &position, string &port
 * Return:   bool
 * *******************************************************/
bool correctPort(char input[], int &position, string &port) 
{

    int intPort;

    // Get rid of the ":"
    position++;

    // Take the input input into the port string
    for (; input[position] != '/'; position++)
        port += input[position];
    
    // Convert that into an integer to be compared
    intPort = stoi(port);

    // Compare it to the port range to make sure the port is valid and in range
    if (intPort > 1 && intPort < 65535)
        return true;

    return false;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: correctPort
 * Descr:    Checks if the current 
 * 
 * Input:    char input[], int &position, string &port
 * Return:   bool
 * *******************************************************/
bool correctFilePath(char input[], int &position, string &filePath)
{

    // If the file path doesn't start with a "/" then it is not a valid file Path 
    if (input[position] != '/')
    {
        // Move the cursor to the decimal to see if the file type is correct
        while (input[position] != '.')
            position++;
        
        return false;
    }

    // If it doesnt start with a "/" then thats an invalid file path so move on to the file type
    else
        for (; input[position] != '.'; position++)
            filePath += input[position];

    return true;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: correctPort
 * Descr:    Checks if the current 
 * 
 * Input:    char input[], int &position, string &port
 * Return:   bool
 * *******************************************************/
bool correctFileType(char input[], int &position, string &fileType)
{

    // Gets rid of the "."
    position++;

    // Grab everything after the "." until the "?" or until the arr ends
    for (; input[position] != '?' && input[position] != '\0'; position++)
        fileType += input[position];
    
    // If the file type is not valid then return false
    if (fileType != "html" && fileType != "htm")
        return false;

    return true;
}

/****************************************************************************************************************************************************************/

/*********************************************************
 * Function: correctPort
 * Descr:    Checks if the current 
 * 
 * Input:    char input[], int &position, string &port
 * Return:   bool
 * *******************************************************/
void correctParameters(char input[], int &position, string &parameters)
{

    position++;

    for (; input[position] != '\0'; position++)
        parameters += input[position];
}
