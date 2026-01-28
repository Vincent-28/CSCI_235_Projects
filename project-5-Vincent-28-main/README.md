# CSCI 235 - The Directory Daemon:

## Project 5 - Wait. Wait Go Back (Undo/Redo Operations)

Kay not wasting time, read this or you will be SUPER lost:

### Working Smart not Hard

Ok elephant in the room. Alright, let's talk about some of the previous projects. Remember all that `new` and `delete` nonsense? Manually tracking pointers, getting yelled at by `ASan` for memory leaks... yeah, that was annoying. I get it.

The good news is, C++ gives us a much better, safer way to handle memory: **Smart Pointers**.

We'll be focusing on `std::shared_ptr`. This is a "smart pointer" that lives in the `<memory>` header. It's a wrapper around a raw pointer that keeps track of how many references point to an object on the heap. When the _last_ `shared_ptr` pointing to that object is destroyed (like when it goes out of scope), it automatically calls `delete` on the raw pointer for us. By the by, there are others like `std::unique_ptr` and `std::weak_ptr` but they're not too big of a concern right now.

To dereference a shared pointer, it's the very same syntax (eg. `mySharedPtr->myFunction()`)

You'll go over this more in-class, but...
**TLDR: Use smart (for now shared) pointers when performance isn't mission critical (in this case it is not) and you want automatic memory management (ie. no need to call delete). See the links below for syntax.**

We'll be using these to build a robust **Undo/Redo** system for our image editor, using a design pattern called the **Command Pattern**.

**BY THE WAY** don't sleep on design patterns. In a nutshell, they're common ways to solve common problems. Think like hammers to nails. I mean you could use something else to hammer in the nail. But this is like if you see a nail and you're like, hmmm well how do I deal with this problem, you don't have to think if you know what a hammer does.

#### Useful Links:

