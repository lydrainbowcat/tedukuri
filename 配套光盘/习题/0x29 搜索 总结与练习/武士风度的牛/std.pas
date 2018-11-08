type
 xoy=record x,y,step:longint; end;
const
 dx:array[1..8]of integer=(-2,-2,-1,-1,1,1,2,2);
 dy:array[1..8]of integer=(-1,1,-2,2,-2,2,-1,1);
var
 a:array[-1..200,-1..200]of char;
 v:array[-1..200,-1..200]of boolean;
 q:array[0..30000]of xoy;
 now:xoy;
 n,m,i,j,sx,sy,l,r:longint;
function bfs:longint;
 begin
  l:=1; r:=1;
  while l<=r do
   begin
    for i:=1 to 8 do
     if not v[q[l].x+dx[i],q[l].y+dy[i]] then
      begin
       if a[q[l].x+dx[i],q[l].y+dy[i]]='H' then exit(q[l].step+1);
       inc(r);
       q[r].x:=q[l].x+dx[i];
       q[r].y:=q[l].y+dy[i];
       q[r].step:=q[l].step+1;
       v[q[r].x,q[r].y]:=true;
      end;
    inc(l);
   end;
 end;
begin
 readln(m,n);
 for i:=-1 to n+2 do
  begin
   v[i,-1]:=true; v[i,0]:=true;
   v[i,m+1]:=true; v[i,m+2]:=true;
  end;
 for i:=-1 to m+2 do
  begin
   v[-1,i]:=true; v[0,i]:=true;
   v[n+1,i]:=true; v[n+2,i]:=true;
  end;
 for i:=1 to n do
  begin
   for j:=1 to m do
    begin
     read(a[i,j]);
     if a[i,j]='K' then
      begin
       q[1].x:=i;
       q[1].y:=j;
       v[i,j]:=true;
      end;
     if a[i,j]='*' then v[i,j]:=true;
    end;
   readln;
  end;
 writeln(bfs);
end.

