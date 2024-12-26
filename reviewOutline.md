## 复杂度

- 算法是一组有穷的规则，它规定了解决某一特定类型问题的一系列运算

- 问题陈述说明了期望的输入/输出关系， 而算法描述了一个特定的计算过程来实现这种输入到输出的转换

- 不正确的算法也并非绝对无用，在不正确的算法错误率可控时， 有可能也是有用和有效的（如NP问题和近似算法）

- **算法5要素：**确定性、能行性、输入、输出、有穷性

- 计算机**模型假设**：有限自动机FA，Turing机，RAM模型随机访问机，单CPU串行算法，有足够的内存

- 算法的执行时间 = Σ fi*ti，分别是 **运算i** 的执行次数和实际执行一次的耗时

- **上界 / 下界 / 渐进紧缺界**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204151718595.png" alt="image-20241204151718595" style="zoom:50%;" />

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204151740863.png" alt="image-20241204151740863" style="zoom:50%;" />

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204151817692.png" alt="image-20241204151817692" style="zoom:50%;" />

  - 渐进紧确界 Θ 也就是：既是上界 O，又是下界 Ω

- **渐进紧确的上界和下界 o ω**

  定义关键是 **任意c**

  - <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204152244097.png" alt="image-20241204152244097" style="zoom:50%;" />
  - <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204152311043.png" alt="image-20241204152311043" style="zoom:50%;" />

- **多项式时间算法**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204151954939.png" alt="image-20241204151954939" style="zoom:50%;" />

- **指数时间算法**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204152023336.png" alt="image-20241204152023336" style="zoom:50%;" />

- 要在现有的计算机系统上运行具有比Ο(nlogn)复杂度还高的算法是比较困难的。

- **一些估算定理：**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204152406974.png" alt="image-20241204152406974" style="zoom:50%;" />

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204152442601.png" alt="image-20241204152442601" style="zoom:50%;" />



## 分治

- 归并排序分析：T(n) = 2T(n/2) + n，O(nlogn)，证明：数学归纳，**假设T(n) 证明T(2n)**

- <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241205140102784.png" alt="image-20241205140102784" style="zoom:50%;" />

- **主定理：**

  ![image-20241202155437506](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202155437506.png)

- **扩展的主定理**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202163026598.png" alt="image-20241202163026598" style="zoom: 33%;" />

- **递归树法：**？



## 堆

- **小顶堆：**每个 父节点<左子节点 && 父节点<右子节点，根节点维护最小值

- 存储在 **heap[1...hs]** 内
  - 根在 heap[1]
  - **K的左儿子是2k，右儿子是2k+1**
  - K的父节点是【k/2】
  
- **删除最小值：**
  - 1.删除根
  - 2.用最后一个元素替代根（**保证根的左右子树都还是二叉堆**）
  - 3.向下调整
    - **比较p和其较小的儿子，比p小就交换，比p大调整停止**
  - O(logn)
  
- **插入元素：**
  - 1.添加到末尾
  - 2.向上调整
  - O(logn)
  
- **堆的建立：**和删除的思路 / 方式是一致的
  
  **调整方式：先保证每一个子树都是二叉堆，故叶子不用调整**
  
  - 1.从最后一个非叶子节点（`heap[hs/2]`）开始，逐个向上（数组编号向前）遍历；
  - 2.对**每个节点**进行**向下调整**（堆化），确保每个节点的值都满足堆的性质。
  - O(n)
  
- **堆排序：**O(nlogn)。通过构建堆，然后**逐步移除根节点并进行重新调整**，最终得到有序序列。
  
- eg. 多路归并、序列和的前n小元素（转k路归并）、轮廓线、丑数



## 并查集

- 带有**秩优化**（控制树高度）的并查集模板

  ```cpp
  vector<int> parent;   // p数组
  vector<int> rankArray;// 秩数组
  
  void init(int n) {
      parent.resize(n + 1);
      rankArray.resize(n + 1, 0);
      for (int i = 0; i <= n; ++i) { 
          parent[i] = i;
      }
  }
  // 路径压缩
  int find(int x) {
      if (parent[x] != x) {
          parent[x] = find(parent[x]); 
      }
      return parent[x];
  }
  // 合并集合
  void unite(int x, int y) {
      int rootX = find(x);
      int rootY = find(y);
      if (rootX != rootY) {
          if (rankArray[rootX] > rankArray[rootY]) {
              parent[rootY] = rootX;
          } else if (rankArray[rootX] < rankArray[rootY]) {
              parent[rootX] = rootY;
          } else {
              parent[rootY] = rootX;
              rankArray[rootX]++; // 只有两个等秩集发生合并，秩才会改变
          }
      }
  }
  ```

  

## 线段树

- 适用于：**区间统计**有关的问题。某些数据可以**按区间进行划分**，**按区间进行修改**，而且还需要**按区间进行查询**

- **区间分解时，每层最多2个“终止节点”**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202235057715.png" alt="image-20241202235057715" style="zoom: 33%;" />

