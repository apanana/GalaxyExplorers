# GalaxyExplorers
CS442 - HW1

# Notes:
So this was my first time coding in C and pretty much my first time doing anything beyond simple arithmetic functions in assembly. There may be some weird syntatical things in my code because of this, but I am relatively sure everything works as far as I expect it to (with one except in the vectorization that I will go into more detail later). 
I ran my benchmarks on gyoza in polytopia.

# Part 1
# A)
For the python benchmarks, the number of iterations used were 10,000 for 2^8 to 2^10, 1,000 for 2^11 to 2^13, 100 for 2^14 to 2^16, 50 for 2^17, 2^18, 10 for 2^19 to 2^21, and 5 for 2^22 to 2^24. For the benchmarks for ports to C, assembly and the vectorization, the number of iterations used were 1,000,000 for 2^8, 2^9, 100,000 for 2^10, 2^11, 10,000 for 2^12 to 2^14, 1,000 for 2^15 to 2^17, 100 for 2^18 to  2^21, and 10 for 2^22 to 2^24. The numbers get smaller as the datasets get bigger because fewer iterations are needed to find an accurate mean. 
# B)
I did ten runs for inputs of size base two from 2^8 to 2^24. I then averaged these runs when making graphs.
# C)
Please see fig. 1 in the graphs spreadsheet.

# Part 2
Please see fig. 2 in the graphs spreadsheet. 
As expected, C is much faster than Python. This is literally the first time I've ever coded in C so I might have done some weird things with the code, but it works and runs as expected as far as I can tell.

# Part 3
Please see fig. 3 in the graphs spreadsheet.
The double version is consistently slower than the float version, which is what we'd expect since doubles are larger.

# Part 4
Please see fig. 4 in the graphs spreadsheet.
This was really baptism by fire. Going from knowing no C to the inline assembly was really hard. Again there may be some strange syntax but it works as expected. The inline assembly version works even faster, which is what we'd expect. Also interesting to note is that the double and float inline assembly versions preserve the same relationship (double being slower than float). I didn't make a graph of this, but it's pretty clear in the data. It's also more clear in the assembly version at high #s of objects that the average time per object is around two times the time for double than it is for float, which is what we expect because doubles take up twice the space.

# Part 5
Was not sure how to do this. :(

# Part 6
Please see fig. 5 in the graphs spreadsheet.
The vectorized version works faster still. Both the float and double versions improve runtime by expected rates. This is around four times quicker for the float version, which is expected since we can add four floats at a time with vectorization, while we can only add two doubles at a time. I believe I am getting some kind of overflow error with my double version, since the checksums no longer match (they do match in between both float versions). You will probably notice one of my commits fixes a change in incrementation from 4 each time to 2 each time for doubles. However, this did not fix the problem and I'm not even really sure where to look to find a solution since this is my first time doing literally all of this.

