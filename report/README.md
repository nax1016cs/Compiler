# 作業1報告
- 學生 : 蔣傑名 學號 : 0516097

## Define Macros
- token(t) : 負責２個字元以上的`operators` 和 `Keyword`。
- tokenChar(t) : 負責單字元的　`operator` 和 `delimeters`。
- tokenInteger(t, i): 負責integers。
- tokenOct(t, i) : 負責8進位數。
- tokenString(t, s) :　負責string。
- tokenScientific(t, s) : 負責科學記號。
- tokenFloat(t,ts) :　負責浮點數。

## Regular expression
-  `digit` : `[0-9]`。
-  `letter` : `[a-zA-Z]`。
-  `int` : `(0|[1-9][0-9]*)`。
-  `oct` : `[0][0-7]+`。
-  `floating` : `{int}[.][0-9]*[1-9]`。
-  `scientific` : `({floating}|{int})[Ee][+-]?{int}`。
-  `identifier` : `{letter}({letter}|{digit})*`。
-  `string` :　`\".*\"`。

## Comment 

- `" /**/ " `: 利用start condition，設定2種TAG。一種是INITIAL，另一種則是 COMMENT。遇到"/"之後，會跳到COMMENT TAG，直到讀到"/"才回到INITIAL ，即可避免在COMMENT中切出不該切的TOKEN。 
- `" // "` : 如果遇到 `"//"` 開頭的COMMENT，則直接加到LIST裡面即可。 
- `pseudo comment` : 把相對應的 `OPT_T` 或 `POT_S` 設為`1`或者`0`。EX: 遇到`//&S+`則把`Opt_S`設為`1`，`//T-`則把`Opt_T`設為`0`，並且LIST。

## Scanner 實作

- `Delimeters` :　利用`token char`切出，並list。
- `Operator` : 單字元利用`token char`切出，並list；2字元以上利用`token`切出，並list。。
- `Keyword` : 利用`token`切出，並將`keyword`名稱傳入後list。
- `Floating-Point Constants` : 利用`tokenFloat(float,yytext)`，但是上頭規定的RE會把0.0去除掉，因此多加上0.0。
- `Scientific Notations` : 利用`tokenString(scientific,yytext)`切出，並list。
- `String Constants` :　由`'"'`開頭，以及由`'"'`結尾的字串，但是要把中間多餘的`'"'`過濾掉，因此多開一個陣列來處理並存放正確的字串，再傳入`tokenString(string,str)`。
- `Whitespace `: 只LIST，不做其他動作。
- `Comments && Pseudocomments` : 利用`<INITIAL>` 和 `<COMMENT>`tag來達到各自的效果。
- `Identifier`: 利用`tokenString(id,yytext)`切出，並且list。


## 結果

- ![imgur](https://imgur.com/1OqlYEt.png)