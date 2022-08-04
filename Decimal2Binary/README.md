This program receives an integer as an input and recursively converts it to its value in binary.
The best way of solving it is dividing the number successively by 2, which the mod of i^th division is the binary number:

#### Ex: 12 = 1100
```
12/2 = 6 mod 0
6/2  = 3 mod 0
3/2  = 1 mod 1
1/2  = 0 mod 1
```
#### Example of input:
```
Digite um numero inteiro: 34
Resultado: 100010
```