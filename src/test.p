//&T-
//&D-
BinaryOperator;

scientific(): real;
begin
    return 1.3e+123;
end
end scientific

begin
    var vDecimal: integer;
    var vBoolArr: array 1 to 2 of boolean;
    print vBoolArr[3] or vBoolArr[2];
    print vDecimal > scientific();

end
end BinaryOperator
