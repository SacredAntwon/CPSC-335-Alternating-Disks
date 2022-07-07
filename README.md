# Project One: Alternating Disks
Project 1 alternating disks DLDL LLDD

Group members:

Name: Anthony Maida

Email: amaida@csu.fullerton.edu

This is my project 1, which involves alternating disks of size 2n and then sorting using two different algorithms. The n is the number of light disks and dark disks, so 2n is all light and dark disks combined. The first algorithm is the lawnmower algorithm and the second is the alternate algorithm.

What I did for this project was I first had to add a check to see if the disks are initialized and if it is sorted. To check if it is initialized, I made sure that the even index disks, including 0, are dark disks or have a value of 1. I then made sure that the odd index disks are light or have a value of 0. To check if it is sorted, I made sure that the first half of the disks are all light disks or have a value of 0.

The next step was to add algorithms for the lawnmower and alternate. The lawnmower has a for loop that repeats (n+1)/2 times. In that loop, I have two more for loops. The first loop goes from left to right and makes swaps and the second for loop goes back to the beginning from right to left also making swaps. The alternate has a loop that runs n+1 times and there are two check conditions in that loop. The first check will see if the index of the parent loop is even, including 0, which will start the algorithm at the first disk going all the way to the right using a loop. The second check will see if the index of the parent loop is odd, which will then start the algorithm at the second disk and end it before the second to last disk using a loop. So this means it alternates between starting at the first disk and starting at the second disk and the amount of times it does it is determined by n, which is the number of either light or dark disks.
