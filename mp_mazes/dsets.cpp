#include "dsets.h"

void DisjointSets::addelements(int e){
    for(int i = 0; i < e; i++){
        _connections.push_back(-1);
    }
}

int DisjointSets::find(int e){
    int r = e;
    while(_connections[r] > 0){
        r = _connections[r];
    }
    return r;
}

void DisjointSets::setunion(int a, int b){
    int ia = find(a);
    int ib = find(b);
    if(_connections[ia] < _connections[ib]){
        int s = _connections[ib];
        _connections[ib] = ia;
        _connections[ia] += s;
    }
    else{
        int s = _connections[ia];
        _connections[ia] = ib;
        _connections[ib] += s;
    }
}	

int DisjointSets::size(int e){
    int ie = find(e);
    return -_connections[ie];
}