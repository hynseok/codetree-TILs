#include <iostream>
#include <vector>
using namespace std;

// 식당의 수 n
int n;
// 각 식당의 고객 수
vector<int> rest;
// 팀장, 팀원
int l, m;
// 필요한 검사자의 최소 수
long long ans;

int main() {
  cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);

  // 입력 처리
  cin >> n;
  for(int i = 0; i < n; i++) {
    int cust_num;
    cin >> cust_num;
    rest.push_back(cust_num);
  }
  cin >> l >> m;

  for(int i = 0; i < n; i++) {
    int cust_num = rest[i];

    cust_num -= l;
    ans++;

    if(cust_num > 0) {
      ans += (cust_num / m);
      if(cust_num % m)
      ans++;
    } 
  }

  cout << ans;

  return 0;
}