- **懒标记：**

  - 思想是为了提高区间更新的效率，避免每次更新都要遍历整个区间退化到O(n)。

  - 具体来说，线段树每个节点存储一个区间的信息，比如区间的和、最小值等。
  - 当对一个区间进行更新时，不立即更新所有涉及的子节点，
    - 而是**先标记**这些节点，并且存储更新需要的信息。表示它们的值需要更新，等到真正需要查询到这些节点的时候再去更新。并且去除懒标记。

- 模板:

  ```cpp
  // 线段树节点 [l, r]，val存储该段的sum，left和right分别存储左右端点下标
  struct Node {
      int val;
      int left, right;
  } tree[4 * N];
  
  // 建树
  void build (int root, int l, int r) {
      tree[root].left = l;
      tree[root].right = r;
      if (l == r) {
          tree[root].val = arr[l];
          return;
      }
      int mid = (l + r) / 2;
      build(root * 2, l, mid); // 左子树
      build(root * 2 + 1, mid + 1, r); // 右子树
      tree[root].val = tree[root * 2].val + tree[root * 2 + 1].val;
  }
  
  // 更新区间 [l, r] 内每个元素加上 x
  // 一直下推到叶子节点，然后向上递归更新
  void range_update(int root, int l, int r, int x) {
      if (tree[root].left == tree[root].right) {
          tree[root].val += x;
          return;
      }
      int mid = (tree[root].left + tree[root].right) / 2;
      if (l <= mid) range_update(root * 2, l, r, x); // 更新左子区间
      if (r > mid) range_update(root * 2 + 1, l, r, x); // 更新右子区间
      tree[root].val = tree[root * 2].val + tree[root * 2 + 1].val; // 更新父节点的和
  }
  
  // 查询区间 [l, r] 的和
  int query (int root, int l, int r) {
      if (tree[root].left == l && tree[root].right == r) { //正好等于该区间
          return tree[root].val;
      }
      int mid = (tree[root].left + tree[root].right) / 2;
      if (mid >= r)
          return query(root * 2, l, r); // 在左子树查找
      else if (mid < l)
          return query(root * 2 + 1, l, r); // 在右子树查找
      else
          return query(root * 2, l, mid) + query(root * 2 + 1, mid + 1, r); // 跨区间查找
  }
  ```
  
  

## 树状数组

- 适用于：**单个元素经常修改**而且还**反复要求任意区间和**的情况（改/查都为 logn）

- 同一个问题也可以用线段树解决，但是用树状数组来做，效率（编程和运行）更高（时间复杂度相同，但是树状数组常数小）
- 如果每次**要修改的不是单个元素**，而是区间，就不能用树状数组，只能用线段树
- **lowbit(x) = x & (-x)**
  
  - 最低位的1代表的数值
  
- 由 a[1...i] 构造一个等长的树状数组 C[1...i]
  
- **C[i] = a[i-lowbit(i)+1] + …+ a[i]**
  - <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202123300292.png" alt="image-20241202123300292" style="zoom:33%;" />
  - 对应的，如果要**更新 a[i]**，有且仅有以下的几项需要更新：  **C[n_1], C[n_2],  …C[n_m]**
    - 其中：**n_1 = i ，n_{i+1} = n_i + lowbit(n_i)**
  - **建树状数组**：**更新每个 a[i] 为对应值**即可建成 C[] 数组

- 可以快速求出任意区间 a[i...j] 的和，原因在于任意 sum[1...k] 都可以在 O(logn) 求出，由**前缀和求出 a[i]...a[j]** 的累加

- **sum(k) = C[n_1]+C[n_2] + …+ C[n_m]**
  
  - 其中，n_m = k
  - n_{i-1} = n_i - lowbit(n_i)
  - 且 n_1 - lowbit(n_1) 一定等于0
  
- 模板:

  ```cpp
  vector<int> bit; // 也就是C[i]
  // 更新树状数组，a[index] += delta
  void update(int index, int delta, int n) {
      while (index <= n) {
          bit[index] += delta;
          index += index & -index;
      }
  }
  
  // 查询树状数组前index项的和
  int query(int index) {
      int sum = 0;
      while (index > 0) {
          sum += bit[index];
          index -= index & -index;
      }
      return sum;
  }
  
  // 查询区间[left, right]的和
  int rangeQuery(int left, int right) {
      return query(right) - query(left - 1);
  }
  
  int main() {
      int n, m;
      cin >> n >> m; // 输入数列长度n和操作次数m
      vector<int> arr(n + 1);
      bit.resize(n + 1, 0);
      // 初始化树状数组
      for (int i = 1; i <= n; ++i) {
          cin >> arr[i];
          update(i, arr[i], n);
      }
      // 处理操作
      for (int i = 0; i < m; ++i) {
          int op, x, y;
          cin >> op >> x >> y;
          if (op == 1) {
              // 将第x个位置增加y
              update(x, y, n);
          } else if (op == 2) {
              // 查询区间[x, y]的和
              cout << rangeQuery(x, y) << endl;
          }
      }
      return 0;
  }
  ```



