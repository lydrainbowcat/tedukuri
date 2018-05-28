// Author: CDQ (Danqi Chen) 
program sightsee;

    const
      finp  =  'sightsee.in';
      fout  =  'sightsee.out';
      maxn  =  1000 + 5;
      eps   =  1e-4;

    type
       nodeptr  =  ^node;
          node   =  record
             p, len  :   longint;
             next    :   nodeptr;
          end;

    var
       hash        :   array [1 .. maxn] of boolean;
       queue, edge :   array [1 .. maxn] of longint;
       dist        :   array [1 .. maxn] of extended;
       a           :   array [1 .. maxn] of nodeptr;
       cost        :   array [1 .. maxn] of longint;
       n, m        :   longint;    

    procedure create(x, y, c  :  longint);
      var
         tmp      :   nodeptr;
      begin
         new(tmp); tmp ^.p := y; tmp ^. len := c;
         tmp ^.next := a[x]; a[x] := tmp;
      end;

    procedure init;
      var
         i        :   longint;
         x, y, c  :   longint;
      begin
         read(n, m);
         for i := 1 to n do read(cost[i]);
         for i := 1 to n do a[i] := nil;
         for i := 1 to m do 
           begin
             read(x, y, c);
             create(x, y, c);
           end;
      end;
 
    function nxt(i  :  longint):  longint;
      begin
         if i = maxn then nxt := 1 else nxt := i + 1;
      end;

    function check(limit  :  extended):  boolean;
      var
         h, t, i :   longint;
         tmp     :   nodeptr;
         v       :   extended;
      begin
         check := true;
         fillchar(hash, sizeof(hash), false);
         h := 0; t := 0;
         for i := 1 to n do 
           begin
             inc(t); queue[t] := i; hash[i] := true;
             dist[i] := 0; edge[i] := 0;
           end;
         while (h <> t) do
           begin
             h := nxt(h);
             tmp := a[queue[h]];
             while (tmp <> nil) do
               begin
                 v := tmp ^. len * limit - cost[tmp^.p];
                 if (dist[queue[h]] + v < dist[tmp^.p]) then
                   begin
                     dist[tmp^.p] := dist[queue[h]] + v;
                     edge[tmp^.p] := edge[queue[h]] + 1;
                     if edge[tmp ^. p] > n then exit; 
                     if not hash[tmp^.p] then
                       begin
                         t := nxt(t);
                         queue[t] := tmp^. p;
                         hash[tmp ^.p] := true;
                       end;
                   end;
                 tmp := tmp ^. next;
               end;
              hash[queue[h]] := false;
           end;
         check := false;
      end;

    procedure work;
      var
         l, r, mid  :  extended;
      begin
         l := 0; r := 1000;
         while (r - l > eps) do
           begin
             mid := (l + r) / 2;
             if check(mid) then l := mid else r := mid;
           end;
         writeln(l : 0 : 2);
      end;

    begin
       assign(input, finp); reset(input);
       assign(output, fout); rewrite(output);
         init;
         work;
       close(input); close(output);
    end.