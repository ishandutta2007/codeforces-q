pub mod solution {
//{"name":"H. ","group":"Codeforces - Deltix Round, Summer 2021 (open for everyone, rated, Div. 1 + Div. 2)","url":"https://codeforces.com/contest/1556/problem/H?locale=ru","interactive":false,"timeLimit":6000,"tests":[{"input":"10 5\n5 3 4 2 1\n29 49 33 12 55 15 32 62 37\n61 26 15 58 15 22 8 58\n37 16 9 39 20 14 58\n10 15 40 3 19 55\n53 13 37 44 52\n23 59 58 4\n69 80 29\n89 28\n48\n","output":"95\n"}],"testType":"single","input":{"type":"stdin","fileName":null,"pattern":null},"output":{"type":"stdout","fileName":null,"pattern":null},"languages":{"java":{"taskClass":"HKonstruktor"}}}

use std::time::Instant;

use crate::algo_lib::collections::array_2d::Array2D;
use crate::algo_lib::collections::index_of::IndexOf;
use crate::algo_lib::collections::peek_random::PeekRandom;
use crate::algo_lib::graph::dsu::Dsu;
use crate::algo_lib::io::output::output;
use crate::algo_lib::io::output::set_global_output_to_file;
use crate::algo_lib::io::task_io_settings::TaskIoType;
use crate::algo_lib::io::task_runner::run_task;
use crate::algo_lib::io::input::Input;
use crate::algo_lib::io::task_io_settings::TaskIoSettings;
use crate::algo_lib::misc::gen_vector::gen_vec;
use crate::algo_lib::misc::min_max::UpdateMinMax;
use crate::algo_lib::misc::rand::Random;
use crate::algo_lib::misc::simulated_annealing::SearchFor;
use crate::algo_lib::misc::simulated_annealing::SimulatedAnnealing;
#[allow(unused)]
use crate::dbg;
use crate::out;
use crate::out_line;
// use marathon_utils::dynamic_plot::DynamicPlot;
// use marathon_utils::html_report::HtmlReport;

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
struct Edge {
    cost: i32,
    fr: usize,
    to: usize,
}

fn solve_test(n: usize, mut edges: Vec<Edge>, max_d: &[usize]) -> i32 {
    let mut dsu = Dsu::new(n);
    edges.sort();
    let mut interesting_edges = vec![];
    let checked = max_d.len();
    for edge in edges.iter() {
        if edge.fr < checked || edge.to < checked {
            interesting_edges.push(edge);
        } else if dsu.get(edge.fr) != dsu.get(edge.to) {
            dsu.unite(edge.fr, edge.to);
            interesting_edges.push(edge);
        }
    }
    let mut edges = interesting_edges;
    let mut res = i32::MAX;
    let mut additional_cost = vec![0; n];
    let mut rnd = Random::new(787788);
    let start = Instant::now();
    let mut free_deg = vec![0; n];
    while start.elapsed().as_millis() < 60 {
        let max_add = rnd.gen_in_range(1..100);
        for i in 0..checked {
            additional_cost[i] = rnd.gen_in_range(0..max_add);
            free_deg[i] = max_d[i];
        }
        for i in checked..n {
            free_deg[i] = n;
        }
        edges.sort_by_key(|edge| edge.cost + additional_cost[edge.fr] + additional_cost[edge.to]);
        dsu.clear();
        let mut cur_cost = 0;
        for edge in edges.iter() {
            if dsu.get(edge.fr) != dsu.get(edge.to)
                && free_deg[edge.fr] > 0
                && free_deg[edge.to] > 0
            {
                free_deg[edge.fr] -= 1;
                free_deg[edge.to] -= 1;
                dsu.unite(edge.fr, edge.to);
                cur_cost += edge.cost;
            }
        }
        if dsu.num_components() != 1 {
            cur_cost += (dsu.num_components() as i32) * 100_000;
        }
        res.update_min(cur_cost);
    }
    res
}

struct Scorer {
    cur_cost: i32,
    used_edges: Vec<Edge>,
    free_deg: Vec<usize>,
    dsu: Dsu,
}

impl Scorer {
    pub fn new(free_deg: Vec<usize>) -> Self {
        let dsu = Dsu::new(free_deg.len());
        Self {
            cur_cost: 0,
            used_edges: vec![],
            free_deg,
            dsu,
        }
    }

    pub fn remove_edge(&mut self, edge: Edge) {
        let idx = self.used_edges.index_of(&edge).unwrap();
        self.free_deg[edge.fr] += 1;
        self.free_deg[edge.to] += 1;
        self.cur_cost -= edge.cost;
        self.used_edges.swap_remove(idx);
        self.dsu.clear();
        for e in self.used_edges.iter() {
            self.dsu.unite(e.fr, e.to);
        }
    }

    pub fn remove_random_edge(&mut self, rnd: &mut Random) -> Edge {
        let idx = rnd.gen_in_range(0..self.used_edges.len());
        let edge = self.used_edges[idx];
        self.remove_edge(edge);
        edge
    }

    pub fn add_edge(&mut self, e: Edge) -> bool {
        if self.dsu.get(e.fr) == self.dsu.get(e.to)
            || self.free_deg[e.fr] == 0
            || self.free_deg[e.to] == 0
        {
            false
        } else {
            self.free_deg[e.fr] -= 1;
            self.free_deg[e.to] -= 1;
            self.cur_cost += e.cost;
            self.used_edges.push(e);
            self.dsu.unite(e.fr, e.to);
            true
        }
    }
}

fn solve_sa(n: usize, mut edges: Vec<Edge>, max_d: &[usize], max_time: f64) -> i32 {
    let mut dsu = Dsu::new(n);
    edges.sort();
    let mut interesting_edges = vec![];
    let checked = max_d.len();
    for edge in edges.iter() {
        if edge.fr < checked || edge.to < checked || edge.to == n - 1 || true {
            interesting_edges.push(edge);
        } else if dsu.get(edge.fr) != dsu.get(edge.to) {
            dsu.unite(edge.fr, edge.to);
            interesting_edges.push(edge);
        }
    }
    let edges = interesting_edges;
    // assert!(interesting_edges.len() <= n * (max_d.len() + 1));
    let mut res = i32::MAX;
    let mut rnd = Random::new(787788);
    let mut free_deg = vec![n; n];
    for i in 0..checked {
        free_deg[i] = max_d[i];
    }
    let mut scorer = Scorer::new(free_deg);
    for &e in edges.iter() {
        if e.to == n - 1 || e.fr == n - 1 {
            assert!(scorer.add_edge(*e));
        }
    }
    assert_eq!(scorer.dsu.num_components(), 1);
    // let mut html = HtmlReport::new("outputs".to_owned(), "index");
    // let mut plot = DynamicPlot::new("score", "time (ms)", "score");
    let mut sa = SimulatedAnnealing::new(max_time, SearchFor::MinimumScore, 100.0, 0.1);
    while sa.should_continue() {
        // plot.add_point(sa.elapsed_ms(), scorer.cur_cost);
        res.update_min(scorer.cur_cost);
        let prev_score = scorer.cur_cost;
        let e_to_remove = scorer.remove_random_edge(&mut rnd);
        loop {
            let e_to_add = **edges.peek_random(&mut rnd).unwrap();
            if scorer.add_edge(e_to_add) {
                if !sa.should_go(prev_score, scorer.cur_cost) {
                    scorer.remove_edge(e_to_add);
                    assert!(scorer.add_edge(e_to_remove));
                }
                break;
            }
        }
        assert_eq!(scorer.dsu.num_components(), 1);
    }
    // html.add_dynamic_plot(plot);
    // html.save().unwrap();
    res
}

fn solve(input: &mut Input, _test_case: usize) {
    let n = input.usize();
    let k = input.usize();
    let max_d = input.vec::<usize>(k);
    let mut edges = vec![];
    for i in 0..n {
        for j in i + 1..n {
            let cost = input.i32();
            edges.push(Edge { fr: i, to: j, cost });
        }
    }
    let res = solve_test(n, edges.clone(), &max_d);
    out_line!(res);
}

pub(crate) fn run(mut input: Input) -> bool {
    solve(&mut input, 1);
    output().flush();
    input.skip_whitespace();
    input.peek().is_none()
}

#[allow(unused)]
pub fn submit() -> bool {
    let io = TaskIoSettings {
        is_interactive: false,
        input: TaskIoType::Std,
        output: TaskIoType::Std,
    };

    run_task(io, run)
}

/*
fn stress() {
    for it in 82.. {
        dbg!(it);
        let mut rnd = Random::new(7 + it);
        let n = 50; //rnd.gen_in_range(2..50);
        let mut edges = vec![];
        for i in 0..n {
            for j in i + 1..n {
                edges.push(Edge {
                    fr: i,
                    to: j,
                    cost: rnd.gen_in_range(1..100),
                });
            }
        }
        let d_len = 5; //rnd.gen_in_range(1..min(n, 6));
        let max_d = rnd.gen_vec(d_len, 1..n);
        let res = solve_test(n, edges.clone(), &max_d);
        let res_sa = solve_sa(n, edges, &max_d);
        assert_eq!(res_sa, res);
    }
}

*/

#[allow(unused)]
fn stress2() {
    for it in 51331.. {
        dbg!(it);
        let mut rnd = Random::new(7 + it);
        let n = 50; //rnd.gen_in_range(2..50);

        let mut d = Array2D::new(100, n, n);
        let mx = rnd.gen_in_range(2..80);
        dbg!(mx);
        for i in 0..n {
            for j in i + 1..n {
                d[i][j] = rnd.gen_in_range(1..mx);
            }
        }
        let max_d = gen_vec(N, |_| rnd.gen_in_range(1..20));
        let mx_balance = rnd.gen_in_range(5..20);
        let balance = gen_vec(n, |_| rnd.gen_in_range(3..mx_balance));
        dbg!(balance);
        const N: usize = 5;
        for x in 0..N {
            for y in x + 1..N {
                d[x][y] = rnd.gen_in_range(1..mx);
            }
            for y in N..n {
                let add = if rnd.gen_in_range(0..N / max_d[x] + 1) == 0 {
                    0
                } else {
                    1
                };
                d[x][y] = balance[y] + add;
            }
        }

        set_global_output_to_file("test.txt");
        out_line!(n, N);
        let mut edges = vec![];
        for i in 0..n {
            for j in i + 1..n {
                edges.push(Edge {
                    fr: i,
                    to: j,
                    cost: d[i][j],
                });
            }
        }
        for e in edges.iter() {
            d[e.fr][e.to] = e.cost;
            d[e.to][e.fr] = e.cost;
            assert!(e.cost >= 1);
            assert!(e.cost <= 100);
        }
        out_line!(max_d);
        for i in 0..n - 1 {
            for j in i + 1..n {
                out!(d[i][j]);
                if j != n - 1 {
                    out!(" ");
                }
            }
            out_line!();
        }
        output().flush();
        let res = solve_test(n, edges.clone(), &max_d);
        let mut ok = false;
        for &time in [0.1, 0.3, 1.0, 5.0, 10.0].iter() {
            dbg!(time);
            let res_sa = solve_sa(n, edges.clone(), &max_d, time);
            if res_sa == res {
                ok = true;
                break;
            }
        }
        assert!(ok);
    }
}

}
pub mod algo_lib {
pub mod collections {
pub mod array_2d {
use crate::algo_lib::io::output::Output;
use crate::algo_lib::io::output::Writable;
use crate::algo_lib::misc::num_traits::Number;
use std::io::Write;
use std::ops::Index;
use std::ops::IndexMut;
use std::ops::Mul;

// TODO: implement good Debug
#[derive(Clone, Debug)]
pub struct Array2D<T> {
    rows: usize,
    cols: usize,
    v: Vec<T>,
}

pub struct Iter<'a, T> {
    array: &'a Array2D<T>,
    row: usize,
    col: usize,
}

impl<T> Array2D<T>
where
    T: Clone,
{
    #[allow(unused)]
    pub fn new(empty: T, rows: usize, cols: usize) -> Self {
        Self {
            rows,
            cols,
            v: vec![empty; rows * cols],
        }
    }

    pub fn gen(rows: usize, cols: usize, mut f: impl FnMut(usize, usize) -> T) -> Self {
        let mut v = Vec::with_capacity(rows * cols);
        for r in 0..rows {
            for c in 0..cols {
                v.push(f(r, c));
            }
        }
        Self { rows, cols, v }
    }

    pub fn rows(&self) -> usize {
        self.rows
    }

    pub fn len(&self) -> usize {
        self.rows()
    }

    pub fn cols(&self) -> usize {
        self.cols
    }

    pub fn swap(&mut self, row1: usize, row2: usize) {
        assert!(row1 < self.rows);
        assert!(row2 < self.rows);
        if row1 != row2 {
            for col in 0..self.cols {
                self.v.swap(row1 * self.cols + col, row2 * self.cols + col);
            }
        }
    }

    pub fn transpose(&self) -> Self {
        Self::gen(self.cols, self.rows, |r, c| self[c][r].clone())
    }

    pub fn iter(&self) -> Iter<T> {
        Iter {
            array: self,
            row: 0,
            col: 0,
        }
    }
}

impl<T> Writable for Array2D<T>
where
    T: Writable,
{
    fn write(&self, output: &mut Output) {
        for r in 0..self.rows {
            self[r].write(output);
            output.write(&[b'\n']).unwrap();
        }
    }
}

impl<T> Index<usize> for Array2D<T> {
    type Output = [T];

