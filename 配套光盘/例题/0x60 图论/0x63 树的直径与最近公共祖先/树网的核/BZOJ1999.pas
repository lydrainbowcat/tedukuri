{$M 100000000}
var
 ver,edge,next:array[0..1000000]of longint;
 head,d,f,q,a,fa:array[0..500000]of longint;
 v:array[0..500000]of boolean;
 n,s,m,tot,i,j,l,r,x,y,z,temp,ans:longint;

function min(x,y:longint):longint;
 begin
  if x<y then exit(x) else exit(y);
 end;
function max(x,y:longint):longint;
 begin
  if x>y then exit(x) else exit(y);
 end;

procedure add(x,y,z:longint);
 begin
  inc(tot);
  ver[tot]:=y;
  edge[tot]:=z;
  next[tot]:=head[x];
  head[x]:=tot;
 end;

procedure dfs(x:longint);
 var
  i:longint;
 begin
  i:=head[x];
  while i<>0 do
   begin
    if fa[x]<>ver[i] then
     begin
      fa[ver[i]]:=x;
      d[ver[i]]:=d[x]+edge[i];
      dfs(ver[i]);
     end;
    i:=next[i];
   end;
 end;

procedure diameter;
 begin
  dfs(1);
  x:=1;
  for i:=2 to n do
   if d[i]>d[x] then x:=i;
  d[x]:=0;
  fillchar(fa,sizeof(fa),0);
  dfs(x);
  y:=1;
  for i:=2 to n do
   if d[i]>d[y] then y:=i;
  while y<>x do
   begin
    v[y]:=true;
    inc(m); a[m]:=y;
    y:=fa[y];
   end;
  v[x]:=true;
  inc(m); a[m]:=x;
 end;

procedure treedp(x:longint);
 var
  i:longint;
 begin
  v[x]:=true;
  i:=head[x];
  while i<>0 do
   begin
    if not v[ver[i]] then
     begin
      treedp(ver[i]);
      f[x]:=max(f[x],f[ver[i]]+edge[i]);
     end;
    i:=next[i];
   end;
 end;

begin
 read(n,s);
 for i:=1 to n-1 do
  begin
   read(x,y,z);
   add(x,y,z);
   add(y,x,z);
  end;
 diameter;
 for i:=1 to m do treedp(a[i]);
 j:=m;
 ans:=maxlongint;
 temp:=0;
 for i:=1 to m do temp:=max(temp,f[a[i]]);
 for i:=m downto 1 do
  begin
   while (j>=1)and(d[a[j]]-d[a[i]]<=s) do dec(j);
   ans:=min(ans,max(temp,max(d[a[i]],d[a[1]]-d[a[j+1]])));
  end;
 writeln(ans);
end.