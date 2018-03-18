var
 n,i,j,k,r:longint;
begin
 assign(output,'New.in');
 rewrite(output);
 readln(n,r,k);
 writeln(n,' ',r);
 for i:=1 to n do
  begin
   j:=random(2);
   if j=0 then j:=-1;
   writeln(random(1000)*j,' ',random(r+k));
  end;
 close(output);
end.