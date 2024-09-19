#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;
use std::io::*;
use std::fmt::Write;

struct Scanner {
  buffer: std::collections::VecDeque<String>
}

impl Scanner {
  fn new() -> Scanner {
    Scanner {
      buffer: std::collections::VecDeque::new()
    }
  }
 
  fn next<T : std::str::FromStr >(&mut self) -> T {
    if self.buffer.len() == 0 {
      let mut input = String::new();
      std::io::stdin().read_line(&mut input).ok();
      for word in input.split_whitespace() {
        self.buffer.push_back(word.to_string())
      }
    }

    let front = self.buffer.pop_front().unwrap();
    front.parse::<T>().ok().unwrap()
  }

  fn next_str(&mut self) -> String {
    if self.buffer.len() == 0 {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).ok();
        for word in input.split_whitespace() {
        self.buffer.push_back(word.to_string())
      }
    }
    self.buffer.pop_front().unwrap()
  }
}

struct Writer {
  output: String 
}

impl Writer {
  fn new() -> Writer {
    Writer {
      output: String::new()
    }
  }

  fn write(&mut self, str: String) {
      writeln!(self.output, "{}", str).unwrap();
  }

  fn print_out(&mut self) {
    println!("{}",self.output);
  }
}

#[derive(Debug, Clone, Copy)]
struct Pos {
  y: usize,
  x: usize
}

fn get_count(map: &mut Vec<Vec<usize>>, queue: &VecDeque<Pos>, n: &usize, m: &usize) -> usize {
  let mut cnt: usize = 0;

  let dy: Vec<i32> = vec![0, 1, 0, -1];
  let dx: Vec<i32> = vec![1, 0, -1, 0];

  let mut visited = vec![vec![0;*m];*n];

  let mut copymap: Vec<Vec<usize>> = map.clone();
  let mut copyqueue: VecDeque<Pos> = queue.clone();

  // bfs
  while !copyqueue.is_empty() {
    let now = copyqueue.pop_front().unwrap();
    for i in 0..4 {
      let ny = now.y as i32 + dy[i];
      let nx = now.x as i32 + dx[i];

      if ny >= *n as i32 || ny < 0 || nx >= *m as i32 || nx < 0 {
        continue;
      } 

      let ny = ny as usize;
      let nx = nx as usize;

      if copymap[ny][nx] == 0 && visited[ny][nx] == 0 {
        visited[ny][nx] = 1;
        copymap[ny][nx] = 2;
        copyqueue.push_back(Pos { y: ny, x: nx });
      }
    }
  }

  for i in 0..*n {
    for j in 0..*m {
      if copymap[i][j] == 0 {
        cnt += 1;
      }
    }
  }

  cnt
}


fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let n: usize = s.next();
  let m: usize = s.next();
  
  let mut map: Vec<Vec<usize>> = vec![vec![0;8];8];
  let mut queue: VecDeque<Pos> = VecDeque::new();

  let mut ans: usize = 0;

  for i in 0..n {
    for j in 0..m {
      map[i][j] = s.next();
      if map[i][j] == 2 {
        queue.push_back(Pos{ y: i, x: j });
      }
    }
  }

  // 벽 세개를 선택. worst case time : ~64C3
  for i1 in 0..n {
    for j1 in 0..m {
      if map[i1][j1] == 1 || map[i1][j1] == 2 {
        continue;
      }
      for i2 in 0..n {
        for j2 in 0..m {
          if map[i2][j2] == 1 || map[i2][j2] == 2 {
            continue;
          }
          for i3 in 0..n {
            for j3 in 0..m {
              if map[i3][j3] == 1 || map[i3][j3] == 2 {
                continue;
              }
              if (i1 == i2 && j1 == j2) || (i2 == i3 && j2 == j3) || (i3 == i1 && j3 == j1) {
                continue;
              }
              
              map[i1][j1] = 1;
              map[i2][j2] = 1;
              map[i3][j3] = 1;

              ans = max(ans, get_count(&mut map, &queue, &n, &m));

              map[i1][j1] = 0;
              map[i2][j2] = 0;
              map[i3][j3] = 0;
            }
          }
        }
      }
    }
  }

  w.write(ans.to_string());
  w.print_out();
}