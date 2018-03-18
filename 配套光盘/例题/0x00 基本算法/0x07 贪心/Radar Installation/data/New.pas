var
 a,b:array[0..1000]of double;
 t,n,d,i,ans,x,y:longint;
 z,r:double;
 bool:boolean;
procedure qsort(l,r:longint);
 var
  i,j:longint;
  x,y,z:double;
 begin
  i:=l; j:=r;
  x:=a[(l+r)>>1];
  y:=b[(l+r)>>1];
  repeat
   while a[i]<x do inc(i);
   while a[j]>x do dec(j);
   if i<=j then
    begin
     z:=a[i]; a[i]:=a[j]; a[j]:=z;
     z:=b[i]; b[i]:=b[j]; b[j]:=z;
     inc(i); dec(j);
    end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
 end;
begin
 assign(input,'New.in');
 assign(output,'New.out');
 reset(input);
 rewrite(output);
 readln(n,d);
 for i:=1 to n do
  begin
   readln(x,y);
   if y>d then ans:=-1
   else begin
    z:=sqrt(sqr(d)-sqr(y));
    a[i]:=x-z;
    b[i]:=x+z;
   end;
  end;
 if ans=0 then
  begin
   qsort(1,n);
   i:=1; bool:=false;
   while i<=n do
    begin   
     if not bool then begin inc(ans); r:=b[i]; end;
     inc(i);
     if i>n then break;
     if a[i]<=r then
      begin
       if b[i]<r then r:=b[i];
       bool:=true;
      end
     else bool:=false;
    end;
  end;
 writeln(ans);
 close(input);
 close(output);
end.
