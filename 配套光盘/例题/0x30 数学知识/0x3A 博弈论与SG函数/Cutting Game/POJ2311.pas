var
 f:array[0..200,0..200]of longint;
 v:array[0..400]of boolean;
 n,m:longint;
function SG(x,y:longint):longint;
 var
  i,temp:longint;
 begin
  if f[x,y]<>-1 then exit(f[x,y]);
  for i:=2 to y-2 do
   begin SG(x,i); SG(x,y-i); end;
  for i:=2 to x-2 do
   begin SG(i,y); SG(x-i,y); end;
  fillchar(v,sizeof(v),0);
  for i:=2 to y-2 do
   v[f[x,i] xor f[x,y-i]]:=true;
  for i:=2 to x-2 do
   v[f[i,y] xor f[x-i,y]]:=true;
  i:=0;
  while v[i] do inc(i);
  f[x,y]:=i;
  f[y,x]:=i;
  exit(i);
 end;

begin
 fillchar(f,sizeof(f),255);
 f[2,3]:=0; f[3,2]:=0; f[3,3]:=0;
 repeat
  read(n,m);
  if SG(n,m)<>0 then writeln('WIN') else writeln('LOSE');
 until seekeof;
end.