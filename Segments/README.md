This program receives an integer array as an input and maps each value to a number in crescent order. After mapping, the program builds *dynamically* a matrix with 2 lines and K columns. The first line contains the mapped value of the segment and the second the number of times it appears in sequence

#### Example:

Receiving the following input:

```
0 0 0 128 128 0 0 255 255 255 255
```

We can map the relate the numbers with values:

```
0 -> 1
128 -> 2
255 -> 3

```

At last, the program builds the matrix of segments:

```
Matrix:
1 2 1 3
3 2 2 4
```