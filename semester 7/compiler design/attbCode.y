%{
   //Code Generation ----------------------------
   
    #include "lex.yy.c"
    
    struct node{
        int type;
        int line_no;
        char name[32];
    };
    
    struct node symbol_table[20];
    int sym_table_index = 0;
    
    char temp_table[10][64];
    
    int temp_table_index;
    
//-------new declarations----------------------
    int Temp_vid=0;
    char temp_v[10];
    
    int STSize =7;
    char stack[100][50];
    int top = 0;
    
    
    void view_symb();
    void newtemp();
    void tostring(char [], int );
    void yyerror(char *);
    void init_Reg();
    void getReg();
    void Code_gen(char, char [], char [], char []);
//----------------New Declarations For Target Code generations------------------
     int Reg[16];
     int L=18;
     int label = 8000;

 //-------------------------------------------------------------------------------------------
    void put_in_temp_table(char *id_name){
        strcpy(temp_table[temp_table_index++],id_name);
    }
 //--------------------------------------------------------------------------------------------
    int search_in_table(char *id_name){
        int j;
        //printf("searching for %s\n",id_name);
        for(j=0;j<sym_table_index;j++){
            if(strcmp(symbol_table[j].name,id_name)==0) return j;
        }
        return -1;
    }
//------------------------------------------------------------------------------------------------
    void move_to_table(int id_type){
        int i,j;
        
        for(i=0;i<temp_table_index;i++){
            for(j=0;j<sym_table_index;j++){
                if(strcmp(symbol_table[j].name,temp_table[i])==0){
                    printf("%d ERROR : Variable already declared at line %d--- Token==%s\n",yylineno,symbol_table[j].line_no,symbol_table[j].name);
                    exit(0);
                }
            }
        }
        
        //now put things in
        for(i=0;i<temp_table_index;i++){
            symbol_table[sym_table_index].type = id_type;
            symbol_table[sym_table_index].line_no = yylineno;
            strcpy(symbol_table[sym_table_index].name,temp_table[i]);
            sym_table_index++;
        }
    }	
    
%}
//-------------------------------------------------------------------------------------------------------------------------------------
%token ID_TOK
%token INT
%token FLOAT
%token CHAR
%token IF
%token ELSE
%token FOR WHILE
%token SWITCH
%token CASE
%token MAIN_FN
%token USER_FN
%token type_int type_char type_float
%start S



%union{
    struct s1{
               int i_value;
               char place[5];
               char code[300];} v;
    struct s2{char name[64];} n;
    struct s3{int i_type;} t;
};

%type <t> type_id type_int type_char type_float

%type <n> ID_TOKENS ID_TOK

%type <v> expr assignment T FLOAT INT CHAR










%%
S:	usr_fn_defn MAIN_FN '('')''{'  statements  '}'   ;



usr_fn_defn:	                                                {printf("No user defined func\n");};
               |usr_fn_defn USER_FN '('')''{'  statements  '}'  ;
               |USER_FN '('')''{'  statements  '}';



statements:
              statements statement;
            | statement ;



statement:
              declaration;
            | assignment;
//            |conditional;
//            |forloop;
//            |whileloop;
//            |function_call;
//            |switch_stat;



declaration:	type_id ID_TOKENS';'		{printf("declaration ----%d\n",$1.i_type);  move_to_table($1.i_type); };


type_id:    type_int 					{$$.i_type = 1;    printf("type found : %d\n",$$.i_type);	temp_table_index = 0;};
           |type_char 					{$$.i_type = 2;    printf("type found : %d\n",$$.i_type);	temp_table_index = 0;};
           |type_float					{$$.i_type = 3;    printf("type found : %d\n",$$.i_type);   temp_table_index = 0;};


ID_TOKENS:  ID_TOK','ID_TOKENS 		    {printf("tok %s\n",$1.name);put_in_temp_table($1.name);};
           |ID_TOK					    {printf("tok %s\n",$1.name);put_in_temp_table($1.name);};



