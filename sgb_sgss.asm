include "dmg.inc"
dmgbios "SGSS",dmg+sgb,0,0
include "dmg.asm"
                mhl sgbpalette0
                cal sgb_send

                mov 0xff47, $e4
                mov 0xff40, $11
                cal sgb_map_init

                mov 0x2000,1
                cal send_16k
                mov 0x2000,2
                cal send_16k
                mov 0x2000,3
                cal send_16k
                mov 0x2000,4
                cal send_16k

                cal lcd_off
                vramcopy 0x8000, jupibgchr
                unrle 0x9800, jupibgnam
                mov 0xff47, $e4
                cal lcd_on

eternal:        bal eternal

send_16k:       mhl 4000h
                cal send_spc_data
                mhl 5000h
                cal send_spc_data
                mhl 6000h
                cal send_spc_data
                mhl 7000h
                cal send_spc_data
                ret

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

sgbdata sgbpalette0, 0, <rgb555 0,0,0, 10,10,10, 20,20,20, 30,30,30>
data jupibgchr, <chrnes "jupibg.chr",0,256>
data jupibgnam, file "jupibg.rle"

include "spchack.inc"
pad 4000h
sgss_song: spcfile "ufodisco.spc"
