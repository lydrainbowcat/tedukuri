var
 max,n,m,i,j,k,x,y:longint;
 a,d:array[1..100,1..100]of longint;
begin
  assign(input,'toy.in');
  assign(output,'toy.out');
  reset(input);
  rewrite(output);
 readln(n,m);
 for i:=1 to m do begin readln(x,y); a[x,y]:=1; a[y,x]:=1; d[x,y]:=1; d[y,x]:=1; end;
 for k:=1 to n do
  for i:=1 to n do
   if d[i,k]>0 then
   for j:=1 to n do
    if d[k,j]>0 then
     begin
      if (i<>j)and(a[i,j]=1) then d[i,j]:=a[i,j]
       else if (i<>j)and((d[i,j]>d[i,k]+d[k,j])or(d[i,j]=0)) then d[i,j]:=d[i,k]+d[k,j];
     end;
 for i:=1 to n-1 do
  for j:=i+1 to n do
   if d[i,j]>max then max:=d[i,j];
 writeln(max);
 close(input);
  close(output);
end.
