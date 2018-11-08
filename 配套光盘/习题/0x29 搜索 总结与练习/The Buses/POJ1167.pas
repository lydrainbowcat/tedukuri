var
 a:array[0..300]of integer;
 b:array[0..60]of integer;
 f:array[0..60]of record color,first:longint; end;
 n,ans,i,j,ID,max:longint;
 flag:boolean;

procedure IDdfs(dep,m:integer);
 var
  i,j,s,e,now,d:longint;
 begin
  if dep>n then
   begin
    for i:=1 to m do//color为1代表是某条线路的第一辆车
     if f[i].color=1 then exit;
    ans:=m;
    flag:=true;
    exit;
   end;
  now:=a[dep];
  if b[now]<=0 then IDdfs(dep+1,m);
  for i:=1 to m do with f[i] do//不当做一条线路的头一辆车
   if color=1 then
    begin
     d:=now-first;//公差
     if d<=first then continue;//注意挖掘深层的隐晦条件，如果d<=first则first-d一定会在输入数据中出现，而我们是把first当做第一辆车处理的，与其矛盾。
     color:=2;
     s:=now;
     while (s<=max)and(b[s]>0) do
      begin
       dec(b[s]);
       inc(s,d);
      end;
    if s>max then IDdfs(dep+1,m);{这里我不得不说理解题意很重要。题目说某一条线路若确定了初始时间和时间间隔，
    则会在整个一小时内均按此规律进站，故线路若中间断开不能延续到12:59之后，就不能算一条线路！}
     if flag then exit;
     color:=1;
     e:=s-d;
     s:=now;
     while s<=e do
      begin
       inc(b[s]);
       inc(s,d);
      end;
    end;
  if (now*2>=59)or(m>=ID) then exit;//每条线路最少两辆车，故now若作为第一辆不会在后一半
  inc(m);
  dec(b[now]);
  with f[m] do
   begin
    color:=1;
    first:=now;
   end;
  IDdfs(dep+1,m);
  if flag then exit;
  inc(b[now]);
 end;

procedure scanf;
 begin
  readln(n);
  for i:=1 to n do
   begin
    read(j);
    if max<j then max:=j;
    inc(b[j]);
    a[i]:=j;
   end;
 end;

begin
 scanf;
 for ID:=1 to 17 do//这题告诉线路<17明摆着让你迭代……
  begin
   IDdfs(1,0);
   if flag then break;
  end;
 writeln(ans);
end.
