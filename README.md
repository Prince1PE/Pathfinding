<h1>Visual Pathfinding</h1>

<p>This is as far as im concerned, my first <strong>big</strong> project, i've spent more time on this than I probably should have :P</p>
<p>It is a pathfinder with a couple extra features, essentially you place an entry and exit node and the algorithm should be able to navigate through the relevent obsticles and find a path.</p>

<h3>Installation and running</h3>

Type the following into your terminal

>\>\>\> git clone https://github.com/Prince1PE/Pathfinding.git<br>
>\>\>\> cd Pathfinding<br>
>\>\>\> gcc run.c<br>
>\>\>\> ./a.out<br>

<p>You can customise the size of your grid by enterring your desired height and width after you type ./a.out</p>
<p>Additionally you can type ./a.out MAX_HEIGHT MAX_WIDTH in order to get the maximum height and width for your relevent screen</p>
<p>You can alter screen sizes using the resize command later on in the code</p>
<strong>If you enter too high of a grid value, it may cause your computer to run slower<br></strong>

<p><br>I really wanted to stick to using just gcc with no flags. <br>In hindsight - that was a terrible idea, or I should have used a make file.<br> Using math.h or the curses library would have been very useful :/</p>

<h3>Basic controls</h3>
<h1></h1>
<p>Use WASD to move, or alternativly, you can use the arrow keys.</p>

<ul>
  <li>Space bar - Places/Removes a block </li>
  <li>H - Press 'h' to access the help menu</li>
  <li>E - Press 'e' to place the entry node </li>
  <li>R - Press 'r' to place the return node </li>
  <li>Q - Press 'q' to exit the program </li>
</ul>

<h3>Command Line</h3>
<h1></h1>
<p>You can run algorithms and access extra functionality using the command line of the program</p>
<p>To access it, simply click the '/' key, enter your command, followed by a space and any arguments required</p>

<h2 style="text-align:center; color:grey;"><u><strong>Use</strong></u></h2>

> <em><h2>Bruteforce - <strong>"/use bruteforce"</strong></h2></em>
> <p>By enterring "/use bruteforce" you can run the bruteforce command, this will manually search every possible outcome. The method used is fairly inneficient, however it does produce quick results, it was quicker than bfs, hence why you no longer see the option to run a bfs search, if you time it, it may also appear quicker than other algorithms. thats because as other algorithms shown here travel 1 square at a time, this one maps upto 4 of the surrounding squares at once, per node visited.</p>
> <p>It starts by setting the entry nodes distance at 0 and makes it visited, sets a counter at 1 and then it loops through the entire grid.<br> If it finds a distance one less then the counter, it maps all adjacent squares as long as it is unmapped, it also records each nodes parent node</p> 
> <p>Once it finds the exit node, it uses the relevent parent nodes in order to find the way back</p>
> <em><p>Since this is an unweighted grid, and the distance between each node is the same, Dikjstra and bfs all simply just flood the grid in the same manner, bfs does use a queue in order to store the items, however I have found this is very slow and jittery, I have kept the source code in, however I have removed the way to run it</p></em>

><em><h2>A* - <strong>"/use astar"</strong></h2></em>
><p>By enterring "/use astar", you can run the Astar algorithm, this is the recommeneded algorithm, it is also the only algoirithm that knows the location of the exit node and is therefore the most efficient algorithm</p>
><p>This algorithm works by calculating a certain heuristic, this heuristic can change and in certain cases makes the algorithm more/less efficient. I have found in my case, after trying a couple heuristics and getting the following results:</p>
><img src="./READMEstuff/Failed1.png" alt="drawing" width="450"/>
><img src="./READMEstuff/Failed2.png" alt="drawing" width="300"/>
><p>I decided to change my heuristic to the following</p>
>
>><code>int H = sqrt(pow(valX - DestX, 2));<br>
>>int G = pow(valY - DestY, 2);<br>
>>return G + H;</code>
>><em><br>Because using the maths library required to use flags in gcc, or a more sensible aproach like using a make file, I coded my own functions (:</em>
>>
><p>This meant it worked really well, by calculating the relevent distance to the exit node, it was able to get a general direction in order to find the exit node while searching the least amount of squares. It works by adding everything into a sorted linked list, ordered by the relevent distances, it would then pop the last node from the list.</p>

><em><h2>DFS - <strong>"/use dfs"</strong></h2></em>
><p>By enterring "/use dfs", you can use the dfs algorithm. Honestly this isn't a very practical algorithm as far as pathfinding goes, since it appends all discovered nodes onto a stack instead of a queue so the first element found is the first one explored, this makes it very ineffcieint, sometimes searching the edges of the grid to find an exit ndoe that is right next to the entry node. I have added some extra code, so that if the algorithm moves past the entry node in order to find the relevent path, the algorithm changes the parent nodes to the start node.</p>
><p>Obviously there are exceptions to this rule, however in general this is the worst algorithm to use, dfs is generally better used to make mazes 😅</p>

