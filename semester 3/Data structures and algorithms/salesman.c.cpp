		#include <stdio.h>
		#include<stdlib.h>
		#include<string.h>
		int price(int id,int quantity);	
		int equals(char a[],char b[]);
		FILE *dt;
		FILE *pr;
		
		int main()
		{
			int c=1;
			while(c!=0)
			{
			printf("Enter 0 for exit\n");
			printf("Enter 1 for accessing product database\n");
			printf("Enter 2 for making new entry\n");
			printf("Enter 3 for displaying report\n");
			scanf("%d",&c);
			
			
					if(c==0)
				{
					exit(0);
					break;}
					
					
				if( c==1)
				{
					int c2=1;
					while(c2==1||c2==0)
					{
					printf("Enter 1 for adding to product database\n");
					printf("Enter 0 for exiting from product database\n");
					scanf("%d",&c2);
					if(c2==0)
						break;
							
					else if(c2==1)
						{
							FILE *pr;
							pr=fopen("Product","ab");
							
							int c3=1;
							while(c3!=0)
							{
								printf("Enter product name:- ");
								char name[20];
								scanf("%s",name);
								
								
								printf("Enter product id(integer):- ");
								int id;
								scanf("%d",&id);
								
								
								printf("Enter product rate:- ");
								int rate;
								scanf("%d",&rate);
								fprintf(pr,"%s %d %d \n",name,id,rate);
								
								printf("Enter 1 to continue, 0 to stop:-");
								scanf("%d",&c3);
								printf("\n\n");
														
							}
							
							fclose(pr);
							}
							
					else
							{
								printf("Wrong input");
								continue;}
					}
					}
					
				
		
				if(c==2)
				{	
						dt=fopen("Database","ab");
					
					int c3=1;
							while(c3!=0)
							{
								printf("Enter region no(1-4):- ");
								int r;
								scanf("%d",&r);
								
								
								printf("Enter employee no(1-6):-");
								int e;
								scanf("%d",&e);
								
								
								printf("Enter product id(integer):- ");
								int id;
								scanf("%d",&id);
							
								
								printf("Enter quantity");
								int q;
								scanf("%d",&q);
								fprintf(dt,"%d %d %d %d \n",r,e,id,q);
								
											
								printf("Enter 1 to continue, 0 to stop:-");
								scanf("%d",&c3);
								printf("\n\n");
														
							}
							fclose(dt);
							}
							
							
						if(c==3)
						{
					
							int a[4][6];
							
							int i,j;
							for(i=0;i<4;i++)
							{
								for(j=0;j<6;j++)
								{a[i][j]=0;
								}
							}
							FILE *dt;
							
							dt=fopen("Database","rb");
							rewind(dt);
							
							while(!feof(dt))
							{
								int r;
								
								
								int e;
								
								int prod;
								
								
								int quan;
								fscanf(dt,"%d %d %d %d \n",&r,&e,&prod,&quan);
								
								
							//	printf("%d and %d \n",prod,quan);
								a[r-1][e-1]+=price(prod,quan);
							//	printf("%d \n",price(prod,quan));
								
							}
							fclose(dt);
							
							printf("            ABC COMPANIES\n\n\n");
							
							
							for(i=0;i<4;i++)
							{
								printf("\n REGION %d \n",(i+1));
								
								for(j=0;j<6;j++)
								{
									printf("Salesman %d :- Rs%d \n",(j+1),a[i][j]);
								}
								
												}						
							
							
							
							
							
							
							
						
						}
					}
					
				}
				
				int price(int prod,int quantity)
				{
					FILE *pr;
					
					pr=fopen("Product","rb");
					while(!feof(pr))
					{char name[20];
					
						
						int id;
							int rate;
						fscanf(pr,"%s %d %d \n",&name,&id,&rate);
						if(id==prod)
						{
						
							return rate*quantity;
						}
						
					
				}
					return 0;
				}
				
			
					
					
					
				
					
			
