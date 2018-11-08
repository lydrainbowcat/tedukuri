type
 atp=record x,y:longint; end;
const
 dx:array[1..8]of integer=(-1,-1,-1,0,0,1,1,1);
 dy:array[1..8]of integer=(-1,0,1,-1,1,-1,0,1);
var
 a:array[0..101,0..101]of char;
 i,j,eat,x,y,mx,my,ans:longint;
 q:array[0..10000]of atp;
 t:array[0..10000]of longint;
 l,r:longint;
procedure bfs;
 var
  now:atp; i:longint;
 begin
  fillchar(q,sizeof(q),0);
  l:=1; r:=1; q[l].x:=mx; q[l].y:=my; t[l]:=0;
  while l<=r do
   begin
    now.x:=q[l].x; now.y:=q[l].y;
    for i:=1 to 8 do
     if a[now.x+dx[i],now.y+dy[i]]='.' then
      begin
       a[now.x+dx[i],now.y+dy[i]]:='M';
       inc(r);
       q[r].x:=now.x+dx[i];
       q[r].y:=now.y+dy[i];
       t[r]:=t[l]+1;
       if t[r]>ans then ans:=t[r];
      end;
    inc(l);
   end;
 end;
begin
 readln(x,y,mx,my);
 {redo}for i:=0 to y+1 do begin a[i,0]:='*'; a[i,x+1]:='*'; end;
 {redo}for i:=0 to x+1 do begin a[0,i]:='*'; a[y+1,i]:='*'; end;
 {read}for i:=y downto 1 do begin for j:=1 to x do read(a[j,i]); readln; end;
 a[mx,my]:='M';
 bfs;
 writeln(ans);
end.
