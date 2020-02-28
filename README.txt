resources used:

https://en.wikipedia.org/wiki/Dining_philosophers_problem

also the slides from class

The code relies on util.c and util.h from part 1

I implemented the resource hierarchy solution from the wikipedia page.
Each Philosopher grabs the lower chopstick first, and only tries for
the higher once the lower has been acquired. After acquring both he
eats for half a second, Then puts down both sticks and thinks for a half-
second.

To prove that the solution works, a loop runs in main which will report
if any one philosopher has gone for 10 seconds without eating and then
end the program.

All the code is original
