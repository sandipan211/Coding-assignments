#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct report
  { int region;
    int id;
    int pcode;
    int qty;
  };
 
  main()
 { struct report r;
   float emp[4][6];
   float cost[5];
   FILE *f1,*f2;
   f1=fopen("report.txt","rb");
   f2=fopen("rate.txt","r");
     if((f1==NULL)||(f2==NULL))
       { printf("Error! File not found!");
         exit(0);
	   }
   int pos=0,i=0;
    for(i=0;i<5;i++)
       fscanf(f2,"%f",&cost[i]);
   i=0;
   while(!feof(f1))
      { pos=i*sizeof(r);
        fseek(f1,pos,SEEK_SET);
        fread(&r,sizeof(r),1,f1);
         if(!feof(f1))
           fprintf(f1,"\n%d %d %d %d ",r.region,r.id,r.pcode,r.qty);
        emp[r.region-1][r.id-1]+=r.qty*cost[r.pcode-1];
        i++;
      }
    fclose(f1);
    fclose(f2);
    printf("\n Enter the region whose report is needed:(press 5 to stop)");
    int p;
    scanf("%d",&p);
    while(p<5)
      { printf("\n            ABC COMPANY");
	    printf("\n Employee                      Cost of total sold items\n");
        for(i=0;i<6;i++)
          printf("employee %d                    %f\n",i+1,emp[p-1][i]);
         scanf("%d",&p);
      }
     getch();
}
