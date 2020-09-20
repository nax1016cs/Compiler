# 作業2報告
- 學生 : 蔣傑名 學號 : 0516097

## Compile command 
- `yacc -d parser.y`: To generate y.tab.h and y.tab.c.
- `lex scanner.l` : Generate lex.yy.c.
- `make` : Link and Compile the whole files.

## Scanner
- Use the version of TA's scanner, and return each token after lex configuring them.

- EX: `"array"   { TOKEN(KWarray); return ARRAY;}`

## Context free grammar 
- ***Program Units***
    - **PROGRAM**: 
        - program :    ID ';' program_body END ID;
        - program_body :      var_dec func_dec compound_stat;
        
    - **FUNCTION**:
        - func_dec: 
                    | non_empty_func_dec;
        - non_empty_func_dec:  non_empty_func_dec function | function;
        -  function    : ID  '('  arguments  ')'  ':'  TYPE  ';' compound_stat  END  ID 
          | ID '(' arguments ')' ';' compound_stat END ID ;
          
- ***Data Types and Declarations***
    - **VARIABLE**:
        - var_dec: 
                    | non_empty_var_dec;
                    
        - non_empty_var_dec:  non_empty_var_dec variable | variable;

        - variable         :VAR id_list ':' TYPE ';'
                |VAR id_list ':' ARRAY INT TO INT OF array_type ';'
                |VAR id_list ':' constant ';';
                
    - **IDLIST**:
        - id_list: 
                    |non_empty_id_list;

        - non_empty_id_list   :non_empty_id_list ',' ID
                    |ID;
                    
    - **CONSTANT**:
        - constant:       TRUE |FALSE |INT |OCT |FLOAT |SCIENTIFIC |STR;
         
    - **ARRAY_TYPE**:
        - array_type     :ARRAY INT TO INT OF array_type
                | TYPE; 
                
    - **VARIABLE_REFERENCE**:
        - variable_reference: ID array_reference;
         
    - **ARRAY_REFERENCE**:
        - array_reference: 
                    |'[' expressions_stat ']' array_reference;
                    
    - **TYPE**:
        - TYPE : BOOLEAN 
           | INTEGER 
           | REAL 
           | STRING;
           
    - **ELSE**:
        - expression_list :
                    |expressions_stat
                    |expression_list ',' expressions_stat;
                    
        - arguments: 
                    | non_empty_arg;

        - non_empty_arg:      non_empty_arg ',' id_list ':' TYPE 
                    | id_list ':' TYPE;
                    
- ***Expressions***:
    - **expression**:
        - expressions_stat:   expressions_stat AND expressions_stat
                    | expressions_stat OR expressions_stat
                    | NOT expressions_stat
                    | expressions_stat NE expressions_stat
                    | expressions_stat GE expressions_stat
                    | expressions_stat LE expressions_stat
                    | expressions_stat '=' expressions_stat
                    | expressions_stat '>' expressions_stat
                    | expressions_stat '<' expressions_stat
                    | expressions_stat '/' expressions_stat
                    | expressions_stat MOD expressions_stat
                    | expressions_stat '*' expressions_stat
                    | expressions_stat '-' expressions_stat
                    | expressions_stat '+' expressions_stat
                    | '-' expressions_stat
                    | '(' expressions_stat ')'
                    | constant
                    | ID 
                    | function_invocation_stat
                    | variable_reference;

- ***Statements***: 
    - **COMPOUND**:
       - compound_stat: BGN var_dec statements END;
       
    - **SIMPLE**:
        - simple_stat:        variable_reference  ASSIGN expressions_stat 
                    | PRINT expressions_stat 
                    | READ variable_reference ;

    - **CONDITIONAL**:
        - conditional_stat: IF expressions_stat THEN statements condition_body END IF;
        - condition_body: 
                | ELSE statements;

    - **WHILE**:
        - while_stat: WHILE expressions_stat DO statements END DO;
        
    - **FOR**:
        - for_stat: FOR ID ASSIGN INT TO INT DO statements END DO;
         
    - **RETURN**:
        - return_stat: RETURN expressions_stat;
         
    - **FUNCTION_INVOCATION**:
        - function_invocation_stat: ID '(' expression_list ')'


## Parser ability

My parser can parse the the grammar written above, i.e a P program. However, it cannot check the semantic error yet. 


## 結果

- ![imgur](https://imgur.com/N1Dgwg3.png)