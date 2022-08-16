This program receives any codified string in a file and decode. The message must be codified into Ceasar's cypher, which contains the following cypher alphabet:

```
Normal:  ABCDEFGHIJKLMNOPQRSTUVWXYZ
Cypher:  DEFGHIJKLMNOPQRSTUVWXYZABC
```
The Ceasar's cypher has the following codification rules:

```
1. Replaces space to `#`
2. Swaps letters to its related one in Ceaser's alphabet, rotating it 3 spaces to the left.
3. Divides the message in equal blocks with `n` each.
4. Reverses each block.
5. Runs a permutation between the extremes of the message (first with the last, second with the second before last and so on)

```
For instance, the steps of coding the message `AMO LIVROS`, would be:

```
1. AMO#LIVROS
2. DPR#OLYURV
3. DP-R#-OL-YU-RV
4. PD-#R-LO-UY-VR
5. VR#RLOUYPD.
```
This programs runs the steps above in reverse, in order to decode the message. 

### Example:

```
Digite o nome do arquivo: mensagem.txt

--------------------
Mensagem codificada:
--------------------
rglfil#drwF#w#udvdgrsdhvkqdi#hpohxhwrpfhp#dudgilvhg#t#qhv#lfhw#u#d#hqhs#r#vhahhgf#uidu#D

----------------------
Mensagem decodificada:
----------------------
A cifra de Cesar pode ser facilmente decifrada mesmo que se tenha apenas o texto cifrado

```