- [Intro to std::shared_ptr in C++](https://www.geeksforgeeks.org/cpp/shared_ptr-in-cpp/)
- [My favorite website for design patterns](https://refactoring.guru/design-patterns/command)

### Some Housekeeping

Ok by the way, having like 5 million different files in one directory is nightmarish. So I've gone ahead and refactored these things. All the code you'll be writing will be placed in the `history/` directory. Note for imports DO NOT USE RELATIVE ADDRESSING (PLEASE). See `ImageFilter.hpp` on examples of addressing across modules/directories (eg. from the `filters` module to the `files` module).

Of course, you're also going to have to update the Makefile (tee-hee). Ok it's not that bad, just like follow the pattern there.

TLDR: Address from the root of your repository folder. So when including say, the `Command` interface in your `main` file, you would say, `#include 'history/Command.hpp`.

### Before You Continue

Make sure the given `main.cpp` file compiles AND runs! You should get a purple amogus picture after doing so.

Work through the tasks sequentially. This project builds on itself, so make sure Task 1 is solid before moving to Task 2.

**Don't Forget\!**

1.  Names of classes and methods must exactly match those in this specification.
2.  Functions that _do not_ modify the object must be declared `const`.
3.  Document your code\!
4.  Do NOT use namespace `std`.

---

## Task 1: The `Command` Interface

**In this task you'll be creating:**

1.  `history/Command.hpp` (only)

First, we need to generalize _what_ an "action" to be undone or redone is. We're going to create an an interface that defines what any command in our system must be able to do: `execute`, `undo`, and `redo`. Interfaces are basically abstract class, but you don't have any implementation (except for the destructor in this case, which is declared as default but that's beside the point), so there will be no `.cpp` file.

TLDR, all your functions (except the destructor) will be **pure virtual**.

Write out the following function sigatures to match the specs:

```c++
/**
 * @brief Executes the command's primary action
 * - Saves the "previous" state before execution of the action
 * - Saves the "after" state after execution of the action.
 */
Command::execute

/**
 * @brief Undoes the action performed by execute()
 * typically by restoring the "previous" state.
 */
Command::undo

/**
 * @brief Re-applies the action performed by execute()
 * typically by restoring the "after" state (avoiding recomputing the command).
 */
Command::redo

/**
 * @brief Returns a stringified version of the command.
 * @return A const std::string describing the command.
 */
Command::toString
```

And declare the destructor virtual and default as so:

```c++
/**
 * @brief Virtual destructor.
 */
virtual ~Command() = default;
```

---

## Task 2: Creating `FilterCommand`

Now we'll make our first _concrete_ command. This class will implement the `Command` interface and will specifically handle _applying an image filter_. It needs to store the state of the image _before_ the filter was applied and _after_ it was applied, so it can undo and redo the action.

**In this task you'll be creating:**

1.  `history/FilterCommand.hpp`
2.  `history/FilterCommand.cpp`

Your `FilterCommand` class must **publicly inherit** from the `Command` interface you just made.

### Private Members

You'll probably want to store:

1.  A reference to the `ImageFile` being modified (NOT A COPY).
2.  A `std::shared_ptr<ImageFilter>` to store the _actual_ filter being applied.
3.  Two 2D `Pixel` vectors to store the "before" and "after" states

But this isn't cut and dry. You can totally like store one `Pixel` vector and toggle between the two depending on whether you undid or redid, or just recompute when redoing, etc. Many ways to make an omelette.

### Constructor (Semi-Provided)

First, add the signature to your `.hpp` file:

```c++
/**
 * @param imageFile The ImageFile object to be modified as a (non-const) reference
 * @param filter The filter to be applied (e.g. InvertFilter) as a const reference.
 */
FilterCommand::FilterCommand
```

I'll be nice (don't get used to it), and give you what the `shared_ptr` member should be. The rest is on you (told you not to get used to it).

```c++
/// Add this to your .hpp
/// Yes it is const -- because we are only assigning the filter pointer once and won't repoint it to some other object.
const std::shared_ptr<ImageFilter> applied_filter_;
```

However, the constructor is a bit tricky because it uses a new `clone()` method. We've added `clone()` to the `ImageFilter` class for you.

**Why?** The constructor receives a `const ImageFilter&`, which is a _base class_ reference. We don't know if it's _actually_ an `InvertFilter` or a `ColorFilter`. We need to store a _copy_ of that specific derived filter, and `clone()` handles this by returning a `std::shared_ptr` to a new copy of the _correct_ derived filter.

**So, add this line in your constructor's intializer list to your `.cpp` file.**

```c++
   /// ... function signature, etc.
    , applied_filter_ { filter.clone() }
    /// ... The rest of your initialization list here.
{
}
```

### Public Methods

Now, implement the rest of the public methods. Remember to add `override` to the virtual functions from the `Command` interface\!

```c++
/**
 * @brief Executes the filter application.
 * @post
 * 1. The pixel data of the image's state *before* filtering is stored.
 * 2. The filter is applied to the image passed in the constructor (and modifying that original image object directly)
 * 3. (depending on implementation) The pixel data of the image's *after* filtering is stored.
 */
execute

/**
 * @brief Undoes the filter application.
 * @post The modified Image's pixels are restored to the pixel data before the filter was applied.
 */
undo

/**
 * @brief Re-applies the filter application.
 * @post The modified Image's pixels are restored the pixel data after the filter was applied.
 */
redo

/**
 * @brief Gets the image file modified by this command.
 * @return The ImageFile object.
 */
getModifiedImage

/**
 * @brief Gets the filter that was applied by this command.
 * @return A shared_ptr to the ImageFilter.
 */
getAppliedFilter

/**
 * @brief Generates a string representation of the command.
 * @return A string in the format: "<Filter Name> --> <Filename>"
 */
toString
```

---

## Task 3: The `CommandManager`

Finally, we need a class to manage our history. This class will hold two **stacks** of `std::shared_ptr<Command>` objects: one for `undo` operations and one for `redo` operations.

Thanks to polymorphism, these stacks can hold _any_ object that inherits from `Command` (like our `FilterCommand`), and we can call `execute()`, `undo()`, etc., without ever knowing what _kind_ of command it is.

**In this task you'll be creating:**

1.  `history/CommandManager.hpp`
2.  `history/CommandManager.cpp`

### Private Members

1.  A stack of `std::std::shared_ptr<Command>` containing all the commands that can be undone.
2.  A stack of `std::std::shared_ptr<Command>` containing all the commands that can be redone.

### An Example

I mean you guys have used Google Docs so it's the exact same. And if you haven't, I have no words. Simply none.

Anyways, here’s a walkthrough of a scenario for undoing/redoing a series of filters showing the state of the `undo` stack and `redo` stack at each step.

I _won't_ use a ImageFilter example, because guess what? We have ANY command here, so theoretically we can use the _exact same `CommandManager`_ class to do `undo` and `redo` operations for some other situation.

Let's use `C1` (Invert), `C2` (Color Filter), `C3` (Channel Swap), and a new action `C4` (New Invert).

Here's the same scenario using a simple text editor analogy.

---

### Undo/Redo Example: Text Editor

Imagine you're tracking commands in a text editor.

1.  **Initial State:**

    - **Text:** ""
    - `Undo`: `[ ]`
    - `Redo`: `[ ]`

2.  **Action 1: `doCommand(Type "Hello")`**

    - **Text:** "Hello"
    - `Undo`: `[ Type "Hello" ]`
    - `Redo`: `[ ]`

3.  **Action 2: `doCommand(Type " world")`**

    - **Text:** "Hello world"
    - `Undo`: `[ Type "Hello", Type " world" ]`
    - `Redo`: `[ ]`

4.  **Action 3: `doCommand(Bold "world")`**
    - **Text:** "Hello **world**"
    - `Undo`: `[ Type "Hello", Type " world", Bold "world" ]`
    - `Redo`: `[ ]`

---

Now, you hit undo twice.

5.  **`undo()`:** (Undoes the bold command)

    - **Text:** "Hello world"
    - `Undo`: `[ Type "Hello", Type " world" ]`
    - `Redo`: `[ Bold "world" ]`

6.  **`undo()`:** (Undoes typing " world")
    - **Text:** "Hello"
    - `Undo`: `[ Type "Hello" ]`
    - `Redo`: `[ Bold "world", Type " world" ]`

---

At this point, you could redo (re-type " world") or undo (delete "Hello"). Instead, you choose to type something new.

7.  **Action 4: `doCommand(Type " there!")`**
    - This new command is executed.
    - **Text:** "Hello there!"
    - `doCommand` pushes `Type " there!"` onto the undo stack.
    - `doCommand` **clears the redo stack**.
    - `Undo`: `[ Type "Hello", Type " there!" ]`
    - `Redo`: `[ ]`

The "future" where you could have re-applied `Bold "world"` or `Type " world"` is now gone, invalidated by your new action.

### Public Methods

Ok, example aside implement the following public methods to manage the command history.

```c++
/**
 * @brief Default constructor.
 */
CommandManager::CommandManager // You can just use = default

/**
 * @brief Executes a new command.
 *
 * @param command A const reference to a shared_ptr<Command> to be executed.
 * @post
 * 1. The command's execute() method is called.
 * 2. The command is pushed onto the undo stack.
 * 3. The redo stack is cleared.
 */
CommandManager::doCommand

/**
 * @brief Undoes the most recent command.
 * @post
 * 1. If the undo stack is not empty:
 * 2. The top command is popped from the undo stack.
 * 3. The command's undo() method is called.
 * 4. The command is pushed onto the redo stack.
 */
CommandManager::undo

/**
 * @brief Redoes the most recently undone command.
 * @post
 * 1. If the redo stack is not empty:
 * 2. The top command is popped from the redo stack.
 * 3. The command's redo() method is called.
 * 4. The command is pushed onto the undo stack.
 */
CommandManager::red

/**
 * @brief Checks if an undo operation is possible.
 * @return True if there are moves to be undone, false otherwise.
 */
CommandManager::canUndo

/**
 * @brief Checks if a redo operation is possible.
 * @return True if there are moves to be redone, false otherwise.
 */
CommandManager::canRedo
```

---

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. Command.hpp
2. FilterCommand.cpp
3. FilterCommand.hpp
4. CommandManager.cpp
5. CommandManager.hpp

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

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan
