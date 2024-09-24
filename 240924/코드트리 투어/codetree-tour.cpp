use std::io::{Write, BufRead};
use std::collections::BinaryHeap;

struct Stdin {
  stdin: std::io::BufReader<std::io::StdinLock<'static>>,
}

impl Stdin {
  fn new() -> Self {
    let stdin = std::io::stdin();
    let stdin = stdin.lock();
    let stdin = std::io::BufReader::new(stdin);
    
    Stdin {
      stdin: stdin
    }
  }

  fn read_line(&mut self) -> String {
    let mut input = String::new();
    self.stdin.read_line(&mut input).unwrap();

    input
  }
}

#[derive(Eq, PartialEq)]
struct Travel {
  id: usize,
  profit: i64,
  revenue: usize,
  dest: usize
}

impl Ord for Travel {
  fn cmp(&self, other: &Self) -> std::cmp::Ordering {
    self.profit.cmp(&other.profit)
    .then_with(|| other.id.cmp(&self.id))
  }
}

impl PartialOrd for Travel {
  fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
    Some(self.cmp(other))
  }
}

#[derive(Eq, PartialEq)]
struct State {
  position: usize,
  cost: usize,
}

impl Ord for State {
  fn cmp(&self, other: &Self) -> std::cmp::Ordering {
    other.cost.cmp(&self.cost)
    .then_with(|| self.position.cmp(&other.position))
  }
}

impl PartialOrd for State {
  fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
    Some(self.cmp(other))
  }
}

struct Edge {
  dest: usize,
  cost: usize
}

impl Edge {
  fn new(dest: usize, cost: usize) -> Self {
    Edge { dest, cost }
  }
}

fn shortest_path(edges: &Vec<Vec<Edge>>, start: usize) -> Vec<usize> {
  let mut dist: Vec<usize> = (0..edges.len()).map(|_| usize::MAX).collect();

  let mut heap = BinaryHeap::new();

  dist[start] = 0;
  heap.push(State { cost: 0, position: start });
  while let Some(State{ cost, position }) = heap.pop() {
    if cost > dist[position] { continue; }
    for edge in &edges[position] {
      let next = State { cost: cost + edge.cost, position: edge.dest };
      
      if next.cost < dist[next.position] {
        dist[next.position] = next.cost;
        heap.push(next);
      } 
    }
  }

  dist
}

fn main() {
  let mut stdin = Stdin::new();
  let stdout = std::io::stdout();
  let stdout = stdout.lock();
  let mut stdout = std::io::BufWriter::new(stdout);
  
  let q = stdin.read_line().trim().parse::<usize>().unwrap();
  let mut edges: Vec<Vec<Edge>> = Vec::new();
  let mut costs: Vec<usize> = Vec::new();

  let mut is_made: Vec<bool> = vec![false;30001];
  let mut is_cancel: Vec<bool> = vec![false;30001];

  let mut travels_heap: BinaryHeap<Travel> = BinaryHeap::new();

  for _i in 0..q {
    let line = stdin.read_line();
    let mut command = Vec::<usize>::new();

    for word in line.split_whitespace() {
      command.push(word.parse::<usize>().ok().unwrap()); 
    }
      
    match command[0] {
      100 => {
        let n = command[1];
        let m = command[2];

        for _i in 0..n {
          edges.push(Vec::new());
        }
        for i in 0..m {
          let src = command[3*(i+1)];
          let dest = command[3*(i+1)+1];
          let cost = command[3*(i+1)+2];
          edges[src].push(Edge::new(dest, cost));
          edges[dest].push(Edge::new(src, cost));
        }

        costs = shortest_path(&edges, 0);
      },
      200 => {
        let id = command[1];
        let revenue = command[2];
        let dest = command[3];
        let mut profit: i64 = 0;
        if revenue < costs[dest] || costs[dest] == usize::MAX {
          profit = -1
        } else {
          profit = (revenue - costs[dest]) as i64;
        }

        is_made[id] = true;
        travels_heap.push(Travel{id, profit, revenue, dest});
      },
      300 => {
        let id = command[1];
        if is_made[id] {
          is_cancel[id] = true;
        }
      },
      400 => {
        let mut success = false;
        while !travels_heap.is_empty() {
          let travel = travels_heap.peek().unwrap();
          if travel.profit == -1 {
            writeln!(stdout, "{}", "-1").unwrap();
            success = true;
            break;
          }
          let travel = travels_heap.pop().unwrap();
          if !is_cancel[travel.id] {
            writeln!(stdout, "{}", travel.id).unwrap();
            success = true;
            break;
          }
        }
        if !success {
          writeln!(stdout, "{}", "-1").unwrap();
        }
      },
      500 => {
        let new = command[1];
        let temp_vec: Vec<Travel> = travels_heap.drain().collect();

        costs = shortest_path(&edges, new);

        for travel in temp_vec {
          let mut profit: i64 = 0;
          if travel.revenue < costs[travel.dest] || costs[travel.dest] == usize::MAX {
            profit = -1
          } else {
            profit = (travel.revenue - costs[travel.dest]) as i64;
          }
          travels_heap.push(
            Travel{id: travel.id, revenue:travel.revenue, profit, dest: travel.dest}
          );
        }
      },
      _ => {

      }
    }

  }
}