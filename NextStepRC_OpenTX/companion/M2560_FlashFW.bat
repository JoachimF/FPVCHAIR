@echo:
@echo ///////// Flashage du firmware /////////
@echo:
@echo ///////// Veuillez SVP sauvegarder au prealable l'eeprom /////////
@echo:
@pause
@echo:
@avrdude -p m2560 -c stk500v2 -P com3 -D -F -U flash:w:..\opentx.hex
@echo:
@pause