    fn index(&self, index: usize) -> &Self::Output {
        &self.v[(index) * self.cols..(index + 1) * self.cols]
    }
}

impl<T> IndexMut<usize> for Array2D<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.v[(index) * self.cols..(index + 1) * self.cols]
    }
}

impl<T> Mul for &Array2D<T>
where
    T: Number,
{
    type Output = Array2D<T>;

    fn mul(self, rhs: Self) -> Self::Output {
        let n = self.rows;
        let m = self.cols;
        assert_eq!(m, rhs.rows);
        let k2 = rhs.cols;
        let mut res = Array2D::new(T::ZERO, n, k2);
        for i in 0..n {
            for j in 0..m {
                for k in 0..k2 {
                    res[i][k] += self[i][j] * rhs[j][k];
                }
            }
        }
        res
    }
}

impl<T> Array2D<T>
where
    T: Number,
{
    pub fn pown(&self, pw: usize) -> Self {
        assert_eq!(self.rows, self.cols);
        let n = self.rows;
        if pw == 0 {
            Self::gen(n, n, |r, c| if r == c { T::ONE } else { T::ZERO })
        } else if pw == 1 {
            self.clone()
        } else {
            let half = self.pown(pw / 2);
            let half2 = &half * &half;
            if pw & 1 == 0 {
                half2
            } else {
                &half2 * &self
            }
        }
    }
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        if self.col == self.array.cols {
            self.col = 0;
            self.row += 1;
        }
        if self.row >= self.array.rows {
            return None;
        }
        let elem = &self.array[self.row][self.col];
        self.col += 1;
        Some(elem)
    }
}
}
pub mod index_of {
pub trait IndexOf<T> {
    fn index_of(&self, elem: &T) -> Option<usize>;
}

impl<T: Eq> IndexOf<T> for &[T] {
    fn index_of(&self, elem: &T) -> Option<usize> {
        self.iter().position(|cur| cur == elem)
    }
}

impl<T: Eq> IndexOf<T> for Vec<T> {
    fn index_of(&self, elem: &T) -> Option<usize> {
        self.iter().position(|cur| cur == elem)
    }
}
}
pub mod peek_random {
use crate::algo_lib::misc::rand::Random;

pub trait PeekRandom<T> {
    fn peek_random(&self, rnd: &mut Random) -> Option<&T>;
    fn peek_random_exn(&self, rnd: &mut Random) -> &T;
}

impl<T> PeekRandom<T> for &[T] {
    fn peek_random(&self, rnd: &mut Random) -> Option<&T> {
        if self.is_empty() {
            return None;
        } else {
            Some(&self[rnd.gen_index(self)])
        }
    }

