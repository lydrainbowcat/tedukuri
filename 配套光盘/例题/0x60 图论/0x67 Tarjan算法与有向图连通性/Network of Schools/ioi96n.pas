{
Solution for task NET
-------- --- ---- ---
The network of schools can be represented by a directed graph whose vertices
are the schools and (A, B) is an edge in the graph iff school B is in the
distribution list of school A. Let us first reformulate the task using graph
terminology.
We use the notation p->q if there is a (directed) path from p to q in a graph.
A set of vertices D of a graph G is called dominator set of G if for each
vertex q there is a vertex p in D such that p->q.
Subtask A is to find a dominator set of G with minimal number of elements.
A set of vertices CD of G is called codominator set of G if for each vertex p
there is a vertex q in CD such that p->q. A graph G is called strongly
connected, if for all vertices p and q there is a path p->q and a path q->p
in G.
Solution of subtask B is the minimal number of new edges that are necessary
to make G strongly connected.
Let us denote the number of elements of a set S by |S|.
Let D be a minimal dominator set and CD be a minimal codominator set of G.

We shall prove that solution of subtask B is 0 if G is strongly connected,
and Max(|D|, |CD|) otherwise.
The proof follows from the statements S1 and S2.
We can assume without loss of generality that |D|<=|CD|.
S1. If D is a one element set containing p and CD contains the elements
    q1,...,qk then introducing the new edges (q1, p), ... , (qk, p) makes G
    strongly connected.
    Proof: Let u,v be arbitrary vertices of G. Then there is an element qi in
    CD such that u->qi, therefore u->qi->p->v is a path from u to v.
S2. If |D|>1 then there are vertices p in D and q in CD such that introducing
    the new edge (q, p) in G makes D-[p] a new dominator set and CD-[q] a new
    codominator set of G.
    Proof: Since |D|>1 there are different vertices p1 and p2 in D, and there
    are different vertices q1 and q2 in CD such that p1->q1 and p2->q2. Then
    the new edge (p,q) will be (q1,p2). Indeed, any vertex u that was
    reachable from p2 by the path p2->u will be reachable from p1 by
    p1->q1->p2->u and for any path v->q1 there will be a path v->q1->p2->q2
    in the new graph.

It is obvious that a codominator set of a graph G is a dominator set of the
transposed graph GT and conversely. Therefore we can compute the minimal
codominator set of G by transposing G and then computing the minimal dominator
set of the transposed graph.

The strategy for computing a minimal dominator set is the following.
( We use Pascal terminology for set operations )

  Dominated:=[];
  D:=[];
  While there is a p not in Dominated Do Begin
    Search(p);(* put all vertices in set Reachable that are reachable from p*)
    Dominated:=Dominated+Reachable;
    D:=D-Reachable; (* exclude all elements of D that are in Reachable *)
    Include p in D;
  End;

Evidently the set D that is produced by this algorithm is a dominator set.
Assume that D contains the vertices p1,...,pk and D is not minimal, i.e.
there is a minimal dominator set Q that contains vertices q1,...ql, and l<k.
Since D is a dominator set and Q is a minimal dominator set it follows that
for each qi in Q there is a unique pi in D such that qi is reachable from pi
by a path pi->qi. But every vertex is reachable from Q, therefore pk is also
reachable from some vertex in Q, say qi->pk. We obtained that there is a path
pi->qi->pk from pi to pk. The algorithm has executed both Search(pi) and
Search(pk). Either Search(pi) or Search(pk) was executed first, the vertex
pk was excluded from D because pk is reachable from pi. This contradicts to
the assumption that D is not minimal.

The algorithm above can be modified to avoid set operations union (+) and
difference (-). Indeed, when Search(p) is executed, we can include p in the
set Dominated and exclude p from D.

}
Program Net;
Const
  MaxN=200;           { max number of schools }
Type
  GraphType=Array[1..MaxN,0..MaxN] Of 0..MaxN;
  VertexSet=Set Of 1..MaxN;
Var
  OutFile: Text;
  N :Word;            { the number of schools }
  G: GraphType;       { representation of the network with graph G; }
                      { G[p,0] is the number of edges outgoing from p }
                      { the outgoing edges from p: (p, G[p,i]) 1<=i<=G[p,0]) }
  Domin,              { dominator set }
  CoDomin: VertexSet; { codominator set }
  NoDomins,           { number of dominator elements   }
  NoCoDomins: 0..MaxN;{ number of codominator elements }
  AnswerB: 0..MaxN;   { solution of subtask B }
  p: 0..MaxN;

Procedure ReadInput;
{ Global output variables: N, G }
  Var InFile: Text;
  i,p: Word;
  Begin
    Assign(InFile, 'input.txt'); Reset(InFile);
    ReadLn(InFile,N);

    For i:=1 To N Do
      G[i,0]:=0;
    For i:=1 To N Do Begin
      Read(InFile, p);
      While p<>0 Do Begin
        Inc(G[i,0]);
        G[i,G[i,0]]:=p;
        Read(InFile, p);
      End;
      ReadLn(InFile);
    End;

    Close(InFile);
  End { ReadInput };

Procedure ComputeDomin(Const G: GraphType; Var D: VertexSet);
{ Computes a minimal dominator set D of graph G }
{ Global input variables: N }
  Var
    Dominated, Reachable: Set of 1..MaxN;
    p: 1..MaxN;

  Procedure Search(p:Word);
    Var i: Word;
  Begin
    Exclude(D, p);
    Include(Dominated, p);
    For i:= 1 To G[p,0] Do
      If Not (G[p,i] in Reachable) Then Begin
        Include(Reachable,G[p,i]);
        Search(G[p,i]);
      End;
  End { Search };

  Begin { ComputeDomin }
    D:=[];
    Dominated:=[];
    For p:=1 To N Do
      If Not (p In Dominated) Then Begin
        Reachable:=[p];
        Search(p);
        Include(D, p);
      End;
  End { ComputeDomin };

Procedure ComputeCoDomin(Const G: GraphType; Var CD: VertexSet);
{ Computes a minimal codominator set D of graph G }
{ Global input variables: N }
  Var
    GT: GraphType;           { transposed graph of G }
    p,q: 1..MaxN; i:Word;

  Begin { ComputeCoDomin }
    For p:=1 To N Do
      GT[p,0]:=0;
    For p:=1 To N Do         { compute the transpose of the graph G in GT }
      For i:=1 To G[p,0] Do Begin
        q:=G[p,i];
        Inc(GT[q,0]); GT[q,GT[q,0]]:=p;
      End;
  ComputeDomin(GT, CD)        { computes CD, the dominator set of GT }
  End;{ ComputeCoDomin }

Begin { Program }
  ReadInput;
  ComputeDomin(G,Domin);
  ComputeCoDomin(G,CoDomin);

  NoDomins:=0;
  For p:=1 To N Do     { count the number of elements in the set Domin }
    If p In Domin Then Inc(NoDomins);

  NoCoDomins:=0;
  For p:=1 To N Do     { count the number of elements in the set CoDomin }
    If p In CoDomin Then Inc(NoCoDomins);

  If (Domin=[1]) And (CoDomin=[1])  { strongly connected }
    Then AnswerB:=0
    Else If NoDomins > NoCoDomins
      Then AnswerB:=NoDomins
      Else AnswerB:=NoCoDomins;

  Assign(OutFile, 'output.txt'); Rewrite(OutFile);
  WriteLn(OutFile, NoDomins);
  Writeln(OutFile, AnswerB);
  Close(OutFile);
End.
{ Scientific Committee IOI'96 }
