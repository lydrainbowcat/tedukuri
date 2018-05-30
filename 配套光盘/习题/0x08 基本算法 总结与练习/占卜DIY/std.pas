var
 i,j,now,ans:integer;
 a:array[1..13,1..5]of integer;
 open:array[1..12]of integer;
 ch:char;
procedure readin;
 begin
 for i:=1 to 13 do
  begin
   j:=0;
   while j<4 do
    begin
     read(ch);
     if ch=' ' then continue;
     inc(j);
     if ch='A' then a[i,j]:=1
     else if ch='0' then a[i,j]:=10
     else if ch='J' then a[i,j]:=11
     else if ch='Q' then a[i,j]:=12
     else if ch='K' then a[i,j]:=13
     else a[i,j]:=ord(ch)-ord('0');
    end;{while}
   readln;
  end;{for i}
 end;
begin
 readin;
 for i:=1 to 4 do
  begin
   now:=a[13,i];
   while now<>13 do
    begin
     inc(open[now]);
     for j:=5 downto 2 do a[now,j]:=a[now,j-1];
     a[now,1]:=now;
     now:=a[now,5];
    end;{while}
  end;{for i}
 for i:=1 to 12 do if open[i]=4 then inc(ans);
 writeln(ans);
end.