    fn peek_random_exn(&self, rnd: &mut Random) -> &T {
        self.peek_random(rnd).unwrap()
    }
}

impl<T> PeekRandom<T> for Vec<T> {
    fn peek_random(&self, rnd: &mut Random) -> Option<&T> {
        if self.is_empty() {
            return None;
        } else {
            Some(&self[rnd.gen_index(self)])
        }
    }

    fn peek_random_exn(&self, rnd: &mut Random) -> &T {
        self.peek_random(rnd).unwrap()
    }
}
}
}
pub mod graph {
pub mod dsu {
pub struct Dsu {
    p: Vec<u32>,
    size: Vec<u32>,
    num_comps: u32,
}

impl Dsu {
    pub fn clear(&mut self) {
        for (idx, val) in self.p.iter_mut().enumerate() {
            *val = idx as u32;
        }
        for val in self.size.iter_mut() {
            *val = 1;
        }
        self.num_comps = self.p.len() as u32;
    }

    pub fn new(n: usize) -> Self {
        let mut res = Self {
            p: vec![0; n],
            size: vec![0; n],
            num_comps: n as u32,
        };
        res.clear();
        res
    }

    pub fn get(&mut self, v: usize) -> usize {
        if self.p[v] as usize != v {
            self.p[v] = self.get(self.p[v] as usize) as u32;
        }
        self.p[v] as usize
    }

    pub fn unite(&mut self, v1: usize, v2: usize) -> bool {
        let v1 = self.get(v1);
        let v2 = self.get(v2);
        if v1 == v2 {
            false
        } else {
            self.p[v1 as usize] = v2 as u32;
            self.size[v2 as usize] += self.size[v1 as usize];
            self.num_comps -= 1;
            true
        }
    }

    pub fn calc_size(&mut self, mut v: usize) -> usize {
        v = self.get(v);
        self.size[v as usize] as usize
    }

    pub fn is_root(&self, v: usize) -> bool {
        self.p[v] as usize == v
    }

    pub fn calc_components(&mut self) -> Vec<Vec<usize>> {
        let n = self.p.len();
        let mut res = vec![vec![]; n];
        for v in 0..n {
            res[self.get(v) as usize].push(v);
        }
        res.into_iter().filter(|vec| !vec.is_empty()).collect()
    }

    pub fn num_components(&self) -> usize {
        self.num_comps as usize
    }
}
}
}
pub mod io {
pub mod input {
use crate::algo_lib::collections::array_2d::Array2D;
use crate::algo_lib::misc::ord_f64::OrdF64;
use std::fmt::Debug;
use std::io::Read;
use std::marker::PhantomData;
use std::path::Path;
use std::str::FromStr;

pub struct Input {
    input: Box<dyn Read>,
    buf: Vec<u8>,
    at: usize,
    buf_read: usize,
}

macro_rules! read_integer_fun {
    ($t:ident) => {
        #[allow(unused)]
        pub fn $t(&mut self) -> $t {
            self.read_integer()
        }
    };
}

impl Input {
    const DEFAULT_BUF_SIZE: usize = 4096;