## 旋转树的基本概念

- AVL（平衡二叉树），又叫**旋转树**

- 就是一个 **平衡的二叉查找树**

  - 一棵空树或它的左右两个子树的高度差的绝对值不超过1
  - 左右两个子树都是一棵平衡二叉树

- 作用：防止二叉树的查找效率退化，保持在 logn

- 为保持平衡，不能简单的进行插入操作，要配合旋转

- **单旋转：**

  - **右旋——左左情况**：

    在节点T的左结点的左子树上插入元素

    ![image-20241203000835999](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203000835999.png)

    ![image-20241203000903348](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203000903348.png)

  - **左旋——右右情况：**

    同左左情况的右旋恰相反

- **双旋转：**

  - **左右旋——左右情况**

    在节点T的左结点的右子树上插入元素

    ![image-20241203001821768](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203001821768.png)

    ![image-20241203001833612](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203001833612.png)

  - **右左旋——右左情况**

    在节点T的右结点的左子树上插入元素



## 图

- 稀疏图一般用邻接表（每个结点一条链表表示相连的所有点）表示，稠密图更倾向于用邻接矩阵表示
- 邻接矩阵可用于需要**快速判断任意两个结点之间**是否有边相连的场景
- 当某结点的**所有邻接结点都被访问**了时， 称该结点**被检测**了
  - 图检索算法：BFS/DFS

---

- **BFS相关**

  - 从结点v开始，首先访问结点v，给v标上已访问标记。 
  - **访问邻接于v且目前尚未被访问的所有结点**，此时结点v 被检测，而v的这些邻接结点是新的未被检测的结点。将这些**结点依次**放置到一个称为未检测结点表的**队列**中
  - 若未检测结点表为空，则算法终止；否则 
  - 取未检测结点表的**队列头结点**作为下一个待检测结点，重复上述过程。直到Q为空，算法终止。

  - 伪代码：O(n+e)

    ```cpp
    procedure BFS(v)
        //宽度优先检索，它从结点v开始。所有已访问结点被标记为VISITED(i)=1。//
        VISITED(v)←1 //VISITED(1:n)是一个标志数组，初始值为VISITED(i)=0, 1≤i≤n //
        u←v
        将Q初始化为空
        loop
            //Q是未检测结点的队列//
        	u = call POPQ(u,Q)
            for 邻接于u的所有结点w do
                if VISITED(w)=0 then     //w未被访问//
                    // T←T∪{(u,w)} 生成树
                	call PUSHQ(w,Q)       
                	VISITED(w)←1        
                endif
            repeat
            if Q 为空then	break  
        repeat
    end BFS
    ```

    - 若用邻接矩阵，判断邻接于u的所有结点需要Θ(n) 的时间，则所有结点的处理时间：Ο(n^2)

  - 若是无向连通图，一次BFS即可遍历，否则需要多次调用BFS

    ```cpp
    procedure BFT(G,n)
        //G的宽度优先周游//
        int VISITED(n)
        for i←1 to n do VISITED(i)←0 repeat
        for i←1 to n do  //反复调用BFS//
            if VISITED(i)=0 then call BFS(i)  endif
        repeat
    end BFT
    ```

    - **应用：**
      - 判定**连通性**（BFS次数大于1）
      - 生成G的**连通分图**——一次BFS中访问到的所有结点+边构成

  - **BFS生成树：**

    - 引理：**有n个结点n-1条边的连通图是一棵树**

    <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202141444374.png" alt="image-20241202141444374" style="zoom: 67%;" />

    - 在BFS模板中加一个集合记录向前边即可得到生成树

---

- **DFS相关**

  - 从结点v开始，首先访问v， 给v标上已访问标记；

  - 然后中止 对v的检测，并从邻接于v且尚未被访问的结点的中找出一个结点w开始新的检测；

  - 在w被检测后， 再恢复对v的检测；

  - 当所有可到达的结点全部被检测完毕后，算法终止。

  - 伪代码：O(n+e) 用邻接矩阵O(n^2)

    ```cpp
    procedure DFS(v)
        //已知n结点的图G＝(V,E)以及初值置零的数组VISITED(1:n) 。//
        VISITED(v)←1
        for 邻接于v的每个结点w do
            if VISITED(w)＝0 then
                // T←T∪{(u,w)} 生成树
                call DFS(w)
            endif
        repeat
    END DFS
    ```

  - **DFS生成树**

    - 同样在遍历时记录向前边即可
    - 盯着一条路径往最深走
    - ![image-20241202143705835](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202143705835.png)

- **D_Search（深度检索）相关**

  - 改造的BFS算法，用**栈**来保存未被检测的结点
  - 结点被压入栈中后将以相反的次序出栈

---