assignment:		ID_TOK'='expr';'	{
                                         printf("assignment\n");
                                         int index = search_in_table($1.name);
                                         if(index==-1){
                                              printf("%d ERROR : identifier '%s' not declared yet\n",yylineno,$1.name);
                                              exit(0);
                                            }
                                    if(symbol_table[index].type!=$3.i_value){
                                          printf("%d ERROR : type of '%s' does not match with type ",yylineno,$1.name);
                                          if($3.i_value==type_int) printf("'int'\n");
                                          else if($3.i_value==type_float) printf("'float'\n");
                                          else if($3.i_value==type_char) printf("'char'\n");
                                          exit(0);
                                        }
                                    $$.i_value = symbol_table[index].type;

                                    //for Intermediate code generation
                                     strcpy($$.code,$3.code);
                                    

                                    //-- Intermediate Code Generation -concat gen===QuadDruple----
                                    strcat($$.code, "\n");
                                    strcat($$.code,$1.name);
                                    strcat($$.code," = ");
                                    strcat($$.code,$3.place);

                                    //Code Gen ======== for Target Machine ============
                                    Code_gen( '=', $3.place, "" , $$.place);


                                    printf("\n===Code:\n  \n%s\n", $$.code);
                                    
                                    
                                    };

expr:	   expr'+'T		{
                         //for type checking
                         if($1.i_value!=$3.i_value){printf("%d ERROR : type mismatch for arithemetic expression\n",yylineno);exit(0);}
                         $$.i_value=$1.i_value;
                         //for code generation
                         $$.code[0] = '\0';
                         newtemp();              // generate temporary variable...
                         strcpy($$.place,temp_v);
                         strcat($$.code, $1.code);
                         if($1.code[0]!= '\0')strcat($$.code, "\n");
                         strcat($$.code, $3.code);
                         if($3.code[0]!= '\0')strcat($$.code, "\n");
                         //---concat gen===Quadruple-------------------------------------------
                         strcat($$.code,$$.place);
                         strcat($$.code,"=");
                         strcat($$.code,$1.place);
                         strcat($$.code,"+");
                         strcat($$.code,$3.place);
                         
                         //Code Gen ======= from Quadruple ===================
                         Code_gen( '+', $1.place, $3.place, $$.place);
                         
                         
                         };

          |expr'-'T		{if($1.i_value!=$3.i_value){printf("%d ERROR : type mismatch for arithemetic expression\n",yylineno);exit(0);}$$.i_value=$1.i_value;};
          |expr'*'T		{if($1.i_value!=$3.i_value){printf("%d ERROR : type mismatch for arithemetic expression\n",yylineno);exit(0);}$$.i_value=$1.i_value;};
          |expr'/'T		{if($1.i_value!=$3.i_value){printf("%d ERROR : type mismatch for arithemetic expression\n",yylineno);exit(0);}$$.i_value=$1.i_value;};
          |expr'%'T		{if($1.i_value!=$3.i_value){printf("%d ERROR : type mismatch for arithemetic expression\n",yylineno);exit(0);}$$.i_value=$1.i_value;};
          |T  			{$$.i_value=$1.i_value;
                        printf("\nplace-expr====> %s\n",$$.place);                                   //For Code Generation
                        strcpy($$.place,  $1.place);
                        strcpy($$.code,$1.code);};             //For Code Generation

T:	   ID_TOK	                  {
                                     int index = search_in_table($1.name);
                                     //printf("type found %s %d\n",$1,type);
                                     if(index==-1){
								           printf("%d ERROR : identifier '%s' not declared yet\n",yylineno,$1.name);
                                           exit(0);
                                         }
                                     /*if(symbol_table[index].type==type_char){
                                     printf("%d ERROR : identifier '%s' of type 'char' not allowed here\n",yylineno,$1);
                                       exit(0);
                                       }*/
                                     $$.i_value = symbol_table[index].type;        // For Type Checking
                                     
                                     strcpy($$.place,  symbol_table[index].name); printf("\nplace====> %s\n",$$.place);        //For Code Generation
                                     strcpy($$.code,"");                                                                       //For Code Generation
                                  };
 //      |INT	                      {$$.i_value = type_int;};
 //      |FLOAT	                  {$$.i_value = type_float;};
 //      |CHAR	                  {$$.i_value = type_char;};


%%


