program Cradle;

{ Boilerplate Code }
{ ------------------------------- }
{ Constant Declarations }
const TAB = ^I;

{ Variable Declarations }
var Look: char;         { lookahead character }

procedure GetChar;
begin
    Read(Look);
end;

procedure Error(s: string);
begin
    WriteLn;
    WriteLn(^G, 'Error: ', s, '.');
end;

procedure Abort(s: string);
begin
    Error(s);
    Halt;
end;

procedure Expected(s: string);
begin
    Abort(s + ' expected');
end;

procedure Match(x: char);
begin
    if Look = x then GetChar
    else Expected('''' + x + '''');
end;

function IsAlpha(c: char): boolean;
begin
    IsAlpha := upcase(c) in ['A'..'Z'];
end;

function IsDigit(c: char): boolean;
begin
    IsDigit := c in ['0'..'9'];
end;

function GetName: char;
begin
    if not IsAlpha(Look) then Expected('Name');
    GetName := upcase(Look); { Should be `UpCase'? }
    GetChar; { Read the next char into lookahead variable }
end;

function GetNum: char;
begin
    if not IsDigit(Look) then Expected('Integer');
    GetNum := Look;
    GetChar; { Read the next char into lookahead variable }
end;

procedure Emit(s: string);
begin
    Write(TAB, s);
end;

procedure EmitLn(s: string);
begin
    Emit(s);
    WriteLn;
end;

procedure Init;
begin
    GetChar;
end;

{ Parser }
{ ------------------------------- }
{ Definition of an expression: }
{ <expression> ::= <term> [<addop> <term>]* }
procedure Term;
begin
    EmitLn('MOVE #' + GetNum + ', D0');
end;

procedure Add;
begin
    Match('+');
    Term;
    EmitLn('ADD D1, D0');
end;

procedure Subtract;
begin
    Match('-');
    Term;
    EmitLn('SUB D1, D0');
    EmitLn('NEG D0');           { Otherwise, the order of operations is wrong }
end;

procedure Expression;
begin
    Term;
    while Look in ['+', '-'] do begin
        EmitLn('MOVE D0, D1');
        case Look of
            '+': Add;
            '-': Subtract;
            else Expected('Addop');
        end;
    end;
end;

{ ------------------------------- }
{ Main Program }
begin
    Init;
    Expression;
end.
