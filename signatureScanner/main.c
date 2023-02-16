#define __USE_MINGW_ANSI_STDIO 1
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int WTFcheck();
int EmergencyFileClose();
int compare();
int sign_read();

struct virus
{
    int length;
    int offset;
    unsigned char sign[1000];
};

int main()
{
    char pathExe[MAX_PATH];
    char pathTxt[MAX_PATH];
    int the_end, check, checkSR;

    if (printf(" This program searches certain signatures in exe-file.\n\n Please, make sure to read user's manual first.\n\n You'll be asked to enter two paths:\n 1st - to the file you want to check\n 2nd - to the file that contains information about signatures (AB)\n\n Make sure that AB-file follows the instructions from user's manual!\n\n\n") < 0)
    {
        printf (" printf (26) error occurred (Is that even possible?!)\n");
        getch();
        return 1;
    }

    if (printf(" Enter FILE path\n ") < 0)
    {
        printf (" printf (33) error occurred (Is that even possible?!)\n");
        getch();
        return 2;
    }

    while (check != 13)
    {
       if (WTFcheck(pathExe, &check) != 0)
       {
            printf(" WayToFileCheck (42) error occurred\n");
            getch();
            return 3;
       }
       if (check != 13)
        {
            if (printf (" Enter valid path\n ") < 0)
            {
                printf (" printf (50) error occurred\n");
                return 4;
            }
        }
    }

    if (printf(" Enter AB-file path\n ") < 0)
    {
        printf (" printf (58) error occurred (Is that even possible?!)\n");
        getch();
        return 5;
    }

    while (check != 31)
    {
       if (WTFcheck(pathTxt, &check) != 0)
       {
           printf(" WayToFile (67) error occurred\n");
           getch();
           return 6;
       }
       if (check != 31)
        {
            if (printf (" Enter valid path\n") < 0)
            {
                printf (" printf (75) error occurred\n");
                getch();
                return 7;
            }
        }
    }

    the_end = sign_read(pathTxt , pathExe, &checkSR);
    if (the_end != 0)
    {
        if (printf (" something went wrong, we'll fix that!\n") < 0)
        {
            printf (" printf (87) error occurred (Is that even possible?!)\n");
            getch();
            return 8;
        }
        getch();
        return 9;
    }

    if (checkSR == 0 || checkSR == 1)
        {
            if (checkSR == 1)
            {
                if (printf ("\n\n File's safe!\n\n") < 0)
                {
                    printf (" printf (101) error occurred (Is that even possible?!)\n");
                    getch();
                    return 10;
                }
                getch();
                return 0;
            }
            if (checkSR == 0)
            {
                if (printf ("\n\n WARNING!\n File %s corrupted!\n\n", pathExe) < 0)
                {
                    printf (" printf (112) error occurred (Is that even possible?!)\n");
                    getch();
                    return 11;
                }
                getch();
                return 0;
            }
        }
}

int WTFcheck(char* a, int* check)
{
    if (a == NULL)
    {
        printf(" WTFcheck argument 1 error occurred\n");
        return 1;
    }

    if (check == NULL)
    {
        printf(" WTFcheck argument 2 error occurred\n");
        return 2;
    }

    FILE* f;
    char path[MAX_PATH];
    char MN[2];
    int buffer, CKAH;
    size_t len;

    while (1)
    {
        CKAH = -1;
        len = 0;
        path[0] = '\0';
        CKAH = scanf("%[^\n]s", &path);
        len = strlen(path);
        if (CKAH != 1 && len != 0)
        {
            printf(" scanf (149) error occurred\n");
            return 3;
        }
        if ((fflush(stdin)) != 0)
        {
            printf (" fflush (156) error occurred\n");
            return 4;
        }
        f = fopen((path), "rb");
        if (f != NULL)  break;
        else if (printf(" Enter valid path\n ") < 0)
        {
            printf(" printf (163) error occurred\n");
            return 5;
        }
    }

    if (fread(MN, 1, 2, f) != 2)
    {
        printf(" fread (170) ERROR occurred!\n");
        EmergencyFileClose(f);
        return 6;
    }
    if (MN[0] == 'M' && MN[1] == 'Z')
    {
        if ((fclose (f) != 0))
        {
            printf (" fclose (178) error occurred\n");
            return 7;
        }
        for (size_t i = 0; i < len+1; i++)
        {
            a[i] = path[i];
        }
        buffer = 13;
        *check = buffer;
        return 0;
    }
    else
    {
        if ((fclose (f) != 0))
        {
            printf (" fclose (193) error occurred\n");
            return 8;
        }
        for (size_t i = 0; i < len+1; i++)
        {
            a[i] = path[i];
        }
        buffer = 31;
        *check = buffer;
        return 0;
    }
}

