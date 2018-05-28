# [ Possible Problems ]

What if instr is -1? Figure out another way to turn off translating without using pointers. Make tokenLine a vector of pair<Token,  bool>?
Check for HexBound
Memory leaks!!
WordBound

# [ Tests ]
## Part 1:
| Test Name             | Status        | Possible Reason                 |
| ----------                | ------           | ----------                           |
| BiggerThanMax     | Pass
| HexBound | | |
| WordBound | **Fail** | |
|Blank | **Fail** | It creates a file with a newline character. |
| Public | Pass | n.a | |
| BlankLines | Pass | |

## Part 2:
| Test Name             | Status        | Possible Reason                 |
| ----------                | ------           | ----------                           |
| LabelsOnly | Pass | |
| LabelsAndWordOnTheSameLine | **Fail** | Words don't work |
| LabelsAndWords | **Fail** | Words don't work |
|MultipleLabels | | |
|ManyToOneLabels | | |
| OneToManyLabelsError | | |