    ///
    /// Using with stdin:
    /// ```no_run
    /// use algo_lib::io::input::Input;
    /// let stdin = std::io::stdin();
    /// let input = Input::new(Box::new(stdin));
    /// ```
    ///
    /// For read files use ``new_file`` instead.
    ///
    ///
    pub fn new(input: Box<dyn Read>) -> Self {
        Self {
            input,
            buf: vec![0; Self::DEFAULT_BUF_SIZE],
            at: 0,
            buf_read: 0,
        }
    }

    pub fn new_file<P: AsRef<Path>>(path: P) -> Self {
        let file = std::fs::File::open(&path)
            .unwrap_or_else(|_| panic!("Can't open file: {:?}", path.as_ref().as_os_str()));
        Self::new(Box::new(file))
    }

    pub fn new_with_size(input: Box<dyn Read>, buf_size: usize) -> Self {
        Self {
            input,
            buf: vec![0; buf_size],
            at: 0,
            buf_read: 0,
        }
    }

    pub fn new_file_with_size<P: AsRef<Path>>(path: P, buf_size: usize) -> Self {
        let file = std::fs::File::open(&path)
            .unwrap_or_else(|_| panic!("Can't open file: {:?}", path.as_ref().as_os_str()));
        Self::new_with_size(Box::new(file), buf_size)
    }

    pub fn get(&mut self) -> Option<u8> {
        if self.refill_buffer() {
            let res = self.buf[self.at];
            self.at += 1;
            Some(res)
        } else {
            None
        }
    }

    pub fn peek(&mut self) -> Option<u8> {
        if self.refill_buffer() {
            Some(self.buf[self.at])
        } else {
            None
        }
    }

    pub fn skip_whitespace(&mut self) {
        while let Some(b) = self.peek() {
            if !char::from(b).is_whitespace() {
                return;
            }
            self.get();
        }
    }

    pub fn next_token(&mut self) -> Option<Vec<u8>> {
        self.skip_whitespace();
        let mut res = Vec::new();
        while let Some(c) = self.get() {
            if char::from(c).is_whitespace() {
                break;
            }
            res.push(c);
        }
        if res.is_empty() {
            None
        } else {
            Some(res)
        }
    }

    //noinspection RsSelfConvention
    pub fn is_exhausted(&mut self) -> bool {
        self.peek().is_none()
    }

    pub fn has_more_elements(&mut self) -> bool {
        !self.is_exhausted()
    }

    pub fn read<T: Readable>(&mut self) -> T {
        T::read(self)
    }

    pub fn vec<T: Readable>(&mut self, size: usize) -> Vec<T> {
        let mut res = Vec::with_capacity(size);
        for _ in 0usize..size {
            res.push(self.read());
        }
        res
    }

    pub fn string_vec(&mut self, size: usize) -> Vec<Vec<u8>> {
        let mut res = Vec::with_capacity(size);
        for _ in 0usize..size {
            res.push(self.string());
        }
        res
    }

    pub fn matrix<T: Readable>(&mut self, rows: usize, cols: usize) -> Array2D<T>
    where
        T: Clone,
    {
        Array2D::gen(rows, cols, |_, _| self.read())
    }

    pub fn read_line(&mut self) -> String {
        let mut res = String::new();
        while let Some(c) = self.get() {
            if c == b'\n' {
                break;
            }
            if c == b'\r' {
                if self.peek() == Some(b'\n') {
                    self.get();
                }
                break;
            }
            res.push(c.into());
        }
        res
    }

    #[allow(clippy::should_implement_trait)]
    pub fn into_iter<T: Readable>(self) -> InputIterator<T> {
        InputIterator {
            input: self,
            phantom: Default::default(),
        }
    }

    fn read_integer<T: FromStr>(&mut self) -> T
    where
        <T as FromStr>::Err: Debug,
    {
        let res = self.read_string();
        res.parse::<T>().unwrap()
    }

    fn read_string(&mut self) -> String {
        match self.next_token() {
            None => {
                panic!("Input exhausted");
            }
            Some(res) => unsafe { String::from_utf8_unchecked(res) },
        }
    }

    pub fn string_as_string(&mut self) -> String {
        self.read_string()
    }

    pub fn string(&mut self) -> Vec<u8> {
        self.read_string().into_bytes()
    }

    fn read_char(&mut self) -> char {
        self.skip_whitespace();
        self.get().unwrap().into()
    }

    fn read_float(&mut self) -> OrdF64 {
        self.read_string().parse().unwrap()
    }

    pub fn f64(&mut self) -> OrdF64 {
        self.read_float()
    }

    fn refill_buffer(&mut self) -> bool {
        if self.at == self.buf_read {
            self.at = 0;
            self.buf_read = self.input.read(&mut self.buf).unwrap();
            self.buf_read != 0
        } else {
            true
        }
    }

    read_integer_fun!(i32);
    read_integer_fun!(i64);
    read_integer_fun!(i128);
    read_integer_fun!(u32);
    read_integer_fun!(u64);
    read_integer_fun!(usize);
}

pub trait Readable {
    fn read(input: &mut Input) -> Self;
}

impl Readable for String {
    fn read(input: &mut Input) -> Self {
        input.read_string()
    }
}

impl Readable for char {
    fn read(input: &mut Input) -> Self {
        input.read_char()
    }
}

impl Readable for f64 {
    fn read(input: &mut Input) -> Self {
        input.read_string().parse().unwrap()
    }
}

impl<T: Readable> Readable for Vec<T> {
    fn read(input: &mut Input) -> Self {
        let size = input.read();
        input.vec(size)
    }
}

pub struct InputIterator<T: Readable> {
    input: Input,
    phantom: PhantomData<T>,
}

impl<T: Readable> Iterator for InputIterator<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        self.input.skip_whitespace();
        self.input.peek().map(|_| self.input.read())
    }
}

macro_rules! read_integer {
    ($t:ident) => {
        impl Readable for $t {
            fn read(input: &mut Input) -> Self {
                input.read_integer()
            }
        }
    };
}

read_integer!(i8);
read_integer!(i16);
read_integer!(i32);
read_integer!(i64);
read_integer!(i128);
read_integer!(isize);
read_integer!(u8);
read_integer!(u16);
read_integer!(u32);
read_integer!(u64);
read_integer!(u128);
read_integer!(usize);

macro_rules! tuple_readable {
    ( $( $name:ident )+ ) => {
        impl<$($name: Readable), +> Readable for ($($name,)+) {
            fn read(input: &mut Input) -> Self {
                ($($name::read(input),)+)
            }
        }
    }
}

