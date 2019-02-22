#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp;

int main()
{
   pid_t p;
   char str2[100];
   fp = fopen("readfork", "w");


   p = fork();
   if(p==0)
   {
   	 printf("Child created!\n");
     fprintf(fp, "%s", "1234");
     

   }

   fclose(fp);
   return 0;
}