#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp;

int main()
{
   pid_t p;
   fp = fopen("readfork", "w");
   

   p = fork();
   if(p==0)
   {
   	 printf("Child created!\n");
     fprintf(fp, "%s", "1000000000000");


   }
   else
   {
     fprintf(fp, "%s", "123456");
   }

   
   
   fclose(fp);

   return 0;
}