tuple_readable! {T}
tuple_readable! {T U}
tuple_readable! {T U V}
tuple_readable! {T U V X}
tuple_readable! {T U V X Y}
tuple_readable! {T U V X Y Z}
tuple_readable! {T U V X Y Z A}
tuple_readable! {T U V X Y Z A B}
tuple_readable! {T U V X Y Z A B C}
tuple_readable! {T U V X Y Z A B C D}
tuple_readable! {T U V X Y Z A B C D E}
tuple_readable! {T U V X Y Z A B C D E F}
}
pub mod output {
use std::io::Write;

pub struct Output {
    output: Box<dyn Write>,
    buf: Vec<u8>,
    at: usize,
    auto_flush: bool,
}

impl Output {
    const DEFAULT_BUF_SIZE: usize = 4096;

    pub fn new(output: Box<dyn Write>) -> Self {
        Self {
            output,
            buf: vec![0; Self::DEFAULT_BUF_SIZE],
            at: 0,
            auto_flush: false,
        }
    }

    pub fn new_with_auto_flush(output: Box<dyn Write>) -> Self {
        Self {
            output,
            buf: vec![0; Self::DEFAULT_BUF_SIZE],
            at: 0,
            auto_flush: true,
        }
    }

    pub fn flush(&mut self) {
        if self.at != 0 {
            self.output.write_all(&self.buf[..self.at]).unwrap();
            self.at = 0;
            self.output.flush().expect("Couldn't flush output");
        }
    }

    pub fn print<T: Writable>(&mut self, s: &T) {
        s.write(self);
    }

    pub fn put(&mut self, b: u8) {
        self.buf[self.at] = b;
        self.at += 1;
        if self.at == self.buf.len() {
            self.flush();
        }
    }

    pub fn maybe_flush(&mut self) {
        if self.auto_flush {
            self.flush();
        }
    }

    pub fn print_per_line<T: Writable>(&mut self, arg: &[T]) {
        for i in arg {
            i.write(self);
            self.put(b'\n');
        }
    }

    pub fn print_iter<T: Writable, I: Iterator<Item = T>>(&mut self, iter: I) {
        let mut first = true;
        for e in iter {
            if first {
                first = false;
            } else {
                self.put(b' ');
            }
            e.write(self);
        }
    }

    pub fn print_iter_ref<'a, T: 'a + Writable, I: Iterator<Item = &'a T>>(&mut self, iter: I) {
        let mut first = true;
        for e in iter {
            if first {
                first = false;
            } else {
                self.put(b' ');
            }
            e.write(self);
        }
    }
}

impl Write for Output {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let mut start = 0usize;
        let mut rem = buf.len();
        while rem > 0 {
            let len = (self.buf.len() - self.at).min(rem);
            self.buf[self.at..self.at + len].copy_from_slice(&buf[start..start + len]);
            self.at += len;
            if self.at == self.buf.len() {
                self.flush();
            }
            start += len;
            rem -= len;
        }
        if self.auto_flush {
            self.flush();
        }
        Ok(buf.len())
    }

    fn flush(&mut self) -> std::io::Result<()> {
        self.flush();
        Ok(())
    }
}

pub trait Writable {
    fn write(&self, output: &mut Output);
}

impl Writable for &str {
    fn write(&self, output: &mut Output) {
        output.write_all(self.as_bytes()).unwrap();
    }
}

impl Writable for String {
    fn write(&self, output: &mut Output) {
        output.write_all(self.as_bytes()).unwrap();
    }
}

impl Writable for char {
    fn write(&self, output: &mut Output) {
        output.put(*self as u8);
    }
}

impl<T: Writable> Writable for [T] {
    fn write(&self, output: &mut Output) {
        output.print_iter_ref(self.iter());
    }
}

impl<T: Writable> Writable for Vec<T> {
    fn write(&self, output: &mut Output) {
        self[..].write(output);
    }
}

macro_rules! write_to_string {
    ($t:ident) => {
        impl Writable for $t {
            fn write(&self, output: &mut Output) {
                self.to_string().write(output);
            }
        }
    };
}

write_to_string!(u8);
write_to_string!(u16);
write_to_string!(u32);
write_to_string!(u64);
write_to_string!(u128);
write_to_string!(usize);
write_to_string!(i8);
write_to_string!(i16);
write_to_string!(i32);
write_to_string!(i64);
write_to_string!(i128);
write_to_string!(isize);
write_to_string!(f32);
write_to_string!(f64);

impl<T: Writable, U: Writable> Writable for (T, U) {
    fn write(&self, output: &mut Output) {
        self.0.write(output);
        output.put(b' ');
        self.1.write(output);
    }
}

impl<T: Writable, U: Writable, V: Writable> Writable for (T, U, V) {
    fn write(&self, output: &mut Output) {
        self.0.write(output);
        output.put(b' ');
        self.1.write(output);
        output.put(b' ');
        self.2.write(output);
    }
}

pub static mut OUTPUT: Option<Output> = None;

pub fn set_global_output_to_stdout() {
    unsafe {
        OUTPUT = Some(Output::new(Box::new(std::io::stdout())));
    }
}

pub fn set_global_output_to_file(path: &str) {
    unsafe {
        let out_file = std::fs::File::create(path).expect(&format!("Can't create file {}", path));
        OUTPUT = Some(Output::new(Box::new(out_file)));
    }
}

pub fn set_global_output_to_none() {
    unsafe {
        match &mut OUTPUT {
            None => {}
            Some(output) => output.flush(),
        }
        OUTPUT = None;
    }
}

pub fn output() -> &'static mut Output {
    unsafe {
        match &mut OUTPUT {
            None => {
                panic!("Global output wasn't initialized");
            }
            Some(output) => output,
        }
    }
}

#[macro_export]
macro_rules! out {
    ($first: expr $(,$args:expr )*) => {
        output().print(&$first);
        $(output().put(b' ');
        output().print(&$args);
        )*
        output().maybe_flush();
    }
}

