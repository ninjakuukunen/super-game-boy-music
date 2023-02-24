initgameboy:    dii
                msp 0xD000
                mve $60
                inc           ; a: 01=dmg  11=cgb  ff=mgb/sgb2
                bze .modeldone
                swp
                shl b         ; b: 00=gb   01=agb
        load cgbflag byte from $143
        if cgbflag < $80
                xor
        else
                ior b
        end if
                sta e
.modeldone:     cal lcd_off
                xor
                sta 0xFF26,0xFF0F,0xFFFF
                sta 0x3000,0x0000,0x4000
                inc
                sta 0x2000
                sta 0xFF02
                and e
                bze .skip_cgb
                sta 0xFF4F
                cal cgb_turbo_off
                xor
                mhl 0x9FFF
.set_vramb1:    sta md
                b7s .set_vramb1, h
                sta 0xFF56,0xFF70,0xFF4F
.skip_cgb:      not
                sta 0xFF4A,0xFF4B        ;window yx
                sta 0xFF45      ;scanline compare
                sta l
                not
                sta 0xFF42,0xFF43        ;bg yx
                mvh 0x9F
.set_vramb0:    sta md
                b7s .set_vramb0, h
                mvh $DF
.set_wram:      sta md
                b6s .set_wram, h
                mvh l
.set_hram:      sta md
                b7s .set_hram, l
                sta l
                dec h
                lda $FF04
                adc e
.set_oam:       adc m
                mvm 0
                pus hl
                cal randomizer.seed
                pul hl
                inc l
                bnz .set_oam
                sta random
                mvc (oamdmacode) and $ff
                mhl .oamdma_data
                bal .load_oamdma
.oamdma_data:   hx E0,46,3E,28,3D,20,FD,C9
.load_oamdma:   lda mi
                sta xc
                inc c
                cmp $c9
                bne .load_oamdma
                lda e
                sta gbmodel
                rrc
                ccs cgb_init_pal
        load sgbflag byte from $146
        if sgbflag <> $03
                mhl 6502
        else
                cal sgb_test
        end if
                lda $e4
                sta 0xFF47,0xFF48,0xFF49 ;palettes
            ;    xor
            ;    sta 0xff0f
            ;    lda $01
            ;    sta 0xffff
                jmp proggy_start
;=============================================================================
lcd_off:        lda 0xFF40
                shl
                rcc
                mvl $90
                cal wait_scan
                lda 0xFF40
                and $7f
                bal @f
lcd_on:         lda 0xFF40
                ior $80
              @ sta 0xFF40
                ret
;--------------------------------------
wait_scan:      lda 0xFF44      ;in: l= target scanline
                cmp l
                bne wait_scan
                ret
;-----------------------------------------------------------------------------
wait_msec:      lda $d0         ;in: b= millisecons ( 16.7 = 1 frame )
              @ dec
                nop
                bnz @b
                dec b
                bnz wait_msec
                ret
;--------------------------------------
wait_irqvb:     cal lcd_on
                mov p_vblank, l         ;in: hl= vblank address
                mov p_vblank_hi, h
                mov l, framecounter
                xor
                sta 0xFF0F
                lda 0xFFFF
                ior 1
                sta 0xFFFF
                eni
              @ hlt
                lda framecounter
                cmp l
                beq @b
                ret
;--------------------------------------
;out: a=padhold, z=set if no keys down
pad_read:       lda padhold
                sta padlast, l
                mov 0xFF00, $20
        rept 3{ lda 0xFF00 }
                not
                and $0f
                swp
                sta h
                lda $10
                sta 0xFF00
        rept 8{ lda 0xFF00 }
                not
                and $0f
                ior h
                sta padhold, h
                pus
                lda l
                xor h
                and h
                sta padtap
                lda h
                cmp l
                lda TURBO_DELAY
                bne .reset
                lda padtimer
                and
                bze .turbo
                dec
.reset:         sta padtimer
                lda padtap
                bal @f
.turbo:         lda padturbo
                xor h
              @ sta padturbo
                mov 0xFF00, $30
                pul
                ret
;=============================================================================
basicvb:        cal pad_read
                cal timers
                cal randomizer
                xor
                sta p_vblank_hi
                ret
;=============================================================================
timers:         mhl timer_counter
                lda m
                dec
                cmp $3c
                blo @f
                lda $3b
              @ sta c, m ;timer_counter
                mvb 0
                mhl .timerbits
                ahl bc
                lda m
                sta timer
                ret

