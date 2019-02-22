#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fp;

int main()
{
   pid_t p;
   char str2[100];
   fp = fopen("readfork", "r");


   p = fork();
   if(p==0)
   {
   	 printf("Child created!\n");
     fscanf(fp, "%[^\n]", str2);
     printf("Child reads: %s\n", str2);

   }

   fclose(fp);
   return 0;
}