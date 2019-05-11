var
 f,d:array[0..100,0..100]of longint;
 s,t:string[100];
 n,i,j,k,len,fold:longint;
function cal(x:longint):longint;
 begin
  if x<10 then exit(1);
  if x<100 then exit(2);
  exit(3);
 end;
procedure print(l,r:longint);
 var
  i,k:longint;
 begin
  k:=d[l,r];
  if k=0 then 
   for i:=l to r do write(s[i])
  else if k>0 then
   begin
    print(l,k);
    print(k+1,r);
   end
  else begin
   k:=abs(k);
   write((r-l+1)div(k-l+1),'(');
   print(l,k);
   write(')');
  end;
 end;
begin
 readln(s);
 n:=length(s);
 for i:=1 to n do
  for j:=i to n do
   f[i,j]:=j-i+1;
 for len:=1 to n do
  for i:=1 to n-len+1 do
   begin
    j:=i+len-1;
    t:=copy(s,i,len);
    for k:=i to j-1 do
     if f[i,j]>f[i,k]+f[k+1,j] then
      begin
       f[i,j]:=f[i,k]+f[k+1,j];
       d[i,j]:=k;
      end;
    k:=j+1; fold:=0;
    while k<=n-len+1 do
     if t=copy(s,k,len) then
      begin
       inc(fold);
       inc(k,len);
       if f[i,k-1]>f[i,j]+cal(fold)+2 then
        begin
         f[i,k-1]:=f[i,j]+cal(fold)+2;
         d[i,k-1]:=-j;
        end;
      end
     else break;
   end;
 print(1,n);
 writeln; 
end.