- **最小生成树MST**

  - **无环且连通所有结点，具有最小边权重加和sum的子图T，称为G的最小生成树**

  - 最小生成树**不唯一**

  - 直觉上怎么建MST？-> **贪心**（两种经典建树算法都是）

    <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202165117215.png" alt="image-20241202165117215" style="zoom:50%;" />

  - **Kruskal算法：“按边排序”**

    ![image-20241202185101789](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202185101789.png)

    - 1.**排序**：首先，将所有**边的权重从小到大**进行排序。
    - 2.**选择边**：从权重最小的边开始，依次检查每条边。如果**这条边连接的两个顶点不在同一个集合中**（不成环），则将它加入到最小生成树中，并将这两个顶点所在的**集合合并**。[通过并查集]
    - 3.**重复**：重复上述步骤，**直到最小生成树中的边数等于顶点数减一**为止。
    - 复杂度：O(ElogV)

  - **Prim算法：“从一个点开始，逐步扩展生成树”**

    ![image-20241202183501194](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241202183501194.png)

    - 1.**选择起点**：从一个任意的点开始，作为当前生成树的起点。
    - 2.**扩展生成树**：每次选择从**开始于当前生成树的点集的 & 终于非当前生成树点集的 & 最小权重的**的边，连接一个新的点，把这个点**加入**生成树点集中。
    - 3.**重复**：迭代，直到所有点都被包含在生成树中。
    - 复杂度：O(ElogV)



## 单源最短路

- **问题：**给定一个图G=(V,E)，找出从**给定的源**点 s∈V 到其它**每个结点 v**∈V 的最短路径

- **最优子结构性质：**两个结点之间的**最短路径的任何子路径**都是最短的

- **不应存在负权重的边**，否则可能存在权重为**负值的环路**， 而造成图中最短路径无定义

- 最短路不应包含环路。 不包含环路的路径称为**简单路径**

- 一些表示：

  - v的**前驱**节点记为`v.π`，一个点的前驱只能是另一个节点或者**NIL**

  - **前驱子图**<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203185827629.png" alt="image-20241203185827629" style="zoom:50%;" />

    - 节点集合<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203185853592.png" alt="image-20241203185853592" style="zoom:50%;" />

      即**前驱节点不为NIL的**和**源节点S**的集合

    - 边集合<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203185918525.png" alt="image-20241203185918525" style="zoom:50%;" />

      即**以前驱子图节点集合（除了S）为终点的边**的集合

- 当算法终结时，`G_π`是一棵**最短路径树**

  包括了**从源节点s到每个可到达的节点的一条最短**路径

- **初始化函数：**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204001824000.png" alt="image-20241204001824000" style="zoom:67%;" />

- **松弛操作：**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203234751932.png" alt="image-20241203234751932" style="zoom:67%;" />

  对于每个结点v，维持一个属性`v.d`，记录从源点s到结点v的**最短路径权重的上界**。称v.d为s到v的最短路径估计。

  - 首先测试一下是否可以对从s到v的最短路径进行改善（即有没有更短的路径）。**如果可以改善，则v.d更新为新的最短路径估计值，v的前驱v.π更新为新的前驱结点**
  - 归纳：在算法中，在v.d达到其下界δ(s,v)后，就无法再减小（也不可能增加），算法终止

- 在最短路径p的第i条边被松弛之后，有**vi.d=δ(s,vi)**

- **Bellman-ford算法**

  可以求解一般情况下的问题，**可以有负权边，不能有负权环**

  G=(V, E)是带权有向图，权重函数 Ω: E->R，s是源节点

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204001704788.png" alt="image-20241204001704788" style="zoom:67%;" />

  - **1.按照每条边来relax**    

  - 2.执行|V|-1次，每次时间O(E) -> 复杂度**O(VE)**

  - **模板：**

    ```cpp
    int n, m;       // n表示点数，m表示边数
    int dist[N];    // dist[x]存储1到x的最短路距离
    
    struct Edge     // 边，a表示出点，b表示入点，w表示权重
    {
        int a, b, w;
    }edges[M];
    
    // 求1到n的最短路距离，如果无法从1走到n，则返回-1。
    int bellman_ford()
    {
        memset(dist, 0x3f, sizeof dist);
        dist[1] = 0;
        // 循环 V-1 次，每次对所有的边 E(u,v) 做松弛 
        for (int i = 0; i < n; i ++ )
        {
            for (int j = 0; j < m; j ++ )
            {
                int a = edges[j].a, b = edges[j].b, w = edges[j].w;
                if (dist[b] > dist[a] + w)
                    dist[b] = dist[a] + w;
            }
        }
        if (dist[n] > 0x3f3f3f3f / 2) return -1;
        return dist[n];
    }
    ```

