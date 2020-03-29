#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{ char str[50],substr[50];
  int i,j=0,len1,len2;
  printf("\n Enter the string:");
  scanf("%[^\n]",str);
  getchar();
  printf("\n Enter the substring:");
  scanf("%[^\n]",substr);
  getchar();
  len1=strlen(str);
  len2=strlen(substr);
   for(i=0;(i<len1)&&(j<len2);)
     { if(str[i]==substr[j])
         { i++;
           j++;
		 }
		else
		   { i++;
		      j=0;
		   }
	 }
	 if(i== len1)
	  
	  printf("\n Substring not found!");
	else
	 
	   printf("\n First occurence of substring at index %d",i-len2);
	   
}
