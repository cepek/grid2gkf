# text2xml
# Conversion from simple text format to GNU Gama XML input

[GNU Gama](https://www.gnu.org/software/gama/) is a free software for adjustment of surveying networks in the local coordinate system, also called coodinate grid. XML format is not easy to edit *manually* and **text2xml** is a tool to help users to create a simple text data format and convert it to GNU Gama input XML. This textual format is largely compatible with Star*Net input data files.

Input text format is defined in terms of records with fixed order format

 tag   | code  | description | comment
---    | ---   |---   |---
 C     | A12  45926.42  2834.23| 'iron pipe| # free point A12

Everything starting from hash # to the end of the line is an internal file commnet and is ignored on input, empty lines are also ignored. Every record can have an inline description which is started by apostrophe. Descriptions are ignored by text2xml. Tags are compulsory and in most cases also its corresoinding codes.

## C - point information
Tag C defines information about points

```
C   A12  45926.42  2834.23 'iron pipe # free point A12
```

## .ORDER

... EN is implicit, alternatively can be set to NE
