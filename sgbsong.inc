basenote = 0
cx1 equ (basenote+$81)
d1  equ (basenote+$82)
dx1 equ (basenote+$83)
e1  equ (basenote+$84)
f1  equ (basenote+$85)
fx1 equ (basenote+$86)
g1  equ (basenote+$87)
gx1 equ (basenote+$88)
a1  equ (basenote+$89)
ax1 equ (basenote+$8a)
b1  equ (basenote+$8b)
c2  equ (basenote+$8c)
cx2 equ (basenote+$8d)
d2  equ (basenote+$8e)
dx2 equ (basenote+$8f)
e2  equ (basenote+$90)
f2  equ (basenote+$91)
fx2 equ (basenote+$92)
g2  equ (basenote+$93)
gx2 equ (basenote+$94)
a2  equ (basenote+$95)
ax2 equ (basenote+$96)
b2  equ (basenote+$97)
c3  equ (basenote+$98)
cx3 equ (basenote+$99)
d3  equ (basenote+$9a)
dx3 equ (basenote+$9b)
e3  equ (basenote+$9c)
f3  equ (basenote+$9d)
fx3 equ (basenote+$9e)
g3  equ (basenote+$9f)
gx3 equ (basenote+$a0)
a3  equ (basenote+$a1)
ax3 equ (basenote+$a2)
b3  equ (basenote+$a3)
c4  equ (basenote+$a4)
cx4 equ (basenote+$a5)
d4  equ (basenote+$a6)
dx4 equ (basenote+$a7)
e4  equ (basenote+$a8)
f4  equ (basenote+$a9)
fx4 equ (basenote+$aa)
g4  equ (basenote+$ab)
gx4 equ (basenote+$ac)
a4  equ (basenote+$ad)
ax4 equ (basenote+$ae)
b4  equ (basenote+$af)
c5  equ (basenote+$b0)
cx5 equ (basenote+$b1)
d5  equ (basenote+$b2)
dx5 equ (basenote+$b3)
e5  equ (basenote+$b4)
f5  equ (basenote+$b5)
fx5 equ (basenote+$b6)
g5  equ (basenote+$b7)
gx5 equ (basenote+$b8)
a5  equ (basenote+$b9)
ax5 equ (basenote+$ba)
b5  equ (basenote+$bb)
c6  equ (basenote+$bc)
cx6 equ (basenote+$bd)
d6  equ (basenote+$be)
dx6 equ (basenote+$bf)
e6  equ (basenote+$c0)
f6  equ (basenote+$c1)
fx6 equ (basenote+$c2)
g6  equ (basenote+$c3)
gx6 equ (basenote+$c4)
a6  equ (basenote+$c5)
ax6 equ (basenote+$c6)
b6  equ (basenote+$c7)

o   equ (basenote+$a4)


; $10 - $7f = volume + gate
_		= $c8 ; tie
r		= $c9 ; rest

		      ; $ca-$df = use prohibited

macro sno op1		{ db $e0,op1		}
;instrument

macro pan op1		{ db $e1,op1		}
;10=mid

macro pam op1,op2	{ db $e2,op1,op2	}
;move pan

macro vib op1,op2,op3	{ db $e3,op1,op2,op3	}
;hold,rate,depth

macro vof		{ db $e3		}

macro mv1 op1		{ db $e5,op1		}

macro mv2 op1,op2	{ db $e6,op1,op2	}

macro tp1 op1		{ db $e7,op1		}

macro tp2 op1,op2	{ db $e8,op1,op2	}

macro ktp op1		{ db $e9,op1		}

macro ptp op1		{ db $ea		}

macro tre op1,op2,op3	{ db $eb,op1,op2,op3	}
;hold,rate,depth

macro tof		{ db $ec		}

macro pv1 op1		{ db $ed,op1		}

macro pv2 op1,op2	{ db $ee,op1,op2	}

macro pat op1,op2	{ db $ef
			  dw op1
			  db op2	}
;addr_lo, addr_hi, repeat

macro vch op1		{ db $f0,op1		}

macro swk op1,op2,op3	{ db $f1,op1,op2,op3	}

macro sws op1,op2,op3	{ db $f2,op1,op2,op3	}
      sof		  =  $f3
macro sof		{ db $f3		}

macro tun op1		{ db $f4,op1		}

macro ecv op1,op2,op3	{ db $f5,op1,op2,op3	}
;channel,left,right

macro eof		{ db $f6		}

macro edl op1,op2,op3	{ db $f7,op1,op2,op3	}
;time,feedback,filter

macro ev2 op1,op2,op3	{ db $f8,op1,op2,op3	}

macro swp op1,op2,op3	{ db $f9,op1,op2,op3	}


; $fa-$ff = use prohibited