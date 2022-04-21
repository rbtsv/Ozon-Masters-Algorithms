#!/usr/bin/python3
import sys
#input = sys.stdin.buffer.readline
import random
random.seed('codeforces!!111!')
# print(random.random())


#For demo
f = open("./tests/01", "r")
input = f.readline


def read_int():
    return int(input())


def read_array(sep=None, maxsplit=-1):
    return input().split(sep, maxsplit)

    
def read_int_array(sep=None, maxsplit=-1):
    return [int(x) for x in input().split(sep, maxsplit)]
    

def write(*args, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in args) + end)


def write_array(array, **kwargs):
    sep = kwargs.get('sep', ' ')
    end = kwargs.get('end', '\n')
    sys.stdout.write(sep.join(str(a) for a in array) + end)


class TreapNode:
    def __init__(self, key, prior):
        self.key = key
        self.prior = prior
        self._left = None
        self._right = None                
        self._parent = self
        self.data = None
    
    def update_data(self):
        pass

    @property
    def left(self):
        return self._left
        
    @left.setter
    def left(self, l):
        if l and l._parent:
            if l._parent._left == l:
                l._parent._left = None
            if l._parent._right == l:
                l._parent._right = None            
        self._left = l
        if l is not None:
            l._parent = self # None._parent
        
    
    @property
    def right(self):
        return self._right
        
    @right.setter
    def right(self, r):
        if r and r._parent:
            if r._parent._left == r:
                r._parent._left = None
            if r._parent._right == r:
                r._parent._right = None
        self._right = r
        if r:
            r._parent = self
            
    @property
    def parent(self):
        return self._parent
    
    @parent.setter
    def parent(self, p):
        if self._parent == p:
            return                            
        if self._parent:
            if self._parent._left == self:
                self._parent._left = None
            if self._parent._right == self:
                self._parent._right = None
        self._parent = p
        

class Treap:
    def __init__(self, key, prior):
        self.root = TreapNode(key, prior)

    def split(self, t, k):    
        if t is None:
            return None, None
        if k > t.key:
            t1, t2 = self.split(t.right, k)
            t.right = t1
            t.update_data()
            return t, t2
        else:
            t1, t2 = self.split(t.left, k)
            t.left = t2
            t.update_data()
            return t1, t
            
    def merge(self, t1, t2):    
        if t2 is None: return t1
        if t1 is None: return t2
        t1.parent = t1; t2.parent = t2
        
        if t1.prior > t2.prior:
            t1.right = self.merge(t1.right, t2)
            t1.update_data()
            return t1
        else:
            t2.left = self.merge(t1, t2.left)
            t2.update_data()
            return t2
            
    def insert(self, key, prior):
        self.root = self._insert(self.root, TreapNode(key, prior))
        
    def _insert(self, t, it):
        t1, t2 = self.split(t, it.key)
        t1 = self.merge(t1, it)
        return self.merge(t1, t2)
    
    def extract(self, k):
        t1, t2 = self.split(self.root, k)        
        if t2.key == k:
            self.root = self.merge(t1, t2.right)
            return t2.key, t2.prior
        tt = t2
        while tt.key > k:     
            tt = tt.left
        assert tt.key == k, "Trying extract key that is not in tree"
        assert tt.left == None, "There should be no left child"        
        tt.parent.left = tt.right
        self.root = self.merge(t1, t2)
        return tt.key, tt.prior
    
    def _print(self, t):
        if t:
            print(f"{t.key} {t.left.key if t.left else None} {t.right.key if t.right else None}")
            self._print(t.left)
            self._print(t.right)
            
    def print_tree(self):
        self._print(self.root)


class TreapNodeIndexed(TreapNode):
    def __init__(self, key, prior, idx):
        super().__init__(key,prior)
        self.idx = idx
        
        
class TreapIndexed(Treap):
    def __init__(self, key, prior, idx):        
        self.root = TreapNodeIndexed(key, prior, idx)
        self.nodes = [self.root]
        
    def insert(self, key, prior, idx):
        node = TreapNodeIndexed(key, prior, idx)
        self.nodes.append(node)
        self.root = self._insert(self.root, node)
 

class TreapNodeIterable(TreapNode): 
    def __init__(self, key, prior):
        super().__init__(key, prior)
    
    def get_min(self):
        l = self
        while l.left:
            l = l.left
        return l
    
    def get_max(self):
        r = self
        while r.right:
            r = r.right
        return r
    
    def is_right_child(self):
        return self._parent and (self._parent.right == self)
    
    def is_left_child(self):
        return self._parent and (self._parent._left == self)
    
    def next(self):        
        if self.right:
                return self.right.get_min()
        if self.parent == self:  
                return None
        p = self
        while p.is_right_child():
            p = p.parent        
        if p.is_left_child():
            return p.parent
        return None  
    
    def prev(self):        
        if self.left:
                return self.left.get_max()
        if self.parent == self:  
                return None
        p = self
        while p.is_left_child():
            p = p.parent        
        if p.is_right_child():
            return p.parent
        return None      


class TreapIterable(Treap):
    def __init__(self, key, prior, cur=None):        
        self.root = TreapNodeIterable(key, prior)
        self.cur = cur
        
    def __iter__(self):
        return TreapIter(self)
            
        
    def insert(self, key, prior):
        node = TreapNodeIterable(key, prior)
        self.root = self._insert(self.root, node)
    

class TreapIter:
    def __init__(self, treap, cur=None):        
        self.treap = treap    
        self.cur = cur      
        
    def __iter__(self):
        return self
        
    def __next__(self):
        if self.cur is None:
            self.cur = self.treap.root.get_min()
            return self.cur
        if self.cur.next():
            self.cur = self.cur.next()
            return self.cur        
        raise StopIteration  

class TreapNodeDS(TreapNodeIterable): 
    def __init__(self, key, val):
        super().__init__(key, random.random())
        self.val = val
        self.data = val
    
    def update_data(self):
        self.data = self.val
        for child in self.left, self.right:
            if child is not None:
                self.data = min(self.data, child.data)
       
class TreapDS(TreapIterable):
    def __init__(self, key, val):        
        self.root = TreapNodeDS(key, val)        
        
    def insert(self, key, val):
        node = TreapNodeDS(key, val)
        self.root = self._insert(self.root, node)
        
    def range_query(self, left, right):
        assert left <= right
        t_l, t_mid = self.split(self.root, left)
        t_mid, t_r = self.split(t_mid, right+1)
        ret = t_mid.data
        t_mid = self.merge(t_mid, t_r)
        self.root = self.merge(t_l, t_mid)
        return ret
                
n = read_int()

a = read_int_array() # a = [k, p]
t = TreapDS(1, a[0])
for i, x in enumerate(a[1:]):
    t.insert(i+2, x)

m = read_int()
for _ in range(m):
    l, r = read_int_array()
    print(t.range_query(l,r))

exit(0)

print("====")

t.print_tree()

for node in t:
    print(node.key, f"{node.val}", f"{node.data}")



    