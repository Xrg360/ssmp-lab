# Algorithm for Pass Two

```pascal
begin
    read first input line from intermediate file 
    if OPCODE = 'START' then
        begin
            write listing line
            read next input line
        end (if 'START')
    write Header record to object program
    initialise first Text record
    while OPCODE != END do
        begin
            if this is not a comment line then
                begin
                    if OPCODE present in OPTAB then
                        begin
                            if there is a symbol in OPERAND field then
                                begin
                                    search SYMTAB for OPERAND
                                    if found then
                                        store symbol value as operand address
                                    else
                                        begin
                                            store 0 as operand address
                                            else error flag // undefined symbol
                                        end (if not found)
                                    end (if symbol in OPERAND)
                            else
                                store 0 as operand address
                            assemble the object code instruction
                    end (if  opcode found)
            else if OPCODE = 'BYTE' or 'WORD' then
                convert constatt to object code
            if object code will fit into current Text record then
                begin
                    add object code to Text record
                    initialise new Text record
                end (if Text record not full)
                add object code to Text record
            end (if not comment line)
        write listing line
        read next input line
    end (while not END)
    write last Text record to object program
    write End record to object program
    write last listing line
end
```
