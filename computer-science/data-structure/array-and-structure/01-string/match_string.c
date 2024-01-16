#include <stdio.h>
#include <string.h>

int matchString(char *, char *);

int main()
{
    char *string = "ababbaabaa";
    char *pat = "aab";
    
    int idx = matchString(string, pat);

    printf("string: %s\n", string);
    printf("pattern: %s\n", pat);
    printf("match idx: %d\n", idx);

    return 0;
}

int matchString(char *string, char *pat)
{
    int i, j, start = 0;
    int lastString = strlen(string) - 1; // string의 마지막 인덱스
    int lastPat = strlen(pat) - 1; // pat의 마지막 인덱스
    int endMatch = lastPat;
    
    for(i = 0; endMatch <= lastString; endMatch++, start++){
        if(string[endMatch] == pat[lastPat])
            for(j = 0, i = start; j < lastPat && string[i] == pat[j]; i++, j++)
                ;
        if(j == lastPat)
            return start;
    }   

    return -1;
}