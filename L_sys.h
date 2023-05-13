#include <stdlib.h>

//-----------string-functions----------
int len(char *str)
{
    int len = 0;
    while (*(str + len) != '\0') len++;

    return len;
}


char *concat(char *s1, char *s2)
{
    char *concat_s = malloc(len(s1) + len(s2) + 1);

    for (int i = 0; i < len(s1); i++)
        concat_s[i] = s1[i];
    for (int i = 0; i < len(s2); i++)
        concat_s[len(s1)+ i] = s2[i];

    concat_s[len(s1) + len(s2)] = '\0';

    return concat_s;
}

char *set_str(char *s1, char *s2)
{
    free(s1);
    s1 = (char *)malloc(len(s2) + 1);

    for (int i = 0; i < len(s2); i++)
        s1[i] = s2[i];

    s1[len(s2)] = '\0';

    return s1;
}
//------------------------------------------


char *Generate_Lsys(char *axiom, int n)
{
    char *tempAx = (char*)malloc(2);
    axiom = "F";
    tempAx = "";

    for (int i = 0; i < n; i++)
    {
        for(int ch = 0; ch < len(axiom); ch++)
        {
            switch(axiom[ch])
            {
            case '+':
                tempAx = set_str(tempAx, concat(tempAx, "+"));
                break;
            case '-':
                tempAx = set_str(tempAx, concat(tempAx, "-"));
                break;
            case 'F':
                tempAx = set_str(tempAx, concat(tempAx, "F+F-F-F+F"));
                break;
            }
        }
        axiom = set_str(axiom, tempAx);
        tempAx = set_str(tempAx, "");
    }

    return axiom;
}

char *Generate_Lsys_2(char *axiom, int n)
{
    char *tempAx = (char*)malloc(2);
    axiom = "0";
    tempAx = "";

    for (int i = 0; i < n+1; i++)
    {
        for(int ch = 0; ch < len(axiom); ch++)
        {
            switch(axiom[ch])
            {
            case '1':
                tempAx = set_str(tempAx, concat(tempAx, "11"));
                break;
            case '0':
                tempAx = set_str(tempAx, concat(tempAx, "1[0]0"));
                break;
            case '[':
                tempAx = set_str(tempAx, concat(tempAx, "["));
                break;
            case ']':
                tempAx = set_str(tempAx, concat(tempAx, "]"));
                break;
            }
        }
        axiom = set_str(axiom, tempAx);
        tempAx = set_str(tempAx, "");

    }
    return axiom;
}

char *Generate_Lsys_DragonC(char *axiom, int n)
{
    char *tempAx = (char*)malloc(3);
    axiom = "FX";
    tempAx = "";
    for (int i = 0; i < n+1; i++)
    {
        for(int ch = 0; ch < len(axiom); ch++)
        {
            switch(axiom[ch])
            {
            case 'X':
                tempAx = set_str(tempAx, concat(tempAx, "X+YF+"));
                break;
            case 'Y':
                tempAx = set_str(tempAx, concat(tempAx, "-FX-Y"));
                break;
            case '+':
                tempAx = set_str(tempAx, concat(tempAx, "+"));
                break;
            case '-':
                tempAx = set_str(tempAx, concat(tempAx, "-"));
                break;
            case 'F':
                tempAx = set_str(tempAx, concat(tempAx, "F"));
            }
        }
        axiom = set_str(axiom, tempAx);
        tempAx = set_str(tempAx, "");

    }
    return axiom;

}