.timerbits:     hx ff,00,c0,20,90,48,a4,40,90,20,ca,00,f4,00,80,69
                hx 90,40,a4,00,da,20,c0,00,b4,48,80,60,90,00,ef,00
                hx d0,20,80,48,b4,40,80,20,da,00,e4,00,90,69,80,40
                hx b4,00,ca,20,d0,00,a4,48,90,60,80,00

randomizer:     lda random
.seed:          shl
                mhl random+1
                rlc m
                inc l
                rlc m
                inc l
                rlc m
                bcs @f
                xor $af
              @ sta random
                ret
;=============================================================================
mem_copy:       inc c           ; bc = bytecount
                inc b           ; hl = source
                bal @f          ; de = dest
.loop:          lda mi
                sta xde
                inc de
              @ dec c
                bnz .loop
                dec b
                bnz .loop
                ret

macro memcopy dst, src, cnt {
        if cnt eq
                mbc size.#src
        else
                mbc cnt
        end if
                mhl src
                mde dst
                cal mem_copy
}
;-----------------------------------------------------------------------------
bank_copy:      sta tmp0,0x2000 ; a  = rombank
                inc c           ; bc = bytecount
                inc b           ; hl = source
                bal @f          ; de = dest
.loop:          lda mi
                b7c .nobank, h
                lda tmp0, inc
                sta tmp0,0x2000
                mvh $40
.nobank:        sta xde
                inc de
              @ dec c
                bnz .loop
                dec b
                bnz .loop
                ret

macro bankcopy  dest, source, bytecount {
                lda source shr 14
                mhl (source and $3fff) or $4000
                mde dest
        if op2 eq
                mbc len_#source
        else
                mbc bytecount
        end if
                cal bank_copy
}
;-----------------------------------------------------------------------------
rle_copy:       lda mi          ; hl = source
                sta b           ; de = dest
.loop:          lda mi
                cmp b
                beq .s
                pus
              @ lda $FF41
                and 2
                bnz @b
                pul
                sta xde
                inc de
                sta tmp0
                bal .loop
        .s:     lda mi
                and
                rze
                sta c
                lda tmp0
        .l:     pus
              @ lda $FF41
                and 2
                bnz @b
                pul
                sta xde
                inc de
                dec c
                bnz .l
                bal .loop

macro unrle dst, src {
                mhl src
                mde dst
                cal rle_copy
}
;-----------------------------------------------------------------------------
vram_copy:      inc c           ; bc = bytecount
                inc b           ; hl = source
                lda b           ; de = dest
                sta tmp0
                mov b,c
                mvc $41
                bal @f
.loop:          lda xc
                and 2
                bnz .loop
                lda mi
                sta xde
                inc de
              @ dec b
                bnz .loop
                lda tmp0
                dec
                sta tmp0
                bnz .loop
                ret

macro vramcopy dst, src, cnt {
        if cnt eq
                mbc size.#src
        else
                mbc cnt
        end if
                mhl src
                mde dst
                cal vram_copy
}
;-----------------------------------------------------------------------------
fill_vram:      inc c           ;  a = fillvalue
                inc b           ; bc = bytecount
                sta d           ; hl = dest
                lda b
                sta tmp0
                mov b,c
                mvc $41
                bal @f
.loop:          lda xc
                and 2
                bnz .loop
                lda d
                sta mi
              @ dec b
                bnz .loop
                lda tmp0
                dec
                sta tmp0
                bnz .loop
                ret
;-----------------------------------------------------------------------------
clr_tmp:        xor
set_tmp:
.0:             sta tmp0
.1:             sta tmp1
.2:             sta tmp2
.3:             sta tmp3
.4:             sta tmp4
.5:             sta tmp5
.6:             sta tmp6
.7:             sta tmp7
.8:             sta tmp8
.9:             sta tmp9
.a:             sta tmpa
.b:             sta tmpb
.c:             sta tmpc
.d:             sta tmpd
.e:             sta tmpe
.f:             sta tmpf
                ret
;=============================================================================
hex2deci:       mvl 0           ;in:    a= hex ff
.999:           mvh $ff         ;       l= hex 03
                inc l           ;out:   a= deci 001
