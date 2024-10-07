#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int map[6][6];
int k, m;
int nums[301];
int pointer = 0;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

struct search_res {
  int y;
  int x;
  int val;
  int roll;
};

bool compare(search_res a, search_res b) {
  if(a.val == b.val) {
    if(a.roll == b.roll) {
      if(a.x == b.x) {
        return a.y < b.y;
      }
      return a.x < b.x;
    }
    return a.roll < b.roll;
  }
  return a.val > b.val;
}

void roll(int y, int x) {
  int t1 = map[y-1][x];
  int t2 = map[y-1][x+1];

  map[y-1][x+1] = map[y-1][x-1];
  map[y-1][x] = map[y][x-1];
  map[y-1][x-1] = map[y+1][x-1];

  map[y][x-1] = map[y+1][x];
  map[y+1][x-1] = map[y+1][x+1];

  map[y+1][x] = map[y][x+1];
  map[y+1][x+1] = t2;

  map[y][x+1] = t1;
}

int find_val(bool d) {
  int val = 0;

  int visited[5][5];
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      visited[i][j] = 0;
    }
  }
  
  for(int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if(!visited[i][j]) {
        queue<pair<int,int> > q;
        queue<pair<int,int> > cand;
        pair<int,int> p = make_pair(i,j);
        visited[i][j] = 1;
        q.push(p);
        cand.push(p);
        while(!q.empty()){
          pair<int,int> t = q.front();
          q.pop();

          for(int k = 0; k < 4; k++) {
            int ny = t.first + dy[k];
            int nx = t.second + dx[k];

            if(ny >= 0 && ny < 5 && nx >= 0 && nx < 5 && !visited[ny][nx] && map[ny][nx] == map[t.first][t.second]) {
              pair<int,int> np = make_pair(ny,nx);
              visited[ny][nx] = 1;
              cand.push(np);
              q.push(np);
            }
          }
        }
        if(cand.size() >= 3) {
          val += cand.size();
          while(!cand.empty()) {
            pair<int, int> c = cand.front();
            cand.pop();
            if(d) map[c.first][c.second] = 0;
          }
        }
      }
    }
  }
  return val;
}

int search() {
  int ret = 0;
  vector<search_res> res;
  for(int i = 0; i < 9; i++) {
    int y = (i / 3) + 1;
    int x = (i % 3) + 1;
    for(int j = 0; j < 3; j++) {
      roll(y,x);
      int val = find_val(false);  
      search_res r = {y, x, val, j+1};
      res.push_back(r);
    }
    
    roll(y,x);
  }

  sort(res.begin(), res.end(), compare);

  search_res found = res[0];
  for(int i = 0; i < found.roll; i++) {
    roll(found.y,found.x);
  }
  int val = find_val(true);

  ret += val;

  val = 0;
  do {
    for(int j = 0; j < 5; j++) {
      for(int i = 4; i >= 0; i--) {
        if(map[i][j] == 0) {
          map[i][j] = nums[pointer];
          pointer++;
        }
      }
    }
    val = find_val(true);
    if(val > 1) {
      ret += val;
    }
  } while(val > 0);

  return ret;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  cin >> k >> m;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      cin >> map[i][j];
    }
  }
  for(int i = 0; i < m; i++) {
    cin >> nums[i];
  }

  for(int i = 0; i < k; i++) {
    int val = search();
    if(val) {
      cout << val << " ";
    } else {
      break;
    }
  }
  return 0;
}