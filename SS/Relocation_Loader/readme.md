# Algorithm for Relocation Loader

## Modification Records Algorithm

This algorithm is used in SIC/XE machines.

```pascal
begin
    get PROGADDR from the Operating System
    while record type != 'E' do
        begin
            read next input record
            while record type = 'T' do
                move object code to location ADDR + specified address
            while record type = 'M' do
                add PROGADDR to to location ADDR + specified address
    end (while != E)
end
```

## Modification Bit Algorithm

This algorithm is used in SIC machines.

```pascal
begin
    get PROGADDR from the Operating System
    while record type != 'E' do
        begin
            read next input record
            while record type = 'T' do
                begin
                    get length & mask bits from object code
                    for each mask bit do
                        if mask bit = 1 then
                            add PROGADDR to location ADDR + specified address
                        else if mask bit = 0 then
                            move object code to location ADDR + specified address
                end (while T)
        end (while != E)
end
```