#[macro_export]
macro_rules! out_line {
    ($first: expr $(, $args:expr )* ) => {
        {
            out!($first $(,$args)*);
            output().put(b'\n');
            output().maybe_flush();
        }
    };
    () => {
        {
            output().put(b'\n');
            output().maybe_flush();
        }
    };
}
}
pub mod task_io_settings {
pub enum TaskIoType {
    Std,
    File(String),
}

pub struct TaskIoSettings {
    pub is_interactive: bool,
    pub input: TaskIoType,
    pub output: TaskIoType,
}
}
pub mod task_runner {
use std::io::Write;

use super::input::Input;
use super::output::Output;
use super::output::OUTPUT;
use super::task_io_settings::TaskIoSettings;
use super::task_io_settings::TaskIoType;

pub fn run_task<Res>(io: TaskIoSettings, run: impl FnOnce(Input) -> Res) -> Res {
    let output: Box<dyn Write> = match io.output {
        TaskIoType::Std => Box::new(std::io::stdout()),
        TaskIoType::File(file) => {
            let out_file = std::fs::File::create(file).unwrap();
            Box::new(out_file)
        }
    };

    unsafe {
        if io.is_interactive {
            OUTPUT = Some(Output::new_with_auto_flush(output));
        } else {
            OUTPUT = Some(Output::new(output));
        }
    }

    let input = match io.input {
        TaskIoType::Std => {
            let sin = std::io::stdin();
            if io.is_interactive {
                Input::new_with_size(Box::new(sin), 1)
            } else {
                Input::new(Box::new(sin))
            }
        }
        TaskIoType::File(file) => {
            if io.is_interactive {
                Input::new_file_with_size(file, 1)
            } else {
                Input::new_file(file)
            }
        }
    };

    run(input)
}
}
}
pub mod misc {
pub mod dbg_macro {
#[macro_export]
#[allow(unused_macros)]
macro_rules! dbg {
    ($first_val:expr, $($val:expr),+ $(,)?) => {
        eprint!("[{}:{}] {} = {:?}",
                    file!(), line!(), stringify!($first_val), &$first_val);
        ($(eprint!(", {} = {:?}", stringify!($val), &$val)),+,);
        eprintln!();
    };
    ($first_val:expr) => {
        eprintln!("[{}:{}] {} = {:?}",
                    file!(), line!(), stringify!($first_val), &$first_val)
    };
}
}
pub mod gen_vector {
pub fn gen_vec<T>(n: usize, mut f: impl FnMut(usize) -> T) -> Vec<T> {
    (0..n).map(|id| f(id)).collect()
}
}
pub mod human_readable_usize {
use std::fmt::Debug;

pub struct HumanReadableUsize(pub usize);

impl Debug for HumanReadableUsize {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let v = self.0;
        if v < 1000 {
            write!(f, "{}", self.0)?
        } else if v < 10_000 {
            write!(f, "{}.{}K", v / 1000, (v % 1000) / 100)?
        } else if v < 1_000_000 {
            write!(f, "{}K", v / 1000)?
        } else if v < 10_000_000 {
            write!(f, "{}.{}M", v / 1_000_000, (v % 1_000_000) / (100_000))?
        } else {
            write!(f, "{}M", v / 1_000_000)?
        }
        Ok(())
    }
}
}
pub mod min_max {
pub trait UpdateMinMax: PartialOrd + Sized {
    fn update_min(&mut self, other: Self) -> bool {
        if other < *self {
            *self = other;
            true
        } else {
            false
        }
    }

    fn update_max(&mut self, other: Self) -> bool {
        if other > *self {
            *self = other;
            true
        } else {
            false
        }
    }
}

impl<T: PartialOrd + Sized> UpdateMinMax for T {}

pub trait FindMinMaxPos {
    fn index_of_min(&self) -> usize;
    fn index_of_max(&self) -> usize;
}

impl<T: PartialOrd> FindMinMaxPos for [T] {
    fn index_of_min(&self) -> usize {
        let mut pos_of_best = 0;
        for (idx, val) in self.iter().enumerate().skip(1) {
            if val < &self[pos_of_best] {
                pos_of_best = idx;
            }
        }
        pos_of_best
    }

    fn index_of_max(&self) -> usize {
        let mut pos_of_best = 0;
        for (idx, val) in self.iter().enumerate().skip(1) {
            if val > &self[pos_of_best] {
                pos_of_best = idx;
            }
        }
        pos_of_best
    }
}

pub fn index_of_min_by<T, F>(n: usize, f: F) -> usize
where
    T: PartialOrd,
    F: Fn(usize) -> T,
{
    assert!(n > 0);
    let mut best_idx = 0;
    let mut best_val = f(0);
    for idx in 1..n {
        let cur_val = f(idx);
        if cur_val < best_val {
            best_val = cur_val;
            best_idx = idx;
        }
    }
    best_idx
}

pub fn index_of_max_by<T, F>(n: usize, f: F) -> usize
where
    T: PartialOrd,
    F: Fn(usize) -> T,
{
    assert!(n > 0);
    let mut best_idx = 0;
    let mut best_val = f(0);
    for idx in 1..n {
        let cur_val = f(idx);
        if cur_val > best_val {
            best_val = cur_val;
            best_idx = idx;
        }
    }
    best_idx
}
}
pub mod num_traits {
use std::fmt::Debug;
use std::ops::Add;
use std::ops::AddAssign;
use std::ops::Div;
use std::ops::DivAssign;
use std::ops::Mul;
use std::ops::MulAssign;
use std::ops::Sub;
use std::ops::SubAssign;

pub trait HasConstants<T> {
    const MAX: T;
    const MIN: T;
    const ZERO: T;
    const ONE: T;
    const TWO: T;
}

pub trait ConvI32<T> {
    fn from_i32(val: i32) -> T;
    fn to_i32(self) -> i32;
}

pub trait Number:
    Copy
    + Add<Output = Self>
    + AddAssign
    + Sub<Output = Self>
    + SubAssign
    + Mul<Output = Self>
    + MulAssign
    + Div<Output = Self>
    + DivAssign
    + Ord
    + PartialOrd
    + Eq
    + PartialEq
    + HasConstants<Self>
    + Default
    + Debug
    + Sized
    + ConvI32<Self>
{
}

impl<
        T: Copy
            + Add<Output = Self>
            + AddAssign
            + Sub<Output = Self>
            + SubAssign
            + Mul<Output = Self>
            + MulAssign
            + Div<Output = Self>
            + DivAssign
            + Ord
            + PartialOrd
            + Eq
            + PartialEq
            + HasConstants<Self>
            + Default
            + Debug
            + Sized
            + ConvI32<Self>,
    > Number for T
{
}

macro_rules! has_constants_impl {
    ($t: ident) => {
        impl HasConstants<$t> for $t {
            // TODO: remove `std` for new rust version..
            const MAX: $t = std::$t::MAX;
            const MIN: $t = std::$t::MIN;
            const ZERO: $t = 0;
            const ONE: $t = 1;
            const TWO: $t = 2;
        }

        impl ConvI32<$t> for $t {
            fn from_i32(val: i32) -> $t {
                val as $t
            }

            fn to_i32(self) -> i32 {
                self as i32
            }
        }
    };
}

has_constants_impl!(i32);
has_constants_impl!(i64);
has_constants_impl!(i128);
has_constants_impl!(u32);
has_constants_impl!(u64);
has_constants_impl!(u128);
has_constants_impl!(usize);
has_constants_impl!(u8);

impl ConvI32<Self> for f64 {
    fn from_i32(val: i32) -> Self {
        val as f64
    }

