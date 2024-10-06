#include <iostream>
#include <queue>

using namespace std;

struct golem {
	int id;
	int y;
	int x;
	int dir; // 0: 북, 1: 동, 2: 남, 3: 서
};
queue<golem> golems;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int map[76][72] = {0, };
int visited[76][72] = {0, };

int r, c, k;

int score = 0;

void clear_map() {
	for(int i = 0; i < r+2; i++) {
		for(int j = 0; j < c; j++) {
			map[i][j] = 0;
		}
	}
}

void clear_visited() {
	for(int i = 0; i < r+2; i++) {
		for(int j = 0; j < c; j++) {
			visited[i][j] = 0;
		}
	}
}

bool check(int y, int x) {
	for(int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if(ny < 0) continue;
		if(map[ny][nx] != 0 || ny >= r+2 || nx >= c || nx < 0)
			return 0;
	}
	return 1;
}

void down(golem* g){
	while(1) {
		while(check(g->y, g->x)) {
			g->y++;
		}
		g->y--;

		// left roll
		g->x--;
		if(check(g->y, g->x)) {
			g->y++;
			if(check(g->y, g->x)) {
				g->dir = (g->dir + 3) % 4;
				continue;
			}
			g->y--;
		}
		g->x++;

		// right roll
		g->x++; 
		if(check(g->y, g->x)) {
			g->y++; 
			if(check(g->y, g->x)) {
				g->dir = (g->dir + 1) % 4;
				continue;
			}
			g->y--;
		}
		g->x--;

		break;
	}
}

void go() {
	queue<golem> q; // for bfs
	golem g = golems.front();
	golems.pop();
	
	down(&g);

	if(g.y < 3) {
		clear_map();
		return;
	}

	map[g.y][g.x] = g.id;
	for(int i = 0; i < 4; i++) {
		int ny = g.y + dy[i];
		int nx = g.x + dx[i];
		map[ny][nx] = g.id;
		if(i == g.dir) 
			map[ny][nx] = -1 * g.id;
	}

	clear_visited();
	int local_score = 0;
	q.push(g);
	while(!q.empty()) {
		golem tg = q.front();
		q.pop();
		visited[tg.y][tg.x] = 1;
		if(tg.y - 1 > local_score) { 
			local_score = tg.y - 1;
		}
		for(int i = 0; i < 4; i++) {
			golem ng;
			int ny = tg.y + dy[i];
			int nx = tg.x + dx[i];

			if(visited[ny][nx]) continue;
			if(ny < 0 || nx < 0 || ny >= r+2 || nx >= c) continue;
			if(map[ny][nx] != tg.id) {
				if(map[ny][nx] < 0 && -1 * map[ny][nx] == tg.id) {
					ng.y = ny; ng.x = nx; ng.id = map[ny][nx];
					q.push(ng);
					continue;
				}
				if(tg.id < 0) {
					if(map[ny][nx] != 0) {
						ng.y = ny; ng.x = nx; ng.id = map[ny][nx];
						q.push(ng);
						continue;
					}
				}
				continue;
			}

			ng.y = ny; ng.x = nx; ng.id = tg.id;
			q.push(ng);
		}
	}
	
	score += local_score;
}

int main() {
	cin >> r >> c >> k;
		
	int row, dir;
	for(int i = 0; i < k; i++) {
		cin >> row >> dir;
		golem g;
		g.id = i + 1;
		g.y = 0;
		g.x = row - 1;
		g.dir = dir;

		golems.push(g);
	}

	while(!golems.empty()){
		go();
	}

	cout << score << "\n";
	return 0;
}