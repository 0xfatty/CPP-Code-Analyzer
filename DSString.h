#ifndef STRING
#define STRING

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

class String{

    public:

        String();
        String(const char*);
        String(const String&);

        String& operator= (const char*);
        String& operator= (const String&);
        bool operator== (const char*);
        bool operator== (const String&);
		
		//String operator+ (const String&);
        bool operator> (const String&);
        char& operator[] (const int);

        int size() const;
        String substring(int, int);
        char* c_str();

        friend std::ostream& operator<< (std::ostream&, const String&);
        friend std::ifstream& getline (std::ifstream &, String &);
        friend std::ifstream& getline (std::ifstream &, String &, char);

		int toInt();
        ~String();

        char* data;

};


inline String operator+ (const String &lhs, const String &rhs){
	char* tempStr = new char[lhs.size()+rhs.size()+1];
	strcpy( tempStr, lhs.data );
	strcpy( tempStr + lhs.size(), rhs.data);
	String retVal(tempStr);
	delete [] tempStr;
	return retVal;
}


#endif