.hun:           inc h           ;       l= deci 010
                sub 100         ;       h= deci 100
                bcc .hun
                dec l
                bnz .hun
                dec l
                add 60
                bcc @f
                mvl 3
                bal .ten
              @ add 40
.ten:           inc l
                sub 10
                bcc .ten
                add 10
                ret

.ascii:         cal     hex2deci
                pus
                lda h
                add $30
                sta h
                lda l
                add $30
                sta l
                pul
                add $30
                ret
;-----------------------------------------------------------------------------
bit2byte:       mvb 8           ;in:    a= 8 bits
                sec             ;       d= byte for 0
                rlc             ;       e= byte for 1
                sta c           ;       hl= dest0
.loop:          lda d           ;out:   dest0-7= bits
                bcc @f          ;       hl= hl+8
                lda e
              @ sta mi
                shl c
                bnz .loop
                ret
;-----------------------------------------------------------------------------
chr_2to4bit:   ; add c,16        ;in:    bc = bytecount


            ;    inc b           ;       hl = dest
            ;    bal .dec        ;       de = source
.loop:

                mvc 16

              @ lda xde
                sta mi
                inc de
                dec c
                bnz @b

                lda 16
.pad:           mvm c
                inc hl
                dec
                bnz .pad


.dec:

                dec b
                bnz .loop
                ret

