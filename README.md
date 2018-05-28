# [ Possible Problems ]

What if instr is -1? Figure out another way to turn off translating without using pointers. Make tokenLine a vector of pair<Token,  bool>?
Check for HexBound
Memory leaks!!
WordBound

# [ Tests ]
## Part 1:
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
|Invalid Instruction |**Fail** | |
| NoSpace | **Pass** | |

## Part 2:
| Test Name             | Status        | Comments                 |
| ----------                | ------           | ----------                           |
| LabelsOnly | Pass | |
| LabelsAndWordOnTheSameLine | **Fail** | Words don't work |
| LabelsAndWords | **Fail** | Words don't work |
|MultipleLabels | | |
|ManyToOneLabels | | |
| OneToManyLabelsError | | |
