avrdude.exe -p m2560 -c stk500v2 -P com3 erase
avrdude.exe -p m2560 -c stk500v2 -P com3 -U eeprom:r:-:h
avrdude.exe -p m2560 -c stk500v2 -P com3 -U eeprom:w:blah.eep
pause