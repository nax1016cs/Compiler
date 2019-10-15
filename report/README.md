# 作業1 報告

學生 : 蔣傑名
學號 : 0516097

1. Define:
	在開頭宣告了token, tokenChar, tokenInteger, tokenOct, tokenString, tokenScientific, tokenFloat等，來切相對應的token。

2. Regular expression: 
	(1) digit : 0-9的數字。
	(2) letter : 英文字母。
	(3) int : 只有0或者以非0為開頭的整數。
	(4) oct : 以0為開頭的 0-7數字。
	(5) floating : 小數點前和int相同，小數點之後為了處理redundant 0s，規定必須是非0結尾。
	(6) scientific : 英文字母E or e前，有可能是floating 或者int ；之後可能會有'+' '-'號，最後則是和int相同。

3.COMMENT:
	(1) 利用start condition，設定2種TAG。一種是INITIAL，另一種則是 COMMENT。遇到"/*"之後，會跳到COMMENT TAG，直到讀到"*/"才回到INITIAL
	，即可避免在COMMENT中切出不該切的TOKEN。
	(2)如果遇到"//"開頭的COMMENT，則直接加到LIST裡面即可。
	(3)遇到pseudo comment則把相對應的OPT設為1或者0。EX: 遇到//&S+則把Opt_S設為1，//T-則把Opt_T設為0，並且LIST。

4.TOKENCHAR , TOKEN:
	遇到operator(mod, :=等)，Keyword(array等)，直接丟到TOKENCHAR，和TOKEN中處理，就會將切出的token印出，並加到LIST。

5.其他TOKEN:
	(1)科學記號、浮點數、8進位數、10進位數等，經由上述的regular expression(第2點)，即可切出適當的TOKEN。
	(2)Identifier: 由於ID只能是英文字母開頭，後面能有英文和數字混合，因此寫成{letter}({letter}|{digit})*。
	(2)0.0: 由於上述的浮點數要處理redundant 0s，規定小數點只能非0數字結尾，因此多加一個token判斷0.0的字串。
	(3)string: 由'"'開頭，以及由'"'結尾的字串，但是要把中間多餘的'"'過濾掉，因此多開一個陣列來處理並存放正確的字串。
