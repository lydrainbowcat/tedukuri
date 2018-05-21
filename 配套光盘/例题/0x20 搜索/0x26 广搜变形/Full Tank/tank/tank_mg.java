import java.util.*;

class Road implements Comparable
{
    int x,y,d;
    public int compareTo(Object o) 
    {
	return x-((Road)o).x;
    }
    
}


public class tank_mg 
{
    static Scanner in = new Scanner(System.in);
    static final int inf=1<<28;
    
    int ncities, nroads;
    int[] start, end;
    int[] price;
    
    Road[] road;
    
    
    public static void main(String[] a) throws Exception
    {
	new tank_mg().run();
    }
    
    void run() throws Exception
    {
	ncities=in.nextInt();
	nroads=in.nextInt();
	price = new int[ncities];
	start = new int[ncities];
	end = new int[ncities];
	road = new Road[2*nroads];
	for (int i=0; i<ncities; ++i) price[i] = in.nextInt();	
	for (int i=0; i<nroads; ++i) {
	    road[2*i]=new Road();
	    road[2*i+1]=new Road();
	    road[2*i].x = road[2*i+1].y = in.nextInt();
	    road[2*i].y = road[2*i+1].x = in.nextInt();
	    road[2*i].d = road[2*i+1].d = in.nextInt();
	}
	nroads *=2;	
	Arrays.sort(road);
	int i=0, j=0;
	while (i<nroads) {
	    start[road[i].x]=i;
	    j=i+1;
	    while (j<nroads && road[j].x==road[i].x) ++j;
	    end[road[i].x]=j;
	    i=j;
	}
	for (int nq = in.nextInt(); nq>0; --nq) solve();	
    }
    
    void solve() throws Exception
    {
	// Uses dijkstra. A node u encodes the state
	// "being at city u/(c+1) with u%(c+1) units of fuel"

	int c=in.nextInt(), s=in.nextInt(), e=in.nextInt();
	int[] dist = new int[(c+1)*ncities];
	int[] heap = new int[(c+1)*ncities];
	int[] pos = new int[(c+1)*ncities];
	for (int i=0; i<(c+1)*ncities; ++i) {
	    dist[i]=inf;	
	    pos[i] = -1;
	}
	
	int nh=1;
	heap[0]=s*(c+1);	
	dist[s*(c+1)]=0;
	while (nh>0) {
	    int x=heap[0];
	    --nh;
	    if (nh>0) {
		heap[0]=heap[nh];
		downheap(heap,0,nh,dist,pos);		
	    }
	    int city = x/(c+1);
	    int tank = x%(c+1);
	    
	    if (city==e) break;	    
	    // can either add one unit and stay or
	    // go along an edge if enough fuel
	    if (tank < c) {
		int y=x+1;
		int dy=dist[x]+price[city];
		if (dist[y]>dy) {
		    dist[y]=dy;
		    if (pos[y]==-1) {
			pos[y]=nh;
			heap[nh++]=y;			
		    }
		    
		    upheap(heap,pos[y],dist,pos);		    
		}
		
	    }
	    for (int j=start[city]; j<end[city]; ++j) 
		if (tank >= road[j].d){
		    int y = road[j].y*(c+1)+tank-road[j].d;
		    int dy = dist[x];		    
		    if (dist[y]>dy) {
			dist[y]=dy;
			if (pos[y]==-1) {
			    pos[y]=nh;
			    heap[nh++]=y;			
			}
			upheap(heap,pos[y],dist,pos);		    
		    }
		}
	}
	if (dist[e*(c+1)] != inf) System.out.println(dist[e*(c+1)]);
	else System.out.println("impossible");
	
    }
   
    
    void downheap(int[] h, int i, int nh, int[] dist, int[] pos)
    {
	int j=2*(i+1)-1;
	if (j>=nh) return;
	if (j+1 < nh && dist[h[j+1]]<dist[h[j]]) ++j;
	if (dist[h[i]] <= dist[h[j]]) return;
	int z=h[i];
	h[i]=h[j];
	h[j]=z;
	pos[h[i]]=i;
	pos[h[j]]=j;
	downheap(h, j, nh, dist,pos);	
    }
    
    int upheap(int[] h, int i, int[] dist, int[] pos)
    {
	while (true) {
	    if (i==0) break;
	    int pi = (i+1)/2 -1;
	    if (dist[h[i]] >= dist[h[pi]]) break;
	    int z=h[i];
	    h[i]=h[pi];
	    h[pi]=z;
	    pos[h[i]]=i;
	    pos[h[pi]]=pi;
	    i=pi;
	}
	return i;	
    }
    
    
}

