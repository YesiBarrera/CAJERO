WR_EEPROM:

    BANKSEL     EEADR ;
    MOVWF       EEADR ;Data Memory Address to write
    BANKSEL     DATA_W
    MOVF        DATA_W,W
    BANKSEL     EEDAT
    MOVWF       EEDAT ;Data Memory Value to write
    BANKSEL     EECON1 ;
    BCF         EECON1, EEPGD ;Point to DATA memory
    BSF         EECON1, WREN ;Enable writes
    BCF         INTCON, GIE ;Disable INTs.
    BTFSC       INTCON, GIE ;SEE AN576
    GOTO        $-2
    MOVLW       0X55 ;
    MOVWF       EECON2 ;Write 55h
    MOVLW       0xAA ;
    MOVWF       EECON2 ;Write AAh
    BSF         EECON1, WR ;Set WR bit to begin write
    BSF         INTCON, GIE ;Enable INTs.
    BCF         EECON1, WREN ;Disable writes
    BANKSEL PORTA
    RETURN
    
RD_EEPROM:

    BANKSEL     EEADR ;
   ; MOVLW       0X57 ;
    MOVWF       EEADR ;Data Memory
    ;Address to read
    BANKSEL     EECON1 ;
    BCF         EECON1, EEPGD ;Point to DATA memory
    BSF         EECON1, RD ; EE Read
    BANKSEL     EEDAT ;
    MOVF        EEDAT, W ;W = EEDAT
    ;BCF         STATUS, RP1 ;Bank 0
    BANKSEL     PORTA
    RETURN


