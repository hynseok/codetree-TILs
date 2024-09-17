#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;
use std::io::*;
use std::fmt::Write;
use std::usize;

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
struct Job {
  time: usize,
  pay: usize
}

fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let n: usize = s.next();

  let mut dp: Vec<usize> = vec![0;16];
  let mut job_info: Vec<Job> = Vec::new();
  
  for i in 0..n {
    let t = s.next::<usize>();
    let p = s.next::<usize>();
    
    job_info.push(Job {time: t, pay: p});
  }

  for i in (0..n).rev() {
    if i + job_info[i].time <= n {
      dp[i] = max(dp[i + job_info[i].time] + job_info[i].pay, dp[i+1])
    } else {
      dp[i] = dp[i+1];
    }
  }
  w.write(dp[0].to_string());
  w.print_out();
}