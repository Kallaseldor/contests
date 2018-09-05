#include <bits/stdc++.h>
using namespace std;

class cart_tree {
  typedef struct _Node {
    int x, y, cnt;
    _Node *l, *r;
 
    _Node(int _x) : x(_x), y(abs ((rand() << 16) ^ rand() )), cnt(1), l(NULL), r(NULL) {}
    ~_Node() { delete l; delete r; }
    void recalc() {
      cnt = 1;
      if (l) cnt += l->cnt;
      if (r) cnt += r->cnt;
    }
  } *Node;
 
  Node merge(Node l, Node r) {
    if (!l || !r) return l ? l : r;
    if (l->y < r->y) {
      l->r = merge(l->r, r);
      l->recalc();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->recalc();
      return r;
    }
  }
 
  void split(Node v, int x, Node &l, Node &r) {
    l = r = NULL;
    if (!v) return;
    if (v->x < x) {
      split(v->r, x, v->r, r);
      l = v;
    } else {
      split(v->l, x, l, v->l);
      r = v;
    }
    v->recalc();
  }

  int query (Node nd, int val) {
    if (!nd) return 0;

    if (nd -> x <= val)
      return query (nd->r, val) + size (nd->l) + 1;

    return query (nd->l, val);
  }
 
  Node root;
  public:
  cart_tree() : root(NULL) {}
  ~cart_tree() { delete root; }
  void insert(int x) {
    Node l, r;
    split(root, x, l, r);
    root = merge(merge(l, new _Node(x)), r);
  }
  void erase(int x) {
    Node l, m, r;
    split(root, x, l, m);
    split(m, x + 1, m, r);
    assert(m && m->cnt == 1 && m->x == x);
    delete m;
    root = merge(l, r);
  }

  int size(Node nd) const { return nd ? nd->cnt : 0; }

  int calcans (int val) {
    return query (root, val);
  }

};

int main () {

  freopen ("environment.in", "r", stdin);
  freopen ("environment.out", "w", stdout);

  cart_tree ls, rs;

  srand (time (NULL));

  int n;
  cin >> n;

  int d = 0;

  for (int i = 0; i < n; ++i) {
    int op;
    scanf ("%d", &op);

    if (op == 1) {
      int l, r;
      scanf ("%d %d", &l, &r);

      l += d; r += d;

      ls.insert (l);
      rs.insert (r + 1);
    } else {
      int x;
      scanf ("%d", &x);

      int ans = ls.calcans(x) - rs.calcans(x);
      printf ("%d\n", ans);
      d = ans;
    }
  }

}