- **Dijkstra算法**

  **要求所有边的权重均为非负值， 不仅仅没有负环**

  `执行流程和MST的Prim算法很像`

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204004406781.png" alt="image-20241204004406781" style="zoom:67%;" />

  - **贪心算法：每次选择 V-S 集合中最短路径估计值最小的结点加入 S 中**

  - Dijkstra算法的总运行时间依赖于最小优先队列Q的实现。 
  
    - 如果用线性数组(无序或者按序插入)实现，每次找d最小的结点u需要 O(V)的时间，所以算法的总运行时间为O(V^2+E)
    - 如果用堆实现，每次找d最小的结点u需要O(lgV )的时间，总运行时间为O((V+E)lgV)

  - **模板：**
  
    ```cpp
    int g[N][N];  // 邻接矩阵存储每条边
    int dist[N];  // 存储1号点到每个点的最短距离
    bool st[N];   // 存储每个点的最短路是否已经确定
    
    // 求1号点到n号点的最短路，如果不存在则返回-1
    int dijkstra()
    {
        memset(dist, 0x3f, sizeof dist);
        dist[1] = 0;
        for (int i = 0; i < n - 1; i ++ )
        {
            int t = -1;     
            // 在还未确定最短路的点中，寻找dist[]距离最小的点
            for (int j = 1; j <= n; j ++ )
                if (!st[j] && (t == -1 || dist[j] < dist[t]))
                    t = j;
            st[t] = true;   //此点即加入 已确定 集合
             // 用刚确定的 t 更新(松弛)其他点的距离dist
             for (int j = 1; j <= n; j ++ )
                 dist[j] = min(dist[j], dist[t] + g[t][j]);
        }
        if (dist[n] == 0x3f3f3f3f) return -1;
        return dist[n];
    }
    ```
  
    



## 多源最短路

问题描述：给定一个带权重的有向图G=(V,E)，其权重函数为ω:E→R。 在图中，对**所有的结点对u,v**∈V，找出从结点u到结点v的最短路径

图G用n*n的邻接矩阵表示<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204134639182.png" alt="image-20241204134639182" style="zoom: 50%;" />

问题的解以表格（二维数组）的形式给出：第u行第v列 给出从结点u到结点v的最短路径权重。

允许存在权重为负值的边，但不能包含权重为负值的环路

- **前驱节点矩阵**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204134716355.png" alt="image-20241204134716355" style="zoom:50%;" />

  - 前驱结点**矩阵П的第i行所诱导(induce)的子图**是一棵 **根结点为i的最短路径树**。

- 如果`G_Π,i`是一颗最短路径树，定义过程：输出**从i到j**的最短路径

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204134918831.png" alt="image-20241204134918831" style="zoom:50%;" />

- 朴素 O(n^3) 最短路算法（Floyd算法，DP）

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204135710944.png" alt="image-20241204135710944" style="zoom:50%;" />

- **Floyd-Warshall算法**：另一种DP算法，复杂度O(V^3)

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204141117401.png" alt="image-20241204141117401" style="zoom:50%;" />

  **中间结点：**一条 **简单路径** 上除了起点和终点以外的所有结点

  考虑G的结点集V，编号为`{1, 2, ... , n}`，其中一个子集是`{1, 2, ... , k}`

  定义`p = <v1, v2, ... , vl>`是从i到j，且所有中间结点全部取自`{1, 2, ... , k}`的最短路

  - **考虑状态转移：以结点k是否包含在 i -> j 的最短路中分类**

    <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204141016888.png" alt="image-20241204141016888" style="zoom:50%;" />

  - 具体最短路的构建和记录：在计算矩阵D的同时计算**前驱矩阵Π**

    - <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204141259876.png" alt="image-20241204141259876" style="zoom:50%;" />

- **有向图的传递闭包**

  有向图 G=(V, E)，定义G的传递闭包 `G*=(V, E*)`,其中<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204141745665.png" alt="image-20241204141745665" style="zoom:40%;" />

  - **求传递闭包**

    - 给E每条边赋值1，运行Floyd算法，如果路径矩阵的 `d_ij < n`，则说明 i -> j 路径是存在的
    - 定义矩阵T，存在 i -> j 的路径则 Tij=1

  - **如何计算T？**

    对Floyd算法改在，用逻辑**或/与**来替代算数**min/+**即可得到<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204142141551.png" alt="image-20241204142141551" style="zoom:50%;" />

    计算过程如下：依然是 O(n^3) 的

    <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204142250750.png" alt="image-20241204142250750" style="zoom:50%;" />

- **Johnson算法？**

**Johnson算法的基本步骤：**

