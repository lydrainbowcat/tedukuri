import java.io.*;
import java.util.*;

public class tank_tab{
  private static class path{
    int d;
    int t;
    public path(int t, int d){this.d = d; this.t = t;}
  }
  
  private static class val implements Comparable<val>{
    int c;
    int f;
    int n;
    public val(int c, int f, int n){ this.c=c; this.f=f; this.n=n;}
    public int compareTo(val v){return c-v.c;}
  }

  public static void main(String[] args) throws Exception{
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    String[] inp = in.readLine().split(" ");
    int n = Integer.parseInt(inp[0]);
    int m = Integer.parseInt(inp[1]);
    inp = in.readLine().split(" ");
    int[] p = new int[n];
    for(int i=0;i<n;i++) p[i]=Integer.parseInt(inp[i]);
    ArrayList<ArrayList<path>> nl = new ArrayList<ArrayList<path>>();
    for(int i=0;i<n;i++) nl.add(new ArrayList<path>());
    for(int i=0;i<m;i++){
      inp = in.readLine().split(" ");
      nl.get(Integer.parseInt(inp[0])).add(
          new path(Integer.parseInt(inp[1]),Integer.parseInt(inp[2])));
      nl.get(Integer.parseInt(inp[1])).add(
          new path(Integer.parseInt(inp[0]),Integer.parseInt(inp[2])));
    }
    int q = Integer.parseInt(in.readLine());
    for(int k=0;k<q;k++){
      inp = in.readLine().split(" ");
      int start = Integer.parseInt(inp[1]);
      int stop = Integer.parseInt(inp[2]);
      int f = Integer.parseInt(inp[0]);
      int[][] b = new int[n][f+1];
      for(int j=0;j<n;j++)for(int l=0;l<=f;l++) b[j][l]=Integer.MAX_VALUE;
      boolean[][] done = new boolean[n][f+1];
      b[start][0]=0;
      PriorityQueue<val> qu = new PriorityQueue<val>();
      qu.add(new val(0,0,start));
      boolean gudd=false;
      while(!qu.isEmpty()){
        val curr = qu.poll();
        int minx=curr.n, miny=curr.f;
        if(done[minx][miny]) continue;
        if(minx==stop && miny==0){
          System.out.println(b[stop][0]);
          gudd=true;
          break;
        }
        if(miny<f) if(b[minx][miny+1]>b[minx][miny]+p[minx]){
          qu.add(new val(b[minx][miny]+p[minx],miny+1,minx));
          b[minx][miny+1]=b[minx][miny]+p[minx];
        }
        for(int i=0;i<nl.get(minx).size();i++)
          if(nl.get(minx).get(i).d<=miny && b[minx][miny]<b[nl.get(minx).get(i).t][miny-nl.get(minx).get(i).d]){
            qu.add(new val(b[minx][miny],miny-nl.get(minx).get(i).d,nl.get(minx).get(i).t));
            b[nl.get(minx).get(i).t][miny-nl.get(minx).get(i).d]=b[minx][miny];
          }
        done[minx][miny]=true;
      }
      if(!gudd) System.out.println("impossible");
    }
  }
}
