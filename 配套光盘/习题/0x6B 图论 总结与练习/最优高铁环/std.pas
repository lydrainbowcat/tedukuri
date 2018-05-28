var
 hash:array['A'..'Z',0..1000]of longint;
 head,c,ver,edge,next:array[0..200000]of longint;
 now,d:array[0..200000]of double;
 q:array[0..4000000]of longint;
 v:array[0..200000]of boolean;
 rate:array['A'..'Z']of longint;
 tot,num,n,x,y,i,j,p,k,num1,num2:longint;
 l,r,mid:double;
 t1,t2:char;

procedure getchar(var t1:char; var num1:longint);
 var
  s:string;
  ch:char;
 begin
  s:='';
  read(t1);
  repeat
   read(ch);
   if ch='-' then break;
   s:=s+ch;
   if eoln then break;
  until false;
  val(s,num1);
  inc(k,rate[t1]);
 end;

function find(x:char; y:longint):longint;
 begin
  if hash[x,y]<>0 then exit(hash[x,y]);
  inc(num); hash[x,y]:=num;
  exit(num);
 end;

procedure add(x,y,z:longint);
 begin
  inc(tot);
  ver[tot]:=y;
  edge[tot]:=z;
  next[tot]:=head[x];
  head[x]:=tot;
 end;

function spfa:boolean;
 var
  i,l,r,x:longint;
 begin
  for i:=1 to num do d[i]:=-100000000;
  fillchar(v,sizeof(v),0);
  fillchar(c,sizeof(c),0);
  l:=2000000; r:=2000000; q[l]:=0;
  d[0]:=0; v[0]:=true; c[0]:=1;
  while l<=r do
   begin
    x:=q[l]; v[x]:=false; inc(l);
    i:=head[x];
    while i<>0 do
     begin
      if d[ver[i]]<d[x]+now[i] then
       begin
        d[ver[i]]:=d[x]+now[i];
        c[ver[i]]:=c[x]+1;
        if c[ver[i]]>num+1 then exit(false);
        if not v[ver[i]] then
         begin
          v[ver[i]]:=true;
          if d[ver[i]]>=d[q[l]] then
           begin dec(l); q[l]:=ver[i]; end
          else begin inc(r); q[r]:=ver[i]; end;
         end;
       end;
      i:=next[i];
     end;
   end;
  exit(true);
 end;

begin
 rate['S']:=1000; rate['G']:=500; rate['D']:=300; rate['T']:=200; rate['K']:=150;
 readln(n);
 for i:=1 to n do
  begin
   k:=0;
   getchar(t1,num1);
   while not eoln do getchar(t2,num2);
   readln;
   x:=find(t1,num1);
   y:=find(t2,num2);
   add(x,y,k);
   if k>r then r:=k;
  end;
 for i:=1 to num do add(0,i,0);
 while r-l>0.01 do
  begin
   mid:=(l+r)/2;
   for i:=1 to tot do now[i]:=edge[i]-mid;
   if spfa then r:=mid else l:=mid+0.01;
  end;
 if r<0.01 then writeln('-1') else writeln(round(r));
end.