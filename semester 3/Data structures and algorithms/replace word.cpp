#include<stdio.h>
#include<conio.h>
#include<string.h>
main()
{ char str1[50],str2[50],word1[30],word2[30];
  int len1,len2,len3,i,j,k,pos;
  printf("\n Enter the string:");
  scanf("%[^\n]",str1);
  getchar();
  printf("\n Enter the word to be replaced:");
  scanf("%[^\n]",word1);
  getchar()	;
  printf("\n Enter the replacing word:");
  scanf("%[^\n]",word2);
  len1=strlen(str1);
  len2=strlen(word1);
  len3=strlen(word2);
  for(i=0,j=0;i<len1,j<len2;)
    { if(str1[i]==word1[j])
        { i++;
          j++;
		}
	  else
	    { i++;
	       j=0;
		}
		
	}
	pos=i-strlen(word1);
	  if(pos==0)
	   { for(k=0,j=0;j<len3;)
           str2[k++]=word2[j++];
		 for(j=i;j<len1;)
		  str2[k++]=str1[j++];
		 str2[k]='\0';

	   }
	   else
	   { for(k=0,j=0;j<pos;)
	       str2[k++]=str1[j++];
	     for(j=0;j<len3;)
	      str2[k++]=word2[j++];
	     for(j=i;j<len1;)
	      str2[k++]=str1[j++];
	      str2[k]='\0';
	   }
    printf("\n Modified string is:");
	printf("%s",str2);
	getch();
}