1. **先给图加一个新节点**：在原图中添加一个新节点，给这个新节点与所有其他节点之间都加上权重为零的边。这个新节点称为“虚拟源节点”。
2. **对新图运行Bellman-Ford算法**：对这个新图（包含虚拟源节点）使用**Bellman-Ford算法**来计算**从虚拟源节点**到所有其他节点的最短路径。Bellman-Ford算法的好处是，它能处理带有负权边的图。
3. **重新标定图中的边权**：通过Bellman-Ford的结果，我们可以计算出每个节点到虚拟源节点的最短路径长度。然后，基于这些最短路径长度，我们**重新调整原图中的边权**。调整的方式是：对于**每一条边 (u, v) 其新权重变为原权重 加上节点u到虚拟源节点的最短路径      再减去节点v到虚拟源节点的最短路径**。这个步骤的目的是消除负权边带来的影响。
4. **对每个节点运行Dijkstra算法**：接下来，针对原图中的**每个节点**，使用**Dijkstra算法**来计算从该节点出发到其他所有节点的最短路径。因为我们在第二步已经调整过了边权，Dijkstra算法可以有效地处理它们。
5. **恢复原来的边权**：因为在第二步调整过了边权，所以在计算最终结果时，需要将Dijkstra得到的最短路径值恢复为原图的边权值。

**总结：**

- **添加一个虚拟节点**，用来计算所有节点到虚拟节点的最短路径。
- **用Bellman-Ford**处理这个虚拟节点，调整图中的边权，消除负权边的影响。
- **用Dijkstra**计算每个节点到其他节点的最短路径。



## 拓扑排序

- **有向无环图（DAG）：**一个无环的有向图

  怎么**判断**是不是DAG？-> **DFS没有出现指向祖先的回边**，即没有一个顶点有一条边指向先前访问过的顶点

- **拓扑排序：**由集合上的一个偏序关系得到集合的全序关系的操作

  偏序就是集合中的部分成员可以比较；全序是集合中的任何成员之间都可以比较

  - 偏序：自反 + 反对称 + 传递
  - 全序：R是集合X上的偏序，对于X的任何元素x, y，如果都有xRy或者yRx，则称R是全序关系
  - **按照有向图给出的次序**关系（对于有向图中没有限定次序关系的顶点，可以加上任意的次序关系）将图中顶点排成一个线性序列

- **AOV网(Activity On Vertex Network)：**用顶点表示活动，弧表示活动间优先关系的有向图。

  不应该出现环，否则有的活动以自己为先决条件。

- 拓扑排序的作用：**判断AOV网是否存在环路**

  - 如果存在环路，则求出图的拓扑序列不完整

    <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204143650553.png" alt="image-20241204143650553" style="zoom: 50%;" />

- **拓扑排序——法1**

  - 从有向图中**选取一个没有前驱**的顶点，并输出之;
  - 从有向图中**删去此顶点**以及所有**以它为尾的边**；
  - **重复**上述两步，**直至图空**，或者图**不空但找不到无前驱**的顶点为止。
  - 形式化的描述：
    - "没有前驱的顶点" = 入度为零的顶点；
    - "删除顶点及以它为尾的边" = 边头顶点的出度减一
    - 复杂度：O(n+e)

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204144313273.png" alt="image-20241204144313273" style="zoom:50%;" />

- **拓扑排序——法2**

  对 DAG 做深度优先搜索DFS

  **按退出DFS的先后记录下来的顶点序列即为逆向的拓扑排序序列**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204144516115.png" alt="image-20241204144516115" style="zoom:50%;" />

- **AOE（Activity On Edge）**网：**顶点表示事件，边表示活动**的网络<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204144622473.png" alt="image-20241204144622473" style="zoom:33%;" />

- **AOE的关键路径：**

  **问题：完成整个工程需要多少时间？哪些活动是影响工程进度的关键？**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204145414014.png" alt="image-20241204145414014" style="zoom:50%;" />

  - **概念：**

    - 最长的路径叫做**关键路径**

    - 影响工程进度的活动叫**关键活动**

    - **关键路径上的活动一定是关键活动**

  - **如何求关键路径？**

    - **e(i)** 和 **l(i)** 表示**活动 ai** 的**最早开始**时间和**最迟开始**时间

      - **e(i) - l(i)** 为活动ai的时间余量

      - **e(i)==l(i)** 的活动是关键活动

    - **ve(i)** 和 **ve(i)** 表示**事件 i** 的**最早开始**和**最迟开始**时间

  - **关键路径算法：**

    - 1.输入n个顶点和e条弧，建立AOE网。

    - 2.求出G的**拓扑排序，从源点出发**（若得到拓扑排序中顶点个数<n，说明G中存在环，算法终止）

      令 ve[0]=0 ，求其余结点的 **ve(j) = max{ ve(i) + dut(<i, j>) }** 最早开始不能早于这个时间

    - 3.求出G的**逆向拓扑序列，从汇点出发**，令 **vl(n-1) = ve(n-1)**

      求其余各结点的 **vl(i) = min{ vl(j) - dut(<i, j>) }** 最晚开始不能晚于这个时间

    - 4.根据求出的ve和vl，求每条弧上的活动 ai[j -> k] 的 **e(s)和l(s)** 

      <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204150338470.png" alt="image-20241204150338470" style="zoom:33%;" />

      **e(i) = ve(j); l(i) = vl(k) - dut(j, k)** 

    - 5.如果某条弧上的活动 **ai** 满足 **e(i) = l(i)**，则ai是关键活动

  - 复杂度 O(n+e)，求出的路径可能大于一条



