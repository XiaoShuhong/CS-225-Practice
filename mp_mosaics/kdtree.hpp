/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first, const Point<Dim>& second, int curDim) const
{
  if (first[curDim] == second[curDim]){
    return first<second;
  }
  return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
  int sc = 0;
  int sp = 0;
  for(int i = 0; i < Dim; i++){
    sc += pow(target[i] - currentBest[i], 2);
    sp += pow(target[i] - potential[i], 2);
  }
  if (sc == sp){
    return potential<currentBest;
  }
  return sp<sc;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  size = newPoints.size();
  if(size == 0){
    root = NULL;
    return;
  }
  vector<Point<Dim>> NPcopy = newPoints;
  root = new KDTreeNode();
  makeNodeFromVec(NPcopy, 0, root);
}

template <int Dim>
void KDTree<Dim>::makeNodeFromVec(vector<Point<Dim>> newPoints, int curDim, KDTreeNode* myNode){
  int s = newPoints.size();
  vector<Point<Dim>> orderByDim;
  while(!newPoints.empty()){
    int minIdx = 0;
    auto min = newPoints[0];
    for(size_t i = 1; i < newPoints.size(); i++){
      if(smallerDimVal(newPoints[i],min, curDim)){
        min = newPoints[i];
        minIdx = i;
      }
    }
    orderByDim.push_back(min);
    newPoints.erase(newPoints.begin()+minIdx);
  }
  int medianIdx = (s-1)/2;
  myNode->point = orderByDim[medianIdx];
  vector<Point<Dim>> leftVec;
  vector<Point<Dim>> rightVec;
  for (int i = 0; i < medianIdx; i++){
    leftVec.push_back(orderByDim[i]);
  }
  for (int i = medianIdx+1; i < s; i++){
    rightVec.push_back(orderByDim[i]);
  }
  if(leftVec.size() > 0){
    myNode->left = new KDTreeNode();
    makeNodeFromVec(leftVec,(curDim+1)%Dim,myNode->left);
  }
  else{
    myNode->left = NULL;
  }
  if(rightVec.size() > 0){
    myNode->right = new KDTreeNode();
    makeNodeFromVec(rightVec,(curDim+1)%Dim,myNode->right);
  }
  else{
    myNode->right = NULL;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this fnction!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  if(!root){
    return Point<Dim>();
  }
  return findNearestNeighborHelper(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(KDTreeNode* myNode,const Point<Dim>& query, int curDim) const{
  Point<Dim> currentBest;
  if (smallerDimVal(query, myNode->point, curDim)){
    if(myNode->left){
      currentBest = findNearestNeighborHelper(myNode->left, query, (curDim + 1) % Dim);
      if(shouldReplace(query, currentBest, myNode->point)){
        currentBest = myNode->point;
      }
    }
    else{
      currentBest = myNode->point;
    }
    if(myNode->right){
      int distSquared = 0;
      for(size_t i = 0; i < Dim; i++){
        distSquared += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
      }
      int dimDistSuared = (myNode->point[curDim] - query[curDim])*(myNode->point[curDim] - query[curDim]);
      if (distSquared >= dimDistSuared){
        auto rightNN = findNearestNeighborHelper(myNode->right, query, (curDim + 1) % Dim);
        if(shouldReplace(query, currentBest, rightNN)){
          currentBest = rightNN;
        }
      }
    }
  }
  else {
    if(myNode->right){
      currentBest = findNearestNeighborHelper(myNode->right, query, (curDim + 1) % Dim);
      if(shouldReplace(query, currentBest, myNode->point)){
        currentBest = myNode->point;
      }
    }
    else{
      currentBest = myNode->point;
    }
    if(myNode->left){
      int distSquared = 0;
      for(size_t i = 0; i < Dim; i++){
        distSquared += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
      }
      int dimDistSuared = (myNode->point[curDim] - query[curDim])*(myNode->point[curDim] - query[curDim]);
      if (distSquared >= dimDistSuared){
        auto leftNN = findNearestNeighborHelper(myNode->left, query, (curDim + 1) % Dim);
        if(shouldReplace(query, currentBest, leftNN)){
          currentBest = leftNN;
        }
      }
    }
  }

  return currentBest;
}
