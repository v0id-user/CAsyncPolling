# Ideas
This is a list of ideas for CPoll and how I think about it.

## 1. No Multi-threading
The easy way to implement cocurrency is to use multi-threading. 
However, I want to see how much I can do in C without using multi-threading.
Means that I need to build the poll system using a single thread.
I can use system specific functions to do it. So that will make it easy 
for cross platform support.


## 2. How will I do it?
Welp, there is a way with longjmp and setjmp or I could try to learn how to manipulate the EIP and ESP stack and registers for linux. On windows I could use the fibers apis todo it, but yet I don't know if they are easy to manage as polling.

### UPDATE
In [Thoughts.md](THOUGHTS.md), I came across a blog post that discusses exactly what I plan to implement. It's called Cooperative Multitasking and relies on context switching and yielding.  

On Windows, there’s an API for this called `Fiber`, while on Unix, the equivalent is `ucontext`. However, the issue with Unix is that `ucontext` is not a standard POSIX API, so I’ll need to find a workaround for it.  

## 3. End result
~~I will understand much better how async works in a simple way under the hood, and the code that I will write will look like:~~

~~poll_t poller = poll_new();~~ \
~~poller->chain(func1, args1);~~ \
~~poller->chain(func2, args2);~~ \
~~poller->chain(func3, args3);~~ \
~~poller->wait();~~ 


~~Something simple like this will immidiatly fire the functions and round robin them. and you can wait for it to finish and get results.~~


I changed the plan, I the end result is yet to be determined as I code.