{$O-,Q+,R+}
uses SysUtils;

label cont;

const MaxN = 100;

var x, y : array [1..MaxN * 2] of integer;
    valid : boolean;
    N, C, i, j, k : integer;


begin
  N := strtoint (paramstr (1));
  C := strtoint (paramstr (2));
  randseed := strtoint (paramstr (3));
  if randseed = 0 then randomize;
  if C = 0 then C := random (501) + 500;
  if N = 0 then N := random (10) + (MaxN - 9);
  writeln (N);
  for i := 1 to N + N do begin
    repeat
      valid := true;
      x[i] := random (2 * C + 1) - C;
      y[i] := random (2 * C + 1) - C;
      //writeln ('--> ', x[i], ' ', y[i]);
      for j := 1 to i - 1 do
        for k := j + 1 to i - 1 do
          if (x[i] - x[k]) * (y[k] - y[j]) - (x[k] - x[j]) * (y[i] - y[k]) = 0 then
            valid := false;
    until valid;
    writeln (x[i], ' ', y[i]);
  end;
end.