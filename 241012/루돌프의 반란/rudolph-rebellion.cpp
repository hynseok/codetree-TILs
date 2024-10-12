#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, p, c, d;
int ry, rx;
int map[51][51] = {0,};

int dy[8] = {-1, 0, 1, 0, 1, 1, -1, -1};
int dx[8] = {0, 1, 0, -1, 1, -1, 1, -1};

struct santa {
  int id;
  int y;
  int x;
  int score;
  int is_stun;
  bool is_out;
};
santa santas[31];

int check_dist(int santa_id, int y, int x) {
  santa s = santas[santa_id-1];
  return (s.y - y)*(s.y - y) + (s.x - x)*(s.x - x);
}

int check_dist(int y, int x) {
  return (ry - y)*(ry - y) + (rx - x)*(rx - x);
}

void move_rudolf() {
  // find santa
  int id, mind = 99999999;
  int maxy = -1;
  int maxx = -1;
  for(int i = 0; i < p; i++) {
    if(santas[i].is_out) continue;
    int d = check_dist(i+1, ry, rx);
    if(mind > d) {
      mind = d;
      id = i+1;
      maxy = santas[i].y;
      maxx = santas[i].x;
    } else if (mind == d) {
      if(maxy < santas[i].y) {
        maxy = santas[i].y;
        maxx = santas[i].x;
        id = i+1;
      } else if (maxy == santas[i].y) {
        if(maxx < santas[i].x) {
          maxx = santas[i].x;
          id = i+1;
        }
      }
    }
  }

  // find direction
  int dir; mind = 99999999;
  for(int i = 0; i < 8; i++) {
    int ny = ry + dy[i];
    int nx = rx + dx[i];

    if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

    int d = check_dist(id,ny,nx);
    if(mind > d) {
      mind = d;
      dir = i;
    }
  }

  // 루돌프 이동
  map[ry][rx] = 0;
  ry = ry + dy[dir];
  rx = rx + dx[dir];
  
  if(map[ry][rx] > 0) { // 산타가 있을 때
    santa &s = santas[map[ry][rx]-1];
    s.score += c; // 점수 추가
    map[s.y][s.x] = 0;
    s.y = s.y + c * dy[dir];
    s.x = s.x + c * dx[dir];
    if(s.y < 0 || s.x < 0 || s.y >= n || s.x >= n) {
      s.is_out = true;
      map[ry][rx] = -1;
      return;
    }
    s.is_stun = 2;
    if(map[s.y][s.x] > 0) {
      bool flag = true;
      santa &ns = santas[map[s.y][s.x]-1];
      while(flag) {
        ns.y = ns.y + dy[dir];
        ns.x = ns.x + dx[dir];

        if(ns.y < 0 || ns.x < 0 || ns.y >= n || ns.x >= n) {
          ns.is_out = true;
          break;
        }

        if(map[ns.y][ns.x] > 0) {
          ns = santas[map[ns.y][ns.x] - 1];
        } else {
          flag = false;
        }
        map[ns.y][ns.x] = ns.id;
      }
      map[s.y][s.x] = s.id;
    } else {
      map[s.y][s.x] = s.id;
    }
    map[ry][rx] = -1;
  } else {
    map[ry][rx] = -1;
  }
}

void move_santa() {
  for(int i = 0; i < p; i++) {
    santa &s = santas[i];
    if(s.is_out) continue;
    if(s.is_stun) {
      s.is_stun--;
      continue;
    }
    
    int dir = -1, mind = check_dist(s.y, s.x);
    for(int j = 0; j < 4; j++) {
      int ny = s.y + dy[j];
      int nx = s.x + dx[j];
      if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
      if(map[ny][nx] > 0) continue;
      int d = check_dist(ny, nx);
      if(mind > d) {
        mind = d;
        dir = j;
      }
    }

    if(dir == -1) continue;

    map[s.y][s.x] = 0;
    s.y = s.y + dy[dir];
    s.x = s.x + dx[dir];

    if(map[s.y][s.x] == -1) {
      s.score += d;
      int ndir = (dir + 2) % 4;
      s.y = s.y + d * dy[ndir];
      s.x = s.x + d * dx[ndir];
      if(s.y < 0 || s.x < 0 || s.y >= n || s.x >= n) {
        s.is_out = true;
        continue;
      }
      s.is_stun = 1;

      if(map[s.y][s.x] > 0) {
        bool flag = true;
        santa &ns = santas[map[s.y][s.x]-1];
        while(flag) {
          ns.y = ns.y + dy[ndir];
          ns.x = ns.x + dx[ndir];

          if(ns.y < 0 || ns.x < 0 || ns.y >= n || ns.x >= n) {
            ns.is_out = true;
            break;
          }

          if(map[ns.y][ns.x] > 0) {
            ns = santas[map[ns.y][ns.x] - 1];
          } else {
            flag = false;
          }
          map[ns.y][ns.x] = ns.id;
        }
        map[s.y][s.x] = s.id;
      } else {
        map[s.y][s.x] = s.id;
      }
    } else {
      map[s.y][s.x] = s.id;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  cin >> n >> m >> p >> c >> d;

  cin >> ry >> rx;
  ry -= 1; rx -= 1;
  map[ry][rx] = -1; // 루돌프 -1

  for(int i = 0; i < p; i++) {
    int id, y, x;
    cin >> id >> y >> x;
    map[y-1][x-1] = id; // 산타 id
    santa s = {id, y-1, x-1, 0, false, false};
    santas[id-1] = s;
  }

  for(int i = 0; i < m; i++) {
    move_rudolf();
    for(int j = 0; j < p; j++) {
      cout << santas[j].score << " ";
    } cout << "\n";
    move_santa();
    
    int out = 0; 
    for(int j = 0; j < p; j++) {
      if(!santas[j].is_out) {
        santas[j].score++;
      } else {
        out++;
      }
    }
    if(out == p) break; 
    for(int j = 0; j < p; j++) {
      cout << santas[j].score << " ";
    } cout << "\n";
  }

  for(int i = 0; i < p; i++) {
    cout << santas[i].score << " ";
  }
}