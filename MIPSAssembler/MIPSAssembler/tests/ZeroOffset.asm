label:
beq $3, $10, foo
foo:
bne $1, $2, foo
bar:
bne $1, $2, foo
bne $1, $2, label
