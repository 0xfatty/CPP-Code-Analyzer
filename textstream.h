/* textstream.h 
 *
 * Object which takes strings as input and 
 * parses out the buffer into space-delinated strings
 * on command.
 * */

#include <string>
#include <stack>
#include <iostream>
#include <algorithm>

class TextStream {
    public:
        TextStream();
        void addString(std::string);
        bool outputReady();
        std::stack<std::string> getOutput();
        std::string getBufferAndWipe();

    private:

        std::string trimWord();
        std::string buf;
};

// This function is a helper function for 
// remove_if to help us trim strings of unwanted characters
bool textTrim(char);
