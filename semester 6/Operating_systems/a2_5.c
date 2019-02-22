#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp;

int main()
{
   pid_t p;
   char str1[100], str2[100];
   fp = fopen("readfork", "r");
   fscanf(fp, "%[^\n]", str1);
   printf("Parent reads: %s\n", str1);

   p = fork();
   if(p==0)
   {
   	 printf("Child created!\n");
     fscanf(fp, "%[^\n]", str2);
     printf("Child reads: %s\n", str2);

   }

   
   else
     fclose(fp);

   return 0;
}