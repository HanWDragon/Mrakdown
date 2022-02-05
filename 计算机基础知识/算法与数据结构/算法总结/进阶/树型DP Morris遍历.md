# Morris遍历

**一种遍历二叉树的方式**

并且时间复杂度 $O(N)$​​ ，额外空间复杂度 $O(1)$​​​  

通过利用原树中大量空闲指针的方式，达到节省空间的目的

这个结构在学术方面叫做**线索二叉树**

如果不能动二叉树的结构，则不能用这种方式的遍历

要是能改变结构，则可以先用这种方式遍历，再通过其他方式，再把树的结构改回来 

**Morris遍历的实质**

建立一种机制，对于没有左子树的节点只到达一次，对于有左子树的节点会到达两次

**遍历细节**

假设我们来到当前节点，开始时当前节点看作头节点

1. 如果当前节点没有左孩子，当前节点向右移动
2. 如果当前节点有左孩子，找到左树上最右的节点
	1. 如果最右的节点的右指针指向空，让它指向当前节点，然后当前节点向左移动
	2. 如果最右的节点的右指针指向当前节点，让它指向当前`null`，然后当前节点向右移动 
3. 当当前节点为空的时候遍历停止

**Morris遍历的应用**

先序、中序、后序都可以由morris遍历加工得到

**先序遍历**

假如这个节点只在Morris遍历中出现一次，那就在出现的时候打印，如果出现两次则在第一次出现的时候打印

**中序遍历**

假如这个节点只在Morris遍历中出现一次，那就在出现的时候打印，如果出现两次则在第二次出现的时候打印

**后序遍历**

假如这个节点只在Morris遍历中出现一次，不处理，如果出现两次则在第二次出现的时候逆序打印左树右边界

当前任务完成后，单独打印这棵树的右边界，而且逆序，其实就是单链表的逆序操作

**用来判断一棵树是否是搜索二叉树**

就是对中序遍历进行修改。比较大小

**在许多遍历二叉树的题目下都把Morris遍历看作最优解**

因为它解决的是最本质的遍历问题，所以它往往是最优解

但是它也有它自己的局限性

比如你发现自己的算法必须做**信息的强整合**

也就是不能使用传统的遍历来实现的算法

只能用二叉树的递归套路

也就是树型DP，需要左右两颗子树提供信息，把信息进行整合

再进行逻辑判断进行递归，在这样的情况无法使用Morris遍历

**代码实现**

```java
package class05;

public class Code01_MorrisTraversal {

    public static class Node {
        public int value;
        Node left;
        Node right;

        public Node(int data) {
            this.value = data;
        }
    }

    //中序遍历
    public static void morrisIn(Node head) {
        if (head == null) {
            return;
        }
        Node cur1 = head;
        Node cur2 = null;
        while (cur1 != null) {
            cur2 = cur1.left;
            if (cur2 != null) {
                while (cur2.right != null && cur2.right != cur1) {
                    cur2 = cur2.right;
                }
                if (cur2.right == null) {
                    cur2.right = cur1;
                    cur1 = cur1.left;
                    continue;
                } else {
                    cur2.right = null;
                }
            }
            System.out.print(cur1.value + " ");
            cur1 = cur1.right;
        }
        System.out.println();
    }

   //先序遍历
    public static void morrisPre(Node head) {
        if (head == null) {
            return;
        }
        Node cur1 = head;
        Node cur2 = null;
        while (cur1 != null) {
            cur2 = cur1.left;
            if (cur2 != null) {
                while (cur2.right != null && cur2.right != cur1) {
                    cur2 = cur2.right;
                }
                if (cur2.right == null) {
                    cur2.right = cur1;
                    System.out.print(cur1.value + " ");
                    cur1 = cur1.left;
                    continue;
                } else {
                    cur2.right = null;
                }
            } else {
                System.out.print(cur1.value + " ");
            }
            cur1 = cur1.right;
        }
        System.out.println();
    }

    //后序遍历
    public static void morrisPos(Node head) {
        if (head == null) {
            return;
        }
        Node cur1 = head;
        Node cur2 = null;
        while (cur1 != null) {
            cur2 = cur1.left;
            if (cur2 != null) {
                while (cur2.right != null && cur2.right != cur1) {
                    cur2 = cur2.right;
                }
                if (cur2.right == null) {
                    cur2.right = cur1;
                    cur1 = cur1.left;
                    continue;
                } else {
                    cur2.right = null;
                    printEdge(cur1.left);
                }
            }
            cur1 = cur1.right;
        }
        printEdge(head);
        System.out.println();
    }

    //逆序打印右边界
    public static void printEdge(Node head) {
        Node tail = reverseEdge(head);
        Node cur = tail;
        while (cur != null) {
            System.out.print(cur.value + " ");
            cur = cur.right;
        }
        //将这棵逆序的右边界调回去
        reverseEdge(tail);
    }

    //翻转单链表
    public static Node reverseEdge(Node from) {
        Node pre = null;
        Node next = null;
        while (from != null) {
            next = from.right;
            from.right = pre;
            pre = from;
            from = next;
        }
        return pre;
    }

    // for test -- print tree
    public static void printTree(Node head) {
        System.out.println("Binary Tree:");
        printInOrder(head, 0, "H", 17);
        System.out.println();
    }

    public static void printInOrder(Node head, int height, String to, int len) {
        if (head == null) {
            return;
        }
        printInOrder(head.right, height + 1, "v", len);
        String val = to + head.value + to;
        int lenM = val.length();
        int lenL = (len - lenM) / 2;
        int lenR = len - lenM - lenL;
        val = getSpace(lenL) + val + getSpace(lenR);
        System.out.println(getSpace(height * len) + val);
        printInOrder(head.left, height + 1, "^", len);
    }

    public static String getSpace(int num) {
        String space = " ";
        StringBuffer buf = new StringBuffer("");
        for (int i = 0; i < num; i++) {
            buf.append(space);
        }
        return buf.toString();
    }

    public static void main(String[] args) {
        Node head = new Node(4);
        head.left = new Node(2);
        head.right = new Node(6);
        head.left.left = new Node(1);
        head.left.right = new Node(3);
        head.right.left = new Node(5);
        head.right.right = new Node(7);
        printTree(head);
        morrisIn(head);
        morrisPre(head);
        morrisPos(head);
        printTree(head);

    }

}

```

