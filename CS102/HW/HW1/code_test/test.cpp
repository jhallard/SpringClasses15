#include <iostream>
#include <vector>
#include <algorithm>    // std::sort
#include <ctime>

bool check_results(std::vector<int> A, int p);
std::vector<int> get_vals(int size);
int alg(const std::vector<int> &, int, int);
void print_vec(std::vector<int> A);

int main() {
  srand(time(0));
  std::vector <int> vec;
  for(int i = 0; i < 100; i++) {
    vec = get_vals(40);
    // print_vec(vec);
    int ind = alg(vec, 0, vec.size()-1);
    std::cout << check_results(vec, ind) << "\n";
  }
}

void print_vec(std::vector<int> A) {
  for(auto & x : A) {
    std::cout << x << ", ";
  }
  std::cout << "\n\n";
}

bool check_results(std::vector<int> A, int p) {
  
  std::cout << "p = " << p << "\n";
  print_vec(A);

  if(A.size() == 1 && p == 0)
    return true;
  int last = A[0];

  for(int i = 1; i < A.size(); i++) {
    if(A[i] < last) {
      return p == i-1;
    }  
    last = A[i];
  }

  if(A.size() >= 2 && A[A.size()-1] > A[A.size()-2] && p == A.size()-1)
    return true;
  return false;

}

std::vector<int> get_vals(int size) {
  
  std::vector<int> temp;
  for(int i = 0; i < size; i++) {
    temp.push_back(rand()%1000);
  }

  int ind = rand()%temp.size();

  std::sort(temp.begin(), temp.end());

  std::reverse(temp.begin()+ind,temp.end()); 

  return temp;
}

int alg(const std::vector<int> & A, int l, int r) {
  
  if(l < 0 || r > A.size()-1) {
    return -1;
  }

  int i = (r+l)/2;

  if(r == l) {
    return l;
  }
  if(r-l == 1) {
    if(A[r] >= A[l])
      return r;
    else
      return l;
  }

  // std::cout << "i : " << i << "\n r : " << r << "\n l : " << l << "\n A.size : " << A.size() << "\n\n\n"; 

  if(A[i] >= A[i-1]) {
    return alg(A, i, r);
  }
  else  {
    return alg(A, l, i);
  }
}
