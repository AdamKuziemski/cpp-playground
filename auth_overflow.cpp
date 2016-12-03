/**
*** This is a simple example of a function susceptible to buffer overflow
**/

#include <iostream>
#include <cstring>
using namespace std;

bool check_authentication(char* password)
{
  bool auth_flag = false;
  char password_buffer[16]; // Try giving it a password that has 17 characters ;)

  cout <<"\nbefore strcpy:\n";
  cout <<"auth_flag at\t\t"<< &auth_flag <<"\t"<< auth_flag;
  cout <<"\npassword_buffer at\t"<< &password_buffer <<'\t'<< password_buffer << endl;

  strcpy(password_buffer, password);

  cout <<"\nafter strcpy:\n";
  cout <<"auth_flag at\t\t"<< &auth_flag <<"\t"<< auth_flag;
  cout <<"\npassword_buffer at\t"<< &password_buffer <<'\t'<< password_buffer << endl;

  if(strcmp(password_buffer, "brillig") == 0 ||
     strcmp(password_buffer, "outgrabe") == 0)
    auth_flag = true;

  return auth_flag;
}

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout <<"Usage: "<< argv[0] <<" <password>\n";
    return 1;
  }

  if(check_authentication(argv[1]))
    cout <<"\nAccess granted.\n";
  else
    cout <<"\nAccess denied.\n";

  return 0;
}
