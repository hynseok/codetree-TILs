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
  begin: usize,
  end: usize,
  pay: usize
}

fn dfs(n: usize, mut pay: usize, max_pay: &mut usize, now: Job, info: &Vec<Job>) {
  if now.end > n+1 {
    return;
  }
  *max_pay = max(*max_pay, pay);
  if now.end == n+1 {
    return;
  }

  for i in now.begin..n {
    if now.end <= info[i].begin {
      pay += info[i].pay;
      dfs(n, pay, max_pay, info[i], info);
      pay -= info[i].pay;
    }
  }
}

fn main() {
  let mut s = Scanner::new();
  let mut w = Writer::new();    
  
  let n: usize = s.next();

  let mut job_info: Vec<Job> = Vec::new();
  
  for i in 0..n {
    let t = s.next::<usize>();
    let p = s.next::<usize>();
    
    job_info.push(Job {begin: i + 1, end: i + t + 1, pay: p});
  }

  let mut max_pay: usize = 0;
  let dummy_job: Job = Job{ begin: 0, end: 0, pay: 0 };
  dfs(n, 0, &mut max_pay, dummy_job, &job_info);

  w.write(max_pay.to_string());
  w.print_out();
}