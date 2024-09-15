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

fn roll(red: Pos, blue: Pos, dir: usize, map: &Vec<Vec<char>>) -> (Pos, Pos, usize) {
  let dy: Vec<i32> = vec![0, 1, 0, -1];
  let dx: Vec<i32> = vec![1, 0, -1, 0];

  let mut nred: Pos = red;
  let mut nblue: Pos = blue;

  let mut is_out: usize = 0;
  let mut other: bool = false;

  loop {
    let ny = (nred.y as i32 + dy[dir]) as usize;
    let nx = (nred.x as i32 + dx[dir]) as usize;

    if map[ny][nx] == '.' {
      if nblue.y == ny && nblue.x == nx {
        other = true;
      }
      nred.y = ny;
      nred.x = nx; 
    } else if map[ny][nx] == '#' {
      if other {
        nred.y = (nred.y as i32 - dy[dir]) as usize;
        nred.x = (nred.x as i32 - dx[dir]) as usize;
        break;
      } else {
        break;
      }
    } else if map[ny][nx] == 'O' {
      is_out += 1;
      break;
    }
  }

  other = false;

  loop {
    let ny = (nblue.y as i32 + dy[dir]) as usize;
    let nx = (nblue.x as i32 + dx[dir]) as usize;

    if map[ny][nx] == '.' {
      if nred.y == ny && nred.x == nx {
        other = true;
      }
      nblue.y = ny;
      nblue.x = nx; 
    } else if map[ny][nx] == '#' {
      if other {
        nblue.y = (nblue.y as i32 - dy[dir]) as usize;
        nblue.x = (nblue.x as i32 - dx[dir]) as usize;
        break;
      } else {
        break;
      }
    } else if map[ny][nx] == 'O' {
      is_out += 2;
      break;
    }
  }
  (nred, nblue, is_out)
}

fn main() {
  // scanner and writer
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  // matrix
  let mut map: Vec<Vec<char>> = vec![vec![' '; 10]; 10];

  // matrix size
  let n: usize = s.next::<usize>();
  let m: usize = s.next::<usize>();

  // red ball and blue ball positions
  let mut red: Pos = Pos { y: 0, x: 0 };
  let mut blue: Pos = Pos { y: 0, x: 0 };

  // get input
  for i in 0..n {
    let s: String = s.next_str();
    let bytes = s.as_bytes();
    for (j, b) in bytes.iter().enumerate() {
      let c: char = *b as char;
      map[i][j] = c;
      if c == 'R' {
        red = Pos { y: i, x: j };
        map[i][j] = '.';
      } else if c == 'B' {
        blue = Pos {y: i, x: j};
        map[i][j] = '.';
      }
    }
  }

  let mut queue: VecDeque<(Pos, Pos, usize)> = VecDeque::from([(red, blue, 0)]);
  let mut flag: bool = false;

  while !queue.is_empty() {
    let (red, blue, turn) = queue.pop_front().unwrap();
    if turn == 10 {
      continue;
    }
    
    for i in 0..4 {
      let (nred, nblue, is_out) = roll(red, blue, i, &map);
      if is_out == 0 {
        queue.push_back((nred, nblue, turn+1));
      } else if is_out == 1 {
        w.write((turn+1).to_string());
        flag = true;
        break;
      }
    }

    if flag {
      break;
    }
  }
  if !flag {
    w.write("-1".to_string());
  }
  w.print_out();
}