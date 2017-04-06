; demoprogramma 6_b: 16 bits optelling met opslag in data memory
;
.INCLUDE "m128def.inc"
;
.CSEG
.ORG $0000
rjmp main
;
.CSEG
.ORG $0200
;
main:
LDI R17, $55
no_end: ; unlimited loop, when done
rjmp no_end
.DSEG
.ORG $0400
a: .BYTE 2
b: .BYTE 2
c: .BYTE 2