## KMP

- **前缀后缀最大值**

  - 一个**长度为N**的字符串**S**，它有 **N+1** 个 前缀（**包括空前缀**），它有N+1个后缀 （包括空后缀）
  - 根据S得到N+1对序偶<前缀，后缀> **删除前缀、后缀等于S本身**的<前缀，后缀>，得到 **N对**<前缀，后缀>
  - 在这N对中，找到一对满足： 1. 前缀=后缀 2. 前缀后缀的长度最大 的值

- **next[i]** 表示 **S[0…i-1]** 这个子字符串的**前缀后缀最大值**

- **规定 next[0] = -1，next[1] = 0**

- **模板：**

  next数组的构建板子，可以用 kmp 匹配的板子来记忆，更好理解

  ```cpp
  // next[]数组的构建
  for (int i = 2, j = 0; i <= m; i ++ )
  {
      while (j>0 && p[i] != p[j + 1]) 
          j = ne[j];
      if (p[i] == p[j + 1]) 
          j ++ ;
      ne[i] = j;
  }
  
  // KMP匹配过程
  for (int i = 1, j = 0; i <= n; i ++ )
  {
      while (j>0 && s[i] != p[j + 1]) 
          j = ne[j]; //当主串S与模式串P失配时，j=next[j]，P向右移动j-next[j]
      if (s[i] == p[j + 1]) 
          j ++ ; //下一位匹配
      if (j == m)
      {
          j = ne[j];
          // ...匹配成功后的逻辑
      }
  }
  ```

- KMP模板可以改造进行各式各样的字符串匹配，模糊匹配等，改造的关键是在**失配函数**上做文章



## 网络流

- **标准流网络的抽象：有向图G(V, E)**

  - 结点表示城市，有一个**源节点s**和**汇节点t**
  - 结点间的有向边 **(u, v)** 表示运输路径和物流的方向
  - 边上的权重 **c(u, v)** 表示运量限制（**不是“边的权重”，网络流模型中边权都是1**）

  ![image-20241203101956980](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203101956980.png)

  - “**流 |f| = 11+8 = 15+4 = 19**”；每条边也有自己的流 **f(u, v)**

- **一些性质：**

  - **流网络是连通图，每个节点都在s->t的某条路径上**
  - 除源结点外，每个结点至少有一条流入的边；除汇点外，每个结点至少有一条流出的边。
  - **容量限制:** 对于所有的结点u, v有：**0 <= f(u, v) <= c(u, v)**
  - **流量守恒: **除了源和汇节点，每个节点的 **Σ流入=Σ流出**，即物料只是“流过”，没有累加/聚集

- **一般流网络 -> 化为标准流网络处理**

  - 1.具有**反平行边**的流网络	

    - 对每一组反平行边 (u, v) 和 (v, u)，选择其中的一条，比如(u, v)，然后加入一个新的结点v’，将其分为两条边(u, v') + (v', v)，并将两条新加入的边的容量设为被替代掉的边 (u, v) 的容量，即：

      **c(u, v') = c(v', u) = c(u, v)**，可以证明转化前后的网络是等价的

      <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203104020246.png" alt="image-20241203104020246" style="zoom:50%;" />

  - 2.具有**多个源节点和汇**节点的流网络

    - **有多个源节点 {s1,s2,...,sm}：** 加入一个**超级源结点s**，并加入有向边 (s, s_i)， 然后令 **c(s, s_i)=∞** 

    - **有多个汇节点：处理同理**

      <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203104438390.png" alt="image-20241203104438390" style="zoom:50%;" />

