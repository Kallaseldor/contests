#include <bits/stdc++.h>

using namespace std;

#define maxn 1123456
#define EPS 1e-8

long long cx,cy;

struct potttt{
	long long x,y,h;
	potttt() {}
	potttt(long long _x,long long _y,long long _h) {
		x = _x, y = _y, h = _h;
	}
	bool operator < (const potttt other) const{
		if(atan2(this->y - cy,this->x - cx) > atan2(other.y - cy,other.x - cx))
			return true;
		return false;
	}

};

long long dist(long long x,long long y) {
	long long res = (x-cx)*(x-cx) + (y-cy)*(y-cy);
	return res;
}

struct potttt2{
	long long x,y,h;
	potttt2() {}
	potttt2(long long _x,long long _y,long long _h) {
		x = _x,y = _y, h = _h;
	}
	bool operator < (const potttt2 other) const{
		if(dist(x,y) > dist(other.x,other.y))
			return false;
		return true;
	}
};
 
vector <potttt> quad1;
vector <potttt> quad2;
vector <potttt> quad3;
vector <potttt> quad4;

vector <potttt2> v;
long long n;
long long tail[maxn];
long long prevyy[maxn];

long long findIndex(long long l,long long r,long long key) {
	while(r - l > 1) {
		long long m = l + (r-l)/2;
		if(v[tail[m]].h >= key)
			r = m;
		else
			l = m;
	}
	return r;
}

long long lis() {
	if(n == 0) return 0;	
	memset(tail,0,sizeof tail);
	memset(prevyy,-1,sizeof prevyy);
	long long ans = 1;
	for(long long i = 1;i < n;i++) {
		if(v[i].h < v[tail[0]].h)
			tail[0] = i;
		else if(v[i].h > v[tail[ans-1]].h) {
			prevyy[i] = tail[ans-1];
			tail[ans++] = i;
		}
		else {
			long long pos = findIndex(-1,ans -1,v[i].h);
			prevyy[i] = tail[pos - 1];
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
	scanf("%lld %lld",&cx,&cy);
	scanf("%lld",&n);
	long long x,y,h;
	for(long long i = 0;i < n;i++) {
		scanf("%lld %lld %lld",&x,&y,&h);
			quad1.push_back(potttt(x,y,h));
	}	
	sort(quad1.begin(),quad1.end());
	long long res = 0;
	double angle;
	for(long long i = 0;i < quad1.size();i++) {
		if(i == 0) {
			angle = atan2((double)quad1[i].y - cy,(double)quad1[i].x - cx);
			v.push_back(potttt2(quad1[i].x,quad1[i].y,quad1[i].h));
			continue;
		}
		if(dif(atan2(quad1[i].y - cy,quad1[i].x - cx),angle) > EPS) {
			n = v.size();
			sort(v.begin(),v.end());
			res += lis();
			angle = atan2(quad1[i].y - cy,quad1[i].x - cx);
			v.clear();
			v.push_back(potttt2(quad1[i].x,quad1[i].y,quad1[i].h));
		}
		else {
			v.push_back(potttt2(quad1[i].x,quad1[i].y,quad1[i].h));
		}
	}
	n = v.size();
	sort(v.begin(),v.end());
	res += lis();
	v.clear();
	printf("%lld\n",res);
	return 0;
}