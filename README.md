## Instruction format
```c
string correctFormat = labelDefinition(s) operand comma [parameters] comment;
operand = {ID, WORD, LABELADDRESS};
```

# Tests
## Part 1: Add support for .word
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| BiggerThanMax     | Pass
|Max | Pass| |
| HexBound | | |
| WordBound | **FAIL** | INT_MAX  is missing left most bytes but individually it passes  |
|Blank | **FAIL** | It creates a file with a newline character but it should not be creating a file. |
| Public | Pass |  | |
| BlankLines | Pass | |
|TooManyInt | Pass | .word 5 5 is wrong |
|AfterParseError | Pass | Program should not output after. |
|Invalid Instruction |Pass | after CheckInstructionFormat( ) |
| NoSpace | Pass | |
| RandomParen | Pass |Be more strict with MIPS command syntax. |
| MultipleWords |**FAIL** | Third word does not output properly. |

## Part 2: Add support for label definitions
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| LabelsOnly | Pass | |
| LabelAndWordsOnTheSameLine | **FAIL** | This is showing an error. |
| LabelsAndWords | Pass|  |
|MultipleLabels | Pass| |
|ManyToOneLabels |Pass | |
| OneToManyLabelsError | | |
|LabelOpThenDef | Pass| |
|MultipleLabelsWordError |Pass | |
| LabelAfterWord | Pass | |
| ManyLabelsManyWords | Pass| Multiple words work when labels are in between them. |
## Part 3: Add support for label as operands

## Part 4: Add support for jr and jalr

## Part 5: Add support for add, sub, slt, multuW