int main(int argc , char *argv[]){
    FILE *fp;
    int token;
    
    if (argc == 2 && (fp = fopen(argv[1], "r")))
    yyin = fp;
    else {
        printf("usage <filename>\n");
        return 0;
    }
    
    if(yyparse()==0) printf("\nparsed successfully\n\n");
    else {printf("\nparsing error at line no %d\n",yylineno);
    
    int i;
    for(i=0;i<sym_table_index;i++){
        if(symbol_table[i].type==type_int) printf("int");
        else if(symbol_table[i].type==type_char) printf("char");
        else if(symbol_table[i].type==type_float) printf("float");
        else printf("???");
        printf("\t%d - %s\n",symbol_table[i].line_no,symbol_table[i].name);
    }}
    
    //---CodeGen
    init_Reg();   // Free the registers.....
   


    
    fclose(fp);
    return 0;
}

void yyerror(char *s){
    printf("yyerror: %s\n",s);
}

//-----------------------------------------------


void view_symb()
{
    
    printf("\n Printing Symbol Table Entries......\n");
    int i;
    for(i=0;i<=5;i++)
    {
        printf("id=%s------line No= %d----- Type = %d\n",symbol_table[i].name, symbol_table[i].line_no, symbol_table[i].type);
    }
    

}

//-------------------------------------------
void newtemp()
{
    Temp_vid ++;
    char str1[20],str[20];
    tostring(str, Temp_vid);
    
    strcpy(str1,"t");
    strcat(str1,str);
    strcpy(temp_v,str1);
}

//--------------
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
    
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

//---------- generate free registers----------------------
void getReg()
{
    int i;
    for(i=0;i<=15;i++)
    {
        if(Reg[i]==0)break;
    }
    L=i;
    if(L > 15) printf("No Free Register are there");
    
}

void init_Reg()
{
    int i;
    for(i=0;i<=15;i++)
    {
        Reg[i]=0;
    }
}

//------takes Quadruple-----and generate Code for Target Machine------------
void Code_gen(char op, char arg1[], char arg2[], char result[])
{
    char tcode[50];
    char R[10],Rt[10];
    char lab[6];
    getReg();
    Reg[L]=1;
    tostring(Rt, L);
    if(L==0)strcpy(Rt,"0");
    strcat(R,"R");
    strcat(R,Rt);
    

    
    //-------ADD arg2 R0------------------
    if (op =='+')
    {
        
        // ---- MOV arg1 R0 -------
        tostring(lab, label);
        strcpy(tcode, lab);
        strcat(tcode, "\t");
        strcat(tcode, "MOV");
        strcat(tcode, "\t");
        strcat(tcode, arg1);
        strcat(tcode, "\t");
        strcat(tcode, R);
        strcat(tcode, "\n");
        label++;   // Increase label according to the size of MOV Instruction
        
        
        tostring(lab, label);
        strcat(tcode, lab);
        strcat(tcode, "\t");
        strcat(tcode, "ADD");
        strcat(tcode, "\t");
        strcat(tcode, arg2);
        strcat(tcode, "\t");
        strcat(tcode, R);
        strcat(tcode, "\n");
        label++;                 // Increase label according to the size of ADD Instruction
    //------- MOV R0 result------------------
        tostring(lab, label);
        strcat(tcode, lab);
        strcat(tcode, "\t");
        strcat(tcode, "MOV");
        strcat(tcode, "\t");
        strcat(tcode, R);
        strcat(tcode, "\t");
        strcat(tcode, result);
        strcat(tcode, "\n");
        label++;
        
        Reg[L]=0;                // Free The Register .................
    }
    // -----------  MOV t4 d
    
    
    if(op == '=')      // Assignment ============
    {
        tostring(lab, label);
        strcat(tcode, lab);
        strcat(tcode, "\t");
        strcat(tcode, "MOV");
        strcat(tcode, "\t");
        strcat(tcode, arg1);
        strcat(tcode, "\t");
        strcat(tcode, result);
        strcat(tcode, "\n");
        label++;
   
    }
    printf("\n%s",tcode);
  
    // generate code for Other Assignment Operations  ...................

  //  printf("%s %c  %s %c %s\n",arg3, '=', arg1, op, arg2 );  // code_gen for Quadruple

}



