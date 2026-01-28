# CSCI 235 - The Directory Daemon:

## Project 6 - It's That Time of Year

Ok we're dealing with trees. Quite festive (though they aren't the typical evergreen ones we tend to think of)!

Since we have a _lot_ of files for the filesystem theming, we've decided to keep this short and contained in a separate, unrelated spin-off.
Kind of how holiday episodes are like for your favorite childhood cartoons.

TLDR: BSTs. BTS. Same difference. Anyway, we'll keep this short since it's finals!

You'll be doing the following:

1. Searching in a BST
2. DFS Traversal (IN, PRE, and POST)
3. BFS Traversal (since this is like a need to know for tree-questions on the technical)

### Task 1 - `contains`

You've been given the `Node` & `BST` classes -- but they're incomplete!

We need to search whether or not our tree contains some value, so implement the following:

```c++
/**
 * @brief Checks if a specific value exists in the BST.
 * @param data A const reference of type T, specifying the value to search for.
 * @return true If the data is found in the tree, false otherwise.
 */
BST::contains
```

By the by, you _could_ use a helper function for this -- but try writing a solution that doesn't do so! Set it up using a `while` loop, and iterate `Node` by `Node`,
instead of using recursion.

### Task 2 - `DFS::collect`

Ok, now we get to some recursion (you could technically do it with stacks, but c'est la vie). You should know about pre, in, and post order traversals. If you don't, then here's the idea: these traversal methods ONLY differ in the relative position of where you "process the parent node."

That is:

- "pre" means you would "process" the parent (ie. node that you're currently dealing with in the traversal), **before** you visit its next children.
- "in" means processing the parent **in-between** its children (ie. left child, then parent, then right child)
- "post" means process the parent **after** processing its children.

In the case of our function, "processing" refers to adding the value stored within that Node to the resultant vector. And the fun part about this is that we can have _one_ function, that does _every_ traversal, with rather little hassle. And that's exactly what we'll do!

In `Collector.hpp` define three things:

1. A namespace called `DFS` (stands for `Depth First Search`)
2. An enum `Order`, within the `DFS` namespace (so when referencing it in main, you would type something like `DFS::Order`), with the following values:

   - `IN_ORDER`
   - `PRE_ORDER`
   - `POST_ORDER`
     These names should _match exactly as they are here, uppercase, underscore, and all._

3. An `internal` namespace within the `DFS` namespace, so we can hide any helper functions (or at least, make it clear to a potential user that they shouldn't use this function directly).

So altogether it should look something like, the following, but I've left out some of the syntactical keywords, so you don't just copy what I have.

```c++
DFS {
   Order {
      IN_ORDER,
      PRE_ORDER,
      POST_ORDER,
   }

   internal {
      // we'll put helpers here.
   }


}
```

Ok organization aside, now we write two functions. Note two things:

1. The namespacing!
2. The template so you should have a `template <class T>` attached to each of the collect functions.

```c++
/**
 * @brief Performs a Depth-First Search (DFS) to collect all elements in the tree.
 * @tparam T The type of valued stored within the BST's nodes,
 * and to be stored in the resultant vector.
 *
 * @param tree A const reference to BST containing type T to traverse.
 * @param traversal_order A const reference to the Order (the enum we defined)
 * to traverse (IN_ORDER, PRE_ORDER, POST_ORDER).
 *
 * @return std::vector<T> A vector containing the collected elements,
 * in the order of traversal
 */
DFS::collect

/**
 * @brief Helper function to recursively
 * collect nodes based on the traversal order.
 * @param traversal_order The order to traverse (IN_ORDER, PRE_ORDER, POST_ORDER).
 * @param collected A (non-const) reference to the vector
 * where data will be stored.
 * @param root The root of the current subtree.
 *
 * @note You should use the vector reference passed in the parameters
 * to maintain a single instance of a vector that stores all the nodes' values
 * as you visit them. DO NOT use a return value here, as this is a helper.
 *
 * Instead, use the DFS::collect method as a wrapper for calling THIS function,
 * with the proper parameters.
 */
DFS::internal::collectHelper
```

### Task 3 - `BFS::collect`

Ok last one. We've done Depth-First Search (DFS) with recursion. Now we'll write up Breadth-First Search (BFS), or you may know it as level-order traversal.

#### An Example

As a helpful guide, queues are the name-of-the-game for BFS. The trick is to queue the root node, and the process every node until the queue is empty -- but the catch is that everytime you process a node, you then add its children (if any) to the queue.

Step 1: Root is in the queue

```
queue: 50 (ie. root)

      50
      /  \
   30      70
   /
20
```

Step 2: Process root & pop. I used (q) to show what's in the queue.

```
queue: 30,70 (50 is popped)
processing: 50

      50 (here)
      /  \
   30(q)      70(q)
   /
20
```

Step 3: Process next node

```
queue: 70,20 (30 is popped)
processing: 30

      50 (read)
      /      \
   30(here)   70(q)
   /
20(q)
```

And rinse and repeat. Get the gist?

#### The Actual Method

Create a new `BFS` namespace within the `Collector.hpp`, and add the following. By the way, don't use helper functions for this traversal. You can (and should) do it without recursion.

```c++
/**
 * @brief Performs a Breadth-First Search (BFS) to
 * collect all elements in the tree level-by-level, left-to-right.
 * @tparam T The type of valued stored within the BST's nodes,
 * and to be stored in the resultant vector.
 *
 * @param tree A const reference to the BST (of type T) to traverse.
 *
 * @return std::vector<T> A vector containing the
 * collected elements, in level-order
 */
BFS::collect
```

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. BST.cpp
2. BST.hpp
3. Collector.cpp
4. Collector.hpp

```

Although Gradescope allows multiple submissions, it is not a platform for testing and/or debugging, and it should not be used for that purpose. You MUST test and debug your program locally.

Before submitting to Gradescope, you MUST ensure that your program compiles using the provided Makefile and runs correctly on the Linux machines in the labs at Hunter College. This is your baseline—if it runs correctly there, it will run correctly on Gradescope. If it does not, you will have the necessary feedback (compiler error messages, debugger, or program output) to guide you in debugging, which you don’t have through Gradescope. “But it ran on my machine!” is not a valid argument for a submission that does not compile. Once you have done all the above, submit it to Gradescope.

### Testing: Compiling with the Included `Makefile`

\*For your convenience, we've included a `Makefile`, which allows you to quickly re-compile your code, instead of writing `g++` over and over again. **It also ensures that your code is being compiled using the correct version of C++. And by correct one, we mean the one the auto-grader uses.\***

In the terminal, in the same directory as your `Makefile` and your source files, you can use the following commands:

```bash
make # Compiles all recently modified files specified by the OBJs list
make clean # Removes all files ending in .o from your directory, ie. clears your folder of old code
make rebulild # Performs clean and make in one step
```

This assumes you did not rename the Makefile and that it is the only one in the current directory.

### Debugging

_Here are some quick tips, in case you run into the infamous "It compiles on my machine, but not on Gradescope"_

1. Ensure your filenames are correct (case-sensitive), and don't contain leading / trailing spaces
2. Ensure that your function signatures are correct (ie. function name spelling, order/type of the parameters, return type).
   **This also includes `const` declarations. Remember, if a function does _not_ modify the underlying object, it must be declared `const`.**

---

### Grading Rubric

- **Correctness:** 80% (distributed across unit testing of your submission)
- **Documentation:** 15%
- **Style and Design:** 5% (proper naming, modularity, and organization)

---

### Due Date

This project is **due on December 12**.
_No late submission will be accepted._

---

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan
