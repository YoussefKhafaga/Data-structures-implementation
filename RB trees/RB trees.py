# 1 for red
# 2 for black
class Node():
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
        self.color = 1


class RBtree():
    def __init__(self):
        self.null = Node(0)
        self.null.color = 2
        self.null.right = None
        self.null.left = None
        self.root = self.null

    def insertion(self, key):
        node = Node(key)
        node.parent = None
        node.val = key
        node.left = self.null
        node.right = self.null
        node.color = 1
        parent = None
        root = self.root
        while root != self.null:
            parent = root
            if node.val < root.val:
                root = root.left
            else:
                root = root.right
        node.parent = parent
        if parent == None:
            self.root = node
        elif node.val < parent.val:
            parent.left = node
        else:
            parent.right = node
        if node.parent == None:
            node.color = 2
            return
        if node.parent.parent == None:
            return
        self.fix(node)

    def fix(self, node):
        while node.parent.color == 1:
            if node.parent == node.parent.parent.right:
                uncle = node.parent.parent.left
                if uncle.color == 1:
                    uncle.color = 2
                    node.parent.color = 2
                    node.parent.parent.color = 1
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.Rrotate(node)
                    node.parent.color = 2
                    node.parent.parent.color = 1
                    self.Lrotate(node.parent.parent)
            else:
                uncle = node.parent.parent.right
                if uncle.color == 1:
                    uncle.color = 2
                    node.parent.color = 2
                    node.parent.parent.color = 1
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self.Lrotate(node)
                    node.parent.color = 2
                    node.parent.parent.color = 1
                    self.Rrotate(node.parent.parent)
            if node == self.root:
                break
        self.root.color = 2

    def Lrotate(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.null:
            y.left.parent = x
        y.parent = x.parent
        if x.parent == None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y


    def Rrotate(self, x):
        y = x.left
        x.left = y.right
        if y.right != self.null:
            y.right.parent = x

        y.parent = x.parent
        if x.parent == None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y


    def search(self, snode, key):
        if snode == self.null or key == snode.val:
            return snode.val
        if key < snode.val:
            return self.search(snode.left, key)
        return self.search(snode.right, key)

    def height(self, node):
        if node == self.null:
            return 0
        else:
            lheight = self.height(node.left)
            rheight = self.height(node.right)
            if lheight > rheight:
                return lheight + 1
            else:
                return rheight + 1

    def size(self, node):
        if node == self.null:
            return 0
        else:
            return self.size(node.left) + self.size(node.right) + 1


    def getroot(self):
        return self.root



rbt = RBtree()
dictf = open('EN-US-Dictionary.txt', 'r')
dictionary = dictf.read().splitlines()
for key in dictionary:
    rbt.insertion(key)
x=1
while x!=0:
    x=input("1-Insert\t 2-Search\t 3-Print height\t 4-Print size\t 0-Exit\n")
    x=int(x)
    if x==1:
        word = input("Insert Word: ")
        word=word.lower()
        if rbt.search(rbt.getroot(),word) == 0:
            rbt.insertion(word)
            print("Insertion done")
            h = rbt.height(rbt.getroot())
            print("Height = ", h)
            s = rbt.size(rbt.getroot())
            print("Size = ", s)
        else:
            print("Word already exist")
    elif x==2:
        word = input("Insert Word: ")
        word = word.lower()
        if   rbt.search(rbt.getroot(),word) == 0:
            print("No")
        else:
            print("Yes")
    elif x==3:
        h=rbt.height(rbt.getroot())
        print("Height = ",h)
    elif x==4:
        s=rbt.size(rbt.getroot())
        print("Size = ",s)
    elif x==0:
        break
    else:
        print("You entered a wrong number")