# 树形dp套路

**树形dp套路使用前提**

如果题目求解目标是S规则，则求解流程可以定成以每一个节点为头节点的子树在S规则下 的每一个答案，并且最终答案一定在其中

1. 以某个节点X为头节点的子树中，分析答案有哪些可能性，并且这种分析是以X的左子树、X的右子树和X整棵树的角度来考虑可能性的

2. 根据第一步的可能性分析，列出所有需要的信息

3. 合并第二步的信息，对左树和右树提出同样的要求，并写出信息结构
4. 设计递归函数，递归函数是处理以X为头节点的情况下的答案。 包括设计递归的`basecase`，默认直接得到左树和右树的所有信息，以及把可能性做整合，并且要返回第三步的信息结构这四个小步骤

# 二叉树节点间的最大距离问题

从二叉树的节点a出发，可以向上或者向下走，但沿途的节点只能经过一次，到达节点b时路 径上的节点个数叫作a到b的距离，那么二叉树任何两个节点之间都有距离，求整棵树上的最 大距离。

**如何求解**

采用树型DP

分为两种情况

- 当前节点不参与最大节点距离的求解
	- 要么左树存在最大距离
	- 要么右树上存在最大距离

- 当前节点参与最大节点距离的求解

	- 选出左树和右树中离我最远的节点，此时可能是最大值

		高度为 左高 + 右高 + 1

最后就在这三种情况下取最大值

**树型DP最重要的就是对可能性的分类和返回值的结构**

**而树型DP建立可能型的基础就是，我当前的节点能向左树和右树要到的信息，能顺利求解题目**

按照此题来说返回值需要 `maxDistance,height`

**代码实现**

