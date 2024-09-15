#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;
use std::i32::MAX;
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

fn move_dir(direction: usize, n: usize, mut map: &mut Vec<Vec<i32>>) {
  let dir: [[i32;2];4] = [[-1,0],[0,1],[1,0],[0,-1]];
  let mut q: VecDeque<i32> = VecDeque::new();

  if direction == 0 {
    for j in 0..n {
      for i in 0..n {
        if map[i][j] != 0 {
          q.push_back(map[i][j]);
        }
        map[i][j] = 0;
      }
      let mut idx = 0;
      while !q.is_empty() {
        let val = q.pop_front().unwrap();
        if map[idx][j] == 0 {
          map[idx][j] = val;
        } else if map[idx][j] == val {
          map[idx][j] *= 2;
          idx += 1;
        } else {
          idx += 1;
          map[idx][j] = val;
        }
      }
    }
  } else if direction == 1 {
    for i in 0..n {
      let mut j = n-1;
      while j > 0 {
        if map[i][j] != 0 {
          q.push_back(map[i][j]);
        }
        map[i][j] = 0;
        j -= 1;
      }
      if map[i][j] != 0 {
        q.push_back(map[i][j]);
      }
      map[i][j] = 0;
      let mut idx = n-1;
      while !q.is_empty() {
        let val = q.pop_front().unwrap();
        if map[i][idx] == 0 {
          map[i][idx] = val;
        } else if map[i][idx] == val {
          map[i][idx] *= 2;
          idx -= 1;
        } else {
          idx -= 1;
          map[i][idx] = val;
        }
      }
    }
  } else if direction == 2 {
    for j in 0..n {
      let mut i = n-1;
      while i > 0 {
        if map[i][j] != 0 {
          q.push_back(map[i][j]);
        }
        map[i][j] = 0;
        i -= 1;
      }
      if map[i][j] != 0 {
        q.push_back(map[i][j]);
      }
      map[i][j] = 0;
      let mut idx = n-1;
      while !q.is_empty() {
        let val = q.pop_front().unwrap();
        if map[idx][j] == 0 {
          map[idx][j] = val;
        } else if map[idx][j] == val {
          map[idx][j] *= 2;
          idx -= 1;
        } else {
          idx -= 1;
          map[idx][j] = val;
        }
      }
    }
  } else {
    for i in 0..n {
      for j in 0..n {
        if map[i][j] != 0 {
          q.push_back(map[i][j]);
        }
        map[i][j] = 0;
      }
      let mut idx = 0;
      while !q.is_empty() {
        let val = q.pop_front().unwrap();
        if map[i][idx] == 0 {
          map[i][idx] = val;
        } else if map[i][idx] == val {
          map[i][idx] *= 2;
          idx += 1;
        } else {
          idx += 1;
          map[i][idx] = val;
        }
      }
    }
  }
}

fn dfs(cnt: i32, mut ans: &mut i32, n: usize, mut map: &mut Vec<Vec<i32>>) {
  if cnt == 5 {
    for i in 0..n {
      for j in 0..n {
        *ans = max(*ans, map[i][j]);
      }
    }
    return
  }

  let mut copymap: Vec<Vec<i32>> = vec![vec![0;20];20];

  for i in 0..n {
    for j in 0..n {
      copymap[i][j] = map[i][j];
    }
  }

  for i in 0..4 {
    move_dir(i, n, map);
    dfs(cnt+1, ans, n, map);

    for i in 0..n {
      for j in 0..n {
        map[i][j] = copymap[i][j]; 
      }
    }
  }
}

fn main() {
  let mut map: Vec<Vec<i32>> = vec![vec![0; 20]; 20];
  let mut s = Scanner::new();
  let mut w = Writer::new();
  let mut ans = 0;

  let n: usize = s.next();
  for i in 0..n {
    for j in 0..n {
      map[i][j] = s.next();
    }
  }
  
  dfs(0, &mut ans, n, &mut map);

  w.write(ans.to_string());
  w.print_out();
}