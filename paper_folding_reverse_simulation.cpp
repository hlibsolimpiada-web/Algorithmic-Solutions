#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(){
    int tests;
    cin >> tests;
    while(tests--){
        int R, T, HX, HY, F;
        cin >> R >> T >> HX >> HY >> F;
        
        vector<char> foldType(F);
        vector<int> foldVal(F);
        vector<int> bxmin(F+1), bxmax(F+1), bymin(F+1), bymax(F+1);
        bxmin[0] = 0; bxmax[0] = R;
        bymin[0] = 0; bymax[0] = T;
        
        for(int i = 0; i < F; i++){
            cin >> foldType[i] >> foldVal[i];
            int I = foldVal[i];
            bxmin[i+1] = bxmin[i]; bxmax[i+1] = bxmax[i];
            bymin[i+1] = bymin[i]; bymax[i+1] = bymax[i];
            
            if(foldType[i] == 'X'){
                if(I <= bxmin[i]){
                    bxmin[i+1] = 2*I - bxmax[i];
                    bxmax[i+1] = 2*I - bxmin[i];
                } else if(I >= bxmax[i]){
                } else {
                    bxmin[i+1] = min(bxmin[i], 2*I - bxmax[i]);
                    bxmax[i+1] = I;
                }
            } else { // Y
                if(I <= bymin[i]){
                    bymin[i+1] = 2*I - bymax[i];
                    bymax[i+1] = 2*I - bymin[i];
                } else if(I >= bymax[i]){
                } else {
                    bymin[i+1] = min(bymin[i], 2*I - bymax[i]);
                    bymax[i+1] = I;
                }
            }
        }
        
        if(HX < bxmin[F] || HX > bxmax[F] || HY < bymin[F] || HY > bymax[F]){
            cout << 0 << "\n";
            continue;
        }
        
        set<pair<int,int>> holes;
        holes.insert({HX, HY});
        
        for(int i = F-1; i >= 0; i--){
            set<pair<int,int>> newHoles;
            int I = foldVal[i];
            int xmn = bxmin[i], xmx = bxmax[i];
            int ymn = bymin[i], ymx = bymax[i];
            
            for(auto& [hx, hy] : holes){
                if(foldType[i] == 'X'){
                    if(hx >= xmn && hx <= xmx)
                        newHoles.insert({hx, hy});
                    int mx = 2*I - hx;
                    if(mx >= xmn && mx <= xmx)
                        newHoles.insert({mx, hy});
                } else {
                    if(hy >= ymn && hy <= ymx)
                        newHoles.insert({hx, hy});
                    int my = 2*I - hy;
                    if(my >= ymn && my <= ymx)
                        newHoles.insert({hx, my});
                }
            }
            holes = newHoles;
        }
        
        cout << holes.size() << "\n";
    }
    return 0;
}
