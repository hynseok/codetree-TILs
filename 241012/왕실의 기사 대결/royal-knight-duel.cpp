#include <iostream>
#include <vector>
#include <queue>

#define MAX_L 41
#define MAX_N 31
#define MAX_Q 101
#define MAX_k 100

using namespace std;
int L, N, Q;

int map[MAX_L][MAX_L] = {0, };
int k_map[MAX_L][MAX_L] = {0, };

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct knight {
  int y;
  int x;
  int h;
  int w;
  int k;
  bool is_dead;
  int dmg;
};

knight knights[MAX_N];

void move(int id, int dir) {
  vector<int> knight_ids; // 이동해야할 기사들의 id저장
  knight_ids.push_back(id);

  knight k = knights[id];

  queue<pair<int, int> > q;
  for(int i = k.y; i < k.y + k.h; i++) {
    for(int j = k.x; j < k.x + k.w; j++) {
      q.push(make_pair(i,j));
    }
  }

  bool visited[L+1][L+1];
  for(int i = 0; i <= L; i++){
    for(int j = 0; j <= L; j++) {
      visited[i][j] = false;
    }
  }

  while(!q.empty()) {
    pair<int,int> pos = q.front();
    q.pop();
    visited[pos.first][pos.second] = true;
    int ny = pos.first + dy[dir];
    int nx = pos.second + dx[dir];
    // 벽이면 실패
    if(ny < 1 || nx < 1 || ny > L || nx > L) return;
    if(map[ny][nx] == 2) return;
    if(visited[ny][nx] || k_map[ny][nx] == 0) continue;

    if(k_map[pos.first][pos.second] != k_map[ny][nx]) {
      int new_id = k_map[ny][nx];
      knight new_k = knights[new_id];
      knight_ids.push_back(new_id);
      for(int i = new_k.y; i < new_k.y + new_k.h; i++) {
        for(int j = new_k.x; j < new_k.x + new_k.w; j++) {
          q.push(make_pair(i,j));
        }
      }
    }
  }

  int attacker = id;
  while(!knight_ids.empty()) {
    int id = knight_ids.back();
    knight_ids.pop_back();
    knight &kni = knights[id];
    
    for(int i = kni.y; i < kni.y + kni.h; i++) {
      for(int j = kni.x; j < kni.x + kni.w; j++) {
        k_map[i][j] = 0;
      }
    }
    for(int i = kni.y + dy[dir]; i < kni.y + kni.h + dy[dir]; i++) {
      for(int j = kni.x + dx[dir]; j < kni.x + kni.w + dx[dir]; j++) {
        k_map[i][j] = id;
        if(map[i][j] == 1 && id != attacker) { 
          kni.k--;
          kni.dmg++;
        }
      }
    }
    
    if(kni.k <= 0) {
      for(int i = kni.y + dy[dir]; i < kni.y + kni.h + dy[dir]; i++) {
        for(int j = kni.x + dx[dir]; j < kni.x + kni.w + dx[dir]; j++) {
          k_map[i][j] = 0;
        }
      }
      kni.is_dead = true;
    }
    kni.y += dy[dir];
    kni.x += dx[dir];
  }
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  cin >> L >> N >> Q;

  for(int i = 1; i <= L; i++) {
    for(int j = 1; j <= L; j++) {
      cin >> map[i][j];
    }
  }

  for(int i = 1; i <= N; i++) {
    int r, c, h, w, k;
    cin >> r >> c >> h >> w >> k;
    knight kni = {r, c, h, w, k, 0};
    knights[i] = kni;
    for(int j = r; j < r + h; j++) {
      for(int k = c; k < c + w; k++) {
        k_map[j][k] = i;
      }
    }
  }

  for(int i = 1; i <= Q; i++) {
    int id, d;
    cin >> id >> d;
    move(id, d);
  }

  int ans = 0;
  for(int i = 1; i <= N; i++) {
    if(!knights[i].is_dead)
      ans += knights[i].dmg;
  }

  cout << ans << "\n";

  return 0;
}