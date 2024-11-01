package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var mod int = 1e9 + 7

type Reader struct {
	*bufio.Reader
}

func newReader() *Reader {
	return &Reader{
		bufio.NewReader(os.Stdin),
	}
}

func bigMod(n, p int) int {
	if n == 0 {
		return 0
	}
	if p == 0 {
		return 1
	}
	if p == 1 {
		return n
	}

	ans := bigMod(n, p>>1)
	ans = (ans * ans) % mod
	if (p & 1) == 1 {
		ans = (ans * n) % mod
	}
	return ans
}

func (b *Reader) ReadInt(endC byte) int {
	input, err := b.ReadString(endC)
	if err != nil {
		panic(err)
	}
	input = strings.TrimSpace(input)
	v, err := strconv.Atoi(input)
	if err != nil {
		panic(err)
	}
	return v
}

type segmentTree struct {
	array []int
	size  int
}

func newSegmentTree(size int) *segmentTree {
	s := &segmentTree{size: size}
	s.array = make([]int, 2+(size<<2))
	return s
}

func (s *segmentTree) update(node, left, right, u, v int) {
	if left == right {
		s.array[node] += v
		return
	}

	mid := (left + right) >> 1
	if u <= mid {
		s.update(node<<1, left, mid, u, v)
	} else {
		s.update(1|(node<<1), mid+1, right, u, v)
	}
	s.array[node] = s.array[node<<1] + s.array[1|(node<<1)]
}

func (s *segmentTree) Update(u, v int) {
	if u < 1 || u > s.size {
		return
	}
	s.update(1, 1, s.size, u, v)
}

func (s *segmentTree) query(node, left, right, u, v int) int {
	if right < u || v < left {
		return 0
	}
	if u <= left && v >= right {
		return s.array[node]
	}
	mid := (left + right) >> 1
	return s.query(node<<1, left, mid, u, v) + s.query(1|(node<<1), mid+1, right, u, v)
}

func (s *segmentTree) Query(u, v int) int {
	if u > v {
		return 0
	}
	return s.query(1, 1, s.size, u, v)
}

type tree struct {
	nodes int

	children  [][]int
	wealth    []int
	visitTime int
	visited   []bool
	startTime []int
	endTime   []int
	level     []int
	ancestor  [][]int
	wealthSum [][]int
	factor    [][]int

	*segmentTree
}

func newTree() *tree {
	t := &tree{}
	t.children = make([][]int, 2)
	t.wealth = make([]int, 2)
	t.ancestor = make([][]int, 20)
	t.wealthSum = make([][]int, 20)
	t.factor = make([][]int, 20)
	return t
}

func (t *tree) addNode(u, w, p int) {
	if len(t.wealth) <= p {
		panic("invalid parent")
	}
	t.children[p] = append(t.children[p], u)
	for len(t.wealth) <= u {
		t.wealth = append(t.wealth, 0)
		t.children = append(t.children, []int{})
	}
	t.wealth[u] = w
}

func (t *tree) dfs(u, p int) {
	if t.visited[u] {
		return
	}
	t.ancestor[0][u] = p
	t.level[u] = t.level[p] + 1
	t.visited[u] = true
	t.visitTime++
	t.startTime[u] = t.visitTime

	for _, c := range t.children[u] {
		t.dfs(c, u)
	}
	t.visitTime++
	t.endTime[u] = t.visitTime
}

func (t *tree) flat() {
	t.visitTime = 0
	t.nodes = len(t.wealth) - 1
	t.visited = make([]bool, t.nodes+1)
	t.startTime = make([]int, t.nodes+1)
	t.endTime = make([]int, t.nodes+1)
	t.level = make([]int, t.nodes+1)
	t.ancestor[0] = make([]int, t.nodes+1)
	t.dfs(1, 0)
	t.segmentTree = newSegmentTree(t.visitTime)
}

func (t *tree) prepare() {
	t.flat()

	t.wealthSum[0] = make([]int, t.nodes+1)
	t.factor[0] = make([]int, t.nodes+1)
	for n := 1; n <= t.nodes; n++ {
		p := t.ancestor[0][n]
		t.factor[0][n] = bigMod(len(t.children[p]), mod-2)
		t.wealthSum[0][n] = (t.wealth[p] * t.factor[0][n]) % mod
	}

	for i := 1; i < 20; i++ {
		t.ancestor[i] = make([]int, t.nodes+1)
		t.wealthSum[i] = make([]int, t.nodes+1)
		t.factor[i] = make([]int, t.nodes+1)
		for n := 1; n <= t.nodes; n++ {
			p := t.ancestor[i-1][n]
			t.ancestor[i][n] = t.ancestor[i-1][p]
			t.wealthSum[i][n] = (t.wealthSum[i-1][p]*t.factor[i-1][n] + t.wealthSum[i-1][n]) % mod
			t.factor[i][n] = (t.factor[i-1][n] * t.factor[i-1][p]) % mod
		}
	}
}

func (t *tree) findAncestor(n, depth int) int {
	for i := 0; depth > 0; i++ {
		if (depth & (1 << i)) != 0 {
			depth -= 1 << i
			n = t.ancestor[i][n]
		}
	}
	return n
}

func (t *tree) nodeDead(u int) {
	t.Update(t.startTime[u], 1)
	t.Update(t.endTime[u], -1)
}

// node `u` is an ancestor of node `v`
func (t *tree) howManyDead(u, v int) int {
	return t.Query(t.startTime[u], t.startTime[v])
}

func (t *tree) totalWealth(n, depth int) int {
	ans := t.wealth[n]
	factor := 1
	for i := 0; depth > 0; i++ {
		if (depth & (1 << i)) != 0 {
			depth -= 1 << i
			ans = (ans + factor*t.wealthSum[i][n]) % mod
			factor = (factor * t.factor[i][n]) % mod
			n = t.ancestor[i][n]
		}
	}
	return ans
}

type query struct {
	t, node int
}

func main() {
	// fmt.Printf("mod %v\n", mod)
	reader := newReader()
	testCases := reader.ReadInt('\n')
	// fmt.Printf("tests %v\n", testCases)

	for testCases > 0 {
		q := reader.ReadInt('\n')
		// fmt.Printf("q %v\n", q)
		queries := make([]query, 0)
		tree := newTree()

		for q > 0 {
			qType := reader.ReadInt(' ')
			// fmt.Printf("qtype %v ", qType)
			if qType == 2 {
				node := reader.ReadInt(' ')
				w := reader.ReadInt(' ')
				par := reader.ReadInt('\n')
				// fmt.Printf("node %v w %v par %v\n", node, w, par)
				tree.addNode(node, w, par)
			} else {
				node := reader.ReadInt('\n')
				// // fmt.Printf("node %v\n", node)
				queries = append(queries, query{qType, node})
			}
			q--
		}

		tree.prepare()
		for _, query := range queries {
			if query.t == 1 {
				tree.nodeDead(query.node)
			} else {
				n := query.node
				left := 0
				right := tree.level[n]
				for left < right {
					mid := (left + right + 1) >> 1
					p := tree.findAncestor(n, mid)
					if tree.howManyDead(p, n) < mid {
						right = mid - 1
					} else {
						left = mid
					}
				}
				fmt.Println(tree.totalWealth(n, left))
			}
		}
		// // fmt.Printf("finished test\n")
		testCases--
	}
	// // fmt.Printf("finished")
}