macro chr2to4bit dst, src, cnt {
        if cnt eq
                mvb ((size.#src) shr 4) and $ff
        else
                mvb cnt
        end if
                mde src
                mhl dst
                cal chr_2to4bit
}
;-----------------------------------------------------------------------------
hex2ascii:      pus             ;in:    a= byte
                cal @f          ;out:   a= ascii hi nybble
                sta l           ;       l= ascii lo nybble
                pul
                swp
              @ and $0f
                add $30
                cmp $3a
                rlo
                add $07
              @ ret
;=============================================================================
; super gameboy
;-----------------------------------------------------------------------------
sgb_test:       cal clr_tmp
                mhl tmp1
                mov md, 1
                mvm $89
                cal sgb_send

                lda 0xFF00
                and $03
                cmp $03
                bnz .super
                mov 0xFF00, $20
rept 2        { lda 0xFF00 }
                mov 0xFF00, $30
                mov 0xFF00, $10
rept 6        { lda 0xFF00 }
                mov 0xFF00, $30
rept 4        { lda 0xFF00 }
                and $03
                cmp $03
                mvc 0
                bnz .dmg
.super:         mvc $80
.dmg:           ior gbmodel, c

                mhl tmp1
                mov md, 0
                mvm $89
                mvb 50
                cal wait_msec
                cal sgb_send

                lda gbmodel
                shl
                rcc

sgb_init:       mhl .init_data
                cal sgb_send
.apu:           mhl .apu_init_data
                cal sgb_send
                ret

.init_data:     hx 79,5D,08,00,0B,8C,D0,F4,60,00,00,00,00,00,00,00
                hx 79,52,08,00,0B,A9,E7,9F,01,C0,7E,E8,E8,E8,E8,E0
                hx 79,47,08,00,0B,C4,D0,16,A5,CB,C9,05,D0,10,A2,28
                hx 79,3C,08,00,0B,F0,12,A5,C9,C9,C8,D0,1C,A5,CA,C9
                hx 79,31,08,00,0B,0C,A5,CA,C9,7E,D0,06,A5,CB,C9,7E
                hx 79,26,08,00,0B,39,CD,48,0C,D0,34,A5,C9,C9,80,D0
                hx 79,1B,08,00,0B,EA,EA,EA,EA,EA,A9,01,CD,4F,0C,D0
                hx 79,10,08,00,0B,4C,20,08,EA,EA,EA,EA,EA,60,EA,EA,0
.apu_init_data: hx 79,00,09,00,0B,AD,C2,02,C9,09,D0,1A,A9,01,8D,00
                hx 79,0B,09,00,0B,42,AF,DB,FF,00,F0,05,20,73,C5,80
                hx 79,16,09,00,0B,03,20,76,C5,A9,31,8D,00,42,68,68
                hx 79,21,09,00,01,60,00,00,00,00,00,00,00,00,00,00
                hx 79,00,08,00,03,4C,00,09,00,00,00,00,00,00,00,00,0
;--------------------------------------
sgb_send:       mvb 100
                cal wait_msec
                xor
                sta c
                sta xc
                mov xc, $30
                mvb $10
.loop1:         mve $08
                mov d, mi
.loop2:         lda $10
                b0s @f,d
                lda $20
              @ sta xc
                mov xc, $30
                rrc d
                dec e
                bnz .loop2
                dec b
                bnz .loop1
                mov xc, $20
                mov xc, $30
                lda m
                and
                bnz sgb_send
                ret
;--------------------------------------
sgb_map_init:   mhl 0x9800
                mde $000c
                xor
.loop:          mvb $14
              @ sta mi
                inc
                rze

                dec b
                bnz @b
                ahl de
                bal .loop
;--------------------------------------
sgb_sound:      mhl tmp4
                mov md, e
                mov md, d
                mov md, c
                mov md, b
                mov m, $41
                xor
                cal set_tmp.5
                cal sgb_send
                ret
sgb_sou_trn:    mhl tmp0
                mov m, $49
                xor
                cal set_tmp.1
                cal sgb_send
                ret
;--------------------------------------

;=============================================================================
;gameboy color
;-----------------------------------------------------------------------------
cgb_turbo_off:  mvl $00
                bal @f
cgb_turbo_on:   mvl $80
              @ lda 0xFF4D
                and $80
                cmp l
                req
                inc l
                lda $30
                sta 0xFF00
                lda l
                sta 0xFF4D
                stp
                ret
;--------------------------------------
cgb_pal_obj:    mvc $6a         ;input: hl = source
                bal @f          ;       a = start palette (1-32)
cgb_pal_bg:     mvc $68         ;       b = palettecount (1-32)
              @ shl
                ior $80

                pus
              @ lda 0xFF41, and 2
                bnz @b
                pul

                sta xc
                inc c

.loop:          lda 0xFF41, and 2
                bnz .loop

                mov xc, mi
                mov xc, mi
                dec b
                bnz .loop
                ret

cgb_init_pal:   mhl cgb_palette
                xor
                mvb 32
                cal cgb_pal_bg
                xor
                mvb 32
                jmp cgb_pal_obj

cgb_palette:
rgb555 00,00,00,00,00,08,05,00,05,05,00,00,04,02,00,03,03,00,00,04,00,00,03,06
rgb555 00,00,00,00,00,08,05,00,05,05,00,00,04,02,00,03,03,00,00,04,00,00,03,06
rgb555 08,08,08,07,00,31,11,03,11,16,00,00,12,06,00,08,08,00,00,11,00,00,07,31
rgb555 08,08,08,07,00,31,11,03,11,16,00,00,12,06,00,08,08,00,00,11,00,00,07,31
rgb555 15,15,15,12,12,31,31,05,31,31,09,09,24,11,00,15,16,00,00,27,00,00,18,31
rgb555 15,15,15,12,12,31,31,05,31,31,09,09,24,11,00,15,16,00,00,27,00,00,18,31
rgb555 31,31,31,21,21,31,31,18,31,31,19,19,31,22,13,31,31,00,18,31,18,17,26,31
rgb555 31,31,31,21,21,31,31,18,31,31,19,19,31,22,13,31,31,00,18,31,18,17,26,31

sgb_palette:
rgb555 00,00,00, 11,11,11, 22,22,22, 31,31,31
rgb555 02,05,10, 08,10,20, 17,22,31, 26,29,31
rgb555 07,00,08, 13,08,17, 28,17,29, 31,26,31
rgb555 07,00,03, 16,06,10, 29,17,20, 31,26,27
rgb555 07,03,00, 15,08,04, 28,19,12, 31,27,23
rgb555 06,05,00, 12,10,00, 25,22,08, 29,29,19
rgb555 00,06,00, 05,12,00, 16,25,04, 25,31,23
rgb555 00,06,07, 00,12,15, 07,25,27, 25,30,31

load_bg_pal:    mvb 32
                mvd 0
              @ lda mi
                sta e
                pus bc,de,hl
                cal load_pal_entry
                pul hl,de,bc
                inc d
                dec b
                bnz @b
                ret

load_pal_entry: lda d        ;d= pal entry
                mvc $68      ;e= color
                cmp 32
                blo @f
                sub 32
                mvc $6a
              @ shl
                ior $80
                sta b

                shl e
                mvd 0
                mhl cgb_palette
                ahl de

              @ lda 0xFF41, and 2
                bnz @b

                lda b
                sta xc
                inc c

                stmi xc,xc
                ret
;=============================================================================
proggy_start:
