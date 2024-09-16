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

#[derive(Debug, Copy, Clone)]
struct Pos {
  y: usize,
  x: usize
}

fn stick(pivot: Pos, map: &Vec<Vec<usize>>) -> usize {
  let h: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let i: Pos = Pos {y: pivot.y + 2, x: pivot.x};
  let j: Pos = Pos {y: pivot.y + 3, x: pivot.x};

  let k: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let l: Pos = Pos {y: pivot.y, x: pivot.x + 2};
  let m: Pos = Pos {y: pivot.y, x: pivot.x + 3};

  map[pivot.y][pivot.x] + max(map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x], map[h.y][h.x] + map[i.y][i.x] + map[j.y][j.x])
}

fn l(pivot: Pos, map: &Vec<Vec<usize>>) -> usize {
  let mut k1: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let mut l1: Pos = Pos {y: pivot.y + 2, x: pivot.x};
  let mut m1: Pos = Pos {y: pivot.y + 2, x: pivot.x + 1};

  let mut k2: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let mut l2: Pos = Pos {y: pivot.y, x: pivot.x + 2};
  let mut m2: Pos = Pos {y: pivot.y + 1, x: pivot.x + 2};
  
  let k3: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let l3: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let m3: Pos = Pos {y: pivot.y + 2, x: pivot.x + 1};

  let k4: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let l4: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let m4: Pos = Pos {y: pivot.y, x: pivot.x + 2};

  let k5: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let l5: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let m5: Pos = Pos {y: pivot.y + 2, x: pivot.x};

  let k6: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let l6: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let m6: Pos = Pos {y: pivot.y + 1, x: pivot.x + 2};

  let first = max(max(max(max( max( map[pivot.y][pivot.x] + map[k1.y][k1.x] + map[l1.y][l1.x] + map[m1.y][m1.x],
                                  map[pivot.y][pivot.x] + map[k2.y][k2.x] + map[l2.y][l2.x] + map[m2.y][m2.x]),
                          map[pivot.y][pivot.x] + map[k3.y][k3.x] + map[l3.y][l3.x] + map[m3.y][m3.x]),
                  map[pivot.y][pivot.x] + map[k4.y][k4.x] + map[l4.y][l4.x] + map[m4.y][m4.x]),
              map[pivot.y][pivot.x] + map[k5.y][k5.x] + map[l5.y][l5.x] + map[m5.y][m5.x]),
          map[pivot.y][pivot.x] + map[k6.y][k6.x] + map[l6.y][l6.x] + map[m6.y][m6.x]);

  if pivot.x > 0 {
    k1 = Pos {y: pivot.y + 1, x: pivot.x};
    l1 = Pos {y: pivot.y + 2, x: pivot.x};
    m1 = Pos {y: pivot.y + 2, x: pivot.x - 1};
  }
  if pivot.y > 0 {
    k2 = Pos {y: pivot.y, x: pivot.x + 1};
    l2 = Pos {y: pivot.y, x: pivot.x + 2};
    m2 = Pos {y: pivot.y - 1, x: pivot.x + 2};
  }
  let second = max(max(first,
                       map[pivot.y][pivot.x] + map[k2.y][k2.x] + map[l2.y][l2.x] + map[m2.y][m2.x]),
                   map[pivot.y][pivot.x] + map[k1.y][k1.x] + map[l1.y][l1.x] + map[m1.y][m1.x]);
  
  second
}

fn square(pivot: Pos, map: &Vec<Vec<usize>>) -> usize {
  let k: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let l: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let m: Pos = Pos {y: pivot.y, x: pivot.x + 1};

  map[pivot.y][pivot.x] + map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x]
}

fn stair(pivot: Pos, map: &Vec<Vec<usize>>) -> usize {
  let mut k: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let mut l: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let mut m: Pos = Pos {y: pivot.y + 2, x: pivot.x + 1};

  let mut h: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let mut i: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let mut j: Pos = Pos {y: pivot.y + 1, x: pivot.x + 2};

  let first = max(map[pivot.y][pivot.x] + map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x],
                      map[pivot.y][pivot.x] + map[h.y][h.x] + map[i.y][i.x] + map[j.y][j.x]);
  
  if pivot.y > 0 {
    k = Pos {y: pivot.y - 1, x: pivot.x + 2};
    l = Pos {y: pivot.y - 1, x: pivot.x + 1};
    m = Pos {y: pivot.y, x: pivot.x + 1};

    h = Pos {y: pivot.y, x: pivot.x + 1};
    i = Pos {y: pivot.y + 1, x: pivot.x};
    j = Pos {y: pivot.y - 1, x: pivot.x + 1};
  }
  let second = max(first, max(map[pivot.y][pivot.x] + map[h.y][h.x] + map[i.y][i.x] + map[j.y][j.x],
                             map[pivot.y][pivot.x] + map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x]));

  second
}

fn ah(pivot: Pos, map: &Vec<Vec<usize>>) -> usize {
  let mut k: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let mut l: Pos = Pos {y: pivot.y + 1, x: pivot.x};
  let mut m: Pos = Pos {y: pivot.y + 2, x: pivot.x};

  let mut h: Pos = Pos {y: pivot.y, x: pivot.x + 1};
  let mut i: Pos = Pos {y: pivot.y + 1, x: pivot.x + 1};
  let mut j: Pos = Pos {y: pivot.y, x: pivot.x + 2};

  let first = max(map[pivot.y][pivot.x] + map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x],
                  map[pivot.y][pivot.x] + map[h.y][h.x] + map[i.y][i.x] + map[j.y][j.x]);

  if pivot.y > 0 {
    k = Pos {y: pivot.y - 1, x: pivot.x + 1};
    l = Pos {y: pivot.y + 1, x: pivot.x + 1};
    m = Pos {y: pivot.y, x: pivot.x + 1};

    h = Pos {y: pivot.y, x: pivot.x + 1};
    i = Pos {y: pivot.y, x: pivot.x + 2};
    j = Pos {y: pivot.y - 1, x: pivot.x + 1};
  }

  let second = max(first, max(map[pivot.y][pivot.x] + map[h.y][h.x] + map[i.y][i.x] + map[j.y][j.x],
                             map[pivot.y][pivot.x] + map[k.y][k.x] + map[l.y][l.x] + map[m.y][m.x]));

  second
}

fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let mut map: Vec<Vec<usize>> = vec![vec![0;203];203];

  let n: usize = s.next::<usize>();
  let m: usize = s.next::<usize>();
  
  for i in 0..n {
    for j in 0..m {
      map[i][j] = s.next::<usize>();
    }
  }

  let mut ans: usize = 0;
  for i in 0..n {
    for j in 0..m {
      let pos: Pos = Pos{y:i, x:j};
      let functions = vec![
        ans,
        stick(pos, &map),
        l(pos, &map),
        square(pos, &map),
        stair(pos, &map),
        ah(pos, &map),
      ];
      ans = functions.into_iter().fold(0, |acc, x| max(acc, x));
    }
  }
  
  w.write(ans.to_string());
  w.print_out();
}