type
 rec=record a,b,c:longint; dat:integer; end;
var
 head,next:array[0..1000000]of longint;
 vera,verb,verc:array[0..1000000]of integer;
 f:array[0..1000000]of rec;
 n,m,p,tot,a,b,dat:longint;

function hash(a,b,c:longint):longint;
 var
  i,temp:longint;
 begin
  temp:=a*b mod 999983;
  i:=head[temp];
  while i<>0 do
   begin
    if (vera[i]=a)and(verb[i]=b) then
     if verc[i]<=c then exit(i) else exit(-i);
    i:=next[i];
   end;
  exit(0);
 end;

function gcd(a,b:longint):longint;
 begin
  if b=0 then exit(a) else exit(gcd(b,a mod b));
 end;

procedure swap(var a,b:rec);
 var
  c:rec;
 begin
  c:=a; a:=b; b:=c;
 end;

procedure heapup(p:longint);
 begin
  while p>1 do
   if f[p].c<f[p>>1].c then
    begin
     swap(f[p],f[p>>1]);
     p:=p>>1;
    end
   else break;
 end;

procedure heapdown(l,r:longint);
 var
  t:longint;
 begin
  t:=l<<1;
  while t<=r do
   begin
    if (t<r)and(f[t].c>f[t+1].c) then inc(t);
    if f[l].c>f[t].c then
     begin
      swap(f[l],f[t]);
      l:=t; t:=l<<1;
     end
    else break;
   end;
 end;

procedure insert(a,b,dat:longint);
 var
  i,c,temp,k:longint;
 begin
  if a>b then begin i:=a; a:=b; b:=i; end;
  c:=dat; i:=b;
  while i<n do
   begin inc(c); i:=i<<1; end;
  k:=hash(a,b,c);
  if (a>m)or(b>m)or(n mod gcd(a,b)<>0)or(k>0) then exit;
  inc(p);
  f[p].a:=a; f[p].b:=b; f[p].dat:=dat; f[p].c:=c;
  heapup(p);
  if k=0 then
   begin
    temp:=a*b mod 999983;
    inc(tot);
    vera[tot]:=a;
    verb[tot]:=b;
    verc[tot]:=c;
    next[tot]:=head[temp];
    head[temp]:=tot;
   end
  else verc[abs(k)]:=c;
 end;

begin
 read(n);
 m:=n*2;
 if m>32767 then m:=32767;
 p:=1;
 f[1].a:=1; f[1].b:=0;
 hash(1,0,0);
 while p>0 do{A*}
  begin
   a:=f[1].a; b:=f[1].b; dat:=f[1].dat;
   if (a=n)or(b=n) then
    begin writeln(dat); halt; end;
   swap(f[1],f[p]);
   dec(p);
   heapdown(1,p);
   insert(a*2,b,dat+1);
   insert(a,b*2,dat+1);
   if a-b>0 then begin insert(a-b,b,dat+1); insert(a-b,a,dat+1); end;
   if b-a>0 then begin insert(a,b-a,dat+1); insert(b,b-a,dat+1); end;
   if a<>0 then insert(a,a*2,dat+1);
   if b<>0 then insert(b*2,b,dat+1);
   insert(a+b,b,dat+1);
   insert(a,a+b,dat+1);
  end;
end.