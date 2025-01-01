# Thoughts
An unordered place for my thoughts.

## Why I want to do this?
As I said on multiple places, I want to sharpen my C skills and learn how to do things in a simple way.

## Inspiration and motivation
I watched [Tsoding | I made Futures from scratch](https://www.youtube.com/watch?v=sNHzizPu7yQ) and [Tsoding | Async vs Multithreading](https://www.youtube.com/watch?v=IGv5WYYmyfo) and I was like "I want to do this in C".

# The end goal in mind
I want to be able to read 6GB of files in async manner, and I want to be able to do it in a simple way.
SIMPLE IS IMPORTANT FOR ME. AND NO ASSEMBLY USEAGE I'm not building a kernel, I'm building a SIMPLE library.

## Notepad
(1/1/2025 12:15AM asia/riyadh)

I did not watch the full videos of Tsoding, but I did watch the first half of each video, and I grasped the idea of how to do it.
The idea is relativly simple, you need an array of functions that you call each one after the other. In round robin fashion. So I
need to save the state and this might be a problem. In [IDEAS.md](IDEAS.md) I have some ideas of how to do it. I said that I may 
save the EIP and ESP stack and registers, but talk is cheap how will I do it?

I will try to find some resources and will document my progress here.

(1/1/2025 12:33AM asia/riyadh)
I'm currently reading [The pattern of async/await](https://en.wikipedia.org/wiki/Async/await) to deepen my understanding of the concept.  
Additionally, I'm revisiting [What is Asynchrony](https://en.wikipedia.org/wiki/Asynchrony_(computer_programming)) along with other resources on the general topic of concurrency to further enhance my understanding.

I find this approach to be a good practice overall. It may be a bit slow, but it pays off in the long run, and I'm thoroughly enjoying the process of learning and gaining new insights.

(1/1/2025 12:41AM asia/riyadh)
I found something interesting, I found the [Cooperative multitasking article](https://en.wikipedia.org/wiki/Cooperative_multitasking) that talks about the approuch that I want to do, but it's name is `Cooperative Multitasking` where as mentioned in the article "in which the operating system never initiates a context switch from a running process to another process. Instead, in order to run multiple applications concurrently, processes voluntarily yield control periodically or when idle or logically blocked" which is exactly what I want to do, and this is a good starting point.

Now what I want to do is implement our own context swtich in `poll.h` and see how it works out for me. Also mentioned in the article that I need to deal with something called [process scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)) I think maybe I need to implement it too or it's provided by the OS I will see in that too.

I need also to think about how to impelement the [Event loop](https://en.wikipedia.org/wiki/Event_loop) that will handle scheduling between the tasks a.k.a. the functions chained in the poll array.

I found this blog post [User-space cooperative-multitasking](https://brennan.io/2020/05/24/userspace-cooperative-multitasking/) I will look into the implementation and try to understand it and implement it in my own way.

(1/1/2025 4:19PM asia/riyadh)
I now understand what I need to do. As mentioned in the blog post, we need to perform a manual context switch using a yield function. This approach is reasonable, but I still need to figure out how and when to use yield. Developing a clear engineering plan will likely help with this.

The blog post demonstrates manipulating the EIP and ESP registers manually, but it also suggests leveraging the context switch functions provided by the OS. That’s what I plan to explore further

