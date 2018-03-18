type
 link=^node;
 node=record ver:longint; next:link; end;
var
 dfn,low,b,c,s,ind,outd:array[0..200000]of longint;
 head:array[0..200000]of link;
 v,ins:array[0..200000]of boolean;
 n,m,t,i,j,k,x,y,num,ans:longint;
 p:link;

function min(x,y:longint):longint;
 begin
  if x<y then exit(x) else exit(y);
 end;

procedure add(x,y:longint);
 var
  p:link;
 begin
  new(p);
  p^.ver:=y;
  p^.next:=head[x];
  head[x]:=p;
 end;

procedure tarjan(x:longint);
 var
  i,y:longint;
  p:link;
 begin
  v[x]:=true;
  inc(num); dfn[x]:=num; low[x]:=num;
  inc(k); s[k]:=x; ins[x]:=true;
  p:=head[x];
  while p<>nil do
   begin
    if not v[p^.ver] then
     begin
      tarjan(p^.ver);
      low[x]:=min(low[x],low[p^.ver]);
     end
    else if ins[p^.ver] then
     low[x]:=min(low[x],dfn[p^.ver]);
    p:=p^.next;
   end;
  if dfn[x]=low[x] then
   begin
    inc(t);
    repeat
     y:=s[k];
     ins[y]:=false;
     dec(k);
     c[y]:=t;
     inc(b[t]);
    until x=y;
   end;
 end;

begin
 read(n,m);
 for i:=1 to m do
  begin
   read(x,y);
   add(x,y);
  end;
 for i:=1 to n do
  if not v[i] then tarjan(i);
 fillchar(v,sizeof(v),1);
 for i:=1 to n do
  begin
   p:=head[i];
   while p<>nil do
    begin
     if c[p^.ver]<>c[i] then
      begin inc(ind[c[p^.ver]]); inc(outd[c[i]]); end;
     p:=p^.next;
    end;
  end;
 for i:=1 to t do
  if ind[i]=0 then inc(ans);
 for i:=1 to n do
  if (ind[c[i]]=0)and(b[c[i]]=1) then
   begin
    p:=head[i];
    while p<>nil do
     begin
      if ind[c[p^.ver]]=1 then break;
      p:=p^.next;
     end;
    if p=nil then begin dec(ans); break; end;
   end;
 writeln((n-ans)/n:0:6);
end.