    fn to_i32(self) -> i32 {
        self as i32
    }
}

impl HasConstants<Self> for f64 {
    const MAX: Self = Self::MAX;
    const MIN: Self = -Self::MAX;
    const ZERO: Self = 0.0;
    const ONE: Self = 1.0;
    const TWO: Self = 2.0;
}
}
pub mod ord_f64 {
use crate::algo_lib::io::input::Input;
use crate::algo_lib::io::input::Readable;
use crate::algo_lib::io::output::Output;
use crate::algo_lib::io::output::Writable;
use crate::algo_lib::misc::num_traits::ConvI32;
use crate::algo_lib::misc::num_traits::HasConstants;
use std::cmp::min;
use std::cmp::Ordering;
use std::f64::consts::PI;
use std::fmt::Debug;
use std::fmt::Display;
use std::fmt::Formatter;
use std::io::Write;
use std::num::ParseFloatError;
use std::ops::Neg;
use std::ops::Rem;
use std::str::FromStr;

#[derive(PartialOrd, PartialEq, Copy, Clone, Default)]
pub struct OrdF64(pub f64);

impl OrdF64 {
    pub const EPS: Self = Self(1e-9);
    pub const SMALL_EPS: Self = Self(1e-4);
    pub const PI: Self = Self(PI);

    pub fn abs(&self) -> Self {
        Self(self.0.abs())
    }

    pub fn eq_with_eps(&self, other: &Self, eps: Self) -> bool {
        let abs_diff = (*self - *other).abs();
        abs_diff <= eps || abs_diff <= min(self.abs(), other.abs()) * eps
    }

    pub fn eq_with_default_eps(&self, other: &Self) -> bool {
        self.eq_with_eps(other, Self::EPS)
    }

    pub fn sqrt(&self) -> Self {
        Self(self.0.sqrt())
    }

    pub fn powf(&self, n: f64) -> Self {
        Self(self.0.powf(n))
    }
}

impl Eq for OrdF64 {}

impl Ord for OrdF64 {
    fn cmp(&self, other: &Self) -> Ordering {
        self.partial_cmp(other).unwrap()
    }
}

impl std::ops::Add for OrdF64 {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        Self(self.0 + rhs.0)
    }
}

impl std::ops::AddAssign for OrdF64 {
    fn add_assign(&mut self, rhs: Self) {
        self.0 += rhs.0;
    }
}

impl std::ops::Sub for OrdF64 {
    type Output = Self;

    fn sub(self, rhs: Self) -> Self::Output {
        Self(self.0 - rhs.0)
    }
}

impl std::ops::SubAssign for OrdF64 {
    fn sub_assign(&mut self, rhs: Self) {
        self.0 -= rhs.0;
    }
}

impl std::ops::Mul for OrdF64 {
    type Output = Self;

    fn mul(self, rhs: Self) -> Self::Output {
        Self(self.0 * rhs.0)
    }
}

impl std::ops::MulAssign for OrdF64 {
    fn mul_assign(&mut self, rhs: Self) {
        self.0 *= rhs.0;
    }
}

impl std::ops::Div for OrdF64 {
    type Output = Self;

    fn div(self, rhs: Self) -> Self::Output {
        Self(self.0 / rhs.0)
    }
}

impl std::ops::DivAssign for OrdF64 {
    fn div_assign(&mut self, rhs: Self) {
        self.0 /= rhs.0;
    }
}

impl Neg for OrdF64 {
    type Output = Self;

    fn neg(self) -> Self::Output {
        Self(-self.0)
    }
}

impl Display for OrdF64 {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        Display::fmt(&self.0, f)
    }
}

impl Debug for OrdF64 {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        Debug::fmt(&self.0, f)
    }
}

impl Writable for OrdF64 {
    fn write(&self, output: &mut Output) {
        output.write_fmt(format_args!("{}", self.0)).unwrap();
    }
}

impl Readable for OrdF64 {
    fn read(input: &mut Input) -> Self {
        Self(input.read::<f64>())
    }
}

impl HasConstants<Self> for OrdF64 {
    const MAX: Self = Self(f64::MAX);
    const MIN: Self = Self(-f64::MAX);
    const ZERO: Self = Self(0.0);
    const ONE: Self = Self(1.0);
    const TWO: Self = Self(2.0);
}

impl ConvI32<Self> for OrdF64 {
    fn from_i32(val: i32) -> Self {
        Self(val as f64)
    }

    fn to_i32(self) -> i32 {
        self.0 as i32
    }
}

impl FromStr for OrdF64 {
    type Err = ParseFloatError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.parse::<f64>() {
            Ok(value) => Ok(Self(value)),
            Err(error) => Err(error),
        }
    }
}

impl From<OrdF64> for f64 {
    fn from(x: OrdF64) -> Self {
        x.0
    }
}

impl Rem for OrdF64 {
    type Output = Self;

    fn rem(self, rhs: Self) -> Self::Output {
        Self(self.0 % rhs.0)
    }
}

#[macro_export]
macro_rules! f {
    ($a:expr) => {
        OrdF64($a)
    };
}

impl From<usize> for OrdF64 {
    fn from(x: usize) -> Self {
        f!(x as f64)
    }
}

impl From<i32> for OrdF64 {
    fn from(x: i32) -> Self {
        f!(x as f64)
    }
}

impl From<f64> for OrdF64 {
    fn from(x: f64) -> Self {
        f!(x)
    }
}
}
pub mod rand {
use crate::algo_lib::misc::gen_vector::gen_vec;
use crate::algo_lib::misc::num_traits::Number;
use std::ops::Range;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;

#[allow(dead_code)]
pub struct Random {
    state: u64,
}

impl Random {
    pub fn gen_u64(&mut self) -> u64 {
        let mut x = self.state;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        self.state = x;
        x
    }

