format binary as "gb"

macro orgpad op1,op2 {if op2 eq
                         db (op1-$) dup $ff
                      else
                         db (op1-$) dup op2
                      end if
                      org op1}

macro   pad addr,data {
        match o, data \{          ;if not blank
         if  data eqtype ""
          virtual at 0            ; count "ascii" size
          db data                 ; for divider
          addrsize = ($-0)        ;
          end virtual             ;
          db (addr-$)/addrsize dup (data)
         else
          db (addr-$) dup (data)
         end if
        \}
        db (addr-$) dup $00
}

macro   address [lab=$] {
        bits = 16
        forward
        match o, lab \{           ;if not blank
         repeat bits/4
          num = '0' + lab shr (bits-%*4) and $0F
           if num > '9'
            num = num + 'A'-'9'-1
           end if
          display num
         end repeat
        display " "
        \}
        common
        display 13,10
}

@ fix @@:

;=============================================================================
;       The most elegant macro-macarony for GB80
;=============================================================================
regB            = $10000
regC            = $10001
regD            = $10002
regE            = $10003
regH            = $10004
regL            = $10005
regM            = $10006
regA            = $10007
regWB           = $10008
regWD           = $10029
regWH           = $1004A
regSP           = $1005B

regXB           = $1005C
regXD           = $1005D
regXHI          = $1005E
regXHD          = $1005F
regIO           = $10062

regXBI          = $1006C
regXDI          = $1006D
regXBD          = $1006E
regXDD          = $1006F



b       equ regB
c       equ regC
d       equ regD
e       equ regE
h       equ regH
l       equ regL
m       equ regM
a       equ regA
bc      equ regWB
de      equ regWD
hl      equ regWH
sp      equ regSP
af      equ regA
xhl     equ regM

xbc     equ regXB
xde     equ regXD
mi      equ regXHI
xhli    equ regXHI
md      equ regXHD
xhld    equ regXHD
xc      equ regIO
xbci    equ regXBI
xbcd    equ regXBD
xdei    equ regXDI
xded    equ regXDD



macro dbw [byte,word] {db byte
                       dw word}

