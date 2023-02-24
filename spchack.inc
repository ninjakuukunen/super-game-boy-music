macro spcfile op1 {
align 4000h
dw enddat-startdat, $ff80
;FE70:
startdat:
;file "spc" :001f0h,$10
;file op1 :10100h,128
;FF00:
hx E8,AA
hx C5,F4,00
hx E8,BB
hx C5,F5,00
hx E5,F4,00
hx 68,CC
hx D0,F9
hx 2F,20
hx EC,F4,00
hx D0,FB
hx 5E,F4,00
hx D0,0F
hx E5,F5,00
hx CC,F4,00
hx D7,00
hx FC
hx D0,F0
hx AB,01
hx 2F,EC
hx 10,EA
hx 5E,F4,00
hx 10,E5
hx E5,F6,00
hx EC,F7,00
hx DA,00
hx EC,F4,00
hx E5,F5,00
hx CC,F4,00
hx D0,CD
hx 5F,80,FF
hx 8F
file op1 :100h,1
hx 00
hx 8F
file op1 :101h,1
hx 01

hx 8f, 6c, f2
hx 8F
file op1 :1016ch,1
hx F3

hx 8F
file op1 :1fch,1
hx FC
hx 8F
file op1 :1fbh,1
hx FB
hx 8F
file op1 :1fah,1
hx FA
hx 8F
file op1 :1f2h,1
hx F2
hx 8F
file op1 :1f1h,1
hx F1

hx CD
file op1 :2bh,1
hx BD

hx E8
file op1 :27h,1
hx 8D
file op1 :29h,1
hx CD
file op1 :28h,1

hx 5F
;hx 2F, FE
file op1 :25h,2
;dw 0c00h
enddat:

dw $8,$0ff8
file op1 :$0ff8+$100,8
dw $8,$1ff8
file op1 :$1ff8+$100,8
dw $8,$2ff8
file op1 :$2ff8+$100,8
dw $8,$3ff8
file op1 :$3ff8+$100,8
dw $8,$4ff8
file op1 :$4ff8+$100,8
dw $8,$5ff8
file op1 :$5ff8+$100,8
dw $8,$6ff8
file op1 :$6ff8+$100,8
dw $8,$7ff8
file op1 :$7ff8+$100,8
dw $8,$8ff8
file op1 :$8ff8+$100,8
dw $8,$9ff8
file op1 :$9ff8+$100,8
dw $8,$aff8
file op1 :$aff8+$100,8
dw $8,$bff8
file op1 :$bff8+$100,8
dw $8,$cff8
file op1 :$cff8+$100,8
dw $8,$dff8
file op1 :$dff8+$100,8
;dw $8,$eff8
;file "spc" :$eff8+$100,8
dw 9, $0e79
hx 8f, 6c, f2  ;mov   $f2,#$4c
hx 8f, e0, f3  ;mov   $f3,#$01
db $5f,$80,$ff
dw 0, $ff80

align 1000h

dw $ef8, $0100
file op1 :$0100+$100,$ef8
dw 0, $ff00

align 1000h

dw $ff8, $1000
file op1 :$1000+$100,$ff8
dw 0, $ff00
dw $ff8, $2000
file op1 :$2000+$100,$ff8
dw 0, $ff00
dw $ff8, $3000
file op1 :$3000+$100,$ff8
dw 0, $ff00
dw $ff8, $4000
file op1 :$4000+$100,$ff8
dw 0, $ff00
dw $ff8, $5000
file op1 :$5000+$100,$ff8
dw 0, $ff00
dw $ff8, $6000
file op1 :$6000+$100,$ff8
dw 0, $ff00
dw $ff8, $7000
file op1 :$7000+$100,$ff8
dw 0, $ff00
dw $ff8, $8000
file op1 :$8000+$100,$ff8
dw 0, $ff00
dw $ff8, $9000
file op1 :$9000+$100,$ff8
dw 0, $ff00
dw $ff8, $a000
file op1 :$a000+$100,$ff8
dw 0, $ff00
dw $ff8, $b000
file op1 :$b000+$100,$ff8
dw 0, $ff00
dw $ff8, $c000
file op1 :$c000+$100,$ff8
dw 0, $ff00
dw $ff8, $d000
file op1 :$d000+$100,$ff8
dw 0, $ff00
;dw $ff8, $e000
;file "spc" :$e000+$100,$ff8
;dw 0, $ff00

;dw $e00, $f000
;file "spc" :$f000+$100,$e00
dw $ee, $0002
file op1 :$0002+$100,$ee
dw 3, $ffc6
db 0,0,0;$8F,$0A,$F0
dw 0, $ff49     }