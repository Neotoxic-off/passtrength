#include "lib.h"
#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void printpart(general *global)
{
    printf("Password....... %s\n\n", global->pass);
    printf("Length......... %d\n", global->length);
    printf("Low............ %d\n", global->low);
    printf("High........... %d\n", global->high);
    printf("Number......... %d\n", global->number);
    printf("Special........ %d\n", global->special);
    printf("Occurrence..... %d\n\n", global->occurrence);
    printf("Strength....... %d\n", global->strength);
    if (global->strength <= 5)
        printf("Comment........ %sDon't use that password\n", KRED);
    if (global->strength <= 7 && global->strength > 5)
        printf("Comment........ %sNot enough strong add more variations\n", KRED);
    if (global->strength <= 10 && global->strength > 7)
        printf("Comment........ %sCorrect password but think to change it quickly\n", KYEL);
    if (global->strength <= 15 && global->strength > 10)
        printf("Comment........ %sStrong password but don't use it in all your accounts\n", KYEL);
    if (global->strength <= 17 && global->strength > 15)
        printf("Comment........ %sGood password you can use it\n", KGRN);
    if (global->strength <= 20 && global->strength > 17)
        printf("Comment........ %sThe strongest password i've ever seen\n", KGRN);
        
}

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

void occurrences(general *global)
{
    for (int i = 0; global->pass[i] != '\0'; i++) {
        for (int j = (i + 1); global->pass[j] != '\0'; j++) {
            if (global->pass[i] == global->pass[j])
                global->occurrence++;
        }
    }
}

void calculs(general *global)
{
    occurrences(global);
    if (global->length == global->low || global->length == global->high ||
    global->length == global->number) {
        global->strength = 0;
    }
    global->strength += global->low;
    global->strength += global->high;
    global->strength += global->number;
    global->strength -= global->occurrence;
    global->strength += global->special * 2;
    if (global->length >= 8)
        global->strength += 2;
    if (global->length >= 10)
        global->strength += 2;

    if (global->strength < 0)
        global->strength = 0;
    if (global->strength > 20)
        global->strength = 20;
}

void parser(char *password)
{
    int i = 0;
    char list[] = "\"!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\0";
    general *global = malloc(sizeof(general));
    global->pass = malloc(sizeof(char) * (my_strlen(password) + 1));
    global->pass = password;

    while (password[i] != '\0') {
        if (password[i] <= 122 && password[i] >= 97)
            global->low++;
        if (password[i] <= 90 && password[i] >= 65)
            global->high++;
        if (password[i] <= 57 && password[i] >= 48)
            global->number++;
        for (int j = 0; list[j] != '\0'; j++) {
            if (password[i] == list[j])
                global->special++;
        }
        global->length++;
        i++;
    }
    calculs(global);
    printpart(global);
}

int main(int ac, char **argv)
{
    if (ac < 2) {
        printf("Usage: ./passtrength <password>");
        return (84);
    }
    else
        parser(argv[1]);
    return (0);
}
