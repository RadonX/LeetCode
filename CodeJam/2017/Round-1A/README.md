### Code Jam - Round 1A 2017

I always know I am too slow to pass Round 1A. This was the second time I participated in Code Jam, and I still felt so stupid in the first half hour of this competition.

#### Problem A - Alphabet Cake

- I just never know how to solve a problem with brute force. Brute force never hits my mind.

- I should copy and paste the problem on to a local document so that I can mark stuff. My memory is so bad that I completely forgot "no initial appears more than once on the cake" and tried to solve a grid like below. I ended up spending a significant amount of time on this problem I made, and wondered how there were so many smart people solving it in a short time.
```
1
5 7
????A??
?A?????
??????C
B??????
???A???
```

#### Problem B - Ratatouille

- An easy greedy problem.

- But I forgot that `multiset` is not sorted internally, and wasted some time debugging. Anyway `set` is not used when I found by the good sample case that 450g of ingredient 1 can be used for either 9 or 10 servings, not just 9. I didn't realize this in the beginning. Guessing many people ran into this trap as well.
```
2 2
50 100
450 449
```

#### Problem C - Play the Dragon

Good enough for me to understand Contest Analysis.