    #[allow(dead_code)]
    pub fn next_in_range(&mut self, from: usize, to: usize) -> usize {
        assert!(from < to);
        (from as u64 + self.gen_u64() % ((to - from) as u64)) as usize
    }

    pub fn gen_index<T>(&mut self, a: &[T]) -> usize {
        self.gen_in_range(0..a.len())
    }

    #[allow(dead_code)]
    pub fn gen_double(&mut self) -> f64 {
        (self.gen_u64() as f64) / (usize::MAX as f64)
    }

    #[allow(dead_code)]
    pub fn new(seed: u64) -> Self {
        let state = if seed == 0 { 787788 } else { seed };
        Self { state }
    }

    pub fn new_time_seed() -> Self {
        let time = SystemTime::now();
        let seed = (time.duration_since(UNIX_EPOCH).unwrap().as_nanos() % 1_000_000_000) as u64;
        if seed == 0 {
            Self::new(787788)
        } else {
            Self::new(seed)
        }
    }

    #[allow(dead_code)]
    pub fn gen_permutation(&mut self, n: usize) -> Vec<usize> {
        let mut result: Vec<_> = (0..n).collect();
        for i in 0..n {
            let idx = self.next_in_range(0, i + 1);
            result.swap(i, idx);
        }
        result
    }

    pub fn gen_in_range<T>(&mut self, range: Range<T>) -> T
    where
        T: Number,
    {
        let from = T::to_i32(range.start);
        let to = T::to_i32(range.end);
        let len = (to - from) as usize;
        T::from_i32(self.next_in_range(0, len) as i32 + from)
    }

    pub fn gen_vec<T>(&mut self, n: usize, range: Range<T>) -> Vec<T>
    where
        T: Number,
    {
        gen_vec(n, |_| self.gen_in_range(range.clone()))
    }

    pub fn gen_nonempty_range(&mut self, n: usize) -> Range<usize> {
        let x = self.gen_in_range(0..n);
        let y = self.gen_in_range(0..n);
        if x <= y {
            x..y + 1
        } else {
            y..x + 1
        }
    }

    pub fn gen_bool(&mut self) -> bool {
        self.gen_in_range(0..2) == 0
    }
}
}
pub mod simulated_annealing {
use std::cmp::max;
use std::time::Instant;

use crate::f;
use crate::algo_lib::misc::human_readable_usize::HumanReadableUsize;

use super::num_traits::HasConstants;
use super::ord_f64::OrdF64;
use super::rand::Random;

pub enum SearchFor {
    MinimumScore,
    MaximumScore,
}

pub struct SimulatedAnnealing {
    rnd: Random,
    instant: Instant,
    max_time_millis: u128,
    search_for: SearchFor,
    start_temp: OrdF64,
    finish_temp: OrdF64,
    current_temperature: OrdF64,
    last_score: OrdF64,
    last_delta: OrdF64,
    last_printed_status_iter: usize,
    max_num_status_updates: usize,
    iterations_passed: usize,
}

impl SimulatedAnnealing {
    ///
    /// Read:
    /// - https://apps.topcoder.com/forums/?module=Thread&threadID=696596&start=0
    /// - https://codeforces.com/blog/entry/94437
    ///
    pub fn new(
        max_time_sec: f64,
        search_for: SearchFor,
        start_temp: f64,
        finish_temp: f64,
    ) -> Self {
        let last_score = match search_for {
            SearchFor::MinimumScore => OrdF64::MAX,
            SearchFor::MaximumScore => OrdF64::ZERO,
        };
        assert!(start_temp >= finish_temp);
        Self {
            rnd: Random::new(787788),
            instant: Instant::now(),
            max_time_millis: (max_time_sec * 1000.0) as u128,
            search_for,
            start_temp: f!(start_temp),
            finish_temp: f!(finish_temp),
            current_temperature: f!(start_temp),
            last_score,
            last_delta: f!(0.0),
            last_printed_status_iter: 0,
            max_num_status_updates: max(max_time_sec as usize, 10),
            iterations_passed: 0,
        }
    }

    pub fn elapsed_ms(&self) -> f64 {
        self.instant.elapsed().as_secs_f64() * 1000.0
    }

    fn print_status(&self) {
        let elapsed_ms = self.instant.elapsed().as_millis();
        eprintln!(
            "After {}ms ({:?} iters) score is: {}",
            elapsed_ms,
            HumanReadableUsize(self.iterations_passed),
            self.last_score
        );
    }

    pub fn should_continue(&mut self) -> bool {
        // TODO: do not call `elapsed` so often.
        let elapsed = self.instant.elapsed().as_millis();

        let part_time_elapsed =
            self.instant.elapsed().as_millis() as f64 / self.max_time_millis as f64;

        // when [part_time_elapsed] = 0.0, should be equal to [self.start_temp]
        // when [part_time_elapsed] = 1.0, should be equal to [self.finish_temp]
        self.current_temperature =
            self.start_temp * (self.finish_temp / self.start_temp).powf(part_time_elapsed);

        let status_iter = (part_time_elapsed * (self.max_num_status_updates as f64)) as usize;
        if status_iter != self.last_printed_status_iter {
            self.last_printed_status_iter = status_iter;
            self.print_status();
        }

        self.iterations_passed += 1;
        elapsed < self.max_time_millis
    }

    pub fn should_go<T>(&mut self, prev_score: T, new_score: T) -> bool
    where
        OrdF64: From<T>,
    {
        let prev_score: OrdF64 = prev_score.into();
        let new_score: OrdF64 = new_score.into();

        let delta_if_positive_is_good = {
            let delta: OrdF64 = new_score - prev_score;

            match self.search_for {
                SearchFor::MinimumScore => -delta,
                SearchFor::MaximumScore => delta,
            }
        };

        self.last_delta = delta_if_positive_is_good;
        if delta_if_positive_is_good >= f!(0.0) {
            self.last_score = new_score;
            return true;
        }

        let accept_probability =
            std::f64::consts::E.powf((delta_if_positive_is_good / self.current_temperature).0);
        assert!(accept_probability <= 1.0 + 1e-9);
        assert!(accept_probability >= 0.0);

        if self.rnd.gen_double() <= accept_probability {
            self.last_score = new_score;
            true
        } else {
            false
        }
    }

    /// Get the simulated annealing's current temperature.
    pub fn current_temperature(&self) -> f64 {
        self.current_temperature.0
    }

    /// Get the simulated annealing's last delta.
    pub fn last_delta(&self) -> f64 {
        self.last_delta.0
    }
}
}
}
}
fn main() {
    crate::solution::submit();
}