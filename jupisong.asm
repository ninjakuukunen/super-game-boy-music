include "sgbsong.inc"

;bass
chvol0=250

;kick
chvol1=255

;snare
chvol2=160

;hihat
chvol3=150

;short
chvol4=170

;long1
chvol5=110

;long2
chvol6=85

;lead
chvol7=100

mainpitch = -6;,-1
maintempo = 7

playlist:
dw bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2,bgm2

bgm2:	dw bgm2_p1
	dw $FF, bgm2
	dw 0

bgm2_p1:
dw bgm2_p1_0, bgm2_p1_1, bgm2_p1_2, bgm2_p1_3, bgm2_p1_4, bgm2_p1_5, bgm2_p1_6, bgm2_p1_7

basenote =  11+mainpitch;+12
bgm2_p1_0:
pv1 chvol0
tp1 maintempo
tun 150
mv1 255
sno $4;7
pan 11
db 2,$7F
pat .intro, 8*16
	;db r,_,e2,_, r,_,e3,_, e2,e3,ax2,a2,_,g2,d3,dx3
db 1,$7F
pat @f, 100
@

	db e3,_,r,_,g3,r,e2,_, r,_,e3,_,a2,_,d3,r, e3,_,e2,_,_,_,d3,_,_,_,g2,_,e3,_,d2,_
	db e2,_,r,_,g2,r,e3,_, r,_,e2,_,a2,_,d3,r, e2,_,e3,r,ax2,_,a2,_,_,_,g2,_,d3,r,dx3,r
	db e3,_,r,_,g2,r,e2,_, r,_,e3,_,a2,_,d3,r, e3,_,e2,_,_,_,d3,_,_,_,g2,_,e3,_,d2,_
	db e2,_,r,_,g2,r,e3,_, r,_,e2,_,a2,_,d3,r, e2,_,e3,r,ax2,_,a2,_,_,_,g2,_,d3,r,dx3,r
	db e2,_,r,_,g3,r,e2,_, r,_,e3,_,a2,_,d3,r, e3,_,e2,_,_,_,d3,_,_,_,g2,_,e3,_,d2,_
	db e3,_,r,_,g2,r,e3,_, r,_,e2,_,a2,_,d3,r, e2,_,e3,r,ax2,_,a2,_,_,_,g2,_,d3,r,dx3,r
	db c3,_,r,_,g3,r,c3,_, r,_,c3,_,a2,_,d2,r, c3,_,_,_,c2,_,c3,_,_,_,a2,_,g2,_,f2,_
	db f3,_,r,_,d3,r,f3,_, r,_,f3,_,a2,_,d2,r, f3,_,_,_,d3,r,e3,_,_,_,g2,_,d3,r,dx3,r
;       db e2,_,r,_,  e2,_,r,_, e2,_,_,_, d2,_,e2,_
;       db r,_,e2,_,  r,_,e2,_, r,_,e2,_, d2,_,e2,_
	db 0
.intro: db r
	db 0
basenote = -9
bgm2_p1_1:
pv1 chvol1
tp1 maintempo
sno $31
pan 9
db 2,$7f

pat .intro, 7*16
	db o,o,_,o, _,o,_,_, o,_,o,o, _,o,o,_
pat @f, 100
@
	db o,_,o,_, _,_,o,_, _,_,o,_, _,_,o,o
	db o,o,_,o, _,o,_,_, o,_,_,o, _,_,o,o
	db 0


.intro: db r
	db 0

basenote = 20
bgm2_p1_2:
pv1 chvol2
tp1 maintempo
sno $34
pan 11
ecv $f5, 14,-17
edl 3, 75, 0
db 2,$7f

pat .intro, 7*16
	db _,_,_,_,o,_,_,o+7, _,o-5,_,_, o,_,_,o
pat @f, 100
@
	db _,_,_,_,o,_,_,_, _,_,_,_, o,_,_,_
	db _,_,_,_,o,_,_,_, _,o+7,_,_, o,_,_,o-5
	db _,_,_,_,o,_,_,_, _,_,_,_, o,_,_,_
	db _,_,_,_,o,_,_,o+7, _,o-5,_,_, o,o-5,_,o+7
;        db _,_,_,_,o,_,_,o, _,o,_,_, o,_,_,_
	db 0

.intro: db r
	db 0


basenote = 18
bgm2_p1_3:
pv1 chvol3
tp1 maintempo
sno $32
pan 9
db 2,$7f
pat .intro, 8*16
pat @f, 200
@
	db o,o,o-16,o, o-25,o-25,o-16,o
	db 0

.intro: db r
	db 0

basenote = 12+mainpitch
bgm2_p1_4:
pv1 chvol4
tp1 maintempo
sno $23
pan 7
tun 175
db 2,$7f
pat @f, 100
@
	db e3,_,_,e3, e4,e4,e3,_, c3,_,c4,c4, _,_,c3,_
	db a2,_,_,a3, a3,_,a2,_, b2,_,b3,b3, b3,_,_,_
	db 0

basenote = -1+mainpitch
bgm2_p1_5:
pv1 chvol5
tp1 maintempo
sno $21
pan 15
tun 240
vib 15,121,150
tre 2,73,74
.ecco:
db 8,$7f
pat .intro, 27
	db e4, _,_,f4,e4

pat @f, 100

@
	db _,_, _,_, _,_, c4,b3
	db _,_, _,_, _,_, f4,_
	db _,e4, _,_, _,_, c4,b3
	db _,e4, _,_, _,_, f4,e4
	db 0

.intro: db r
	db 0

bgm2_p1_6:
pv1 chvol6
tp1 maintempo
sno $21
pan 9
tun 230
db 4,$7f
vib 2,75,76
tre 5,97,120
	db r,r,r
pat bgm2_p1_5.ecco, 100

;       db g3,_,_,_, _,_,_,_, _,_,_,_, _,_,_,_
;       db b3,_,_,_, _,_,_,_, _,_,_,_, _,_,_,_
	db 0



basenote = -1+mainpitch
bgm2_p1_7:
pv1 chvol7
tp1 maintempo
sno $20
pan 10
tun 240
vib 15,121,150
tre 2,73,74
db 8,$7f
pat @f, 100
@	db b2,_, _,_, _,_, _,_
	db b2,_, _,_, _,_, _,_
	db b2,_, _,_, _,_, _,_
	db c3,_, _,_, _,_, _,_
	db 0


