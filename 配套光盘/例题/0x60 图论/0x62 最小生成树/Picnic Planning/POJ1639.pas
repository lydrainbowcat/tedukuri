var
 a,b:array[0..30,0..30]of longint;
 d,pre:array[0..30]of longint;
 v:array[0..30]of boolean;
 str:array[0..30]of string;
 n,m,tot,ans,i,j,k,min,max,ver,du,t,maxj:longint;

procedure scanf;
 var
  s:string;
  ch:char;
  x,y,z,i:longint;
 function cal(s:string):longint;
  var
   i:longint;
  begin
   for i:=1 to n do
    if str[i]=s then exit(i);
   inc(n); str[n]:=s;
   cal:=n;
  end;//cal
 begin
  n:=1; str[1]:='Park';
  readln(m);
  for i:=1 to m do
   begin
    read(ch);
    s:='';
    while ch<>' ' do
     begin s:=s+ch; read(ch); end;
    x:=cal(s);
    s:='';
    repeat read(ch); until ch<>' ';
    while ch<>' ' do
     begin s:=s+ch; read(ch); end;
    y:=cal(s);
    readln(z);
    if (a[x,y]=0)or(a[x,y]>z) then a[x,y]:=z;
    a[y,x]:=a[x,y];
   end;
  readln(du);
 end;//scanf

procedure color(x:longint);
 var
  i:longint;
 begin
  v[x]:=true;
  inc(b[tot,0]); b[tot,b[tot,0]]:=x;
  for i:=2 to n do
   if not v[i] and(a[x,i]<>0) then
    color(i);
 end;

procedure prim(k:longint);
 var
  i,j,min,next:longint;
 begin
  for i:=1 to b[k,0] do
   begin
    min:=maxlongint shr 1;
    for j:=1 to b[k,0] do
     if not v[b[k,j]] and(d[b[k,j]]<min) then
      begin min:=d[b[k,j]]; next:=b[k,j]; end;
    v[next]:=true;
    for j:=1 to b[k,0] do
     if not v[b[k,j]] and(a[next,b[k,j]]<>0)and(d[b[k,j]]>a[next,b[k,j]]) then
      begin
       d[b[k,j]]:=a[next,b[k,j]];
       pre[b[k,j]]:=next;
      end;
   end;
 end;

begin
 scanf;
 for i:=2 to n do
  if not v[i] then
   begin inc(tot); color(i); end;
 fillchar(v,sizeof(v),0);
 fillchar(d,sizeof(d),127);
 d[1]:=0;
 for i:=1 to tot do
  begin
   min:=maxlongint;
   for j:=1 to b[i,0] do
    if (a[1,b[i,j]]<>0)and(a[1,b[i,j]]<min) then
     begin min:=a[1,b[i,j]]; k:=b[i,j]; end;
   d[k]:=min; pre[k]:=1; inc(t);
   prim(i);
  end;
 for i:=1 to du-t do
  begin
   max:=0;
   for j:=2 to n do
    begin
     if a[j,1]=0 then continue;
     k:=j;
     while k<>1 do
      begin
       if d[k]-a[j,1]>max then begin max:=d[k]-a[j,1]; ver:=k; maxj:=j; end;
       k:=pre[k];
      end;
    end;
   if max=0 then break;
   d[ver]:=a[maxj,1];
   pre[ver]:=1;
  end;
 for i:=1 to n do inc(ans,d[i]);
 writeln('Total miles driven: ',ans);
end.
