@cd companion
@echo:
@echo ///////// Effacement eeprom + flash et programmation des fusibles /////////
@echo:
@pause
@echo:
@avrdude -p m2560 -c usbasp -P usb -F -e -u -Ulfuse:w:0xFF:m -Uhfuse:w:0xD8:m -Uefuse:w:0xFD:m -v
@echo:
@pause
@echo:
@echo ///////// Flashage du bootloader /////////
@echo:
@pause
@echo:
@avrdude -p m2560 -c usbasp -P usb -U lock:w:0x3F:m -V -U flash:w:M2560_stk500v2boot_opentx.hex -U lock:w:0x0F:m
@echo:
@pause
@echo:
@echo ///////// Transfert de l'eeprom /////////
@echo:
@pause
@echo:
@avrdude -p m2560 -c usbasp -P usb -U eeprom:w:eeprom_base.bin
@echo:
@pause