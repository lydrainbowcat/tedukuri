var
 d:array[0..1000,0..1000]of longint;
 s,t:array[0..1000]of longint;
 kase,n,m,i,j,k,x,y,w,h,p,ans:longint;
 ch:char;
function min(x,y,z:longint):longint;
 begin
  if x<y then y:=x;
  if y<z then z:=y;
  exit(z);
 end;
begin
   read(n,m);
   fillchar(d,sizeof(d),0);
   for i:=1 to n do
    for j:=1 to m do
     begin
      repeat read(ch); until(ch='F')or(ch='R');
      if ch='R' then continue;
      d[i,j]:=d[i-1,j]+1;
     end;
   ans:=0;
   for i:=1 to n do
    begin
     s[0]:=-1; p:=0;
     for j:=1 to m do
      begin
       w:=0; h:=d[i,j];
       while s[p]>h do
        begin
         inc(w,t[p]);
         if w*s[p]>ans then ans:=w*s[p];
         dec(p);
        end;
       inc(p);
       s[p]:=h;
       t[p]:=w+1;
      end;
     w:=0;
     while p>0 do
      begin
       inc(w,t[p]);
       if w*s[p]>ans then ans:=w*s[p];
       dec(p);
      end;
    end;
   writeln(3*ans);
end.