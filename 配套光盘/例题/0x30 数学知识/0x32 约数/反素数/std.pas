const
 a:array[1..10]of integer=(2,3,5,7,11,13,17,19,23,29);
var
 n,ans,temp,max:longint;
procedure dfs(i,last,now,num,k:longint);
 begin
  temp:=k*(now+1);
  if (temp>max)or((temp=max)and(num<ans)) then
   begin max:=temp; ans:=num; end;
  if (now<last)and(num<=n div a[i]) then dfs(i,last,now+1,num*a[i],k);
  if (now<>0)and(num<=n div a[i+1]) then dfs(i+1,now,0,num,k*(now+1));
 end;
begin
 read(n);
 dfs(1,100,0,1,1);
 writeln(ans);
end.