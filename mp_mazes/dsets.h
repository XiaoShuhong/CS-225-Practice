#pragma once

#include <vector>

using namespace std;

class DisjointSets{
    private:
        vector<int> _connections;

    public:
        void addelements(int e);
        int find(int e);
        void setunion(int a, int b); 
        int size(int e);
};