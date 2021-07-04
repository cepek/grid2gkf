# grid2gkf
# Conversion from simple textual input format to GNU Gama XML input

[GNU Gama](https://www.gnu.org/software/gama/) is a free software for adjustment of surveying networks in the local coordinate system, also called coodinate grid. XML format is not easy to edit *manually* and **grid2gkf** is a tool to help users to create a simple record oriented data format with fixed order of parameters (files typically with extension .dat) and convert them to GNU Gama input XML (for historical reasons we use extension .gkf to distinguish them from adjustment output .xml files). This grid textual format is largely compatible with Star*Net input data files.

Input data format is defined in terms of records with fixed order format

 tag   | code  | description | comment
---    | ---   |---   |---
 C     | A12  45926.42  2834.23| 'iron pipe| # free point A12

Everything starting from hash # to the end of the line is an internal file commnet and is ignored on input, empty lines are also ignored. Every record can have an inline description which is started by apostrophe. Descriptions are ignored by grid2gkf. Tags are compulsory and in most cases also its corresoinding codes.

## C - point information
Tag C defines information about points

```
C   A12  45926.42  2834.23 'iron pipe # free point A12 
```

...
