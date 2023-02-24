include "dmg.inc"
dmgbios "N-SPC",dmg+sgb,0,0
include "dmg.asm"
                mhl sgbpalette0
                cal sgb_send

                mov 0xff47, $e4
                mov 0xff40, $11
                cal sgb_map_init

                mhl sgbsong
                cal send_spc_data
                mhl sgbsong_samples
                cal send_spc_data
                mhl sound_song2
                cal sgb_send

                cal lcd_off
                vramcopy 0x8000, jupibgchr
                unrle 0x9800, jupibgnam
                mov 0xff47, $e4
                cal lcd_on

eternal:        bal eternal

send_spc_data:  pus hl
                cal lcd_off
                pul hl
                mde $8000
                mbc $1000
                cal mem_copy
                cal lcd_on
                cal sgb_sou_trn
                mvb 100
                cal wait_msec
                ret


sgbdata sound_song2, 08h, <db 0,0,0,2>

sgbdata sgbpalette0, 0, <rgb555 0,0,0, 10,10,10, 20,20,20, 30,30,30>
data jupibgchr, <chrnes "jupibg.chr",0,256>
data jupibgnam, file "jupibg.rle"

pad 4000h
;------------------------
sgbsong:
;lenght,address,data
dw len_songdata, $2b00
ramcode songdata, $2b00
include "jupisong.asm"
endsongdata

dw len_snare,$7CC3
lenbin snare,"snare.brr"

dw 2, $4BD2,$7CC3+len_snare

;end of data, jump address
dw 0, $0400

pad 5000h
;------------------------
sgbsong_samples:

dw 4,$4b08+8,$2b00+len_songdata+len_snare,endbass
dw 6,$4c3c+12
db $04,$00,$00,$7f,$02,$B0

dw len_bass,$2b00+len_songdata+len_snare
lenbin bass,"bass.brr"
dw 0, $0400

pad 6000h