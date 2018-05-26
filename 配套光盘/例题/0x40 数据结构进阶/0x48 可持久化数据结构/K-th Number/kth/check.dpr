{-----------------------------------------------------------}
{ ACM ICPC 2004-2005, NEERC, Northern Subregional Contest   }
{ St Petersburg, October 30, 2004                           }
{-----------------------------------------------------------}
{ Problem K. K-th Number                                    }
{                                                           }
{ Original idea:    Andrew Stankevich                       }
{ Text:             Andrew Stankevich                       }
{-----------------------------------------------------------}
{ Checker program                                           }
{                                                           }
{ Author:           Andrew Stankevich                       }
{-----------------------------------------------------------}

uses
  testlib, sysutils;

function ending(x: longint): string;
begin
  x := x mod 100;
  if x div 10 = 1 then
    ending := 'th'
  else
    case x mod 10 of
      1: ending := 'st';
      2: ending := 'nd';
      3: ending := 'rd';
      else
        ending := 'th';
    end;
end;

var
  j, p, n: longint;

begin
  n := 0;
  while not ans.seekeof do
  begin
    inc(n);
    j := ans.readlongint;
    p := ouf.readlongint;

    if j <> p then
      quit(_wa, inttostr(n) + ending(n) + ' numbers differ - expected: "' + inttostr(j) + 
        '", found: "' + inttostr(p) + '"');
  end;
  quit(_ok, inttostr(n) + ' numbers');
end.
