var
 n,m,i,x,y,r:longint;
 fa:array[1..1000]of longint;
function find(x:longint):longint;
 begin
  if x=fa[x] then exit(x);
  fa[x]:=find(fa[x]);
  exit(fa[x]);
 end;
begin
 assign(output,'Color.in');
 rewrite(output);
 randomize;
 readln(n);
 r:=random(n)+1; 
 writeln(n,' ',r);
 for i:=1 to n do write(random(100)+1,' '); writeln;
 for i:=1 to n do fa[i]:=i;
 for i:=1 to n-1 do
  begin
   repeat
    x:=find(random(n)+1);
    y:=find(random(n)+1);
   until (x<>y)and(y<>r);
   fa[y]:=x;
   writeln(x,' ',y);
  end;
 close(output);
end.
