//
//  main.cpp
//  trap-rain
//
//  Created by mndx on 15/08/2022.
//

#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b) {
    int res = 0;
    
    if(a < b) res = a;
    else res = b;
    
    return res;
}

int trap(vector<int> & height) {
    
    int n = (int) height.size();
    
    int res = 0;
    
    int trackl = 0;
    int trackr = 0;
    int trackbk = 0;
    int end = n - 1;
    
    if(n <= 1) {
        return 0;
    }
    
    // Get starting point
    while(height[trackl + 1] >= height[trackl]) {
        trackl++;
        trackr++;
    }
    
    // Get ending point
    while(end > 0 && height[end - 1] >= height[end]) {
        end--;
    }
    
    
    // Compute max rainwater trapped
    while(trackl < end) {
        
        // Check first location to the right
        trackr++;
        
        int track_change = trackl;
        int h = height[trackl];
        int h_loc = height[trackr];
        
        int max_h = 0;
        
        // Compute location of right boundary wall trackr
        while(h_loc < h && trackr < end) {
            trackr++;
            h_loc = height[trackr];
            if(h_loc > max_h) {
                max_h = h_loc;
                trackbk = trackr;
            }
        }

        // If wall height at trackr is equal to the wall at trackl, then choose first trackr with wall with height greater or equal to wall at trackl
        while(trackr < end && h == height[trackr] && h <= height[trackr + 1]) {
            trackr++;
            h_loc = height[trackr];
        }
        
        // If there is no right wall with height greater than h, then choose height stored in backup trackbk
        if(trackr == end && h > max_h) {
            trackr = trackbk;
            h_loc = max_h;
        }
        
        // Determine minimum wall height between the wall at trackl and at trackr
        int h_low = min(h_loc, h);
        
        // Compute amount of rainwater trapped between trackl and trackr
        for(int i = trackl + 1; i < trackr; ++i) {
            int diff = h_low - height[i] >= 0 ? h_low - height[i] : 0;
            res = res + diff;
        }

        // Update left track pointer
        trackl = trackr;
        
        // Detect if track pointers have reached a steady state
        if(track_change == trackl) {
            trackl = end;
        }
    }
    
    return res;
}

int main(int argc, const char * argv[]) {

    // Input height vector
    vector<int> height = {4, 2, 0, 3, 2, 5};
    
    // Compute amount of rain water trapped
    int amount_rain = trap(height);
    
    // Print results
    cout << "amount of rain trapped: " << amount_rain << endl;
    
    return 0;
}
