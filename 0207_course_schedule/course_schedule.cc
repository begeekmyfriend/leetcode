#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isCycle(int course, vector<vector<int>>& adj, vector<int>& visited) {
        if(visited[course] == 2) return true ;
        if(visited[course] == 1) return false ;
        visited[course] = 2 ;
        for(auto connectedCourse : adj[course]) {
            if(isCycle(connectedCourse, adj, visited)) {
                return true ;
            }
        }
        visited[course] = 1 ;
        return false ;
    }    
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses) ;
        for(auto courses : prerequisites) {
            auto course1 = courses[0] ;
            auto course2 = courses[1] ;
            adj[course2].push_back(course1) ;
        }
        vector<int> visited(numCourses, 0) ;
        for(int course = 0 ; course < numCourses ; course++) {
            if(!visited[course]) {
                if(isCycle(course, adj, visited)) {
                    return false;
                }
            }
        }
        return true ;
    }
};