int sign_read(char* A, char* E, int* checkSR)
{
    if (A == NULL)
    {
        printf(" sign_read argument 1 error occurred\n");
        return 1;
    }

    if (E == NULL)
    {
        printf(" sign_read argument 2 error occurred\n");
        return 2;
    }

    if (checkSR == NULL)
    {
        printf(" sign_read argument 3 error occurred\n");
        return 3;
    }

    FILE* TXT;
    int check;
    struct virus* sign;
    int buffer;
    int N;
    int checkCMPR = -1;

    if ((TXT = fopen(A,"r")) == NULL)
    {
        printf (" fopen (235) error occurred\n");
        EmergencyFileClose (TXT);
        return 5;
    }

    if ((sign = (struct virus*)malloc(sizeof(struct virus))) == NULL)
    {
        printf(" malloc (242) error occurred\n");
        EmergencyFileClose (TXT);
        return 6;
    }
    if (fscanf(TXT, "%d", &N) != 1)
    {
        printf(" fscanf (248) error occurred\n");
        EmergencyFileClose (TXT);
        return 7;
    }
    for (int i = 0; i < N; i++)
    {
         if ((fscanf(TXT, "%d%d", &sign->offset, &sign->length)) != 2)
         {
             printf(" fscanf (256) error occurred\n");
             EmergencyFileClose (TXT);
             return 8;
         }
        for (int j = 0; j < sign->length; j++)
        {
            if (fscanf(TXT, "%hhu", &sign->sign[j]) != 1)
            {
                printf (" fscanf (264) error occurred\n");
                EmergencyFileClose (TXT);
                return 9;
            }
        }

        while(1)
        {
            if (sign->length < 8) break;

            check = compare(E, sign, &checkCMPR);
            if (check != 0)
            {
                printf(" compare (276) error occurred\n");
                EmergencyFileClose (TXT);
                return 10;
            }
            if (checkCMPR == 0)
            {
                if ((fclose (TXT) != 0))
                {
                    printf (" fclose (285) error occurred\n");
                    return 11;
                }
                buffer = 0;
                *checkSR = buffer;
                return 0;
            }
            if (checkCMPR == 1) break;
        }
    }
    if ((fclose (TXT) != 0))
    {
        printf (" fclose (297) error occurred\n");
        return 12;
    }
    if (checkCMPR == 1)
    {
        buffer = 1;
        *checkSR = buffer;
        return 0;
    }
    return 13;
}

int compare(char* E, struct virus* sign, int* checkCMPR)
{
    if (E == NULL)
    {
        printf(" compare argument 1 error occurred\n");
        return 1;
    }

    if (sign == NULL)
    {
        printf(" compare argument 2 error occurred\n");
        return 2;
    }

    if (checkCMPR == NULL)
    {
        printf(" compare argument 3 error occurred\n");
        return 3;
    }

    FILE* EXE;
    int same = 0;
    int buffer;
    unsigned char exesign[1000];
    long int fileMaxOffset;

    if ((EXE = fopen(E,"rb")) == NULL)
    {
        printf (" fopen (337) error occurred\n");
        return 4;
    }

    if ((fseek(EXE, 0, SEEK_END)) == -1)
    {
        printf (" fseek (343) ERROR occurred\n");
        EmergencyFileClose (EXE);
        return 5;
    }
    if ((fileMaxOffset = ftell(EXE)) == -1)
    {
        printf (" ftell (349) error occurred\n");
        EmergencyFileClose (EXE);
        return 6;
    }

    if (fileMaxOffset < (sign->offset + sign->length))
    {
        buffer = 1;
        *checkCMPR = buffer;
        if (fclose(EXE) != 0)
        {
            printf (" fclose (360) error occurred\n");
            return 7;
        }
        return 0;
    }

    if ((fseek(EXE, sign->offset, SEEK_SET)) == -1)
    {
        printf(" fseek (368) error occurred\n");
        EmergencyFileClose (EXE);
        return 8;
    }
    if (fread(exesign, 1, sign->length, EXE) != sign->length)
    {
        printf (" fread (374) error occurred!\n");
        EmergencyFileClose (EXE);
        return 9;
    }

    for (size_t i = 0; i < sign->length; i++)
    {
        if (exesign[i] == sign->sign[i]) { same++; }
    }
    if (same == sign->length)
    {
        if ((fclose (EXE) != 0))
        {
            printf (" fclose (387) error occurred\n");
            return 10;
        }
        buffer = 0;
        *checkCMPR = buffer;
        return 0;
    }
    else
    {
        if ((fclose (EXE) != 0))
        {
            printf (" fclose (398) error occurred\n");
            return 11;
        }
        buffer = 1;
        *checkCMPR = buffer;
        return 0;
    }
}

int EmergencyFileClose(FILE* f)
{
    if (fclose(f) != 0)
    {
        printf(" fclose error occurred\n");
        return 1;
    }
    printf(" File was closed because some error occurred\n");
    return 0;
}

