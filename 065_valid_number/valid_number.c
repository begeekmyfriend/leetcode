#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isNumber(const char *s) {
    bool point = false;
    bool hasE = false;
    
    //trim the space
    while(isspace(*s)) s++;
    //check empty 
    if (*s == '\0' ) return false;
    //check sign
    if (*s=='+' || *s=='-') s++;

    const char *head  = s;
    for(; *s!='\0'; s++){
        // if meet point
        if ( *s == '.' ){
            if ( hasE == true || point == true){
                return false;
            }
            if ( s == head && !isdigit(*(s+1))  ){
                return false;
            }
            point = true; 
            continue; 
        }
        //if meet "e"
        if ( *s == 'e' ){
            if ( hasE == true || s == head) {
                return false;
            }
            s++;
            if ( *s=='+' || *s=='-' )  s++;
            if ( !isdigit(*s) ) return false;
      
            hasE = true; 
            continue; 
        }
        //if meet space, check the rest chars are space or not
        if (isspace(*s)){
            for (; *s != '\0'; s++){
                if (!isspace(*s)) return false;
            }
            return true;
        }
        if ( !isdigit(*s) ) {
            return false;
        }
       
    }
    
    return true; 
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }
    printf("%s\n", isNumber(argv[1]) ? "true" : "false");
    return 0;
}
