# Board modelisation

To compute the path with the shortest time to join a $d_1$ point from an $d_2$
one, given a robot which only can make feed-forward movements (i.e. only
rectilinear movements and stationary rotations), we establish the following
model for the board:

- The table is modeled by a graph whose the nodes are positions in the table.
These positions are abstracted as cells in a matrix of shape $(N, M)$. Then,
the vertecies list is 
  $$V = [|1; N|] \times [|1; M|]$$
- Sometimes, the robot has to make movements without passing some obstacles.
  Then, for some $t$ moment, a set of obstacles positions $O_t = \{a_k=(i_k,
  j_k), 1 \leq k \leq N_{\text{obstacle}, t}\}$ is registered
- $\forall t$, each position $a = (i, j)$ which can be directly bound from
  another one $b = (i', j')$ with a segment passing by no obstacle is bound by
  an edge. The edges at a $t$ moment is therefore
  $$E_t = \{\{a, b\}, \forall (a, b)\in V^2 \mid a\neq b 
  \land (\forall c \in [a, b], c \notin O_t) \}$$
  ($[a, b]$ is the geometrical segment)
- each edge $\{A, B\}$ is labeled by a time duration for the robot
  to cross it. This time is 
  $$\Delta T(\{a, b\}) = \frac{||\overrightarrow{ab}||_2}{S}+\Delta T_\omega$$
  with $S$ the constant maximal speed of the robot and $\Delta T_\omega$ an
  average time for the robot to accelerate, decelerate and perform its
  stationary rotation.

## Shortest path in time

We use the A* algorithm to find out the shortest path in time.

With the $\Delta T_\omega$ bias value, a path with many edges should not be
returned by the algorithm to promote a path with a minimum of points where the
robot should stop to rotate.

However the algorithm might be slow if it always first try to take path with small
edges. To speed it up, we use an heuristic which will incite to take big edges
pointing to rectilinearly joinable positions which are the closest to the final
position.


