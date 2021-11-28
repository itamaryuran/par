/**
 * File Name: par.c
 * Program that checks if the codes brackets are eligble
 *
 * @author Itamar Yuran
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define IN 1
#define OUT 0
#define MAXLINE 100



int special(char line[]);                           /* checks if the line contains only one curleybrackets */
int checkline(char line[]);                               /* checks bracets in line */
void printline(char line[], int state);                       /* prints the line, state sais if line is eligble */

int main()
{
    char line[MAXLINE];                             /*the current line*/
    char specialline[MAXLINE];                           /*stack for specialline brackets*/
    int ndxspecial =0;
    int BADLINES = 0;
    specialline[0] = '-';

    printf("\n ############### HELLO, PLEASE ENTER A BRICK OF CODE ###############\n");
        while (fgets(line, MAXLINE+1, stdin) != NULL)
        {
        if (special(line) == IN)
        {
            if (line[0] == '{' ||line[1] == '{')
            {
                specialline[ndxspecial] = '{';
                ndxspecial++;
            }
            else if (line[0] == '}'|| line[1] == '}')
            {
               if (specialline[ndxspecial-1] == '{')
               {
                   specialline[ndxspecial-1] = '-';
                   ndxspecial--;
               }
            }
            printline(line, OUT);
        }
        else
        {
            if (checkline(line) == OUT)
            {
                BADLINES++;
                printline(line, OUT);
            }
            else 
            {
                printline(line, IN);
            }
        }
        }
   
    if (BADLINES == 0 && specialline[0] == '-')
    {
        printf("\n +++++++++++++++ YOUR CODE'S BRACKETS ARE FINE +++++++++++++++\n");
    }
    else 
    {
        printf("\n --------------- YOUR CODE'S BRACKETS ARE NOT O.K. ---------------\n");
    }
    return -1;
}


int checkline(char line[])
{
    char line2[MAXLINE];

    int i = 0;
    int ndx = 0;
    line2[0] = '-';
    do
    {
        /*this loop keeps going as long as we are currently inside a coment, and doesnt check brackets*/
        if (line[i] == '"' || (line[i] == '/' && line[i+1] == '*'))
        {
         i++;
            while ((line[i] != '"' && (line[i] != '*' && line[i+1] != '/')))
            {
               if (line[i]== '\0')
               {
                   printline(line,IN);
                   fgets(line, MAXLINE+1, stdin);
                   i=0;
                   ndx =0;
               }
                if (line[i] == '"' || (line[i] == '*' && line[i+1] == '/'))
                   {
                       break;
                   }
            i++;
            } 
            
        }
/*checks the brackets*/
        switch (line[i])
    {
        case '}':
        if (line2[ndx-1] == '{')
        {
            line2[--ndx] = '-';
        }
        else
        {
        return OUT;
        }
        break;

        case ']':
        {
        if (line2[ndx-1] == '[')
        {
            line2[ndx-1] = '-';
            ndx--;
        }
        else
        {
        return OUT;
        }
        }
        break;
        case ')':
        if (line2[ndx-1] == '(')
        {
            line2[--ndx] = '-';
        }
        else
        {
        return OUT;
        }
        break;
        

        case '{':
        {
            line2[ndx++] = '{';
        }
        break;

        case '[':
        {
            line2[ndx++] = '[';  
        }
        break;

        case '(':
        {
            line2[ndx++] = '('; 
        }
        break;

    }
    i++;
    } 
    while (line[i] != '\0');

if (line2[0] == '-')
{
    return IN;
}
else 
return OUT;
        

}




void printline(char line[], int state)
{
    if (state == IN)
    {
            printf("+++++++++THIS LINE'S BRACKETS ARE O.K.: %s\n", line);
    }

     if (state == OUT)
    {
            printf("---THIS LINE'S BRACKETS ARE ^NOT^ O.K.: %s\n", line);
    }
}


int special(char line[])             /*return IN if special, OUT if not*/
{
    int j = 0;
    int cnt =0;
 do
{
    switch (line[j++])
    {
    case ' ':
    case '\t':
    case '\n':
    case '\v':
    case '\r':
    case '\f':
      {
          {
             break;
          }
           break;
      } 
    case '{':
    case '}':
    {
    cnt++;
    if (cnt>1)
    {
        return OUT;
    }
    }
    default:
        return OUT;
    }
}
while (line[j] != '\0'||line[j+1] != '\0');

return IN;
}