- **※Ford-Fulkerson方法**

  通过不断增加可行流值的方法确定最大流

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203105525447.png" alt="image-20241203105525447" style="zoom:67%;" />

  - **残存网络 G_f(V, E_f)**

    对于给定流网络 G 和流量 f，G 的残存网络 **G_f** 由 **G 中的节点**和以下的所有边组成：

    - 1.若 **f(u, v)<c(u, v)** 则将**边(u,v)和它的反向边(v,u)**都加入G_f，并设其**“残存容量”**为：
      - **c_f(u, v) = c(u, v) - f(u, v)**
      - **c_f(v, u) = f(u, v)**
    - 2.若 **f(u, v)=c(u, v)**，则只将**反向边(v,u)**加入G_f，且**c_f(v, u) = f(u, v)**
    - 残存容量表示这个方向的这条边可以增加流量的空间

  - **增广路径 p**

    - **f'** 是 G_f 中的一个流， 定义 **f ↑ f'** 是对原本G的流f的递增，且有 **|f ↑ f'| = |f| + |f'|**
    - **增广路径p** 是其残存网络G_f 中一条从源结点s到汇点t的简单路径
    - 对于一条**增广路径p，能增加的最大流值称为该路径的残存容量**，等于p上**所有边残存容量的最小值(瓶颈)**
    - 将增广路径的流 **f_p** 与 **f** 叠加，就可以对流进行递增效果

  - **流网络的切割**

    G=(V, E)的切割 (S, T)，将**V分成两部分S和T=V-S**

    - **横跨切割(S, T)的净流量 f(S, T)为**<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203112328895.png" alt="image-20241203112328895" style="zoom:50%;" />

      **双向都要算！！！**

    - **切割(S, T)的容量 c(S, T)为**<img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203112440880.png" alt="image-20241203112440880" style="zoom:50%;" />

      **只计算 S->T 的单向！！！**

    - **最小切割：网络中容量 c(S, T) 最小的切割**

  - **引理： 任何切割的净流量和网络流的关系：f(S, T) = |f|**

    - 也即，最大流不可能超过最小切割的容量，**最大流值等于最小切割的容量**

  - **最大流最小切割定理**

    f是G=(V, E)的一个流，以下三个命题是等价的

    - f是G的**最大**流
    - 残存网络G_f中**不包括任何增广**路径p
    - |f|=c(S, T)，其中(S, T)是流网络G**的某个切割**

  - **朴素FF方法求解最大流的workflow：**

    - 迭代建残存网络/找增广路径，由 **f_p ↑ f** 逐步增加可行的流 |f|。直到找不到p终止

    - **如何找增广路径？**

      DFS或BFS即可

    - 每次循环：**计算残存网络 + 寻找增广路径 + 更新每条边的流值**

    - 复杂度 **O(|E|*|f_max|)**

  - 问题：**复杂度和最大流值有关**，不稳定，当最大流|f_max|非常大时效率非常低

- 改进：**Edmonds-Karp算法**

  **使用 BFS 寻找 s->t 的最短路径(经过最少节点)作为增广路径**

  ![image-20241203115329618](C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241203115329618.png)

  - 复杂度**O(V*E^2)**，稳定且与最大流值无关



## NP

- 如果一个问题П存在一个运行时间为O(n^k)的算法， 其中k为常数，则称问题П存在多项式时间算法。

  - 存在多项式时间算法的问题看做是易解问题
  - 超多项式时间算法的问题看做是难解问题

- **难解问题不是不可解**问题，可解、但时间复杂度高(超多项式时间)的问题也是难解问题

- 多项式时间复杂性具有**独立性**，在某一计算模型下有多项式时间，在其它模型下也一定具有多项式时间，如RAM模型、Turing模型。

- **判定性**问题(Decision-problem)：仅回答Yes/No的问题，判定性问题也是有易解和难解的

- **功能性**问题：由一个函数f给出，目标是计算f在某种定义下的值。 如最优化问题，求目标函数的极值。

- **非确定性算法**：算法流程为 ”**猜测**阶段(以非确定性的方式) + **验证**阶段(用确定性的算法)“

  - 非确定性算法不是一个可以实际运行的算法

- **P(Polynomial)类问题**：具有多项时间复杂度的问题（确定性算法）

  - 可以用多项式时间的确定性算法来进行判定或求解

- **NP类问题**：具有多项式时间非确定性算法的问题

  - **必须存在一个确定性算法**，能够**以多项式时间来检查和验证在非确定的猜测阶段**所产生的解是 否是问题的一个正确答案
  - 是难解问题的一个子类

- 尽管NP类问题是对于判定问题定义的，但已经证明可以**在多项式时间应用非确定性算法解决的所有问题**都属于NP类问题

  - P类问题的算法一般具有一个计算公式，将输入带入公式，就可以算出结果，如x+y
  - NP类问题没有明确的计算公式可以求解，比如没有一个 公式可以计算出最大的质数是多少或者能够求解哈密顿回路问题

- **规约：**

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204154736253.png" alt="image-20241204154736253" style="zoom:50%;" />

- **NP-hard问题**：

  难解问题中还有一类问题， 虽然也能证明所有的NP类问题可以在多项式时间内变换为问题 Π，但是并不能证明问题Π是NP类问题，所以问题Π不是NPC的， 但是问题Π至少与任意NP类问题有同样的难度

- **NP完全问题（NPC）**：

  希望能够在NP类问题的内部找到一种方法，比较两个问题的计算复杂性，并进一步找到NP类问题中最难的问题。

  比较两个问题的计算复杂性的方法就是**问题变换（归约）**。

  <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204154835964.png" alt="image-20241204154835964" style="zoom:50%;" />

  - NP完全问题是NP类问题的一个子类，同时也是NP 类问题中最难的一类，其中**任何一个问题都没有找到多项式**时间算法。
  - NPC问题有一种非常令人惊奇的性质：即如果一个NPC问题能在多项式时间内得到解决，那么，NP中的每一个问题都可以在多项式时间内求解，即会有NP=P。
  - <img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204155000851.png" alt="image-20241204155000851" style="zoom:50%;" /><img src="C:\Users\kobedai\AppData\Roaming\Typora\typora-user-images\image-20241204155200955.png" alt="image-20241204155200955" style="zoom:50%;" />  

  
