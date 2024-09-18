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

#[derive(Debug, Clone)]
struct Car {
  pos: Pos,
  dir: usize, // 0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽
  visited: Vec<Vec<usize>>,
  cnt: usize
}

impl Car {
  fn new() -> Self {
    Car { pos: Pos { y: 0, x: 0}, 
          dir: 0,
          visited: vec![vec![0;51];51],
          cnt: 0
        }
  }

  fn go(&mut self, map: &Vec<Vec<usize>>) {
    let dy: Vec<i32> = vec![-1, 0, 1, 0];
    let dx: Vec<i32> = vec![0, 1, 0, -1];

    for i in 1..5 {
      let mut dir = self.dir as i32 - i as i32;
      if dir < 0 {
        dir += 4;
      }

      let ny = (self.pos.y as i32 + dy[dir as usize]) as usize;
      let nx = (self.pos.x as i32 + dx[dir as usize]) as usize;

      if map[ny][nx] == 1 || self.visited[ny][nx] == 1 {
        if i == 4 {
          let mut back = dir + 2;
          if back > 3 {
            back -= 4;
          }

          let by = (self.pos.y as i32 + dy[back as usize]) as usize;
          let bx = (self.pos.x as i32 + dx[back as usize]) as usize;

          if map[by][bx] == 1 {
            return;
          }

          self.dir = dir as usize;
          self.pos = Pos { y: by, x: bx };
          self.go(map);
          return;
        }
        continue;
      }
      
      self.visited[ny][nx] = 1;
      self.dir = dir as usize;
      self.pos = Pos { y: ny, x: nx };
      self.cnt += 1;
      self.go(map);
    }
  }
}

fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let n: usize = s.next();
  let m: usize = s.next();
  
  let mut map: Vec<Vec<usize>> = vec![vec![0;51];51];
  let mut car: Car = Car::new();

  car.pos.y = s.next();
  car.pos.x = s.next();
  car.dir = s.next();
  car.cnt = 1;
  car.visited[car.pos.y][car.pos.x] = 1;

  for i in 0..n {
    for j in 0..m {
      map[i][j] = s.next();
    }
  }

  car.go(&map);

  w.write(car.cnt.to_string());
  w.print_out();
}