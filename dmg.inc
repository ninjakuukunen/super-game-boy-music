include "flatgb80.inc"
tmp0            = 0xffa0
tmp1            = 0xffa1
tmp2            = 0xffa2
tmp3            = 0xffa3
tmp4            = 0xffa4
tmp5            = 0xffa5
tmp6            = 0xffa6
tmp7            = 0xffa7
tmp8            = 0xffa8
tmp9            = 0xffa9
tmpa            = 0xffaa
tmpb            = 0xffab
tmpc            = 0xffac
tmpd            = 0xffad
tmpe            = 0xffae
tmpf            = 0xffaf

random          = 0xffbf
               ;= 0xffc0
               ;= 0xffc1
               ;= 0xffc2
framecounter    = 0xffc3
timer_counter   = timer-1
timer           = 0xffc5
;01= 15
;02= 10
;04= 6
;08= 5
;10= 4
;20= 3
;40= 2/3
;80= 2

hblankcode      = 0xffd0

padhold         = padlast-1
padlast         = 0xffe2
;pad_a            = $01
;pad_b            = $02
;pad_select       = $04
;pad_start        = $08
;pad_right        = $10
;pad_left         = $20
;pad_up           = $40
;pad_down         = $80
padtap          = 0xffe3
padtimer        = 0xffe4
padturbo        = 0xffe5

gbmodel         = 0xfff0
;01= cgb
;02= agb
;20= dmg
;40= sgb2/mgb
;80= sgb

p_vblank        = 0xfff4
p_vblank_hi     = 0xfff5
oamdmacode      = 0xfff7

;-----------------------------------------------------------------------------
TURBO_DELAY     = 40
SGB_REPEAT      = 1
;-----------------------------------------------------------------------------
macro dmgbios op1, op2, op3, op4, op5 {
org 0
pad $0030
rst6calhl:      jmp hl
              @ not
                sta 0xff42, 0xff47
                bal @b
rst7error:      dii
                lda $d7
                sta 0xff40
                jmp @b
irqvb:          pus a
                lda p_vblank_hi
                and
                bnz vblank
                bal vblank.simple
irqlcd:         pus
                lda $ff41
                and 7
                hx 28,81 ;bze hblankcode (0xffd0)
                hx 18 ;bal irqscan (0x0069)
                bal irqtimer

pad $0058
irqcom:         rti

pad $0060
irqpad:         rti

pad $0069
irqscan:        pul
irqtimer:       rti

vblank:         pus bc,de,hl
                sta h
                lda p_vblank
                sta l
                cal 0x30
                pul hl,de,bc
.simple:        lda framecounter
                dec
                sta framecounter
                pul a
                rti
gbheader op1,op2,op3,op4,op5
postpone  \{
if $ < $8001
pad $8000
else if $ < $10001
pad $10000
else if $ < $20001
pad $20000
else if $ < $40001
pad $40000
else if $ < $80001
pad $80000
else if $ < $100001
pad $100000
else if $ < $200001
pad $200000
else if $ < $400001
pad $400000
end if
\}}





macro chrnes op1*, op2*, op3  {
count = op2*16
 @
 file op1:count,op3*16
 repeat op3
   load a0 byte from @b+count+0
   load a1 byte from @b+count+1
   load a2 byte from @b+count+2
   load a3 byte from @b+count+3
   load a4 byte from @b+count+4
   load a5 byte from @b+count+5
   load a6 byte from @b+count+6
   load a7 byte from @b+count+7
   load b0 byte from @b+count+8
   load b1 byte from @b+count+9
   load b2 byte from @b+count+10
   load b3 byte from @b+count+11
   load b4 byte from @b+count+12
   load b5 byte from @b+count+13
   load b6 byte from @b+count+14
   load b7 byte from @b+count+15
   store byte a0 at @b+count+0
   store byte b0 at @b+count+1
   store byte a1 at @b+count+2
   store byte b1 at @b+count+3
   store byte a2 at @b+count+4
   store byte b2 at @b+count+5
   store byte a3 at @b+count+6
   store byte b3 at @b+count+7
   store byte a4 at @b+count+8
   store byte b4 at @b+count+9
   store byte a5 at @b+count+10
   store byte b5 at @b+count+11
   store byte a6 at @b+count+12
   store byte b6 at @b+count+13
   store byte a7 at @b+count+14
   store byte b7 at @b+count+15
   count = count+16
end repeat
}





macro rgb555 [op1*,op2*,op3*] {
dw ((op1) and $1f) or (((op2) and $1f) shl 5) or (((op3) and $1f) shl 10)  }

macro sgbdata op1*, command*,data {
#op1: db ((command and $1f) shl 3) or 1
#data
db $11-($-#op1) dup 0 }

macro padturbo? op1,op2 {
 lda padturbo
if op1 eq a
 and $01
else if op1 eq b
 and $02
else if op1 eq c
 and $04
else if op1 eq s
 and $08
else if op1 eq r
 and $10
else if op1 eq l
 and $20
else if op1 eq u
 and $40
else if op1 eq d
 and $80
else
 and op1
end if
local .skip
match o, op2 \{ ;if not blank
 bze .skip
 #op2
.skip:     \} }






macro vramcopy dst, src, cnt {
if cnt eq
 mbc size.#src
else
 mbc cnt
end if
 mhl src
 mde dst
 cal vram_copy               }




macro waitlcd {
local .wt
.wt: lda $ff41
     and 2
     bnz .wt  }
               
              
macro ifcgb op1=.endcgb {
        lda gbmodel
        rrc
        bcc op1         }
macro endcgb { .endcgb:  }


macro data lab, dat {
#lab:
#dat
size.#lab = $ - lab }

macro datasize lab {
size.#lab = $ - lab }



