# Assembler

# Tests
## Part 1: Add support for .word
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| BiggerThanMax     | Pass
|Max | Pass| |
| HexBound | | |
| WordBound | **Fail** | INT_MAX  is missing left most bytes but individually it passes  |
|Blank | **Fail** | It creates a file with a newline character but it should not be creating a file. |
| Public | Pass |  | |
| BlankLines | Pass | |
|TooManyInt | Pass | .word 5 5 is wrong |
| LabelAfterWord | Pass | |
|AfterParseError | Pass | Program should not output after. |
|Invalid Instruction |**Fail** | There should not be any output. |
| NoSpace | Pass | |
| RandomParen | Pass |Be more strict with MIPS command syntax. |
|MultipleLabelsWordError |Pass | |

## Part 2: Add support for label definitions
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| LabelsOnly | Pass | |
| LabelsAndWordOnTheSameLine | **Fail** | Words don't work |
| LabelsAndWords | **Fail** | Words don't work |
|MultipleLabels | | |
|ManyToOneLabels | | |
| OneToManyLabelsError | | |

## Part 3: Add support for label as operands
