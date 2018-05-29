## Instruction format
```c
string correctFormat = labelDefinition(s) operand comma [parameters] comment;
operand = {ID, WORD, LABELADDRESS};
```

## To Do
* Check hex bounds
* Test each set of instructions for comments

# Tests
## Part 1: Add support for .word (11/16)
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| BiggerThanMax     | Pass
|Max | Pass| |
| HexBound | | |
| WordBound | Pass | This is failing because unsigned int_max is not an error, but your program doesn't account for it. |
|Blank | Pass | |
|Blind |Pass| No information: Did you check for comments? |
| Public | Pass |  | |
| BlankLines | Pass | |
|TooManyInt | Pass | .word 5 5 is wrong |
|AfterParseError | Pass | Program should not output after. |
|Invalid Instruction |Pass | after CheckInstructionFormat( ) |
| NoSpace | Pass | |
| RandomParen | Pass |Be more strict with MIPS command syntax. |
| MultipleWords |Pass |  |
| Blind | **FAIL** | But this tests passes in submission #10: 5 points |
| WordComments | Pass | |

## Part 2: Add support for label definitions (16/16)
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| LabelsOnly | Pass | |
| LabelAndWordsOnTheSameLine |Pass | |
| LabelsAndWords | Pass|  |
|MultipleLabels | Pass| |
|ManyToOneLabels |Pass | |
| OneToManyLabelsError | Pass| |
|LabelOpThenDef | Pass| |
|MultipleLabelsWordError |Pass | |
| LabelAfterWord | Pass | |
| ManyLabelsManyWords | Pass| Multiple words work when labels are in between them. |
| Label Comments | | |
## Part 3: Add support for label as operands (11/16)
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| LabelWord | Pass | Public Test|
|LabelAfterWord | Pass | |
|LabelsAndWords | Pass | |
| Blind | **FAIL**| 5 points|
|LabelLabelOnlly | | label: otherlabel |

## Part 4: Add support for jr and jalr (4/8)
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
|JrJalr |Pass | Public test |
|Blind |**FAIL** | 4 points|
|Jump| Pass | |
|JumpAndLink| Pass | |
|Register| Pass | |

## Part 5: Add support for add, sub, slt, multu (6/8)
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
|AddSubSltSltu | Pass | Public Test |
|Blind | **FAIL** | 2 points|

## Part 6: Add support for bne and beq without label offsets
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
|beq | Pass |  |
|bne | Pass | |
|BeqBne|**FAIL** | Public Test|
|PublicBne| **FAIL** | Not working for negative offsets.|
|Blind | **FAIL** |  points|
