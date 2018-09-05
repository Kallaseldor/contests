#include <bits/stdc++.h>

using namespace std;

#define maxn 1123456
#define EPS 1e-8

int cx,cy;

struct point{
	int x,y,h;
	double angle;
	point() {}
	point(int _x,int _y,int _h) {
		x = _x, y = _y, h = _h,angle = atan2(y-cy,x-cx);
	}
	bool operator < (const point other) const{
		if(angle > other.angle)
			return true;
		return false;
	}

};

long long dist(long long x,long long y) {
	long long res = (x-cx)*(x-cx) + (y-cy)*(y-cy);
	return res;
}

struct point2{
	int x,y,h;
	point2() {}
	point2(int _x,int _y,int _h) {
		x = _x,y = _y, h = _h;
	}
	bool operator < (const point2 other) const{
		if(dist(x,y) > dist(other.x,other.y))
			return false;
		return true;
	}
};
 
vector <point> quad1;
vector <point> quad2;
vector <point> quad3;
vector <point> quad4;

vector <point2> v;
int n;
int tail[maxn];
int prev[maxn];

int findIndex(int l,int r,int key) {
	while(r - l > 1) {
		int m = l + (r-l)/2;
		if(v[tail[m]].h >= key)
			r = m;
		else
			l = m;
	}
	return r;
}

int lis() {
	// printf("%d\n",n);
	// printf("_______________________________________\n");
	// for(int i = 0;i < n;i++) {
	// 	printf("%d %d\n",v[i].x,v[i].y);
	// }
	// printf("_______________________________________\n");
	if(n == 0) return 0;	
	memset(tail,0,sizeof tail);
	memset(prev,-1,sizeof prev);
	int ans = 1;
	for(int i = 1;i < n;i++) {
		if(v[i].h < v[tail[0]].h)
			tail[0] = i;
		else if(v[i].h > v[tail[ans-1]].h) {
			prev[i] = tail[ans-1];
			tail[ans++] = i;
		}
		else {
			int pos = findIndex(-1,ans -1,v[i].h);
			prev[i] = tail[pos - 1];
			tail[pos] = i;
		}
	}
	return ans;
}

double dif(double x,double y) {
	if(x > y)
		return x-y;
	return y-x;
}

int main() {
	// freopen("in","r",stdin);
	scanf("%d %d",&cx,&cy);
	scanf("%d",&n);
	int x,y,h;
	for(int i = 0;i < n;i++) {
		scanf("%d %d %d",&x,&y,&h);
		//if(x >= cx && y >= cy)
			quad1.push_back(point(x,y,h));
		// else if(x < cx && y >= cy)
		// 	quad2.push_back(point(x,y,h));
		// else if(x < cx && y < cy)
		// 	quad3.push_back(point(x,y,h));
		// else
		// 	quad4.push_back(point(x,y,h));
	}	
	sort(quad1.begin(),quad1.end());
	// sort(quad2.begin(),quad2.end());
	// sort(quad3.begin(),quad3.end());
	// sort(quad4.begin(),quad4.end());

	// printf("QUADRANTE 1\n");
	// for(int i = 0;i < quad1.size();i++)
	// 	printf("%d %d\n",quad1[i].x,quad1[i].y);
	// printf("QUADRANTE 2\n");
	// for(int i = 0;i < quad2.size();i++)
	// 	printf("%d %d\n",quad2[i].x,quad2[i].y);
	// printf("QUADRANTE 3\n");
	// for(int i = 0;i < quad3.size();i++)
	// 	printf("%d %d\n",quad3[i].x,quad3[i].y);
	// printf("QUADRANTE 4\n");
	// for(int i = 0;i < quad4.size();i++)
	// 	printf("%d %d\n",quad4[i].x,quad4[i].y);

	int res = 0;
	double angle;
	for(int i = 0;i < quad1.size();i++) {
		if(i == 0) {
			angle = quad1[i].angle;
			v.push_back(point2(quad1[i].x,quad1[i].y,quad1[i].h));
			continue;
		}
		// printf("%d %d %.15lf %.15lf\n",quad1[i].x - cx,quad1[i].y - cy,angle,atan2(quad1[i].y - cy,quad1[i].x - cx));
		if(dif(quad1[i].angle,angle) > EPS) {
			// printf("ENTROU AQUI\n");
			n = v.size();
			sort(v.begin(),v.end());
			res += lis();
			angle = quad1[i].angle;
			v.clear();
			v.push_back(point2(quad1[i].x,quad1[i].y,quad1[i].h));
		}
		else {
			v.push_back(point2(quad1[i].x,quad1[i].y,quad1[i].h));
		}
	}
	n = v.size();
	sort(v.begin(),v.end());
	res += lis();
	v.clear();
	// for(int i = 0;i < quad2.size();i++) {
	// 	if(!i) {
	// 		angle = atan2(quad2[i].y - cy,quad2[i].x - cx);
	// 		v.push_back(point2(quad2[i].x,quad2[i].y,quad2[i].h));
	// 		continue;
	// 	}
	// 	if(dif(atan2(quad2[i].y - cy,quad2[i].x - cx),angle) > EPS) {
	// 		n = v.size();
	// 		sort(v.begin(),v.end());
	// 		res += lis();
	// 		angle = atan2(quad2[i].y - cy,quad2[i].x - cx);
	// 		v.clear();
	// 		v.push_back(point2(quad2[i].x,quad2[i].y,quad2[i].h));
	// 	}
	// 	else {
	// 		v.push_back(point2(quad2[i].x,quad2[i].y,quad2[i].h));
	// 	}
	// }
	// n = v.size();
	// sort(v.begin(),v.end());
	// res += lis();
	// v.clear();
	// for(int i = 0;i < quad3.size();i++) {
	// 	if(!i) {
	// 		angle = atan2(quad3[i].y - cy,quad3[i].x - cx);
	// 		v.push_back(point2(quad3[i].x,quad3[i].y,quad3[i].h));
	// 		continue;
	// 	}
	// 	if(dif(atan2(quad3[i].y - cy,quad3[i].x - cx),angle) > EPS) {
	// 		n = v.size();
	// 		sort(v.begin(),v.end());
	// 		res += lis();
	// 		angle = atan2(quad3[i].y - cy,quad3[i].x - cx);
	// 		v.clear();
	// 		v.push_back(point2(quad3[i].x,quad3[i].y,quad3[i].h));
	// 	}
	// 	else {
	// 		v.push_back(point2(quad3[i].x,quad3[i].y,quad3[i].h));
	// 	}
	// }
	// n = v.size();
	// sort(v.begin(),v.end());
	// res += lis();
	// v.clear();
	// for(int i = 0;i < quad4.size();i++) {
	// 	if(!i) {
	// 		angle = atan2(quad4[i].y - cy,quad4[i].x - cx);
	// 		v.push_back(point2(quad4[i].x,quad4[i].y,quad4[i].h));
	// 		continue;
	// 	}
	// 	if(dif(atan2(quad4[i].y - cy,quad4[i].x - cx),angle) > EPS) {
	// 		n = v.size();
	// 		sort(v.begin(),v.end());
	// 		res += lis();
	// 		angle = atan2(quad4[i].y - cy,quad4[i].x - cx);
	// 		v.clear();
	// 		v.push_back(point2(quad4[i].x,quad4[i].y,quad4[i].h));
	// 	}
	// 	else {
	// 		v.push_back(point2(quad4[i].x,quad4[i].y,quad4[i].h));
	// 	}
	// }
	// n = v.size();
	// sort(v.begin(),v.end());
	// res += lis();
	printf("%d\n",res);
	return 0;
}