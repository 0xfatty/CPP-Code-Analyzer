/* textstream.cpp
 *
 * Object which takes strings as input and 
 * parses out the buffer into space-delinated strings
 * on command.
 * */

#include "textstream.h"

// Clear buffer 
TextStream::TextStream() {
    buf = "";
}

// Add a string to the buffer
void TextStream::addString(std::string s) {
    // Replace tabs with spaces
    std::replace(s.begin(), s.end(), '\t', ' ');
    buf = buf + s;
}

// If there are any spaces in the buffer we can generate output
bool TextStream::outputReady() {
    // if it starts with a space, trim beginning whitespace
    if(buf[0]==' ') {
        size_t start;
        start = buf.find_first_not_of(" ");
        if(start==std::string::npos) {
            buf = "";
        } else {
            buf = buf.substr(start);
        }
    }
    return (buf.find(" ")!=std::string::npos);
}

// While there are spaces left in the buffer generate output
std::stack<std::string> TextStream::getOutput() {
    std::stack<std::string> retVal;

    while(outputReady()) {
        retVal.push(trimWord());
    }

    return retVal;
}

// Used when we hit token ET
std::string TextStream::getBufferAndWipe() {
    std::string retVal = buf;
    buf = "";
    std::transform(retVal.begin(), retVal.end(), retVal.begin(), ::tolower);
    retVal.erase(std::remove_if(retVal.begin(), retVal.end(), textTrim), retVal.end());
    //std::cerr << "W: " << retVal << std::endl;
    return retVal;
}

// Make a string containing all characters from the start of the
// string until the first space, then trim all spaces off until the next character
// or string is empty
std::string TextStream::trimWord() {
    std::string retVal;
    size_t start, end, newstart;

    start = buf.find_first_not_of(" ");
    end = buf.find(" ", start);

    retVal = buf.substr(start,end);

    newstart = buf.find_first_not_of(" ", end);
    if(newstart==std::string::npos)  {
        buf = "";
    } else {
        buf = buf.substr(newstart);
    }

    //std::cerr << "Extracted String " << retVal << "\nRemaining buffer: " << buf <<std::endl;
    
    // Transform all to lowercase
    std::transform(retVal.begin(), retVal.end(), retVal.begin(), ::tolower);
    
    // Use textTrim() to process out other characters
    retVal.erase(std::remove_if(retVal.begin(), retVal.end(), textTrim), retVal.end());

    //std::cerr << "W: " << retVal << std::endl;

    return retVal;
}

// Return true to remove character
// Return false to keep character
bool textTrim(char c) {
    // Keep all characters and numbers
    if(std::isalnum(c)) 
        return false;
    // Keep space
    if(c==' ') 
        return false;

    // Remove if not on whitelist
    return true;
}
