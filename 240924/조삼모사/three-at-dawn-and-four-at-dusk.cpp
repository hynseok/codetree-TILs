use std::{cmp, io::{ BufRead, Write }, usize};

struct Stdin {
  stdin: std::io::BufReader<std::io::StdinLock<'static>>,
}

impl Stdin {
  fn new() -> Self {
    let stdin = std::io::stdin();
    let stdin = stdin.lock();
    let stdin = std::io::BufReader::new(stdin);
    
    Stdin { stdin }
  }

  fn read_line(&mut self) -> String {
    let mut input = String::new();
    self.stdin.read_line(&mut input).unwrap();

    input
  }
}

struct Stdout {
  stdout: std::io::BufWriter<std::io::StdoutLock<'static>>
}

impl Stdout {
  fn new() -> Self {
    let stdout = std::io::stdout();
    let stdout = stdout.lock();
    let stdout = std::io::BufWriter::new(stdout);

    Stdout { stdout }
  }

  fn writeln(&mut self, str: String) {
    writeln!(self.stdout, "{}", str).unwrap();
  }
}

fn next_permutation(nums: &mut [usize]) -> bool {
  let k = match (0..nums.len() - 1).rfind(|&i| nums[i] < nums[i + 1]) {
      Some(k) => k,
      None => {
          nums.reverse();
          return false;
      }
  };
  let l = (k + 1..nums.len()).rfind(|&i| nums[k] < nums[i]).unwrap();
  nums.swap(k, l);
  nums[k + 1..].reverse();

  true
}

fn main() {
  let mut stdin = Stdin::new();
  let mut stdout = Stdout::new();

  let n = stdin.read_line().trim().parse::<usize>().unwrap();
  let mut works: Vec<Vec<usize>> = vec![vec![0;21];21];

  for i in 0..n {
    let line = stdin.read_line();
    let mut j = 0;
    for word in line.split_whitespace() {
      let w = word.parse::<usize>().unwrap();
      works[i][j] = w;
      j += 1;
    }
  }

  let mut temp = Vec::<usize>::new();
  let mut element = Vec::<usize>::new();
  for _i in 0..n/2 {
    temp.push(0); 
  }
  for _i in 0..n/2 {
    temp.push(1);
  }
  for i in 0..n {
    element.push(i+1);
  }

  let mut diff = usize::MAX;

  loop {
    let mut morning = Vec::<usize>::new();
    let mut evening = Vec::<usize>::new();

    for i in 0..n {
      if temp[i] == 0 {
        morning.push(element[i]);
      } else {
        evening.push(element[i]);
      }
    }

    let mut morning_sum = 0;
    let mut evening_sum = 0;

    for i in 0..n/2 {
      for j in i+1..n/2 {
        morning_sum += works[morning[i]-1][morning[j]-1] + works[morning[j]-1][morning[i]-1];
        evening_sum += works[evening[i]-1][evening[j]-1] + works[evening[j]-1][evening[i]-1];
      }
    }

    diff = cmp::min(diff, cmp::max(morning_sum, evening_sum) - cmp::min(morning_sum,evening_sum));

    if !next_permutation(&mut temp) { break; }
  }

  stdout.writeln(diff.to_string());
}