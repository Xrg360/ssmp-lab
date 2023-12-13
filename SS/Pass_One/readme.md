# Algorithm for pass one

```pascal
begin
    read first input line
    if OPCODE = 'START' then
        begin
            save #[OPERAND] as starting address
            save #[OPERAND] as LOCCTR, // initialize LOCCTR to starting address
            write line to intermediate file
            read next input line
        end (if 'START')
    else
        save starting address as LOCCTR // initialize LOCCTR to 0
    while OPCODE != 'END' do
        begin
            if this is not a comment line then
                begin
                    if there is a symbol in the LABEL field then
                        begin
                            search SYMTAB for LABEL
                            if found then
                                set error flag // duplicate symbol 
                            else
                                insert (LABEL, LOCCTR) into SYMTAB
                        end (if there is a symbol in the LABEL field)
                    search OPTAB for OPCODE
                    if found then
                        add 3 to LOCCTR
                    else if OPCODE = 'WORD' then
                        add 3 to LOCCTR
                    else if OPCODE = 'RESW' then
                        add 3 * #[OPERAND] to LOCCTR
                    else if OPCODE = 'RESB' then
                        add #[OPERAND] to LOCCTR
                    else if OPCODE = 'BYTE' then
                        begin
                            if BYTE is X then
                                add 1 to LOCCTR
                            else if BYTE is C then
                                add length of constant in bytes to LOCCTR
                        end (if OPCODE = 'BYTE')
                    else
                        set error flag (invalid operation code)
                end (if this is not a comment line)
```
