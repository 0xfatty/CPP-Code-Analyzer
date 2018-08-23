//include the header file
#include"DSString.h"

String::String(){
    data = new char[1];
    data[0] = '\0';
}

//destructor to delete the character array
String::~String()
{
    delete[]data;
}

// parameterized constructor which will take a character array as an argument
String::String(const char *input){
    // here we can utilize builtin functionality of Cstring to get
    //the length of character array either by using sizeof() or strlen()
    int length = strlen(input);
    //dynamically allocate the new size to character array
    //size +1 for null character at the end of array
    // copy the array passed as argument to the data array utilizing strcpy of Cstring library
    if(length==0) {
        data = new char[1];
        data[0]='\0';
    }
    else {
        data = new char[length+1];
        strcpy(data,input);
        data[length]='\0';
    }
}

//this function returns the length
int String::size() const{
    return strlen(data);
}

// copy constructor to copy the value of object given as argument
//here we know our object contains length and char array
String::String(const String &Obj){
    // as the String object also has length and data part
    // so new length = length of passed object
    int length  = Obj.size();
     // dynamically allocate the size of character array
    data = new char[length+1];
    // copy data portion of passed object to data array
    strcpy(data,Obj.data);
}

//Here we are assigning a character array to a String object and return the new object
String & String::operator=( const char *input)
{
    if(data!=NULL)
        delete [] data;
    //update length to new length of char array provided as parameter
    int length = strlen(input);
    data = new char[length+1];
    strcpy(data,input);
    //return the new updated object
    return *this;
}

// assign an object to another object and return the updated object
String & String::operator=( const String &Obj)
{
    if(data!=NULL)
        delete [] data;
    int length = Obj.size();
    data = new char[length+1];
    strcpy(data, Obj.data);
    return *this;
}

// to check whether the string passed as char array in paramter is equal to char array data or not
bool String::operator==(const char* input)
{
    //if both are equal then strcmp will return 0 and this function will return true else false
   return strcmp( data,	input ) == 0;
}


// to check whether the string passed as an object is equal to char array data or not
bool String::operator==(const String &Obj)
{
    //if both are equal then strcmp will return 0 and this function will return true else false
   return strcmp( data,	Obj.data ) == 0;
}

//whether the object passed as an argument contains string greater than data array or not
bool String::operator>(	const String &Obj)
{
    //if value is greate than 0 it will return true else false
   return strcmp(Obj.data,data) > 0;

}

// return the character at given index
char &String::operator[](int index)
{

	if(index >= size() || index*-1 >= size()) {
		static char ret;
		ret = '\0';
		return ret;
	}
	int i;
	if(index < 0) {
		i = size()+index;
	} else {
		i = index;
	}
	return data[i];
}
// this function return substring from the array if given start and end index
String String::substring(int start, int end ){
	// local start and end variables so that they can be changed
	int s = start;
	int e = end;
	// if the start or stop index is out of range, return empty string
	if (start >=size() || start*(-1) >=size() || end >=size() || end*(-1) >=size()){
		return "";
	}
	// if start or stop are negative, find their positive index
	if (start < 0) {
		s = size() + start +1;
	}
	if (end < 0) {
		e = size() + end +1;
	}
	// determine length of substring
	int len = (e - s);
	// temporary character array for substring
	char *subptr = new char[len + 1];
	// copy substring to array
	strncpy( subptr, &data[s], len);
	// end with null
	subptr[len] = '\0';
	// make String from array to return
	String Sstring(subptr);
	// delete temp array
	delete [] subptr;
	// return the local String object
	return Sstring;
}

// return the character array
char* String::c_str(){
    return data;
}

// output overloading
std::ostream& operator<<(std::ostream &output, const String &Obj) {
   output << Obj.data;
   return output;
}

// Input overloading
std::ifstream& getline (std::ifstream &input, String &str) {
    char ichar[1000];
    input.getline(ichar, 1000);
    str = ichar;
    return input;
}

std::ifstream& getline (std::ifstream &input, String &str, char delin) {
    char ichar[1000];
    input.getline(ichar, 1000, delin);
    str = ichar;
    return input;
}

int String::toInt(){
	int ret = 0;
	int i;
	for(i=0; i<size();i++){
		// ASCII values of 1 thru 9
		ret *= 10;
		if(data[i]>=49 && data[i]<=57) {
			ret += data[i] - 48;
		}
	}
	return ret;
}
