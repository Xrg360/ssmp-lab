# Algorithm for Absolute Loader

```pascal
begin
    read Header record
    verify program name and length
    read first Text record
    while record type 'E' do //while not end of object program
        begin
            (if object code is in character fom, convert into internal representation)
            move object code to specified location in mernory
            read next object program record
        end
    jump to address specified in the end record //to start progrma execution
end
```
