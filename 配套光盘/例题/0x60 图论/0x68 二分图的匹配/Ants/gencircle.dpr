{$O-,Q+,R+}
uses SysUtils;

label cont;

const MaxN = 100;

var x, y : array [1..MaxN * 2] of integer;
    valid : boolean;
    N, C, i, j, k : integer;
    a : extended;


begin
  writeln (MaxN);
  randseed := 123454321;
  for i := 1 to MaxN + MaxN do begin
    repeat
      valid := true;
      a := random * 2 * PI;
      x[i] := round (10000 * cos (a));
      y[i] := round (10000 * sin (a));
      //writeln ('--> ', x[i], ' ', y[i]);
      for j := 1 to i - 1 do
        for k := j + 1 to i - 1 do
          if (x[i] - x[k]) * (y[k] - y[j]) - (x[k] - x[j]) * (y[i] - y[k]) = 0 then
            valid := false;
    until valid;
    writeln (x[i], ' ', y[i]);
  end;
end.