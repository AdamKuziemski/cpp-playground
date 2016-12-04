/**
*** This is a simple example of a function susceptible to buffer overflow. Here's why:
***
*** First of all, neither the authentication flag nor the buffer are necessary in this case.
***
*** Second of all, even if they were necessary for some reason,
*** an array of a fixed size is never a good idea in this kind of code.
***
*** Third, strcpy is pointless as you can simply compare the char* password to some password strings.
***
*** Plus, if this was real code and if you really wanted to pull out some bigger guns,
*** you could disassembly the executable to find the hard-coded passwords.
*** 
*** All of this happens because the compiler usually places the authentication flag after the password buffer,
*** which means that passwords longer than the fixed-size array will overwrite the flag no matter what.
**/

/** STL **/
#include <iostream>
#include <cstring>
using namespace std;

bool check_authentication(char* password)
{
  bool auth_flag = false; // Should be placed in the memory right after the password buffer, so...
  char password_buffer[16]; // Try giving it a password that has 17 characters ;)
  
  // Let's show how the memory looks right before trying to gain access
  cout <<"\nbefore strcpy:\n";
  cout <<"auth_flag at\t\t"<< &auth_flag <<'\t'<< auth_flag;
  cout <<"\npassword_buffer at\t"<< &password_buffer <<'\t'<< password_buffer << endl;

  strcpy(password_buffer, password); // This is where it can go very bad
  
  // Proof
  cout <<"\nafter strcpy:\n";
  cout <<"auth_flag at\t\t"<< &auth_flag <<"\t"<< auth_flag;
  cout <<"\npassword_buffer at\t"<< &password_buffer <<'\t'<< password_buffer << endl;
  
  // Check if the password matches the presets
  if(strcmp(password_buffer, "w1n5t0n") == 0 ||
     strcmp(password_buffer, "m1k3y") == 0)
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
