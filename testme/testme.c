#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
      //get random ASCII character with range that includes characters checked
    char c = (rand() % (127 - 32)) + 32;
    return c;
}

char *inputString()
{
//in order to get a better chance at getting the string to fit the "reset" check and reduce runtime, I set the string size to 6
//the last value in the strings is a null terminator (which is the last argument in the check against s)
    int length = 6;
    char* string = malloc(length);
    int i;
    for(i = 0; i < length - 1; i++)
    {
      //Gets a random ASCII character from lower case alphabet
      string[i] = (rand() % (123-97)) + 97;
    }
    string[i] = '\0';

    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("ERROR- FOUND STRING RESET\n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
