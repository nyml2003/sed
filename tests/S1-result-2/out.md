```mermaid
graph TD
6[CompilationUnit]
6--0-->4
4[FunctionDefinition]
4--returnType-->5[int]
4--identifier-->0
0[Identifier|name = main|]
4--block-->3
3[Block]
3--statement0-->2
2[ReturnStatement]
2--expression-->1
1[Int32: 0]
```
