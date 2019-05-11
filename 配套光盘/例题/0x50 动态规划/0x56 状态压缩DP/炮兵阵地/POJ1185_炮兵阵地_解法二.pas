type
 arr=array[1..10]of longint;
const
 pow:array[0..10]of longint=(1,3,9,27,81,243,729,2187,6561,19683,59049);
var
 a:array[0..100,0..10]of longint;
 v:array[0..1,0..12]of boolean;
 f:array[0..1,0..59049]of longint;
 d:array[0..2]of arr;
 b,next,e:array[1..200000]of longint;
 head:array[0..59049]of longint;
 c:array[0..59049]of arr;
 n,m,i,j,k,ans,t1,t2,tot:longint;
 ch:char;
 bool:boolean;

function cal_3_10(c:arr):longint;
 var
  i:longint;
 begin
  cal_3_10:=0;
  for i:=1 to m do
   inc(cal_3_10,c[i]*pow[m-i]);
 end;

function cal_10_3(k:longint):arr;
 var
  i:longint;
 begin
  fillchar(cal_10_3,sizeof(cal_10_3),0);
  i:=m;
  while k>0 do
   begin
    cal_10_3[i]:=k mod 3;
    k:=k div 3;
    dec(i);
   end;
 end;

procedure add(t1,t2,temp:longint);
 begin
  inc(tot);
  b[tot]:=t2;
  e[tot]:=temp;
  next[tot]:=head[t1];
  head[t1]:=tot;
 end;

procedure dfs(x,y,temp:longint);
 begin
  if (x=1)and(y=m+1) then//两行状态全部填好
   begin
    t1:=cal_3_10(d[0]);
    t2:=cal_3_10(d[1]);
    add(t1,t2,temp);
    exit;
   end;
  if y=m+1 then begin dfs(1,1,temp); exit; end;//到达行末
  if d[x,y]<>-1 then begin dfs(x,y+1,temp); exit; end;//已经填过
  d[x,y]:=0; dfs(x,y+1,temp);//放0
  if x=0 then//能放1
   begin
    d[x,y]:=1; d[1,y]:=0;
    dfs(x,y+1,temp);
    d[1,y]:=-1;
   end;
  if v[x,y] then//能放2
   begin
    d[x,y]:=2;
    if x=0 then d[1,y]:=1;
    v[x,y+1]:=false; v[x,y+2]:=false;
    if x=1 then inc(temp);
    dfs(x,y+1,temp);
    if x=1 then dec(temp);
    if x=0 then d[1,y]:=-1;
    v[x,y+1]:=true; v[x,y+2]:=true;
   end;
  d[x,y]:=-1;
 end;

procedure scanf_prework;
 begin
  readln(n,m);
  fillchar(a,sizeof(a),0);
  fillchar(v,sizeof(v),true);
  fillchar(d,sizeof(d),255);
  dfs(0,1,0);
  for i:=1 to n do
   begin
    for j:=1 to m do
     begin
      read(ch);
      if ch='H' then
       begin
        inc(a[i,0]);
        a[i,a[i,0]]:=j;
       end;
     end;
    readln;
   end;
  for i:=0 to pow[m]-1 do c[i]:=cal_10_3(i);
 end;

function judge(i,j:longint):boolean;
 var
  k:longint;
 begin
  for k:=1 to a[i,0] do
   if c[j,a[i,k]]=2 then exit(false);
  exit(true);
 end;

begin
 scanf_prework;
 fillchar(f,sizeof(f),255);
 f[0,0]:=0;
 for i:=1 to n do
  for j:=0 to pow[m] do
   begin
    if (head[j]=0)or(f[(i-1)and 1,j]=-1) then continue;
    k:=head[j];
    while k<>0 do
     begin
      if (f[(i-1)and 1,j]+e[k]>f[i and 1,b[k]])and judge(i,b[k]) then
       f[i and 1,b[k]]:=f[(i-1)and 1,j]+e[k];
      if (i=n)and(f[i and 1,b[k]]>ans) then ans:=f[i and 1,b[k]];
      k:=next[k];
     end;
   end;
 writeln(ans);
end.