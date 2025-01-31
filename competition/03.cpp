#include <iostream>
#include <math.h>
using namespace std;

double lines[10001][2];

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    double a1, a2, pi=3.141592;
    double x1, x2, y1, y2, p, q;
    for(int i=1; i<=n; i++){
        cin >> a1 >> a2;
        x1 = cos(a1*pi/1800)*1000;
        y1 = sin(a1*pi/1800)*1000;
        x2 = cos(a2*pi/1800)*1000;
        y2 = sin(a2*pi/1800)*1000;
        if(x2==x1){
            p=9999999;
        }
        else p = (y2-y1)/(x2-x1);
        
        q = -x1*p+y1;
        lines[i][0] = p;
        lines[i][1] = q;
    }

    int p1l, p2l, cnt1=0, cnt2=0;
    double px, py, p1a, p2a;
    cin >> p1a >> p1l;
    cin >> p2a >> p2l;

    px = cos(p1a*pi/1800)*p1l;
    py = sin(p1a*pi/1800)*p1l;

    for(int i = 1; i<=n; i++){
        if(lines[i][1]>0){
            if(lines[i][0]*px+lines[i][1]<py) cnt1++;
        }
        else{
            if(lines[i][0]*px+lines[i][1]>py) cnt1++;
        }
    }

    px = cos(p2a*pi/1800)*p2l;
    py = sin(p2a*pi/1800)*p2l;

    for(int i = 1; i<=n; i++){
        if(lines[i][1]>0){
            if(lines[i][0]*px+lines[i][1]<py) cnt2++;
        }
        else{
            if(lines[i][0]*px+lines[i][1]>py) cnt2++;
        }
        // cout << lines[i][0] << lines[i][1] << "\n";
    }

    if(abs(cnt1-cnt2)%2==1) cout << "NO";
    else cout << "YES";

    // cout << cnt1 << " " << cnt2;

}