```java
package class05;

public class Code02_MaxDistanceInTree {

    public static class Node {
        public int value;
        public Node left;
        public Node right;

        public Node(int data) {
            this.value = data;
        }
    }

    public static int maxDistance(Node head) {
        int[] record = new int[1];
        return posOrder(head, record);
    }

    //返回值类型
    public static class ReturnType {
        //最大距离
        public int maxDistance;
        //树的高度
        public int h;

        public ReturnType(int m, int h) {
            this.maxDistance = m;
            this.h = h;
        }
    }

    //返回以X为头的整棵树的两个信息
    public static ReturnType process(Node head) {
        if (head == null) {
            //到了树的叶子节点的初始化
            return new ReturnType(0, 0);
        }
        //先向左树得到信息
        ReturnType leftReturnType = process(head.left);
        //再从右树得到信息
        ReturnType rightReturnType = process(head.right);
        //可能性三
        int includeHeadDistance = leftReturnType.h + 1 + rightReturnType.h;
        //可能性一
        int p1 = leftReturnType.maxDistance;
        //可能性二
        int p2 = rightReturnType.maxDistance;
        //得出最大高度
        int resultDistance = Math.max(Math.max(p1, p2), includeHeadDistance);
        //因为要计算当前节点的高度
        int hitself = Math.max(leftReturnType.h, leftReturnType.h) + 1;
        //向上递归
        return new ReturnType(resultDistance, hitself);
    }

    public static int posOrder(Node head, int[] record) {
        if (head == null) {
            record[0] = 0;
            return 0;
        }
        int lMax = posOrder(head.left, record);
        int maxfromLeft = record[0];
        int rMax = posOrder(head.right, record);
        int maxFromRight = record[0];
        int curNodeMax = maxfromLeft + maxFromRight + 1;
        record[0] = Math.max(maxfromLeft, maxFromRight) + 1;
        return Math.max(Math.max(lMax, rMax), curNodeMax);
    }

    public static void main(String[] args) {
        Node head1 = new Node(1);
        head1.left = new Node(2);
        head1.right = new Node(3);
        head1.left.left = new Node(4);
        head1.left.right = new Node(5);
        head1.right.left = new Node(6);
        head1.right.right = new Node(7);
        head1.left.left.left = new Node(8);
        head1.right.left.right = new Node(9);
        System.out.println(maxDistance(head1));

        Node head2 = new Node(1);
        head2.left = new Node(2);
        head2.right = new Node(3);
        head2.right.left = new Node(4);
        head2.right.right = new Node(5);
        head2.right.left.left = new Node(6);
        head2.right.right.right = new Node(7);
        head2.right.left.left.left = new Node(8);
        head2.right.right.right.right = new Node(9);
        System.out.println(maxDistance(head2));

    }

}

```

# 派对的最大快乐值

员工信息的定义如下

```java
class Employee {
	public int happy; // 这名员工可以带来的快乐值
	List<Employee> subordinates; // 这名员工有哪些直接下级 
	}
```

公司的每个员工都符合 Employee 类的描述。

整个公司的人员结构可以看作是一棵标准的、 没有环的多叉树。

树的头节点是公司唯一的老板。除老板之外的每个员工都有唯一的直接上级。 

叶节点是没有 任何下属的基层员工`(subordinates列表为空)`，除基层员工外，每个员工都有一个或多个直接下级。

这个公司现在要办party，你可以决定哪些员工来，哪些员工不来。但是要遵循如下规则。 

1. 如果某个员工来了，那么这个员工的所有直接下级都不能来 
2. 派对的整体快乐值是所有到场员工快乐值的累加
3. 你的目标是让派对的整体快乐值尽量大

给定一棵多叉树的头节点boss，请返回派对的最大快乐值。

**如何求解**

采用树型DP

分为两种情况

- 当前节点不参与宴会
	- 即当前节点的直接下属来或者不来的快乐最大值之和

- 当前节点参与宴会

	- 当前的快乐最大值可能为

		当前节点的快乐值 + 它直接下属员工不来的最大快乐值之和

最后就在这两种种情况下取最大值

**代码实现**

```java
package class05;

public class Code03_MaxHappy {

    public static int maxHappy(int[][] matrix) {
        int[][] dp = new int[matrix.length][2];
        boolean[] visited = new boolean[matrix.length];
        int root = 0;
        for (int i = 0; i < matrix.length; i++) {
            if (i == matrix[i][0]) {
                root = i;
            }
        }
        process(matrix, dp, visited, root);
        return Math.max(dp[root][0], dp[root][1]);
    }

    public static void process(int[][] matrix, int[][] dp, boolean[] visited, int root) {
        visited[root] = true;
        dp[root][1] = matrix[root][1];
        for (int i = 0; i < matrix.length; i++) {
            if (matrix[i][0] == root && !visited[i]) {
                process(matrix, dp, visited, i);
                dp[root][1] += dp[i][0];
                dp[root][0] += Math.max(dp[i][1], dp[i][0]);
            }
        }
    }

    public static void main(String[] args) {
        int[][] matrix = {{1, 8}, {1, 9}, {1, 10}};
        System.out.println(maxHappy(matrix));
    }
}

```