macro hx [byte] {db $#byte}

macro   sec             {db $37 }
macro   clc             {db $3f }
macro   eni             {db $fb }
macro   dii             {db $f3 }

macro   nop             {db $00 }
macro   daa             {db $27 }
macro   not             {db $2f }


macro   hlt             {db $76,$00     }
macro   stp             {db $10,$00     }

macro   bal     op1*    {db $18,((op1)-1)-$      }
macro   bnz     op1*    {db $20,((op1)-1)-$      }
macro   bne     op1*    {db $20,((op1)-1)-$      }
macro   bze     op1*    {db $28,((op1)-1)-$      }
macro   beq     op1*    {db $28,((op1)-1)-$      }
macro   bcc     op1*    {db $30,((op1)-1)-$      }
macro   bcs     op1*    {db $38,((op1)-1)-$      }

macro   bhi     op1*    {db $28,$02,$38,(o1)-1-$ }
macro   bhs     op1*    {db $30,(op1)-1-$ }
macro   bls     op1*    {db $28,(op1)-1-$,$38,(o1)-1-$ }
macro   blo     op1*    {db $38,(op1)-1-$ }

macro   b0s  op1*,op2=a{db $cb,($40 or (op2 and $7)),$20,(op1)-1-$ }
macro   b1s  op1*,op2=a{db $cb,($48 or (op2 and $7)),$20,(op1)-1-$ }
macro   b2s  op1*,op2=a{db $cb,($50 or (op2 and $7)),$20,(op1)-1-$ }
macro   b3s  op1*,op2=a{db $cb,($58 or (op2 and $7)),$20,(op1)-1-$ }
macro   b4s  op1*,op2=a{db $cb,($60 or (op2 and $7)),$20,(op1)-1-$ }
macro   b5s  op1*,op2=a{db $cb,($68 or (op2 and $7)),$20,(op1)-1-$ }
macro   b6s  op1*,op2=a{db $cb,($70 or (op2 and $7)),$20,(op1)-1-$ }
macro   b7s  op1*,op2=a{db $cb,($78 or (op2 and $7)),$20,(op1)-1-$ }
macro   b0c  op1*,op2=a{db $cb,($40 or (op2 and $7)),$28,(op1)-1-$ }
macro   b1c  op1*,op2=a{db $cb,($48 or (op2 and $7)),$28,(op1)-1-$ }
macro   b2c  op1*,op2=a{db $cb,($50 or (op2 and $7)),$28,(op1)-1-$ }
macro   b3c  op1*,op2=a{db $cb,($58 or (op2 and $7)),$28,(op1)-1-$ }
macro   b4c  op1*,op2=a{db $cb,($60 or (op2 and $7)),$28,(op1)-1-$ }
macro   b5c  op1*,op2=a{db $cb,($68 or (op2 and $7)),$28,(op1)-1-$ }
macro   b6c  op1*,op2=a{db $cb,($70 or (op2 and $7)),$28,(op1)-1-$ }
macro   b7c  op1*,op2=a{db $cb,($78 or (op2 and $7)),$28,(op1)-1-$ }

macro   jmp     op1*    {
if op1 eq regWH
 db $e9
else
 dbw $c3,op1
end if
}

macro   jnz     op1*    {dbw $c2,op1    }
macro   jne     op1*    {dbw $c2,op1    }
macro   jze     op1*    {dbw $ca,op1    }
macro   jeq     op1*    {dbw $ca,op1    }
macro   jcc     op1*    {dbw $d2,op1    }
macro   jcs     op1*    {dbw $da,op1    }
macro   jhs     op1*    {dbw $d2,op1    }
macro   jlo     op1*    {dbw $da,op1    }

macro   cal     op1*    {
if op1 in <$00,$08,$10,$18,$20,$28,$30,$38>
 db $c7 or op1
else
 dbw $cd,op1
end if
}
macro   cnz     op1*    {dbw $c4,op1    }
macro   cne     op1*    {dbw $c4,op1    }
macro   cze     op1*    {dbw $cc,op1    }
macro   ceq     op1*    {dbw $cc,op1    }
macro   ccc     op1*    {dbw $d4,op1    }
macro   ccs     op1*    {dbw $dc,op1    }
macro   chs     op1*    {dbw $d4,op1    }
macro   clo     op1*    {dbw $dc,op1    }

macro   ret             {db $c9 }
macro   rnz             {db $c0 }
macro   rne             {db $c0 }
macro   rze             {db $c8 }
macro   req             {db $c8 }
macro   rcc             {db $d0 }
macro   rcs             {db $d8 }
macro   rhs             {db $d0 }
macro   rlo             {db $d8 }

macro   rti             {db $d9}

;=============================================================================
;       instruction macro
;-----------------------------------------------------------------------------
macro instrugb80 mnem*,impl*,imm*,lmem*,reg*
    { macro mnem opr \{

 local flg
 define flg 0
 match =0  ==op1,  flg opr  \{
  db imm,op1
  define flg 1                 \\}
 match =0  ,  flg   \{




if opr eq
 db impl
else if opr <= $ff
 db imm,opr
else if opr <= $ffff
 dbw $21,opr
 db  lmem
else if opr in <regB,regC,regD,regE,regH,regL,regM,regA>
 db reg or (opr and $7)
else if opr in <regXB,regXD>
 if mnem in <and,ior,add,adc>
  db $67, $0a or ((opr and $1) shl 4),reg or ($4)
 end if

end if
\\}
\} }

;-----------------------------------------------------------------------------
TYP  = 666
;          MNE,imp,imm,mem,reg
instrugb80 mvb,$47,$06,$46,$40
instrugb80 mvc,$4f,$0e,$4e,$48
instrugb80 mvd,$57,$16,$56,$50
instrugb80 mve,$5f,$1e,$5e,$58
instrugb80 mvh,$67,$26,$66,$60
instrugb80 mvl,$6f,$2e,$6e,$68
instrugb80 mvm,$77,$36,TYP,$70
instrugb80 mva,$7f,$3f,$fa,$78
instrugb80 and,$a7,$e6,$a6,$a0
instrugb80 ior,$b7,$f6,$b6,$b0
instrugb80 xor,$af,$ee,$ae,$a8
instrugb80 add,$87,$c6,$86,$80
instrugb80 adc,$8f,$ce,$8e,$88
instrugb80 sub,$97,$d6,$96,$90
instrugb80 sbc,$9f,$de,$9e,$98
instrugb80 cmp,$bf,$fe,$be,$b8

macro   lda     opr,opt {
 local flg
 define flg 0
;match =0  ==op1,  flg opr  \{
; db $3e,op1
; define flg 1                 \}
 match =0  ,  flg   \{


 if opr <= $ff
  db $3e,opr

 else if opr <= $feff
  dbw $fa,opr
 else if opr <= $ffff
  db $f0,((opr) and $ff)
 else if opr in <regB,regC,regD,regE,regH,regL,regM>
  db $78 or (opr and $7)
 else if opr in <regXB,regXD,regXHI,regXHD>
  db $0a or ((opr and $3) shl 4)
 else if opr eq regIO
  db $f2
 else if opr in <regXBI,regXDI>
  db $0a or ((opr and $1) shl 4),$03 or ((opr and $1) shl 4)
 else if opr in <regXBD,regXDD>
  db $0a or ((opr and $1) shl 4),$0b or ((opr and $1) shl 4)
 end if
\}
#opt
}
macro   sta     [opr]   {
if opr <= $feff
 dbw $ea,opr
else if opr <= $ffff
 db $e0,((opr) and $ff)
else if opr in <regB,regC,regD,regE,regH,regL,regM>
 db $47 or ((opr and $7) shl 3)
else if opr in <regXB,regXD,regXHI,regXHD>
 db $02 or ((opr and $3) shl 4)
else if opr eq regIO
 db $e2
else if opr in <regXBI,regXDI>
 db $02 or ((opr and $1) shl 4),$03 or ((opr and $1) shl 4)
else if opr in <regXBD,regXDD>
 db $02 or ((opr and $1) shl 4),$0b or ((opr and $1) shl 4)
end if
}

macro   inc     op1     {
if op1 eq
 db $3c ;inc a
else if op1 in <regB,regC,regD,regE,regH,regL,regM,regA>
 db $04 or ((op1 and $7) shl 3)
else if op1 in <regWB,regWD,regWH,regSP>
 db $03 or ((op1 and $3) shl 4)
else if op1 <= $ffff
 dbw $21,op1
 db $34
end if
}
macro   dec     op1     {
if op1 eq
 db $3d ;dec a
else if op1 in <regB,regC,regD,regE,regH,regL,regM,regA>
 db $05 or ((op1 and $7) shl 3)
else if op1 in <regWB,regWD,regWH,regSP>
 db $0b or ((op1 and $3) shl 4)
else if op1 <= $ffff
 dbw $21,op1
 db $35
end if
}

macro   mbc     op1     {dbw $01,op1    }
macro   mde     op1     {dbw $11,op1    }

macro   mhl     op1*,op2=0      {
if op1 eq regSP
 db $f8,op2
else
 dbw $21,op1
end if
}
macro   msp     op1*    {
if op1 eq regWH
 db $f9
else
 dbw $31,op1
end if
}

macro   asp     op1*    {db $e8,op1     }
macro   ssp     op1*    {dbw $08,op1    }

macro   ahl     op1*    {
if op1 in <regWB,regWD,regWH,regSP>
 db $09 or ((op1 and $3) shl 4)
end if
}

macro   pus     [op1]   {
if op1 eq
 db $f5 ;pus a
else if op1 in <regWB,regWD,regWH,regA>
 db $c5 or ((op1 and $3) shl 4)
else if op1 in <regB,regD,regH>
 db $c5 or ((op1 and $6) shl 3)
end if
}

macro   pul     [op1]   {
if op1 eq
 db $f1 ;pul a
else if op1 in <regWB,regWD,regWH,regA>
 db $c1 or ((op1 and $3) shl 4)
else if op1 in <regB,regD,regH>
 db $c1 or ((op1 and $6) shl 3)
end if
}

pop fix pul


macro   tst     op1,op2 {
if op1 eq
 and a
else if op2 eq
 and op1
else
 lda op1
 and op2
end if
}

macro   ts0     op1=a   {db $cb,$40+((0 * 8)+(op1 and $7)) }
macro   ts1     op1=a   {db $cb,$40+((1 * 8)+(op1 and $7)) }
macro   ts2     op1=a   {db $cb,$40+((2 * 8)+(op1 and $7)) }
macro   ts3     op1=a   {db $cb,$40+((3 * 8)+(op1 and $7)) }
macro   ts4     op1=a   {db $cb,$40+((4 * 8)+(op1 and $7)) }
macro   ts5     op1=a   {db $cb,$40+((5 * 8)+(op1 and $7)) }
macro   ts6     op1=a   {db $cb,$40+((6 * 8)+(op1 and $7)) }
macro   ts7     op1=a   {db $cb,$40+((7 * 8)+(op1 and $7)) }

macro   cl0     op1=a   {db $cb,$80+((0 * 8)+(op1 and $7)) }
macro   cl1     op1=a   {db $cb,$80+((1 * 8)+(op1 and $7)) }
macro   cl2     op1=a   {db $cb,$80+((2 * 8)+(op1 and $7)) }
macro   cl3     op1=a   {db $cb,$80+((3 * 8)+(op1 and $7)) }
macro   cl4     op1=a   {db $cb,$80+((4 * 8)+(op1 and $7)) }
macro   cl5     op1=a   {db $cb,$80+((5 * 8)+(op1 and $7)) }
macro   cl6     op1=a   {db $cb,$80+((6 * 8)+(op1 and $7)) }
macro   cl7     op1=a   {db $cb,$80+((7 * 8)+(op1 and $7)) }

macro   se0     op1=a   {db $cb,$c0+((0 * 8)+(op1 and $7)) }
macro   se1     op1=a   {db $cb,$c0+((1 * 8)+(op1 and $7)) }
macro   se2     op1=a   {db $cb,$c0+((2 * 8)+(op1 and $7)) }
macro   se3     op1=a   {db $cb,$c0+((3 * 8)+(op1 and $7)) }
macro   se4     op1=a   {db $cb,$c0+((4 * 8)+(op1 and $7)) }
macro   se5     op1=a   {db $cb,$c0+((5 * 8)+(op1 and $7)) }
macro   se6     op1=a   {db $cb,$c0+((6 * 8)+(op1 and $7)) }
macro   se7     op1=a   {db $cb,$c0+((7 * 8)+(op1 and $7)) }

macro   rol     op1,op2=1 {
if op1 eq
 db $07
else
  rept (op2 and $f) \{db $cb,$00+(op1 and $7)\}
end if
}
macro   rlc     op1,op2=1 {
if op1 eq
 db $17
else
  rept (op2 and $f) \{db $cb,$10+(op1 and $7)\}
end if
}
macro   ror     op1,op2=1 {
if op1 eq
 db $0f
else
  rept (op2 and $f) \{db $cb,$08+(op1 and $7)\}
end if
}
macro   rrc     op1,op2=1 {
if op1 eq
 db $1f
else
  rept (op2 and $f) \{db $cb,$18+(op1 and $7)\}
end if
}
macro   shl     op1,op2=1 {
if op1 eq
 db $87 ;add a
else
 rept (op2 and $f) \{db $cb,$20+(op1 and $7) \}
end if }
macro   shr     op1=a,op2=1     {rept (op2 and $f) \{db $cb,$38+(op1 and $7) \}}
macro   asr     op1=a,op2=1     {rept (op2 and $f) \{db $cb,$28+(op1 and $7) \}}
macro   swp     op1=a           {db $cb,$30+(op1 and $7) }

macro   mov     op1,op2     {
local flg
define flg 0
match =0  ==opr,  flg op2  \{
 if op1 in <regB,regC,regD,regE,regH,regL,regM,regA>
  db $06 or ((op1 and $7) shl 3),opr
 else if op1 in <regWB,regWD,regWH,regSP>
  dbw $01 or ((op1 and $3) shl 4),opr
 else
  lda opr
  sta op1
 end if
 define flg 1                 \}
match =0  ,  flg   \{
 if op1 in <regB,regC,regD,regE,regH,regL,regM,regA>
  if op2 <= $ff
   db $06 or ((op1 and $7) shl 3),op2
  else if op2 <= $ffff
   lda op2
   sta op1
  else if op2 in <regB,regC,regD,regE,regH,regL,regM,regA>
   db $40 or (op2 and $7) or ((op1 and $7) shl 3)
  else
   lda op2
   sta op1
  end if
 else if op1 in <regWB,regWD,regWH>
  lda op2
  db $47 or ((op1 and $3) shl 4)
  lda op2+1
  db $4f or ((op1 and $3) shl 4)
 else
  lda op2
  sta op1
 end if
 \}
}
macro   ldaoprsta [mnem] {
        macro mnem op1,op2,op3  \{
        if op2 eq
         #mnem op1
        else if op3 eq
         lda op1
         #mnem op2
          sta op1
        else
         lda op2
         #mnem op3
         sta op1
        end if
        \}
}

ldaoprsta and,ior,xor,add,adc,sub,sbc

macro   cmp     op1,op2 {
if op2 eq
 cmp op1
else
 lda op1
 cmp op2
end if
}

macro shl1 { db $87 }
macro shl2 { db $87,$87 }
macro shl3 { db $87,$87,$87 }
macro shl4 { db $87,$87,$87,$87 }

macro shr1 { shr a }
macro shr2 { shr a,2 }
macro shr3 { shr a,3 }
macro shr4 { swp
             and $0f }


macro stmi [opr] { mov opr, mi }
macro stmd [opr] { mov opr, md }
macro ldmi [opr] { mov mi, opr }
macro ldmd [opr] { mov mi, opr }


macro ramcode op1*,op2* { macro end#op1 \{
end#op1:
org ramcode_#op1 + len_#op1 \}
ramcode_#op1:
org op2
#op1:
len_#op1 = end#op1 - #op1 }

macro lenbin op1*,[op2*] {
common
#op1:
len_#op1 = end#op1 - #op1
forward
file #op2
common
end#op1:               }
;=============================================================================
;       HEADERS
;-----------------------------------------------------------------------------
; gb:   $00= dmg
;       $80= cgb
;       $33= dmg/sgb
;       $b3= cgb/sgb
; board:$00= rom
;       $09= rom+sram
;       $01= mbc1
;       $03= mbc1+sram
;       $19= mbc5
;       $1b= mbc5+sram
;       $22= gyroscope+sram
;       $fc= camera+sram
; rom:  $00= 32k
;       $01= 64k
;       $02= 128k
;       $03= 256k
;       $04= 512k
;       $05= 1024k
;       $06= 2048k
;       $07= 4096k
;       $08= 8192k
; ram:  $00= none
;       $01= 2k
;       $02= 8k
;       $03= 32k
;       $04= 128k
macro gbheader title="GB8080",gb=0,rom=0,ram=0,board=$01 {
pad $100
dw $C300,$0150      ; Jump to $150
db $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D ;Nintendo
db $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99 ;  logo
db $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E
@@: db title,$d-($-@b) dup 0
dmg equ $00
cgb equ $80
sgb equ $33
;if ram < 0
; board equ $03
;end if
db 0,0,(gb) and $C0,0,0,(gb) and $03,board,rom,ram,0,(gb) and $33,1
checksum = 0
header = $134
 repeat 25
  load val byte from header
  checksum = checksum-val-1
  header = header+1
 end repeat
db (checksum and $ff),0,0
}
;-----------------------------------------------------------------------------
