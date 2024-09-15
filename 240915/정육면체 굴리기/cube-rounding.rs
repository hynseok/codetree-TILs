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

#[derive(Debug, Copy, Clone)]
struct Cube {
  top: usize,
  bottom: usize,
  left: usize,
  right: usize,
  front: usize,
  back: usize,

  pos: Pos
}
impl Cube {
  fn new(pos: Pos) -> Self{
    Self { top: 0, bottom: 0, left: 0, right: 0, front: 0, back: 0, pos: pos }
  }

  fn roll_right(&mut self) {
    let temp = self.top;
    self.top = self.left;
    self.left = self.bottom;
    self.bottom = self.right;
    self.right = temp;
  }
  fn roll_left(&mut self) {
    let temp = self.top;
    self.top = self.right;
    self.right = self.bottom;
    self.bottom = self.left;
    self.left = temp;
  }
  fn roll_up(&mut self) {
    let temp = self.top;
    self.top = self.front;
    self.front = self.bottom;
    self.bottom = self.back;
    self.back = temp;
  }
  fn roll_down(&mut self) {
    let temp = self.top;
    self.top = self.back;
    self.back = self.bottom;
    self.bottom = self.front;
    self.front = temp;
  }
}

fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let dy: Vec<i32> = vec![0,0,-1,1];
  let dx: Vec<i32> = vec![1,-1,0,0];

  let n: usize = s.next::<usize>();
  let m: usize = s.next::<usize>();

  let start: Pos = Pos { y: s.next::<usize>(), x: s.next::<usize>() };
  
  let nq: usize = s.next::<usize>();

  let mut map: Vec<Vec<usize>> = vec![vec![0;20];20];

  let mut cube: Cube = Cube::new(start);

  for i in 0..n {
    for j in 0..m {
      map[i][j] = s.next::<usize>();
    }
  }

  for _i in 0..nq {
    let q = s.next::<usize>();

    let ny: i32 = cube.pos.y as i32 + dy[q-1];
    let nx: i32 = cube.pos.x as i32 + dx[q-1];

    if ny < 0 || ny >= n as i32 || nx < 0 || nx >= m as i32 {
      continue;
    }

    cube.pos.y = ny as usize;
    cube.pos.x = nx as usize;
    
    match q {
      1 => {
        cube.roll_right();
      },
      2 => {
        cube.roll_left();
      },
      3 => {
        cube.roll_up();
      },
      4 => {
        cube.roll_down();
      },
      _ => {
      }
    }
    
    if map[cube.pos.y][cube.pos.x] == 0 {
      map[cube.pos.y][cube.pos.x] = cube.bottom;
    } else {
      cube.bottom = map[cube.pos.y][cube.pos.x];
      map[cube.pos.y][cube.pos.x] = 0;
    }
    w.write(cube.top.to_string());
  }

  w.print_out();
}