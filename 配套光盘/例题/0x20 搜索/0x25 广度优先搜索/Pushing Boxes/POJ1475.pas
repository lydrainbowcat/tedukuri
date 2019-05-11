const
 dx:array[1..4]of integer=(-1,1,0,0);
 dy:array[1..4]of integer=(0,0,-1,1);
 dir:array[1..4]of char=('n','s','w','e');
var
 a:array[0..21,0..21]of char;
 q:array[0..100000]of record x,y,px,py,last:longint; str:ansistring; end;
 f:array[0..500]of record x,y:longint; str:ansistring; end;
 vb:array[0..21,0..21,1..4]of boolean;
 vp:array[0..21,0..21]of boolean;
 l,r,sx,sy,bx,by,tx,ty,i,j,n,m,t,boxcnt,boxans:longint;
 s,ans,route:ansistring;

procedure scanf;
 begin
  fillchar(a,sizeof(a),0);
  for i:=1 to n do
   begin
    for j:=1 to m do
     begin
      read(a[i,j]);
      if a[i,j]='S' then begin a[i,j]:='.'; sx:=i; sy:=j; end;
      if a[i,j]='B' then begin a[i,j]:='.'; bx:=i; by:=j; end;
      if a[i,j]='T' then begin a[i,j]:='.'; tx:=i; ty:=j; end;
     end;
    readln;
   end;
 end;

procedure print(p:longint); // 递归得到方案，保存在字符串route里
 begin
  if q[p].last<>0 then print(q[p].last);
  route:=route+q[p].str;
  if q[p].str<'a' then inc(boxcnt);
 end;

function bfsman(x,y:integer):boolean;
 var
  ll,rr,i,nx,ny:longint;
 begin
  fillchar(vp,sizeof(vp),0);
  ll:=1; rr:=1;
  f[1].x:=q[l].px; f[1].y:=q[l].py; vp[q[l].px,q[l].py]:=true;
  if (q[l].px=x)and(q[l].py=y) then begin s:=''; exit(true); end;
  while ll<=rr do
   begin
    for i:=1 to 4 do
     begin
      nx:=f[ll].x+dx[i];
      ny:=f[ll].y+dy[i];
      if not vp[nx,ny] and(a[nx,ny]='.')and((nx<>q[l].x)or(ny<>q[l].y)) then
       begin
        vp[nx,ny]:=true;
        inc(rr);
        f[rr].x:=nx;
        f[rr].y:=ny;
        f[rr].str:=f[ll].str+dir[i];
        if (nx=x)and(ny=y) then begin s:=f[rr].str; exit(true); end;
       end;
     end;
    inc(ll);
   end;
  exit(false);
 end;

procedure push(x,y:integer; ch:char; s:ansistring; dire:integer);
 begin
  inc(r);
  vb[x,y,dire]:=true;
  q[r].x:=x; q[r].y:=y;
  q[r].px:=q[l].x; q[r].py:=q[l].y;
  q[r].str:=s+ch;
  q[r].last:=l;
  if (x=tx)and(y=ty) then // 到达终点，得到方案
   begin
    boxcnt:=0;
    route:='';
    print(r);
    if (boxans=0)or((boxcnt=boxans)and(length(route)<length(ans))) then // 与现有的方案的箱子移动次数和总步数比较
     begin
      ans:=route;
      boxans:=boxcnt;
     end;
    dec(r); // 终点状态就不用再扩展了
   end;
 end;

procedure bfsbox;
 begin
  fillchar(vb,sizeof(vb),0);
  ans:=''; boxans:=0;
  l:=1; r:=1;
  q[1].x:=bx; q[1].y:=by;
  q[1].px:=sx; q[1].py:=sy;
  for i:=1 to 4 do vb[bx,by,i]:=true;
  while l<=r do
   begin
    if (a[q[l].x-1,q[l].y]='.')and(a[q[l].x+1,q[l].y]='.') then
     begin
      if not vb[q[l].x-1,q[l].y,1] and bfsman(q[l].x+1,q[l].y) then push(q[l].x-1,q[l].y,'N',s,1);
      if not vb[q[l].x+1,q[l].y,2] and bfsman(q[l].x-1,q[l].y) then push(q[l].x+1,q[l].y,'S',s,2);
     end;
    if (a[q[l].x,q[l].y-1]='.')and(a[q[l].x,q[l].y+1]='.') then
     begin
      if not vb[q[l].x,q[l].y-1,3] and bfsman(q[l].x,q[l].y+1) then push(q[l].x,q[l].y-1,'W',s,3);
      if not vb[q[l].x,q[l].y+1,4] and bfsman(q[l].x,q[l].y-1) then push(q[l].x,q[l].y+1,'E',s,4);
     end;
    inc(l);
   end;
 end;

begin
 repeat
  inc(t);
  readln(n,m);
  if (n=0)and(m=0) then break;
  scanf;
  bfsbox;
  writeln('Maze #',t);
  writeln(ans);
 until false;
end.
