_PALETTECOLOR 1, _RGB32(255, 255, 255)
COLOR 0, 1

'FOR I = 1 TO 100: PRINT I; COS(I);: NEXT: END





xx = 200: DIM counter(xx)
DIM name$(xx), typ$(xx), nat$(xx), trmov(xx), ccmov(xx), fcap(xx), fcons(xx), susp$(xx)
DIM tf(xx), ts(xx), tr(xx), hf(xx), hs(xx), hr(xx)
DIM weap(xx), wtyp$(xx, 10), wqual$(xx, 10), rof(xx, 10), rng(xx, 10)
DIM ps(xx, 10), pm(xx, 10), pl(xx, 10), px(xx, 10), ammo(xx, 10), con(xx, 10), bur(xx, 10), pran(xx, 10), damage(xx, 10)
DIM weight(xx), load(xx), crew(xx), pass(xx), mnt(xx), price(xx), rf(xx), deck(xx), belly(xx)
DIM stab$(xx), fuel$(xx), night$(xx), rad$(xx), x5$(xx), x6$(xx), x7$(xx), x8$(xx), loca$(xx)

DIM minh$(6), mint$(6), majh$(6), majt$(6)
DIM LOCATION$(6)

DIM text$(100)

ARX = 20
DIM ARTL(ARX), ARTYPE$(ARX), ARMOR(ARX), ARWEIGHT(ARX), ARCOST(ARX): GOSUB 19000

DIM STRIKER(120)
FOR I = 1 TO 13: STRIKER(I) = I * .25: NEXT
RESTORE 20
FOR I = 1 TO 107: READ STRIKER(I + 13): NEXT

RESTORE 25
DIM SPEED$(11), SPEEDBAND(11), MAXSPEED(11)

FOR I = 1 TO 11:
    READ SPEED$(I)
    READ SPEEDBAND(I)
    READ MAXSPEED(I)
NEXT
'speed bands
'speed band speed band number kilometres per hour
'Stopped 0 0
'Idle 1 1-20
'Very Slow 2 20-50
'Slow 3 50-100
'Medium 4 100-200
'High 5 200-300
'Fast 6 300-500
'Very Fast 7 500-800
'Subsonic 8 800-1200
'Supersonic 9 1200-6000
'Hypersonic 10 (A) 6000 or more

'speed band speed band number kilometres per hour
25
DATA "Stopped",0,0
DATA "Idle",1,20
DATA "Very Slow",2,50
DATA "Slow",3,100
DATA "Medium",4,200
DATA "High",5,300
DATA "Fast",6,500
DATA "Very Fast",7,800
DATA "Subsonic",8,1200
DATA "Supersonic",9,6000
DATA "Hypersonic",10,10000


CLS
PRINT " This software generates TAC cards for GDWs  T2K, TNE & 2300AD"
PRINT
PRINT " Choose the measuring system you want to use"
PRINT ""
PRINT " 1. Twilight 2000 (2.2) and TNE rules"
PRINT ""
PRINT " 2. Striker I rules"
PRINT ""
PRINT " 3. Actual armor equivalent in centimeters of steel (cm)"
PRINT ""
PRINT " 4. Mongoose T2E vehicle rules"
PRINT
PRINT " 5. Cepheus vehicle rules"
PRINT
PRINT " 6. Armor calculator"
PRINT
INPUT " ", style: IF style = 0 THEN style = 1
IF style = 6 GOTO 19001
'T2K Armor Values are usually Armor in cm x 2
'DIV=2 is armor in cm
'DIV=1 is T2K value
'DIV=2.1666 = MgT2E values

HEX = 100: REM Feldgr■Аe in m
HEX = HEX / 50

DDMOD = 3.5

IF style = 1 THEN DIV = 1: Style$ = " T2K+TNE"
IF style = 2 THEN DIV = 2: HEX = 10: Style$ = " Striker I"
IF style = 3 THEN DIV = 2: Style$ = " Armor in cm"
IF style = 4 THEN DIV = 2.16666: Style$ = " MgT2E"
IF style = 5 THEN DIV = 5.4: Style$ = " Cepheus"

PRINT
'INPUT " 0 for Twilight, 1 for Traveller ", trav
'PRINT
'PRINT
INPUT " Vehicle Name ? (partial possible) "; SEARCH$: SEARCH$ = UCASE$(SEARCH$)
IF SEARCH$ = "" THEN SEARCH$ = "M1A2E"

PRINT


PRINT " The list output format is for OGRE:2300 from Challenge 34"
PRINT
PRINT " SPACE = TAC card, after opening the TAC press P to generate a DOC, R = Restart"
PRINT ""
PRINT " TYP Name                       A/D   DEF   MOV    Att/Rng    SEC"
PRINT

REM Twilight 2000 Vehicle Programm

GOSUB 8001: RESTORE
wlen = 12
T26 = 1





20
DATA 3.54,3.86,4.2,4.59,5,5.54
DATA 5.95,6.48,7.07,7.71,8.41,9.17,10,10.9,11.9,13
DATA 14.1,15.4,16.8,18.3,20,21.8,23.8,25.9,28.3,30.8
DATA 33.6,36.7,40,43.6,47.6,51.9,56.6,61.7,67.3,73.4
DATA 80,87.2,95.1,104,113,123,135,147,160,174
DATA 190,207,226,247,269,293,320,349,381,415
DATA 453,494,538,587,640,698,761,830,905,987
DATA 1080,1170,1280,1400,1520,1660,1810,1970,2150,2350
DATA 2560,2790,3040,3320,3620,3950,4310,4700,5120,5580
DATA 6090,6640,7240,7900,8610,9360,10200,11200,12200,13300
DATA 14500,15800,17200,18800,20500,22300,24400,26600,29000,31600,34400

GOSUB 19000 'Armor


RESTORE 10000

FOR I = 1 TO xx
    READ name$(I), typ$(I), nat$(I), trmov(I), ccmov(I), fcap(I), fcons(I), susp$(I)
    IF name$(I) = "XXX" THEN xz = I - 1: I = xx: PRINT xz: GOTO 10
    READ tf(I), ts(I), tr(I), hf(I), hs(I), hr(I)
    READ weap(I): IF weap(I) = 0 GOTO 11
    FOR Q = 1 TO weap(I)
        READ wtyp$(I, Q), wqual$(I, Q), rof(I, Q), rng(I, Q)
        wt$ = wtyp$(I, Q)
        'FOR u = 1 TO LEN(wt$): w$ = MID$(wt$, u, 2)
        'IF w$ = "mm" THEN wtyp$(I, q) = LEFT$(wt$, u + 1): u = LEN(wt$)
        'NEXT

        READ ps(I, Q), pm(I, Q), pl(I, Q), px(I, Q), ammo(I, Q)
        READ con(I, Q), bur(I, Q), pran(I, Q) ', damage(I, Q)
    NEXT
    11 REM

    READ weight(I), load(I), crew(I), pass(I), mnt(I), price(I), rf(I), deck(I), belly(I)

    IF deck(I) = 0 THEN deck(I) = CINT(hr(I) / 2)
    IF belly(I) = 0 THEN belly(I) = CINT(hr(I) / 2)



    READ stab$(I), fuel$(I), night$(I), rad$(I), x5$(I), x6$(I), x7$(I), x8$(I), loca$(I)
    IF crew(I) = 3 AND pass(I) = 4 THEN crew(I) = 4: pass(I) = 0

    name$ = UCASE$(name$(I)): nale = LEN(name$)
    FOR z = 1 TO nale
        IF MID$(name$, z, LEN(SEARCH$)) = SEARCH$ THEN counter(I) = 1: ' PRINT name$;: GOSUB 1000
    NEXT
    10 IF xz = 0 THEN xz = xx
NEXT

100 'Beginn
FOR x0 = 90 TO 65 STEP -1
    FOR x1 = 65 TO 90
        FOR I = 1 TO xx
            IF CHR$(x0) <> LEFT$(typ$(I), 1) GOTO 900
            IF CHR$(x1) <> LEFT$(name$(I), 1) GOTO 900
            IF counter(I) = 0 GOTO 900


            'Ogre
            PRINT " "; typ$(I); " "; name$(I); SPC(25 - LEN(name$(I)));
            OFFEN = ps(I, 1) / DIV: ttx = OFFEN: GOSUB 9001: OFFEN = ttz
            DEFEN = hf(I) / DIV: ttx = DEFEN: GOSUB 9001: DEFEN = ttz

            PRINT USING "###/### "; OFFEN; DEFEN;

            armor = CINT((hf(I) + tf(I)) / 80)
            IF armor < .3 THEN armor = 1: GOTO 110
            IF armor < 2 THEN armor = 2: GOTO 110

            110
            PRINT USING "D#"; armor;
            move = trmov(I) / 2 * .6666 / 22.5
            IF LEFT$(susp$(I), 1) = "G" THEN move = ccmov(I) / 22.5 / 3
            IF move < 5 THEN PRINT USING "    M# "; move; ELSE PRINT USING "    M#/#"; CINT(move / 2); INT(move / 2);
            offe = (ps(I, 1) + 7) / 40: ran = rng(I, 1) * 8 / 1500
            IF wqual$(I, 1) = "R" THEN ran = ran / 8
            PRINT USING "    P## /##"; offe; ran;
            IF wqual$(I, weap(I)) = "R" THEN PRINT USING "    R## /## x##"; (ps(I, weap(I)) + 7) / 40; rng(I, weap(I)) / 1500; ammo(I, weap(I));
            PRINT
            GOSUB 1000: IF a$ = " " OR UCASE$(a$) = "P" GOTO 101
        900 NEXT
    NEXT

NEXT
PRINT " END"
GOSUB 1000
RUN


101 'Screen Output
save$ = name$(I) + Style$ + ".DOC"
CLS
horiz = 9: vert = 67: horiz = 4
t3 = 68: t4 = 18 ': t4 = 21

pp$ = name$(I) + ", "
IF LEFT$(susp$(I), 1) = "T" THEN pp$ = pp$ + "Tracked ": mv$ = "Treads"
IF LEFT$(susp$(I), 1) = "W" THEN pp$ = pp$ + "Wheeled ": mv$ = "Wheels"
IF LEFT$(susp$(I), 1) = "G" THEN pp$ = pp$ + "Antigrav ": mv$ = "A-Grav"
IF LEFT$(susp$(I), 1) = "H" THEN pp$ = pp$ + "Hovercraft ": mv$ = "Plenum"

RGEAR = VAL(RIGHT$(susp$(I), LEN(susp$(I)) - 1)) / DIV
crew = crew(I): pass = pass(I)
GOSUB 4000

p$ = ""
IF typ$(I) = "MBT" THEN p$ = "Main Battle Tank"
IF typ$(I) = "SPG" THEN p$ = "Self Propelled Gun"
IF typ$(I) = "SPA" THEN p$ = "Self Propelled Artillery"
IF typ$(I) = "APC" THEN p$ = "Armored Personnel Carrier"
IF typ$(I) = "RCV" THEN p$ = "Reconnaissance Vehicle"
IF typ$(I) = "LCV" THEN p$ = "Light Combat Vehicle"
IF typ$(I) = "IFV" THEN p$ = "Infantry Fighting Vehicle"
IF typ$(I) = "AGS" THEN p$ = "Armored Gun System"
IF typ$(I) = "ATG" THEN p$ = "Anti Tank Gun"
IF typ$(I) = "HVT" THEN p$ = "Hovertank"
IF typ$(I) = "HVC" THEN p$ = "Hovercraft"

IF typ$(I) = "TLT" THEN p$ = "Tank"
IF typ$(I) = "APC" THEN p$ = "Personal Carrier"
IF typ$(I) = "SPD" THEN p$ = "Attack Speeder"
IF typ$(I) = "GRT" THEN p$ = "Grav Tank"
IF typ$(I) = "ISS" THEN p$ = "Support Sled"
IF typ$(I) = "GTD" THEN p$ = "Tank Destroyer"
pp$ = pp$ + p$

dfm = deck(I) / DIV: ttx = dfm: GOSUB 9001: dfm = ttz
bfm = belly(I) / DIV: ttx = bfm: GOSUB 9001: bfm = ttz
IF dfm > 99 THEN dfm = 99
IF bfm > 99 THEN bfm = 99


cr$ = " C "
IF crew > 1 THEN cr$ = cr$ + " D "
IF crew > 2 THEN cr$ = cr$ + " G "
IF crew > 3 THEN cr$ = cr$ + " L "
IF crew > 4 THEN cr$ = cr$ + " R "
IF pass > 0 THEN cr$ = cr$ + "   ": FOR z = 1 TO pass: cr$ = cr$ + " T ": NEXT

'55.38% of km/h
road = trmov(I) / 5 * 3.6 / 1.3
country = ccmov(I) / 5 * 3.6 / 1.3

IF style = 1 OR style = 5 THEN roadHEX = CINT(trmov(I) / 4.287 / 5) * 5: countryhex = CINT(ccmov(I) / 4.287 / 5) * 5: GOTO 222
IF style = 2 THEN roadHEX = CINT(road / 1.2 / 5) * 5: countryhex = CINT(country / 1.2 / 5) * 5: GOTO 222
IF style = 3 THEN roadHEX = road / 15: countryhex = country / 15: GOTO 222

FOR zz = 1 TO 7
    IF road > MAXSPEED(zz) THEN roadHEX = SPEEDBAND(zz)
NEXT
FOR zz = 1 TO 7
    IF country > MAXSPEED(zz) THEN countryhex = SPEEDBAND(zz)
NEXT
222


IF a$ = "P" OR a$ = "p" THEN GOTO 3000: 'Write to doc adress

CLS
GOSUB 2000

LOCATE 1, 1:
PRINT "з";
FOR f = 1 TO LEN(pp$) + 2: PRINT "д";: NEXT: PRINT "©"
PRINT "Ё "; pp$; " Ё"; Style$
PRINT "ю";
FOR f = 1 TO LEN(pp$) + 2: PRINT "д";: NEXT: PRINT "ы"


149

PRINT "з";
FOR f = 1 TO LEN(cr$) + 2: PRINT "д";: NEXT: PRINT "©"

PRINT "Ё "; cr$; " Ё"
PRINT "ю";
FOR f = 1 TO LEN(cr$) + 2: PRINT "д";: NEXT: PRINT "ы"


zz0 = 67
LOCATE 1, zz0: PRINT "здддддбддддд©"
LOCATE 2, zz0: PRINT USING "Ё#### Ё#### Ё"; road; country
LOCATE 3, zz0: PRINT "цдддддеддддд╢"
LOCATE 4, zz0: PRINT USING "Ё###  Ё###  Ё"; roadHEX; countryhex
LOCATE 5, zz0: PRINT "юдддддаддддды"


801 LOCATE 7, 1
PRINT "            здддддддддбдддддддддбдддддддддбдддддддддбддддддддд©"
PRINT "            Ё Average ЁDifficultЁ Formid. Ё Extreme Ё CC   FR Ё"
PRINT "здддддддддддедддддддддедддддддддедддддддддедддддддддеддддддддд╢"
FOR Q = 1 TO weap(I)
    wtyp$ = wtyp$(I, Q)
    IF LEN(wtyp$) > 10 THEN wtyp$ = LEFT$(wtyp$, 10)
    rng = rng(I, Q) / HEX: ' IF rng / 12.5 > 99 THEN rng = 99 * 25
    ps = ps(I, Q)
    pm = pm(I, Q)
    pl = pl(I, Q)
    px = px(I, Q)
    mult = 1: IF rof(I, Q) > 1 THEN mult = rof(I, Q)
    mult = 2

    PQX = ps: IF style > 3 THEN PQX = ps / 3.5
    IF PQX < 1 THEN GOTO 800



    'IF wqual$(I, q) = "C" THEN ps = ps + 7: pm = pm + 7: pl = pl + 7: px = px + 7
    qq = ps / DIV: GOSUB 1100: ps = qq
    qq = pm / DIV: GOSUB 1100: pm = qq
    qq = pl / DIV: GOSUB 1100: pl = qq
    qq = px / DIV: GOSUB 1100: px = qq

    ttx = ps: GOSUB 9001: ps = ttz
    ttx = pm: GOSUB 9001: pm = ttz
    ttx = pl: GOSUB 9001: pl = ttz
    ttx = px: GOSUB 9001: px = ttz

    rof = rof(I, Q)
    IF rof < 1 THEN rs = 1: rm = 1: rl = 1: rx = 1
    IF rof = 1 THEN rs = 2: rm = 1: rl = 1: rx = 1
    IF rof > 1 THEN rs = 2: rm = 1: rl = 1: rx = 1
    IF rof > 2 THEN rs = 3: rm = 2: rl = 1: rx = 1
    IF rof > 3 THEN rs = 4: rm = 3: rl = 2: rx = 1
    IF rof > 5 THEN rs = 5: rm = 4: rl = 3: rx = 2
    IF rof > 10 THEN rs = 7: rm = 6: rl = 5: rx = 4

    PRINT "Ё "; wtyp$; SPC(10 - LEN(wtyp$));
    REM PRINT USING "Ё###"; ammo(i, q) / 6 / rof(i, q);
    IF wqual$(I, Q) = "R" OR pm(I, Q) = 0 THEN PRINT USING "Ё         Ё1W###"; ps;: PRINT USING "### Ё         Ё         "; rng / 50;: GOTO 789
    'IF ps < 1.5 THEN PRINT "Ё                                     "; : GOTO 790
    'PRINT USING "Ё#W###"; rs; ps;: PRINT USING "### "; rng / 50;
    'PRINT USING "Ё#W###"; rm; pm;: PRINT USING "### "; rng / 25;
    'PRINT USING "Ё#W###"; rl; pl;: PRINT USING "### "; rng / 12.5;
    'PRINT USING "Ё#W###"; rx; px;: PRINT USING "### "; rng / 6.25;
    IF style > 3 GOTO 787
    rnx = rng: GOSUB 790: PRINT USING "###P"; ps;
    rnx = rng * 2: GOSUB 790: PRINT USING "###P"; pm;
    rnx = rng * 4: GOSUB 790: PRINT USING "###P"; pl;
    rnx = rng * 8: GOSUB 790:: PRINT USING "###P"; px;
    GOTO 789

    790
    IF rnx < 1000 THEN PRINT USING "Ё#### "; rnx; ELSE PRINT USING "Ё##.#K"; rnx / 1000;
    RETURN



    787
    rnx = rng: GOSUB 790: PENETRATION = ps: GOSUB 788
    rnx = rng * 2: GOSUB 790: PENETRATION = pm: GOSUB 788
    rnx = rng * 4: GOSUB 790:: PENETRATION = pl: GOSUB 788
    rnx = rng * 8: GOSUB 790: PENETRATION = px: GOSUB 788
    GOTO 789


    788 PENETRATION = (PENETRATION + 7 / DIV) / DDMOD
    IF CINT(PENETRATION) < 10 OR style = 5 THEN PRINT USING "###D"; CINT(PENETRATION); ELSE PRINT USING "##DD"; CINT(PENETRATION / 10);
    RETURN

    789
    pran = pran(I, Q) / 25 / HEX: IF pran > 99 THEN pran = 99
    pran = bur(I, Q) / 50 / HEX
    'ep = CINT(SQR(con(I, q) * mult)):

    pran = bur(I, Q) / HEX: ep = con(I, Q)
    IF wqual$(I, Q) <> "C" THEN ep = 0
    IF ep = 0 THEN PRINT "Ё         Ё";: GOTO 792
    PRINT USING "Ё### "; con(I, Q);: PRINT ":";

    PRINT USING "### Ё"; pran;


    792 PRINT
    IF Q < weap(I) THEN PRINT "цдддддддддддедддддддддедддддддддедддддддддедддддддддеддддддддд╢"
800 NEXT Q
IF weap(I) > 0 THEN PRINT "юдддддддддддадддддддддадддддддддадддддддддадддддддддаддддддддды": PRINT
REM                    PRINT "здддддддддддедддддддддедддддддддедддддддддедддддддддеддддддддд╢"
802 GOSUB 4000
tfm = CINT(tf(I) / DIV)
tsm = ts(I) / DIV
trm = tr(I) / DIV

hfm = CINT(hf(I) / DIV)
hsm = hs(I) / DIV
hrm = hr(I) / DIV

t11 = 1
t12 = 10 / DIV
t20 = t12 + 1
t21 = 20 / DIV
t30 = t21 + 1
t31 = 40 / DIV
t40 = t31 + 1
t41 = 60 / DIV


h1$ = "Body" + STR$(0 + hfm) + "+": h2$ = "Major" + STR$(t30 + hfm) + "+"
t1$ = "": t2$ = ""
h1$ = "Minor Body": h2$ = "Major Body"
t1$ = "": t2$ = ""

xc = 14
IF loca$(I) <> "VEH" THEN t1$ = "Turret" + STR$(0 + tfm) + "+": t2$ = "Major" + STR$(t30 + tfm) + "+"
IF loca$(I) <> "VEH" THEN t1$ = "Min. Turret": t2$ = "Maj. Turret"

LOCATE 16, 1: PRINT "здб";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "б";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "б";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "б";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "©"


PRINT "Ё Ё "; h1$; SPC(xc - 1 - LEN(h1$));
PRINT "Ё "; h2$; SPC(xc - 1 - LEN(h2$));
PRINT "Ё "; t1$; SPC(xc - 1 - LEN(t1$));
PRINT "Ё "; t2$; SPC(xc - 1 - LEN(t2$)); "Ё"
PRINT "цде";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "е";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "е";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "е";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "╢"


FOR j = 1 TO 6
    LOCATE 18 + j, 1
    PRINT USING "Ё#Ё "; j;
    PRINT minh$(j); SPC(xc - 1 - LEN(minh$(j)));
    PRINT "Ё "; majh$(j); SPC(xc - 1 - LEN(majh$(j)));
    PRINT "Ё "; mint$(j); SPC(xc - 1 - LEN(mint$(j)));
    PRINT "Ё "; majt$(j); SPC(xc - 1 - LEN(majt$(j))); "Ё";
NEXT
LOCATE 25, 1
PRINT "юда";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "а";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "а";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "а";
FOR f = 1 TO xc: PRINT "д";: NEXT: PRINT "ы";


LOCATE t4, t3: PRINT "здддбдддддд©"
FOR t = 1 TO 6
LOCATE t4 + t, t3: PRINT USING "Ё## Ё"; t;: PRINT LOCATION$(t); SPC(6 - LEN(LOCATION$(t))); "Ё";: NEXT
LOCATE t4 + 7, t3: PRINT "юдддадддддды";

GOSUB 2000
GOSUB 1000:
IF UCASE$(a$) = "P" THEN GOTO 3000
CLS
RUN




1000 a$ = INKEY$: IF a$ = "" GOTO 1000
aa = ASC(a$)
IF aa > 64 AND aa < 91 THEN x0 = aa: x1 = 65


'IF a$ = "q" OR a$ = "Q" THEN END
IF a$ = "r" OR a$ = "R" THEN RUN
RETURN





1100 REM Kalibrierung
RETURN
IF qq < 10 / DIV THEN RETURN
'qq = CINT(qq / (10 / div)) * (10 / div)
RETURN

2000 REM Panzerdarstellung
tfm = tf(I) / DIV: ttx = tfm: GOSUB 9001: tfm = ttz
'IF ttz < 2 THEN tfm = 2
IF ttz <= .3 THEN tfm = 1
tsm = ts(I) / DIV: ttx = tsm: GOSUB 9001: tsm = ttz
'IF ttz < 2 THEN tsm = 2
IF ttz <= .3 THEN tsm = 1
trm = tr(I) / DIV: ttx = trm: GOSUB 9001: trm = ttz
'IF ttz < 2 THEN trm = 2
IF ttz <= .3 THEN trm = 1

hfm = hf(I) / DIV: ttx = hfm: GOSUB 9001: hfm = ttz
'IF ttz < 2 THEN hfm = 2
IF ttz <= .3 THEN hfm = 1

hsm = hs(I) / DIV: ttx = hsm: GOSUB 9001: hsm = ttz
'IF ttz < 2 THEN hsm = 2
IF ttz <= .3 THEN hsm = 1

hrm = hr(I) / DIV: ttx = hrm: GOSUB 9001: hrm = ttz
'IF ttz < 2 THEN hrm = 2
IF ttz <= .3 THEN hrm = 1

IF tfm = 0 GOTO 2900


IF loca$(I) = "CIH" GOTO 2810
IF loca$(I) = "VEH" GOTO 2900

ts0 = 0: ts1 = 0
'IF tsm >= 99.9 THEN ts0 = 10: ts1 = tsm - 100: GOTO 2001
IF tsm >= 90 THEN ts0 = 9: ts1 = tsm - 90: GOTO 2001
IF tsm >= 80 THEN ts0 = 8: ts1 = tsm - 80: GOTO 2001
IF tsm >= 70 THEN ts0 = 7: ts1 = tsm - 70: GOTO 2001
IF tsm >= 60 THEN ts0 = 6: ts1 = tsm - 60: GOTO 2001
IF tsm >= 50 THEN ts0 = 5: ts1 = tsm - 50: GOTO 2001
IF tsm >= 40 THEN ts0 = 4: ts1 = tsm - 40: GOTO 2001
IF tsm >= 30 THEN ts0 = 3: ts1 = tsm - 30: GOTO 2001
IF tsm >= 20 THEN ts0 = 2: ts1 = tsm - 20: GOTO 2001
IF tsm >= 10 THEN ts0 = 1: ts1 = tsm - 10: GOTO 2001
IF tsm < 10 THEN ts0 = 0: ts1 = tsm
2001
ts1 = INT(ts1)


'IF hsm >= 99.9 THEN hs0 = 10: hs1 = hsm - 100: GOTO 2002

hs0 = 0: hs1 = 1
IF hsm >= 89.9 THEN hs0 = 9: hs1 = hsm - 90: GOTO 2002
IF hsm >= 79.9 THEN hs0 = 8: hs1 = hsm - 80: GOTO 2002
IF hsm >= 69.9 THEN hs0 = 7: hs1 = hsm - 70: GOTO 2002
IF hsm >= 59.9 THEN hs0 = 6: hs1 = hsm - 60: GOTO 2002
IF hsm >= 49.9 THEN hs0 = 5: hs1 = hsm - 50: GOTO 2002
IF hsm >= 39.9 THEN hs0 = 4: hs1 = hsm - 40: GOTO 2002
IF hsm >= 29.9 THEN hs0 = 3: hs1 = hsm - 30: GOTO 2002
IF hsm >= 19.9 THEN hs0 = 2: hs1 = hsm - 20: GOTO 2002
IF hsm >= 10 THEN hs0 = 1: hs1 = hsm - 10: GOTO 2002
IF hsm < 10 THEN hs0 = 0: hs1 = hsm



2002
hs1 = INT(hs1): IF hs1 > 9 THEN STOP
'horiz = horiz - 1
'LOCATE horiz + 0, vert: PRINT "      ╨"
'LOCATE horiz + 1, vert: PRINT "      ╨"
LOCATE horiz + 2.00000000000000000000000, vert: PRINT " зддддвдддд© "
IF hfm < 100 THEN LOCATE horiz + 3, vert: PRINT USING "зы  ###    ю©"; hfm
IF hfm >= 100 THEN LOCATE horiz + 3, vert: PRINT USING "зы   ###   ю©"; hfm
LOCATE horiz + 4.000000000000000000000000, vert: PRINT "цдбмммпмммбд╢"
IF tfm < 100 THEN LOCATE horiz + 5, vert: PRINT USING "Ё гд©## зд╤ Ё"; tfm
IF tfm >= 100 THEN LOCATE horiz + 5, vert: PRINT USING "Ё гд©###зд╤ Ё"; tfm

IF ts0 > 0 THEN LOCATE horiz + 6, vert: PRINT USING "Ё ╨#цддд╢#╨ Ё"; ts0; ts0
IF ts0 > 0 THEN LOCATE horiz + 7, vert: PRINT USING "Ё ╨#Ё   Ё#╨ Ё"; ts1; ts1
IF hs0 > 0 THEN LOCATE horiz + 8, vert: PRINT USING "Ё#╨ Ё## Ё ╨#Ё"; hs0; trm; hs0
IF hs0 > 0 THEN LOCATE horiz + 9, vert: PRINT USING "Ё#цмомммом╢#Ё"; hs1; hs1
'IF ts0 > 0 AND hs0 > 0 GOTO 2102

IF ts0 = 0 THEN LOCATE horiz + 6.00000, vert: PRINT "Ё ╨ цддд╢ ╨ Ё"
IF ts0 = 0 THEN LOCATE horiz + 7, vert: PRINT USING "Ё ╨#Ё   Ё#╨ Ё"; ts1; ts1
IF hs0 = 0 THEN LOCATE horiz + 8, vert: PRINT USING "Ё#╨ Ё## Ё ╨#Ё"; hs1; trm; hs1
IF hs0 = 0 THEN LOCATE horiz + 9.00000, vert: PRINT "Ё цмомммом╢ Ё"

2102 LOCATE horiz + 10, vert: PRINT "Ё Ём м м мЁ Ё"
LOCATE horiz + 11, vert: PRINT USING "Ё Ём ##  мЁ Ё"; hrm
LOCATE horiz + 12, vert: PRINT USING "ю©Ё### ###Ёзы"; dfm; bfm
IF deck(I) = 0 AND belly(I) = 0 THEN LOCATE horiz + 12, vert: PRINT "ю©Ём м м мЁзы"
       
LOCATE horiz + 13, vert: PRINT " юадддддддаы";
RETURN
2810
hs0 = 0: hs1 = 1
IF hsm >= 89.9 THEN hs0 = 9: hs1 = hsm - 90: GOTO 2802
IF hsm >= 79.9 THEN hs0 = 8: hs1 = hsm - 80: GOTO 2802
IF hsm >= 69.9 THEN hs0 = 7: hs1 = hsm - 70: GOTO 2802
IF hsm >= 59.9 THEN hs0 = 6: hs1 = hsm - 60: GOTO 2802
IF hsm >= 49.9 THEN hs0 = 5: hs1 = hsm - 50: GOTO 2802
IF hsm >= 39.9 THEN hs0 = 4: hs1 = hsm - 40: GOTO 2802
IF hsm >= 29.9 THEN hs0 = 3: hs1 = hsm - 30: GOTO 2802
IF hsm >= 19.9 THEN hs0 = 2: hs1 = hsm - 20: GOTO 2802
IF hsm >= 10 THEN hs0 = 1: hs1 = hsm - 10: GOTO 2802
IF hsm < 10 THEN hs0 = 0: hs1 = hsm
2802

'horiz = horiz - 1
LOCATE horiz + 0, vert: PRINT "       "
LOCATE horiz + 1, vert: PRINT "       "
LOCATE horiz + 2.000000, vert: PRINT " зддддедддд© "
LOCATE horiz + 3., vert: PRINT USING "зы  ###    ю©"; hfm
LOCATE horiz + 4.000000, vert: PRINT "цдбдбдодбдбд╢"
LOCATE horiz + 5., vert: PRINT USING "Ё Ёзы## ю©Ё Ё"; tfm
LOCATE horiz + 6., vert: PRINT USING "Ё ЁЁ##И##ЁЁ Ё"; tsm; tsm
LOCATE horiz + 7., vert: PRINT USING "Ё Ёю©## зыЁ Ё"; trm
IF hs0 > 0 THEN LOCATE horiz + 7., vert: PRINT USING "Ё#Ёю©## зыЁ#Ё"; hs0; trm; hs0
IF hs0 > 0 THEN LOCATE horiz + 8., vert: PRINT USING "Ё#цмомммом╢#Ё"; hs1; hs1
IF hs0 > 0 THEN LOCATE horiz + 9.000000, vert: PRINT "Ё Ё   Ё   Ё Ё"
IF hs0 > 0 THEN LOCATE horiz + 10, vert: PRINT USING "Ё Ё  ##   Ё Ё"; hrm
IF hs0 > 0 THEN LOCATE horiz + 11.00000, vert: PRINT "ю©цдддаддд╢зы"
IF hs0 > 0 THEN LOCATE horiz + 12.00000, vert: PRINT " юадддддддаы": RETURN

LOCATE horiz + 8., vert: PRINT USING "Ё#Ё юддды Ё#Ё"; hsm; hsm
LOCATE horiz + 9.000000, vert: PRINT "Ё цдддбддд╢ Ё"
LOCATE horiz + 10.00000, vert: PRINT "Ё Ё   Ё   Ё Ё"
LOCATE horiz + 11, vert: PRINT USING "Ё Ё  ##   Ё Ё"; hrm
LOCATE horiz + 12.00000, vert: PRINT "ю©цдддаддд╢зы"
LOCATE horiz + 13.00000, vert: PRINT " юадддддддаы";
RETURN


2900
LOCATE horiz + 2, vert: PRINT " зддддддддд© "
LOCATE horiz + 3, vert: PRINT USING "зы  ###    ю©"; hfm
LOCATE horiz + 4, vert: PRINT "цдббдддддббд╢"
LOCATE horiz + 5, vert: PRINT "Ё ЁюдддддыЁ Ё"
LOCATE horiz + 6, vert: PRINT "Ё Ё       Ё Ё"
LOCATE horiz + 7, vert: PRINT "Ё Ё       Ё Ё"
LOCATE horiz + 8, vert: PRINT USING "Ё#цдддбддд╢#Ё"; hsm; hsm
LOCATE horiz + 9, vert: PRINT "Ё Ё   Ё   Ё Ё"
LOCATE horiz + 10, vert: PRINT "Ё Ё   Ё   Ё Ё"
LOCATE horiz + 11, vert: PRINT USING "Ё Ё   #   Ё Ё"; hrm
LOCATE horiz + 12, vert: PRINT "ю©цдддаддд╢зы"
LOCATE horiz + 13, vert: PRINT " юадддддддаы";

RETURN





















































END
3000 'PRINT
IF nnn = 0 THEN nnn = 1: OPEN save$ FOR OUTPUT AS #1: PRINT " Written to HD as "; save$


10150 REM
LOCATE 4, 1:
cr$ = " C "
IF crew > 1 THEN cr$ = cr$ + " D "
IF crew > 2 THEN cr$ = cr$ + " G "
IF crew > 3 THEN cr$ = cr$ + " L "
IF crew > 4 THEN cr$ = cr$ + " R "
IF pass > 0 THEN cr$ = cr$ + "   ": FOR z = 1 TO pass: cr$ = cr$ + " T ": NEXT

zz0 = 71: zz0 = 67


10801
'55.38% of km/h
road = trmov(I) / 5 * 3.6 / 1.3
country = ccmov(I) / 5 * 3.6 / 1.3

IF style = 1 OR style = 5 THEN roadHEX = CINT(trmov(I) / 4.287 / 5) * 5: countryhex = CINT(ccmov(I) / 4.287 / 5) * 5: GOTO 10222
IF style = 2 THEN roadHEX = CINT(road / 1.2 / 5) * 5: countryhex = CINT(country / 1.2 / 5) * 5: GOTO 10222
IF style = 3 THEN roadHEX = road / 15: countryhex = country / 15: GOTO 10222

FOR zz = 1 TO 7
    IF road > MAXSPEED(zz) THEN roadHEX = SPEEDBAND(zz)
NEXT
FOR zz = 1 TO 7
    IF country > MAXSPEED(zz) THEN countryhex = SPEEDBAND(zz)
NEXT



10222
dfm = deck(I) / DIV: ttx = dfm: GOSUB 9001: dfm = ttz: IF dfm < 1 THEN dfm = 1
bfm = belly(I) / DIV: ttx = bfm: GOSUB 9001: bfm = ttz: IF bfm < 1 THEN bfm = 1
GOSUB 102000

PRINT #nnn, "  здддддбддддд©"
PRINT #nnn, USING "  ЁD:###ЁB:###Ё  зддддддддддбддддддддддбддддддддддбддддддддддбдддддддддд©"; dfm; bfm
PRINT #nnn, "  юдддддаддддды  Ё   Short  Ё EffectiveЁ   Long   Ё Extreme  Ё Conc  FR Ё"
PRINT #nnn, "зддддддддддддддддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
EP0 = 0
'IF style = 5 THEN weap(I) = 1
FOR Q = 1 TO weap(I)
    wtyp$ = wtyp$(I, Q)
    IF LEN(wtyp$) > 15 THEN wtyp$ = LEFT$(wtyp$, 15)
    rng = rng(I, Q) / HEX: ' IF rng / 12.5 > 99 THEN rng = 99 * 25
    ps = ps(I, Q)
    pm = pm(I, Q)
    pl = pl(I, Q)
    px = px(I, Q)
    mult = 1: IF rof(I, Q) > 1 THEN mult = rof(I, Q)
    mult = 2

    PQX = ps: IF style > 3 THEN PQX = ps / 3.5
    IF PQX < 1 THEN GOTO 10800



    ep = CINT(SQR(con(I, Q) * mult)): IF wqual$(I, Q) = "x" THEN ep = 0
    'IF wqual$(I, q) = "C" THEN ps = ps + 7: pm = pm + 7: pl = pl + 7: px = px + 7
    qq = ps / DIV: GOSUB 1100: ps = qq
    qq = pm / DIV: GOSUB 1100: pm = qq
    qq = pl / DIV: GOSUB 1100: pl = qq
    qq = px / DIV: GOSUB 1100: px = qq

    ttx = ps: GOSUB 9001: ps = ttz
    ttx = pm: GOSUB 9001: pm = ttz
    ttx = pl: GOSUB 9001: pl = ttz
    ttx = px: GOSUB 9001: px = ttz

    rof = rof(I, Q)
    IF rof < 1 THEN rs = 1: rm = 1: rl = 1: rx = 1
    IF rof = 1 THEN rs = 2: rm = 1: rl = 1: rx = 1
    IF rof > 1 THEN rs = 2: rm = 1: rl = 1: rx = 1
    IF rof > 2 THEN rs = 3: rm = 2: rl = 1: rx = 1
    IF rof > 3 THEN rs = 4: rm = 3: rl = 2: rx = 1
    IF rof > 5 THEN rs = 5: rm = 4: rl = 3: rx = 2
    IF rof > 10 THEN rs = 7: rm = 6: rl = 5: rx = 4

    PRINT #nnn, "Ё "; wtyp$; SPC(15 - LEN(wtyp$));
    REM print #nnn, USING "Ё###"; ammo(i, q) / 6 / rof(i, q);
    IF wqual$(I, Q) = "R" OR pm(I, Q) = 0 THEN PRINT #nnn, "Ё          ";: rOx = rs: rnx = rng: GOSUB 10790: STP = ps: GOSUB 10795: PRINT #nnn, "Ё          Ё          ";: GOTO 10789
    'IF ps < 1.5 THEN print #nnn, "Ё                                     "; : GOTO 10790
    'print #nnn, USING "Ё#W###"; rs; ps;: print #nnn, USING "### "; rng / 50;
    'print #nnn, USING "Ё#W###"; rm; pm;: print #nnn, USING "### "; rng / 25;
    'print #nnn, USING "Ё#W###"; rl; pl;: print #nnn, USING "### "; rng / 12.5;
    'print #nnn, USING "Ё#W###"; rx; px;: print #nnn, USING "### "; rng / 6.25;
    IF style > 3 GOTO 10787
    rOx = rs: rnx = rng: GOSUB 10790: STP = ps: GOSUB 10795
    rOx = rm: rnx = rng * 2: GOSUB 10790: STP = pm: GOSUB 10795
    rOx = rl: rnx = rng * 4: GOSUB 10790: STP = pl: GOSUB 10795
    rOx = rx: rnx = rng * 8: GOSUB 10790: STP = px: GOSUB 10795
    GOTO 10789

    10790 IF style > 1 GOTO 10782
    IF rnx < 1000 THEN PRINT #nnn, USING "Ё# ###"; rOx; rnx; ELSE PRINT #nnn, USING "Ё#"; rOx;: PRINT #nnn, USING "##.#"; rnx / 1000;
    RETURN

    10782
    IF rnx < 1000 THEN PRINT #nnn, USING "Ё#### "; rnx; ELSE PRINT #nnn, USING "Ё##.# "; rnx / 1000;
    RETURN


    10795
    IF STP < 10 THEN PRINT #nnn, USING "  (#)"; STP;: RETURN
    IF STP < 100 THEN PRINT #nnn, USING " (##)"; STP;: RETURN
    PRINT #nnn, USING "(###)"; STP;: RETURN

    10787
    rnx = rng: GOSUB 10790: PENETRATION = ps: GOSUB 10788
    rnx = rng * 2: GOSUB 10790: PENETRATION = pm: GOSUB 10788
    rnx = rng * 4: GOSUB 10790:: PENETRATION = pl: GOSUB 10788
    rnx = rng * 8: GOSUB 10790: PENETRATION = px: GOSUB 10788
    GOTO 10789


    10788 PENETRATION = (PENETRATION + 7 / DIV) / DDMOD
    IF CINT(PENETRATION) < 10 OR style = 5 THEN PRINT #nnn, USING "####D"; CINT(PENETRATION);: RETURN
    IF CINT((PENETRATION / 10 - INT(PENETRATION / 10))) < 1 THEN PRINT #nnn, USING "###DD"; INT(PENETRATION / 10);: RETURN
    PRINT #nnn, USING "#DD+#"; INT(PENETRATION / 10); CINT((PENETRATION / 10 - INT(PENETRATION / 10)));

    RETURN




    10789
    10791 pran = pran(I, Q) / HEX: IF pran > 99 THEN pran = 99
    pran = bur(I, Q) / HEX: ep = con(I, Q)
    'ep = CINT(SQR(con(I, Q) * mult)):
    IF wqual$(I, Q) <> "C" THEN ep = 0
    IF ep > EP0 THEN EP0 = ep: FRAG = pran
    IF ep = 0 THEN PRINT #nnn, "Ё          Ё";: GOTO 10792
    PRINT #nnn, "Ё "; wqual$(I, Q);
    PRINT #nnn, USING ":## "; ep;
    PRINT #nnn, USING "### Ё"; pran;
    10792 PRINT #nnn,
    IF Q < weap(I) THEN PRINT #nnn, "цддддддддддддддддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
10800 NEXT Q
IF weap(I) > 0 THEN PRINT #nnn, "юддддддддддддддддаддддддддддаддддддддддаддддддддддаддддддддддадддддддддды"


IF EP0 = 0 GOTO 10802

PRINT #nnn, "здддддддддддддддддддддддддддбддддддддддбддддддддддбддддддддддбдддддддддд©"

EP0 = EP0 / DIV
PRINT #nnn, USING "Ё Conc. Damage up to 10 m##DЁ"; EP0;
IF INT(EP0 / 2) > 0 THEN PRINT #nnn, USING "to 20 m##DЁ"; INT(EP0 / 2); ELSE PRINT #nnn, "          Ё";
IF INT(EP0 / 4) > 0 THEN PRINT #nnn, USING "to 30 m##DЁ"; INT(EP0 / 4); ELSE PRINT #nnn, "          Ё";
IF INT(EP0 / 8) > 0 THEN PRINT #nnn, USING "to 40 m##DЁ"; INT(EP0 / 8); ELSE PRINT #nnn, "          Ё";
IF INT(EP0 / 16) > 0 THEN PRINT #nnn, USING "to 50 m##DЁ"; INT(EP0 / 16); ELSE PRINT #nnn, "          Ё";
PRINT #nnn,
PRINT #nnn, "цдддддддддддддбдддбдддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё Frag:## m 2DЁD10Ё<4 D6 hitЁ<7 1 hit  ЁFr:## m 1DЁ<3 D6 hitsЁ<5 1 hit  Ё"; FRAG; FRAG * 2
PRINT #nnn, "юдддддддддддддадддадддддддддаддддддддддаддддддддддаддддддддддадддддддддды"











10802

t11 = 1
t12 = 10 / DIV
t20 = t12 + 1
t21 = 20 / DIV
t30 = t21 + 1
t31 = 40 / DIV
t40 = t31 + 1
t41 = 60 / DIV

PRINT #nnn, "зддддддддбдддддддддддбдддддддддддбддддддддддддбддддддддддддбдддддддддддд©"
PRINT #nnn, USING "Ё DAMAGE Ё<##   MinorЁ<## 2 MinorЁ<##   MAJOR Ё<## 2 MAJOR Ё>## 3 MAJOR Ё"; t12; t21; t31; t41; t41
PRINT #nnn, "юддддддддадддддддддддадддддддддддаддддддддддддаддддддддддддадддддддддддды"
IF style <> 4 THEN GOTO 10803
hull = CINT(weight(I) * 4 / 5) * 5: space = hull / 2
xc = 5
PRINT #nnn, "здддддддддддб";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "©"



'IF hull > 10 THEN hull = CINT(hull / 5) * 5
PRINT #nnn, "Ё CRITICALS Ё";: FOR x = 1 TO 10: PRINT #nnn, USING "#### Ё"; hull / 10 * x;: NEXT: PRINT #nnn,


PRINT #nnn, "юддддддддддда";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "ы"



GOTO 10803
aa = 7
PRINT #nnn, "здддбддддддддбдддбддддддддддбддддддддддбддддддддддбддддддддддбдддддддддд©"
PRINT #nnn, USING "Ё   ЁLOCATIONЁ   Ё ##  - ## Ё ##  - ## Ё ##  - ## Ё ##  - ## Ё    ##+   Ё"; t11; t12; t20; t21; t30; t31; t40; t41; t41 + 1
PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 1;: PRINT #nnn, LOCATION$(1); SPC(aa - LEN(LOCATION$(1))); "Ё 1 Ё No EffectЁ  MINOR   Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё"
'PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 2;: PRINT #nnn, LOCATION$(2); SPC(aa - LEN(LOCATION$(2))); "Ё 2 Ё No EffectЁ  MINOR   Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё"
'PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 3;: PRINT #nnn, LOCATION$(3); SPC(aa - LEN(LOCATION$(3))); "Ё 3 Ё  MINOR   Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё  X X X   Ё"
'PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 4;: PRINT #nnn, LOCATION$(4); SPC(aa - LEN(LOCATION$(4))); "Ё 4 Ё  MINOR   Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё  X X X   Ё"
'PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 5;: PRINT #nnn, LOCATION$(5); SPC(aa - LEN(LOCATION$(5))); "Ё 5 Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё  X X X   Ё  X X X   Ё"
'PRINT #nnn, "цдддеддддддддедддеддддддддддеддддддддддеддддддддддеддддддддддедддддддддд╢"
PRINT #nnn, USING "Ё## Ё "; 6;: PRINT #nnn, LOCATION$(6); SPC(aa - LEN(LOCATION$(6))); "Ё 6 Ё 2 MINOR  Ё  MAJOR   Ё 2 MAJOR  Ё  X X X   Ё  X X X   Ё"
PRINT #nnn, "юдддаддддддддадддаддддддддддаддддддддддаддддддддддаддддддддддадддддддддды"


10803





GOSUB 4000
tfm = CINT(tf(I) / DIV)
tsm = ts(I) / DIV
trm = tr(I) / DIV

hfm = CINT(hf(I) / DIV)
hsm = hs(I) / DIV
hrm = hr(I) / DIV

t11 = 1
t12 = 10 / DIV
t20 = t12 + 1
t21 = 20 / DIV
t30 = t21 + 1
t31 = 40 / DIV
t40 = t31 + 1
t41 = 60 / DIV


h1$ = "Body" + STR$(0 + hfm) + "+": h2$ = "MAJOR" + STR$(t30 + hfm) + "+"
t1$ = "": t2$ = ""
h1$ = "Minor Body": h2$ = "MAJOR Body"
t1$ = "": t2$ = ""

aa = 6
xc = 15
IF loca$(I) <> "VEH" THEN t1$ = "Turret" + STR$(0 + tfm) + "+": t2$ = "MAJOR" + STR$(t30 + tfm) + "+"
IF loca$(I) <> "VEH" THEN t1$ = "Minor Turret": t2$ = "MAJOR Turret"

PRINT #nnn, "здбддддддб";
FOR f = 1 TO xc - 1: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "©"


PRINT #nnn, "Ё ЁHITLOCЁ "; h1$; SPC(xc - 2 - LEN(h1$));
PRINT #nnn, "Ё "; h2$; SPC(xc - 1 - LEN(h2$));
PRINT #nnn, "Ё "; t1$; SPC(xc - 1 - LEN(t1$));
PRINT #nnn, "Ё "; t2$; SPC(xc - 1 - LEN(t2$)); "Ё"
PRINT #nnn, "цдедддддде";
FOR f = 1 TO xc - 1: PRINT #nnn, "д";: NEXT: PRINT #nnn, "е";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "е";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "е";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "╢"


FOR j = 1 TO 6

    PRINT #nnn, USING "Ё#Ё"; j;
    PRINT #nnn, LOCATION$(j); SPC(aa - LEN(LOCATION$(j))); "Ё ";
    PRINT #nnn, minh$(j); SPC(xc - 2 - LEN(minh$(j)));
    PRINT #nnn, "Ё "; majh$(j); SPC(xc - 1 - LEN(majh$(j)));
    PRINT #nnn, "Ё "; mint$(j); SPC(xc - 1 - LEN(mint$(j)));
    PRINT #nnn, "Ё "; majt$(j); SPC(xc - 1 - LEN(majt$(j))); "Ё"
NEXT

PRINT #nnn, "юдадддддда";
FOR f = 1 TO xc - 1: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "ы"



text$ = ""

text$ = "Range" + STR$(INT(trmov(I) * fcap(I) / fcons(I))) + " /" + STR$(INT(ccmov(I) * fcap(I) / fcons(I))) + " km."
IF fuel$(I) <> "" THEN text$ = text$ + " Runs on " + fuel$(I) + "."
IF weight(I) = 1 AND load(I) = 2 GOTO 7001
text$ = text$ + " Weight:" + STR$(weight(I)) + " t."
IF load(I) > 0 THEN text$ = text$ + " Load:" + STR$(load(I)) + " t."
7001 text$ = text$ + " Crew:" + STR$(crew(I)) + "."
IF pass(I) > 0 THEN text$ = text$ + " Passenger:" + STR$(pass(I)) + "."
text$ = text$ + " Maintenance:" + STR$(mnt(I)) + "."
IF stab$(I) <> "" THEN text$ = text$ + " " + stab$(I) + " Stabilization."
IF night$(I) <> "" THEN text$ = text$ + " Night Vision : " + night$(I) + "."
IF rad$(I) <> "4" THEN text$ = text$ + " Radiation " + rad$(I) + "."
text$ = text$ + " "
GOSUB 19999

IF LEN(x8$(I)) > 5 THEN text$ = x8$(I): GOSUB 19999



GOTO 7100

IF style <> 4 THEN GOTO 7100
xc = 5
PRINT #nnn, "здддддддддддб";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "б";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "©"



'IF hull > 10 THEN hull = CINT(hull / 5) * 5
PRINT #nnn, USING "ЁSpaces:####Ё"; space;: FOR x = 1 TO 10: PRINT #nnn, USING "#### Ё"; hull / 10 * x;: NEXT: PRINT #nnn,


PRINT #nnn, "юддддддддддда";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "а";
FOR f = 1 TO xc: PRINT #nnn, "д";: NEXT: PRINT #nnn, "ы"


7100 CLOSE #nnn,

GOSUB 1000: CLS
RUN


102000 REM Panzerdarstellung
tfm = tf(I) / DIV: ttx = tfm: GOSUB 9001: tfm = ttz: IF ttz <= .3 THEN tfm = 1
tsm = ts(I) / DIV: ttx = tsm: GOSUB 9001: tsm = ttz: IF ttz <= .3 THEN tsm = 1
trm = tr(I) / DIV: ttx = trm: GOSUB 9001: trm = ttz: IF ttz <= .3 THEN trm = 1
hfm = hf(I) / DIV: ttx = hfm: GOSUB 9001: hfm = ttz: IF ttz <= .3 THEN hfm = 1
hsm = hs(I) / DIV: ttx = hsm: GOSUB 9001: hsm = ttz: IF ttz <= .3 THEN hsm = 1
hrm = hr(I) / DIV: ttx = hrm: GOSUB 9001: hrm = ttz: IF ttz <= .3 THEN hrm = 1
dfm = deck(I) / DIV: IF dfm > 99 THEN dfm = 99
bfm = belly(I) / DIV: IF bfm > 99 THEN bfm = 99



IF tfm = 0 GOTO 102900
IF loca$(I) = "CIH" GOTO 102810
IF loca$(I) = "VEH" GOTO 102900

crx = 52 - LEN(cr$)
xz = 41

102002

PRINT #nnn, "        в        "; pp$
PRINT #nnn, "        ╨        "
PRINT #nnn, "        ╨        "
PRINT #nnn, "        ╨        "
PRINT #nnn, " зддмдддвдддмдд© ";: GOSUB 102851
PRINT #nnn, USING "зы     ###     ю©"; hfm;: GOSUB 102852
PRINT #nnn, "цддбммммпммммбдд╢";: GOSUB 102853
PRINT #nnn, USING "Ё  гдд©###здд╤  Ё"; tfm;: GOSUB 102854
PRINT #nnn, "Ё  ╨  цддд╢  ╨  Ё";: GOSUB 102855
PRINT #nnn, USING "Ё  ╨##Ё   Ё##╨  Ё"; tsm; tsm
PRINT #nnn, "Ё  ╨  Ё   Ё  ╨  Ё"
PRINT #nnn, USING "Ё  ╨  Ё ##Ё  ╨  Ё"; trm
PRINT #nnn, USING "Ё##цммомммомм╢##Ё"; hsm; hsm
PRINT #nnn, "Ё  Ё м м м м Ё  Ё"
PRINT #nnn, "Ё  Ё м м м м Ё  Ё"
PRINT #nnn, "Ё  Ё м м м м Ё  Ё"
PRINT #nnn, USING "Ё##Ё м м м м Ё##Ё"; RGEAR; RGEAR;
PRINT #nnn, SPC(crx); "з";: FOR f = 1 TO LEN(cr$) + 2: PRINT #nnn, "д";: NEXT: PRINT #nnn, "©"
PRINT #nnn, USING "ю© Ё м м## м Ё зы"; hrm;
PRINT #nnn, SPC(crx); "Ё "; cr$; " Ё"
PRINT #nnn, " юдадддддддддады ";
PRINT #nnn, SPC(crx); "ю";: FOR f = 1 TO LEN(cr$) + 2: PRINT #nnn, "д";: NEXT: PRINT #nnn, "ы"
RETURN

102850
102851 PRINT #nnn, SPC(xz); "зддддддбдддддд©": RETURN
102852 PRINT #nnn, SPC(xz); USING "Ё####kmЁ####kmЁ"; road; country: RETURN
102853 PRINT #nnn, SPC(xz); "цддддддедддддд╢": RETURN
102854 PRINT #nnn, SPC(xz); USING "Ё  ##  Ё  ##  Ё"; roadHEX; countryhex: RETURN
102855 PRINT #nnn, SPC(xz); "юддддддадддддды": RETURN


102810
crx = 52 - LEN(cr$)
xz = 41

PRINT #nnn, "        Ё"; pp$
PRINT #nnn, "        Ё"
PRINT #nnn, " зддмдддвдддмдд© ";: GOSUB 102851
PRINT #nnn, USING "зы    ###      ю©"; hfm;: GOSUB 102852
PRINT #nnn, "цддбддддпддддбдд╢";: GOSUB 102853
PRINT #nnn, USING "Ё  цдд©## здд╢  Ё"; tfm;: GOSUB 102854
PRINT #nnn, "Ё  Ё  цддд╢  Ё  Ё";: GOSUB 102855
PRINT #nnn, USING "Ё  Ё##Ё   Ё##Ё  Ё"; tsm; tsm
PRINT #nnn, USING "Ё##Ё  Ё## Ё  Ё##Ё"; hsm; trm; hsm
PRINT #nnn, "Ё  Ё  Ё   Ё  Ё  Ё"
PRINT #nnn, "Ё  цддадбдадд╢  Ё"
PRINT #nnn, "Ё  Ё    Ё    Ё  Ё"
PRINT #nnn, "Ё  Ё    Ё    Ё  Ё"
PRINT #nnn, "Ё  Ё    Ё    Ё  Ё"
PRINT #nnn, "Ё  Ё    Ё    Ё  Ё"
PRINT #nnn, USING "Ё  Ё   ##    Ё  Ё"; hrm;
PRINT #nnn, SPC(crx); "з";: FOR f = 1 TO LEN(cr$) + 2: PRINT #nnn, "д";: NEXT: PRINT #nnn, "©"
PRINT #nnn, USING "ю©#Ё##  Ё  ##Ё#зы"; RGEAR; dfm; bfm; RGEAR;
PRINT #nnn, SPC(crx); "Ё "; cr$; " Ё"
PRINT #nnn, " юдаддддаддддады ";
PRINT #nnn, SPC(crx); "ю";: FOR f = 1 TO LEN(cr$) + 2: PRINT #nnn, "д";: NEXT: PRINT #nnn, "ы"
RETURN

102900 xz = 45
PRINT #nnn, " зддддддддд© "; pp$
PRINT #nnn, USING "зы  ###    ю©"; hfm;: GOSUB 102851
PRINT #nnn, "цдббдддддббд╢";: GOSUB 102852
PRINT #nnn, "Ё ЁюдддддыЁ Ё";: GOSUB 102853
PRINT #nnn, "Ё Ё       Ё Ё";: GOSUB 102854
PRINT #nnn, "Ё Ё       Ё Ё";: GOSUB 102855
PRINT #nnn, USING "Ё#цдддбддд╢#Ё"; hsm; hsm
PRINT #nnn, "Ё Ё   Ё   Ё Ё"
PRINT #nnn, "Ё Ё   Ё   Ё Ё"
PRINT #nnn, USING "Ё Ё   #   Ё Ё"; hrm
PRINT #nnn, "ю©цдддаддд╢зы"
PRINT #nnn, " юадддддддаы"
RETURN








GOSUB 1000
RETURN
4000 REM Location
IF loca$(I) <> "TUR" THEN GOTO 4100
LOCATION$(1) = mv$
LOCATION$(2) = "Body"
LOCATION$(3) = "Body"
LOCATION$(4) = "Body"
LOCATION$(5) = "Turret"
LOCATION$(6) = "Turret"


minh$(1) = "Driver"
minh$(2) = "Loader": IF crew(I) < 4 THEN minh$(2) = "Autoloader"
minh$(3) = "2 Troops": IF pass(I) = 0 THEN minh$(3) = "Gunner"
minh$(4) = "2 Troops": IF pass(I) = 0 THEN minh$(4) = "Commander"
minh$(5) = "Radio"
minh$(6) = "Major Body"

mint$(1) = "Commander"
mint$(2) = "Loader": IF crew(I) < 4 THEN mint$(2) = "Autoloader"
mint$(3) = "Sight Vision"
mint$(4) = "Traverse"
mint$(5) = LEFT$(wtyp$(I, weap(I)), wlen)
mint$(6) = "Major Turret"

majh$(1) = "Engine"
majh$(2) = "Engine"
majh$(3) = "Fuel"
majh$(4) = "Fuel"
majh$(5) = "Ammo"
majh$(6) = "Ammo"

majt$(1) = "Ldr/Cmdr"
majt$(2) = "Gnr/Cmdr"
majt$(3) = LEFT$(wtyp$(I, 1), wlen)
majt$(4) = LEFT$(wtyp$(I, 1), wlen)
majt$(5) = "Ammo"
majt$(6) = "Minor Body"
RETURN

4100 REM CIH
IF loca$(I) <> "CIH" GOTO 4200
LOCATION$(1) = mv$
LOCATION$(2) = "Body"
LOCATION$(3) = "Body"
LOCATION$(4) = "Body"
LOCATION$(5) = "Body"
LOCATION$(6) = "Turret"




minh$(1) = "Driver"
minh$(2) = "Loader": IF crew(I) < 4 THEN minh$(2) = "Autoloader"
minh$(3) = "2 Troops": IF pass(I) = 0 THEN minh$(3) = "Crewmember"
minh$(4) = "2 Troops": IF pass(I) = 0 THEN minh$(4) = "Crewmember"
minh$(5) = "Radio"
minh$(6) = "Major Body"

mint$(1) = "Loader": IF crew(I) < 4 THEN mint$(1) = "Autoloader"
mint$(2) = "Sight/Vision"
mint$(3) = "Sight Vision"
mint$(4) = "Traverse"
mint$(5) = LEFT$(wtyp$(I, weap(I)), wlen)
mint$(6) = "Major Turret"

majh$(1) = "Engine"
majh$(2) = "Engine"
majh$(3) = "Fuel"
majh$(4) = "Fuel"
majh$(5) = "Ammo"
majh$(6) = "Ammo"

majt$(1) = LEFT$(wtyp$(I, 1), wlen)
majt$(2) = LEFT$(wtyp$(I, 1), wlen)
majt$(3) = LEFT$(wtyp$(I, 1), wlen)
majt$(4) = LEFT$(wtyp$(I, 1), wlen)
majt$(5) = "Major Body"
majt$(6) = "Minor Body"
RETURN

4200 REM Vehicle
LOCATION$(1) = mv$
LOCATION$(2) = "Body"
LOCATION$(3) = "Body"
LOCATION$(4) = "Body"
LOCATION$(5) = "Body"
LOCATION$(6) = "Miss"



minh$(1) = "Driver"
minh$(2) = "Gunner"
minh$(3) = "2 Troops": IF pass(I) = 0 THEN minh$(3) = "Loader"
minh$(4) = "2 Troops": IF pass(I) = 0 THEN minh$(4) = "Commander"
minh$(5) = "Radio"
minh$(6) = "Major Body"

mint$(1) = ""
mint$(2) = ""
mint$(3) = "     No"
mint$(4) = "   Turret"
mint$(5) = ""
mint$(6) = ""

majh$(1) = "Engine"
majh$(2) = "Engine"
majh$(3) = "Fuel"
majh$(4) = "Fuel"
majh$(5) = "Ammunition"
majh$(6) = LEFT$(wtyp$(I, 1), wlen)

majt$(1) = ""
majt$(2) = ""
majt$(3) = "     No"
majt$(4) = "   Turret"
majt$(5) = ""
majt$(6) = ""
RETURN


'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)


10000 '2300

DATA "M107 SPA","SPA","US",95,50,700,180,"T4"
DATA 1,1,1,8,3,3
DATA 2
DATA "175 mm HEAT","C",.333,400
DATA 110,110,110,110,3
DATA 24,30,0

DATA "175 mm HE","C",.333,400
DATA 3,3,3,3,3
DATA 34,40,0


DATA 30,.8,6,0,10,375000,1,0,0
DATA "Basic","D,A","Passive IR/thermal, searchlight","Shielded","5","6","7"
DATA "Indirect Firing Range: 24 km. The M107 is an earlier variation on the M110, using a 175mm howitzer. It is no longer in service with the US Army, but it remains in the arsenals of many other armies. Like the M110, the gun system is mounted externally on the chassis, and (unlike the M109) there is no protection forthe gun crew (except for the driver, who rides inside) or for the ammunition. To remedy this (at least for the crew), a kit consisting of a tubular metal framework and Kevlar shields was issued, but most crews found these kits too cumbersome to erect. They were usually discarded or left with the supply units. The turret armor rating is with these shields in place; without them, the armor is 0. No provision is made for a weapons mount."
DATA "TUR"

DATA "M110 SPA","SPA","US",95,50,704,180,"T4"
DATA 1,1,1,10,3,3
DATA 1
DATA "203 mm HEAT","C",.333,400
DATA 4,4,4,4,2
DATA 36,44,0

DATA 31,.5,4,3,10,375000,1,0,0
DATA "Basic","D,A","Passive IR/thermal, searchlight","Shielded","5","6","7"
DATA "Indirect Firing Range: 24 km. The gun system is mounted externally on the chassis, and (unlike the M109) there is no protection forthe gun crew (except for the driver, who rides inside) or for the ammunition. To remedy this (at least for the crew), a kit consisting of a tubular metal framework and Kevlar shields was issued, but most crews found these kits too cumbersome to erect. They were usually discarded or left with the supply units. The turret armor rating is with these shields in place; without them, the armor is 0. No provision is made for a weapons mount."
DATA "TUR"





DATA "Centurion Mk.I","MBT","GB",60,32,1400,280,"T6"
DATA 31,8,8,30,8,8
DATA 3
DATA "17 pdr","C",.5,250
DATA 37,36,34,30,50,6,0,0
DATA "Polsten 20mm","x",10,125,6,4,2,1,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 52.6,.6,4,0,10,350000,1,0,0
DATA "Basic","D,A","Passive IR/thermal, searchlight","Shielded","5","6","7","8","TUR"
'the uparmoured Centurion Mark II soon arrived; it had a new 118 mm-thick glacis and the side and rear armour had been increased from 38 mm to 51 mm

'Production: 1953√60
'Vehicles produced: 775
'Combat weight: 51.62 tonnes
'Crew: four (commander, gunner, loader/radio operator, driver)
'dimensions
'Hull length / overall: 7.82m / 9.85m
'Width (without aprons / with aprons): 3.28m / 3.39m Height: 3.02m Ground clearance: 0.51m
'armour (degrees from vertical)
'Glacis (upper / lower): 76mm @ 57 degrees / 76mm @ 45 degrees
'Hull side: 51mm @ 12 degrees Hull rear (upper / lower): 32mm @ 7 degrees / 19mm @ 62 degrees
'Hull roof (forward / main / rear): 29mm @ 80 degrees / 29mm @ 90 degrees / 10mm @ 90 degrees
'Hull bottom: 17mm @ 90 degrees
'Turret face: 152mm @ 0 degrees
'Turret mantlet: 152mm curved
'Turret side (starboard / port upper / port lower): 89mm @ 0degrees / 51mm @ 60 degrees / 89mm @ 10 degrees
'Turret rear (upper / lower): 51mm curved / 89mm @ 0 degrees
'Turret roof (forward / main): 51mm @ 73 degrees / 29mm @ 90 degrees
'Cupola side: 90mm @ 0 degrees Skirting plate: 6mm @ 0 degrees
'armament
'Main gun: QF 20-pdr (83.8mm) L/67 (64 rounds, typically 50 per cent AP and 50 per cent HE)
'Elevation / depression: 20 degrees / 10 degrees
'Sight: Mk 1 or Mk 1/1 periscopic (6в)
'Secondary: One 303in Browning M1919 A4 MG coaxial (3,600 rounds)
'Main gun rate of fire: 4√8rds/min
'Turret rotation (360 degrees): 25 seconds @ 3,000 engine rpm
'Communications
'I'nternal: Intercom (incorporated in No. 19 WT)
'External: No. 19 WT and No. 38 AFV radios
'motive power
'Engine: Rolls-Royce Meteor Mk IVB (or Mk IVB/1) 12-cylinder
'(liquid-cooled) 60-degree vee of 27l (above 80-octane petrol)
'Power/weight (net): 635bhp (474kW) (sustained) @ 2,550rpm (9.32kW/tonne)
'Transmission: Merritt-Brown Z51R (five forward, two reverse)
'Performance
'Ground pressure: 0.928kg/cm╡
'Maximum speed (road): 34.6km/h
'Operational range (road/ cross country): 190km / 96km
'Fuel consumption (road / cross country): 5.45l/km / 10.80l/km
'Fording: 1.45m
'Step climbing: 0.91m
'Climbing, degrees: 35 degrees
'Trench crossing: 3.35m

DATA "Centurion Mk.VII","MBT","GB",62.50,40,850,280,"T6"
DATA 30,40,20,30,10,10
DATA 2
DATA "QF 20-pdr L/67","P",.5,250
DATA 44,40,34,28,50,8,0,64



DATA "M1919 A4 MG","x",10,125,2,2,1,0,999,.4,2,3600
DATA 51.62,.6,4,0,10,350000,1,0,0
DATA "Basic","G,A","Searchlight","Shielded","5","6","7","8","TUR"
'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)



DATA "AC-8 (Aero-Char, 8ton)","HVT","X",2356,570,55500,1850,"Grav"
DATA 80,30,30,80,30,30
DATA 2
DATA "8 cm Mass Driver","X",5,1980
DATA 397,397,198,40,200,158,35,1980
DATA "25 mm Autocannon","x",50,300,6,6,2,1,120000,.4,2,300
DATA 0,0,0,0,0,0,0,252,252
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"


DATA "PzKw IV-H","MBT","DR",65,45,730,450,"T6"
DATA 10,6,6,16,6,4
DATA 1
DATA "7,5L/48 APCR","X",1,250
DATA 36,34,30,26
DATA 50,6,0,0
DATA 0,0,0,0,0,0,0,3,3
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"



DATA "PzKw V Panther","MBT","DR",100,65,730,450,"T6"
DATA 22,13.5,13.5,32,8,12
DATA 2
DATA "7,5cm/70 APCR","X",.5,500
DATA 50,47,40,29,50,6,0,0
DATA "7,5cm/70 APCBC","X",.5,250
DATA 37,36,34,30,50,6,0,0
DATA 0,0,0,0,0,0,0,3,7
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"






'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)

DATA "PzKw VI Tiger","MBT","DR",65,35,860,600,"T6"
DATA 20,16,16,22,16,16
DATA 2
DATA "8,8L/56 PzGr.39","X",.5,500
DATA 32,30,25,22,50,8,0,0
DATA "8,8L/56 PzGr.40","X",.5,500
DATA 44,40,34,28,50,8,0,0
DATA 69.8,2,5,0,25,0,0,8.1,8.1
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"


DATA "PzKw VIb K■nigstiger","MBT","DR",65,35,860,600,"T6"
DATA 36,24,24,45,24,24
DATA 2
DATA "8,8L/71 PzGr.40","X",.5,500
DATA 61,56,51,42,50,8,0,0
DATA "8,8L/71 PzGr.39","X",.5,500
DATA 46,44,41,36,50,8,0,0
DATA 69.8,2,5,0,25,0,0,8.1,8.1
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

'DATA "8,8L/56 PzGr.39","X",.5,500
'DATA 32,30,25,22,50,8,0,0
'
'DATA "8,8L/56 PzGr.40","X",.5,500
'DATA 44,40,34,28,50,8,0,0

'DATA "8,8L/71 PzGr.40","X",.5,500
'DATA 61,56,51,42,50,8,0,0

'DATA "8,8L/71 PzGr.39","X",.5,500
'DATA 46,44,41,36,50,8,0,0
'



DATA "T-34-85","MBT","SU",110,90,590,130,"T4"
DATA 15,12,12,12,08,06
DATA 3
DATA "85 mm APCR","C",.5,250
DATA 35,32,20,11,56,4,10,250
DATA "85 mm APBC","C",.5,250
DATA 28,26,21,16,56,4,10,250
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 33,.5,4,0,5,100000,0,0,0
DATA "","D,A","Active IR","4","5","6","7","8","TUR"

'DATA "85 mm AP","C",.5,250
'DATA 28,25,70,16,56,4,10,250

'DATA "85 mm APBC","C",.5,250
'DATA 28,26,21,16,56,4,10,250

'DATA "85 mm APCR","C",.5,250
'DATA 35,32,20,11,56,4,10,250



'DATA "XXX",",MBT","US",0,0,0,0,"T6"

8000 'TNE
DATA "Heavy Grav Tank","GRT","X",2356,570,55500,1850,"Grav"
DATA 336,168,168,336,168,168
DATA 2
DATA "175 Mj RPZ-15","C",5,1980,397,397,198,40,200,158,35,1980
DATA "VRF 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 0,0,0,0,0,0,0,252,252
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Trepida I Grav Tank","GRT","X",2140,534,19923,1083,"Grav"
DATA 258,129,129,258,129,129
DATA 2
DATA "74 Mj RPX-14","C",5,1290,258,258,129,26,410,67,25,1290
DATA "VRF 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 0,0,0,0,0,0,0,129,129
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Trepida II Grav Tank","GRT","X",2136,534,16891,1083,"Grav"
DATA 258,129,129,258,129,129
DATA 2
DATA "125 Mj RPY-14","C",4,1680,335,335,168,34,200,112,35,1680
DATA "VR 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 0,0,0,0,0,0,0,129,129
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Intrepid-120 Grav Tank","GRT","X",2168,504,19923,1083,"Grav"
DATA 258,129,129,258,129,129
DATA 2
DATA "120mm/75 ETC","C",3,780,545,535,525,505,520,29,35,580
DATA "15mmRC/E","x",10,300,8,8,8,8,5000,.4,2,300
DATA 0,0,0,0,0,0,0,129,129
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Pyrrhus Support Sled","ISS","X",6000,480,0,0,"Grav"
DATA 60,8,4,60,8,4
DATA 2
DATA "12 Mj Plasma","C",1,350,104,104,52,10,100,10,20,350
DATA "7.5 mm LMG","x",10,300,4,4,2,2,999999,.4,2,300
DATA 0,0,0,0,0,0,0,8,4
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Oriflamme Assault Sled","ISS","X",6300,360,0,0,"Grav"
DATA 84,30,30,84,30,30
DATA 1
'ATA "12 Mj Plasma","C",1,350 ,104,104, 52,10,100,10 ,20,350
DATA "15 mm HMG","x",50,300,8,8,8,8,999999,.4,2,300
DATA 0,0,0,0,0,0,0,30,38
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Oriflamme","APC","X",6300,360,0,0,"Grav"
DATA 60,30,30,60,30,30
DATA 1
'ATA "12 Mj Plasma","C",1,350 ,104,104, 52,10,100,10 ,20,350
DATA "15 mm HMG","x",50,300,8,8,8,8,999999,.4,2,300
DATA 0,0,0,0,0,0,0,30,38
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Oriflamme Cavalry Vehicle","ISS","X",5880,360,0,0,"Grav"
DATA 48,33,24,48,33,24
DATA 2
DATA "7 cmL75","C",3,740,225,215,205,185,50,9,30,550
DATA "15 mm HMG","x",50,300,8,8,8,8,999999,.4,2,300
DATA 0,0,0,0,0,0,0,24,34
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Oriflamme Grav Tank","GRT","X",4860,360,0,0,"Grav"
DATA 204,72,42,204,72,42
DATA 2
DATA "7 cmL75","C",3,740,225,215,205,185,200,9,30,550
DATA "15 mm HMG","x",50,300,8,8,8,8,999999,.4,2,300
DATA 0,0,0,0,0,0,0,42,57
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Oriflamme","GTD","X",4920,360,0,0,"Grav"
DATA 204,42,42,204,42,72
DATA 2
DATA "12cmL75","C",3,780,545,535,525,505,75,30,40,580
DATA "15 mm HMG","x",50,300,8,8,8,8,999999,.4,2,300
DATA 0,0,0,0,0,0,0,42,50
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Mongoose","SPD","X",6660,440,0,0,"Grav"
DATA 21,16,11,21,16,11
DATA 2
DATA "4.75 Mj Fusion","C",1,220,65,65,33,7,75,4,10,220
DATA "Thunderbyrd","R",1,36000,281,281,281,281,4,81,100,36000
DATA 0,0,0,0,0,0,0,11,11
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Ferret","SPD","X",6660,440,0,0,"Grav"
DATA 21,16,11,21,16,11
DATA 2
DATA "14 Mj Fusion","C",1,370,112,112,56,11,75,10,20,370
DATA "Thunderbyrd","R",1,36000,281,281,281,281,2,81,100,36000
DATA 0,0,0,0,0,0,0,11,11
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Norris Grav Tank","GRT","X",2352,570,19489,1083,"Grav"
DATA 258,129,129,258,129,129
DATA 2
DATA "175 Mj RPZ-15","C",5,1980,397,397,198,40,105,158,35,1980
DATA "VRF 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 0,0,0,0,0,0,0,129,129
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Astrin Grav APC","APC","X",2600,540,20528,733,"Grav"
DATA 258,129,129,258,129,129
DATA 2
DATA "3 Mj RPV-14","C",5,260,52,52,26,5,500,3,5,260
DATA "VRF 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 130,0,2,10,0,0,0,129,129
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"


DATA "Imperial Marine Grav APC","APC","X",3276,570,16783,1083,"Grav"
DATA 252,140,126,252,140,126
DATA 2
DATA "175 Mj RPZ-15","C",3,650
DATA 129,129,65,13,500
DATA 17,15,650
DATA "VRF 4x20 mm/60 Dart","x",50,300,6,6,2,1,120000,.4,2,300
DATA 130,0,2,10,0,0,0,126,140
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)


DATA "Abomination","TLT","XX",110,85,2500,1,"T60"
DATA 288,192,120,288,192,120
DATA 1
DATA "120mm/20 6-barrel AC","C",10,280
DATA 137,137,137,137,1200
DATA 29,35,400
DATA 1291,.6,4,10,113,6460000,2,192,120
DATA "Advanced","Fission","30 km HRT","Pressurized","5","6","7","8","TUR"



DATA "Prairie Fire","TLT","XX",280,215,28500,2724,"T24"
DATA 192,48,24,192,48,24
DATA 2
DATA "130mm/60 HV Gun","C",.2,670
DATA 207,197,187,167,100
DATA 30,35,510
DATA "7 mm Rotary","x",50,270,3,3,2,0,2500,1,9,270
'DATA "MAG MG","x",10,125,2 ,2,1,0,999,.4,2,125
DATA 247,0,3,0,67,866875,2,36,24
DATA "Advanced","L-Hyd","3 km HRT","Overpressure","5","6","7","8","TUR"

DATA "LRV-51 Pandina","LCV","XX",130,85,890,190,"T8"
DATA 9,4,3,9,4,3
DATA 2
DATA "30mm/70 Gun","C",10,470,23,20,17,11,140,1,5,350
DATA "7 mm LMG","x",10,150,2,2,0,0,1000,1,9,150
'DATA "MAG MG","x",10,125,2 ,2,1,0,999,.4,2,125
DATA 35,0,3,0,12,66648,0,3,3
DATA "Basic","L-Hyd","30km Radio","Overpressure","5","6","7","8","TUR"

'DATA "XXX",",MBT","US",0,0,0,0,"T6"

















9000

DATA "M1 - Abrams","MBT","US",150,130,1900,1100,"T6"
DATA 80,40,16,160,16,16
DATA 3
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,55,6,15,400
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 54,.7,4,0,14,600000,2,0,0
DATA "Good","D,G,AvG,A","Passive IR/thermal","Shielded","5","6","7"
DATA "A tracked main battle tank with a large turret There is a driver's hatch in the center of the front deck, and a commander's and loader's hatch on the turret deck. The tank's gunner uses the commander's hatch. A weapons mount is located by each of the commander's and loader's hatches. Supplanted in regular service by the M1A1 and M1A2, the M1 remains in service with national guard units."
DATA "TUR"

DATA "M1A1 - Abrams","MBT","US",130,110,1900,1200,"T6"
DATA 120,40,16,200,16,16
DATA 3
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,40,10,25,400
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 63,.7,4,0,14,650000,2,0,0
DATA "Good","D,G,AvG,A","Passive IR/thermal","Shielded","5","6","7"
DATA "An extensively improved version of the basic M1. The most significant changes are the substitution of a 120mm smoothbore gun for the rifled 105mm gun of the M1, and the use of depleted uranium armor inserts to increase the armor protection on the hull and turret front. Due to the nature of the M1 turret, a turret (but not hull) hitwhich results in an ammunition explosion (see page 219) does not automatically kill the crew and destroy the vehicle. Instead, consider ail armament, sensors, and electronics to be damaged and inoperative. Then apply 50 points of concussion damage to the commander, gunner, and loader."
DATA "TUR"


DATA "M1A2 - Abrams","MBT","US",130,110,1900,600,"T6"
DATA 120,40,20,200,16,16
DATA 3
DATA "120 mm Smth","C",.5,600,150,140,130,110,40,10,25,400
DATA "MAG MG","x",10,125,2,2,1,0,11400,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,1000,1,9,150
DATA 63,.7,4,0,16,700000,2,0,0
DATA "Good","D,G,AvG,A","Passive IR/thermal","Shielded","5","6","7"
DATA "An extensively improved version of the basic M1. The most significant changes are the substitution of a 120mm smoothbore gun for the rifled 105mm gun of the M1, and the use of depleted uranium armor inserts to increase the armor protection on the hull and turret front. Due to the nature of the M1 turret, a turret (but not hull) hitwhich results in an ammunition explosion (see page 219) does not automatically kill the crew and destroy the vehicle. Instead, consider ail armament, sensors, and electronics to be damaged and inoperative. Then apply 50 points of concussion damage to the commander, gunner, and loader."
DATA "TUR"

DATA "M1A2E1 - Abrams","MBT","US",140,110,1900,600,"T6"
DATA 120,40,20,300,16,16
DATA 5

DATA "120 mm APFDSDDU","P",.5,500,150,140,130,110,40,10,25,400
DATA "120 mm APFDSD","P",.5,500,110,100,090,070,40,10,25,400
DATA "120 mm HEAT","C",.5,600,110,110,110,110,40,10,25,400

DATA "MAG MG","x",10,125,2,2,1,0,11400,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,1000,1,9,150
DATA 63,.7,4,0,16,700000,2,0,0
DATA "Good","D,G,AvG,A","Passive IR/thermal","Shielded","5","6","7"
DATA "An extensively improved version of the basic M1. The most significant changes are the substitution of a 120mm smoothbore gun for the rifled 105mm gun of the M1, and the use of depleted uranium armor inserts to increase the armor protection on the hull and turret front. Due to the nature of the M1 turret, a turret (but not hull) hitwhich results in an ammunition explosion (see page 219) does not automatically kill the crew and destroy the vehicle. Instead, consider ail armament, sensors, and electronics to be damaged and inoperative. Then apply 50 points of concussion damage to the commander, gunner, and loader."
DATA "TUR"


DATA "M4A3E8","MBT","US",85,70,700,180,"T5"
DATA 16,12,8,12,8,6
DATA 3
DATA "76 mm HVAP","C",1,300,12,6,6,3,71,6,12,300
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 33,.5,5,0,6,90000,0,0,0
DATA "","G,A","Headlights","4","5","6","7","8","TUR"

DATA "M26 Pershing","MBT","US",100,80,880,120,"T6"
DATA 26,12,10,40,12,10
DATA 3
DATA "90 mm APDS-T","C",.5,350
DATA 30,25,20,15,71,5,10,350
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 46,.5,5,0,5,95000,1,0,0
DATA "","G,A","Headlights","4","5","6","7","8","TUR"

DATA "M46 Patton","MBT","US",100,80,880,120,"T6"
DATA 26,12,10,40,12,10
DATA 3
DATA "90 mm APDS-T","C",.5,350
DATA 30,25,20,15,71,5,10,350
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 46,.5,5,0,5,95000,1,0,0
DATA "","G,A","Headlights","4","5","6","7","8","TUR"

DATA "M47 Patton","MBT","US",100,80,880,120,"T6"
DATA 26,12,10,40,12,10
DATA 3
DATA "90 mm APFSDS","C",.5,350
DATA 55,50,46,40,71,5,10,350
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 46,.5,5,0,5,95000,1,0,0
DATA "","G,A","Headlights","4","5","6","7","8","TUR"

DATA "M48A3","MBT","US",110,65,1400,280,"T6"
DATA 36,15,15,44,22,22
DATA 2
DATA "90 mm APFSDSDU","C",.5,500
DATA 56,50,41,30,54,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 49,.5,4,0,10,350000,1,0,0
DATA "Basic","D,A","Passive IR, W/Searchlight","Enclosed","5","6","7","8","TUR"


DATA "M48A5","MBT","US",110,65,1400,280,"T6"
DATA 36,15,15,44,22,22
DATA 2
DATA "105 mm APFSDSDU","C",.5,500
DATA 100,90,80,60,54,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 49,.5,4,0,10,350000,1,0,0
DATA "Basic","D,A","Passive IR, W/Searchlight","Enclosed","5","6","7","8","TUR"

DATA "M60A3","MBT","US",110,65,1400,280,"T6"
DATA 50,15,15,50,24,24
DATA 3
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,63,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 52.6,.6,4,0,10,350000,1,0,0
DATA "Basic","D,A","Passive IR/thermal, searchlight","Shielded","5","6","7","8","TUR"



'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)



DATA "Cadillac Gage Stingray","MBT","US",140,110,1920,560,"T6"
DATA 40,20,28,40,20,28
DATA 3
DATA "105 mm APFSDSDU","C",1,500,100,90,80,60,36,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 21,.7,4,0,14,800000,4,0,0
DATA "Good","D,A,AvG,A","Headlights, Passive IR","Shielded","5","6","7","8","TUR"

DATA "M8 AGS - 1","LCV","US",150,130,570,170,"T4"
DATA 6,6,4,4,3,4
DATA 3
DATA "105 mm APFSDSDU","C",1,500,100,90,80,60,30,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,4500,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 38.5,.2,3,0,10,250000,2,0,0
DATA "Good","D,A","Passive IR/thermal","Shielded","5","6","7","R/R","TUR"

DATA "M8 AGS - 2","LCV","US",150,130,570,170,"T4"
DATA 6,6,4,6,6,4
DATA 3
DATA "105 mm APFSDSDU","C",1,500,100,90,80,60,30,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 44.5,.2,3,0,10,250000,2,0,0
DATA "Good","D,A","Passive IR/thermal","Shielded","5","6","7","R/R","TUR"


DATA "M8 AGS - 3","LCV","US",150,130,570,170,"T4"
DATA 16,6,4,20,14,4
DATA 3
DATA "105 mm APFSDSDU","C",1,500,100,90,80,60,30,6,15,400
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 49.5,.2,3,0,10,250000,2,0,0
DATA "Good","D,A","Passive IR/thermal","Shielded","5","6","7","R/R","TUR"

DATA "M2 Bradley","IFV","US",140,110,650,225,"T4"
DATA 10,6,4,8,6,6
DATA 3
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,900,1,2,250
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "TOW","R",1,3500,220,0,0,0,7,12,12,3500
DATA 33,1.5,3,6,8,200000,1,0,0
DATA "Good","D,A","Passive IR/thermal imaging","Shielded","5","6","7","8","CIH"


DATA "M2A2 Bradley","IFV","US",130,110,660,220,"T4"
DATA 12,6,4,14,12,6
DATA 3
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,900,1,3,250
DATA "MAG MG","x",10,125,2,2,1,0,2200,.4,2,125
DATA "TOW","R",1,3500,220,0,0,0,7,12,15,3500
DATA 33,1.5,3,6,8,200000,1,0,0
DATA "Good","D,A","Passive IR/thermal imaging","Shielded","5","6","7","S/R","CIH"

DATA "M2A3 Bradley Hellfire","IFV","US",140,110,650,225,"T4"
DATA 10,6,4,14,12,6
DATA 3
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,900,1,2,250
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "Hellfire","R",1,4500,220,0,0,0,7,12,12,4500
DATA 33,1.5,3,6,8,200000,1,0,0
DATA "Good","D,A","Passive IR/thermal imaging","Shielded","5","6","7","8","CIH"

DATA "M3 Bradley","RCV","US",140,110,650,225,"T4"
DATA 10,6,4,14,12,6
DATA 3
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,300,1,2,250
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "TOW","R",1,3500,220,0,0,0,12,12,12,3500
DATA 33,1.5,3,3,8,200000,1,0,0
DATA "Good","D,A","Passive IR/thermal imaging","Shielded","5","6","7","8","CIH"

DATA "AIFV","IFV","US",130,85,400,100,"T2"
DATA 4,2,2,8,6,4
DATA 1
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,324,1,1,250
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","CIH"


DATA "M113-A3","APC","US",130,85,360,90,"T2"
DATA 0,0,0,6,4,4
DATA 1
DATA "M2HB","x",5,150,4,4,3,3,2000,1,9,150
DATA 11,2,2,11,6,75000,0,0,0
DATA "","D,A","Headlights, Passive IR","Shielded","5","6","7","S/R","VEH"

DATA "M1097 HHV (Heavy Hummer)","LCV","US",215,85,94,31,"W2"
DATA 6,3,3,3,3,3
DATA 1
DATA "Mk-19 HVHEDP","C",5,200,4,4,4,4,150,3,15,200
DATA 10,1.25,3,0,3,20000,0,0,0
DATA "","D,G,A","Headlights","Open","5","6","7","C/S","VEH"
                                                 
DATA "LAV-25","APC","US",195,95,300,90,"W6"
DATA 6,3,3,6,3,3
DATA 2
DATA "25 mm APFSDSDU","C",5,250,13,9,3,3,630,1,3,250
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 12,2,3,6,6,10000,1,0,0
DATA "Basic","D,A","Passive IR","Enclosed","5","6","7","8","CIH"

DATA "LAV-75","LCV","US",160,95,520,130,"T2"
DATA 16,4,4,12,3,3
DATA 2
DATA "75 mm APFSDS","C",3,400,30,20,20,10,36,6,12,300
DATA "MAG MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 15,.5,3,0,10,250000,2,0,0
DATA "Good","D,G,A,AvG","Active/Passive IR","Enclosed","5","6","7","8","CIH"


DATA "M109 A2-A3","SPG","US",110,70,495,165,"T4"
DATA 4,4,4,10,3,3
DATA 2
'DATA "155 mm HE  ","C",.33,350, 1,1,1,1   , 36,30,45          ,0
DATA "155 mm HEAT","C",.33,350,110,110,110,110,36,30,45,350
DATA "M2HB","x",5,150,4,4,3,3,600,1,9,150
DATA 25,1,6,0,10,300000,0,0,0
DATA "","D,A","Headlights","Shielded","5","6","7","8","TUR"

DATA "Sp└hpanzer Luchs","RCV","D",180,120,320,160,"W3"
DATA 10,06,04,12,06,04
DATA 2
DATA "25 mm AC APFSDSDU","C",5,250,13,9,3,3,0,1,3,250
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","CIH"

DATA "Fuchs APC","IFV","D",215,85,390,205,"W2"
DATA 0,0,0,3,3,3
DATA 1
DATA "MG3 MG","x",10,125,2,2,1,0,1000,.4,2,125
DATA 17,1,2,10,6,120000,7,0,0
DATA "","D,A","Active/Passive IR","Shielded","5","6","7","S/-","VEH"

DATA "Sch│tzenpanzer Marder","IFV","D",140,90,440,110,"T4"
DATA 12,08,08,25,10,05
DATA 3
DATA "25 mm AC APFSDSDU","C",5,250,13,9,3,3,1100,1,3,250
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA "Milan II","R",1,2000,145,0,0,0,3,0,0,0
DATA 29,.6,3,7,10,200000,7,0,0
DATA "Fair","D,A","Passive/Active IR, Searchlight","4","5","6","7","8","CIH"

DATA "TH-301","LCV","D",130,110,650,150,"T3"
DATA 35,20,20,35,25,15
DATA 2
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,0,6,15,400
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"




DATA "Jagdpanzer Kanone","SPG","D",130,80,800,200,"T6"
DATA 20,7,6,20,7,6
DATA 3
DATA "90 mm HEAT","C",.5,350,60,60,60,60,51
DATA 7,15,250
DATA "90 mm HESH","C",.5,200,3,3,3,3,51
DATA 10,5,250
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 23,.5,4,0,6,850000,4,6,6
DATA "No","D,G,AvG,A","Headlights/Passive IR","Shielded","5","6","7","8","TUR"
'The gun of the Kanonenjagdpanzer 4√5 was a Rheinmetall L/40,4, the main types of ammunition being HEAT and HESH, plus HE, smoke and illumination.
'Barrel length: 4,91m
'Weight of shell: 5,74kg HEAT and 7,45kg HESH
'Muzzle velocity: 1145m/s HEAT and 795m/s HESH
'Maximum effective range: 2000m
'300mm RHA penetration HEAT
'Ammunition load: 51


'name$(i), typ$(i), nat$(i), trmov(i), ccmov(i), fcap(i), fcons(i), susp$(i)
'tf(i), ts(i), tr(i), hf(i), hs(i), hr(i)
'weap(i)
'FOR q = 1 TO weap(i)
'READ wtyp$(i, q), wqual$(i, q), rof(i, q), rng(i, q)
'ps(i, q), pm(i, q), pl(i, q), px(i, q), ammo(i, q)
'con(i, q), bur(i, q), pran(i, q)
'NEXT
'weight(i), load(i), crew(i), pass(i), mnt(i), price(i), rf(i), deck(i), belly(i)
'stab$(i), fuel$(i), night$(i), rad$(i), x5$(i), x6$(i), x7$(i), x8$(i), loca$(i)


DATA "Leopard 1A4","MBT","D",130,85,955,200,"T6"
DATA 50,12,12,28,7,5
DATA 2
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,60,6,15,400
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 40,.7,4,0,8,420000,1,4,5
DATA "Full","D,G,A","W/IR Searchlight, Active/Passive IR","Shielded","5","6","7","8","TUR"

DATA "Leopard 2A1","MBT","D",140,110,1200,315,"T6"
DATA 162,24,20,110,24,10
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA "MG3 MG","x",10,125,2,2,1,0,999,.4,2,125
DATA 62.5,.7,4,0,14,650000,2,0,0
DATA "Good","D,G,A","W/IR Searchlight, Active/Passive IR","Shielded","5","6","7","8","TUR"


DATA "Leopard 2A4","MBT","D",140,110,1200,315,"T6"
DATA 258,24,20,142,24,10
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA "MG3 MG","x",10,125,2,2,1,0,4750,.4,2,125
DATA 62.5,.7,4,0,14,650000,2,0,0
DATA "Good","D,G,A","W/IR Searchlight, Active/Passive IR","Shielded","5","6","7","S/R","TUR"


DATA "Leopard 2A5","MBT","D",140,110,1200,315,"T6"
DATA 350,24,20,150,24,10
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA "MG3 MG","x",10,125,2,2,1,0,4750,.4,2,125
DATA 62.5,.7,4,0,14,650000,2,0,0
DATA "Good","D,G,A","W/IR Searchlight, Active/Passive IR","Shielded","5","6","7","S/R","TUR"

DATA "Challenger 2","MBT","GB",130,110,1800,500,"T6"
DATA 120,40,16,200,24,20
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,52,14,25,400
DATA "L7A2 GPMG","x",10,125,2,2,1,0,4000,.4,2,125
DATA 62.5,.5,4,0,16,850000,2,0,0
DATA "Good","D,G,A,AvG","A/P IR, Thermal","Shielded","5","6","7","R/-","TUR"

DATA "FV-4030 Challenger","MBT","GB",110,85,1250,500,"T6"
DATA 100,40,16,160,24,20
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA "L7A2 GPMG","x",10,125,2,2,1,0,999,.4,2,125
DATA 58,.5,4,0,16,850000,2,0,0
DATA "Good","D,G,A,AvG","A/P IR, Thermal","Shielded","5","6","7","8","TUR"

DATA "FV-4201 Chieftain","MBT","GB",100,75,950,380,"T6"
DATA 80,25,12,120,12,12
DATA 2
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA "L7A2 GPMG","x",10,125,2,2,1,0,999,.4,2,125
DATA 54,.4,4,0,8,600000,2,0,0
DATA "Good","D,G,A","Passive IR, Thermal","Shielded","5","6","7","8","TUR"

DATA "Vickers Valiant","MBT","GB",110,90,1000,250,"T6"
DATA 100,32,14,300,20,16
DATA 2
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,0,6,15,400
DATA "L7A2 GPMG","x",10,125,2,2,1,0,999,.4,2,125
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "FV-510 Warrior","IFV","GB",150,110,770,175,"T4"
DATA 6,04,02,6,4,3
DATA 2
DATA "30 mm Rarden APDS","C",5,250,8,3,-2,-2,200,1,3,250
DATA "L7A2 GPMG","x",10,125,2,2,1,0,999,.4,2,125
DATA 24,.6,3,7,12,250000,1,0,0
DATA "Good","D,eA","IR Spotlight, Active/Passive IR","Shielded","5","6","7","S/R","CIH"

DATA "SK-105 K│rassier","LCV","AU",110,80,184,48,"T6"
DATA 6,5,2,6,4,4
DATA 1
DATA "105 mm HEAT","C",.5,400,80,80,80,80,0,6,15,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","CIH"

DATA "Saurer 4K 4FA-G1","LCV","AU",130,85,184,130,"T2"
DATA 0,0,0,7,4,2
DATA 1
DATA "M2HB","x",5,150,4,4,3,3,500,1,9,150
DATA 12.5,.8,2,8,4,100000,0,0,0
DATA "","D,A","Headlights","Enclosed","5","6","7","R/-","VEH"

DATA "Saurer 4K 4FA-G2","LCV","AU",130,85,184,130,"T2"
DATA 10,5,4,7,4,2
DATA 1
DATA "20 mm AC API","C",10,250,3,3,-2,-5,100,1,3,250
DATA 15,.8,2,8,4,100000,0,0,0
DATA "","D,A","Headlights","Enclosed","5","6","7","R/-","CIH"

DATA "Leonidas APC","APC","GR",130,85,360,176,"T3"
DATA 0,0,0,12,6,4
DATA 1
DATA "M2HB","x",5,150,4,4,3,3,300,1,9,150
DATA 14.8,.8,2,8,5,75000,0,0,0
DATA "","D,A","Headlights, Passive IR","Enclosed","5","6","7","-/S","VEH"
                                              
DATA "EPC - Leclerc","MBT","FR",150,130,1300,350,"T6"
DATA 100,20,10,140,20,10
DATA 1
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "EBR-75","LCV","FR",180,110,320,90,"W3"
DATA 8,06,04,10,06,04
DATA 2
DATA "90 mm HEAT","C",.5,300,60,60,60,60,0,0,0,0
DATA "      APFSDS","C",.5,300,30,25,20,15,0,0,0,0
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "ERC-90","LCV","FR",200,140,480,120,"W3"
DATA 8,08,04,8,06,04
DATA 2
DATA "90 mmf HEAT","C",.5,300,60,60,60,60,0,0,0,0
DATA "       APFSDS","C",.5,300,30,25,20,15,0,0,0,0
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"


DATA "AMX-10RC","LCV","FR",170,120,720,280,"W3"
DATA 6,04,03,8,04,04
DATA 1
DATA "105 mm HEAT","C",.5,400,80,80,80,80,0,6,15,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"


DATA "AMX - 10P","APC","F",130,85,530,115,"T2"
DATA 6,04,04,6,4,4
DATA 1
DATA "20 mm AC API","C",5,250,5,1,-2,-2,760,0,0,0
DATA 14,.5,3,8,12,100000,0,0,0
DATA "Basic","D,A","Passive IR","Shielded","5","6","7","8","CIH"

DATA "AMX-13","LCV","FR",110,090,720,275,"T3"
DATA 6,05,02,6,04,03
DATA 2
DATA "105 mm HEAT  ","C",.5,300,60,60,60,60,0,6,15,400
DATA "       APFSDS","C",.5,300,30,25,20,15,0,0,0,0
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","CIH"


DATA "AMX-30","MBT","FR",120,100,970,250,"T6"
DATA 16,08,08,16,12,6
DATA 2
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,0,6,15,400
DATA " 20 mm AC API","C",10,250,3,-2,-5,-5,0,0,0,0
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "EE-T1 Osorio","MBT","BR",120,90,800,200,"T6"
DATA 40,12,12,27,07,05
DATA 2
DATA "120 mm APFSDSDU","C",.5,500,150,140,130,110,0,10,25,400
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,0,6,15,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"



DATA "C-1 Ariete","MBT","IT",130,110,1400,350,"T6"
DATA 90,20,10,140,20,10
DATA 1
DATA "120 mm APFSDSDU","C",.5,600,150,140,130,110,0,10,25,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"

DATA "Pz-68","MBT","CH",110,88,710,180,"T6"
DATA 24,5,5,26,7,5
DATA 1
DATA "105 mm APFSDSDU","C",.5,500,100,90,80,60,0,6,15,400
DATA 0,0,0,0,0,0,0,0,0
DATA "Stab","Fuel","Nightision","RAD shield","FREE","FREE","7","8","TUR"





DATA "T-54","MBT","SU",110,65,950,190,"T6"
DATA 41,26,12,40,16,12
DATA 3
DATA "100 mm APDS-T","C",.5,350,70,60,50,32,0,6,15,300
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA 36,.4,4,0,8,300000,1,0,0
DATA "","D,A","Active IR","","5","6","7","8","TUR"

DATA "T-55","MBT","SU",110,65,950,190,"T6"
DATA 41,26,12,40,16,12
DATA 3
DATA "100 mm APDS-T","C",.5,350,70,60,50,43,0,6,15,300
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA 36,.4,4,0,8,300000,1,0,0
DATA "","D,A","Active IR","","5","6","7","8","TUR"

DATA "T-62","MBT","SU",100,60,675,380,"T6"
DATA 40,24,5,40,16,5
DATA 3
DATA "115 mm APFSDS","C",.5,400,90,80,70,60,40,12,24,400
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA 36.5,.5,4,0,6,300000,1,0,0
DATA "","D,A","","","","6","7","8","TUR"

DATA "T-64","MBT","SU",120,70,675,240,"T6"
DATA 48,24,20,44,16,10
DATA 3
DATA "125 mm APFSDSDU","C",.3333,400,110,100,90,70,36,14,35,400
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "AT-8 Songster  ","R",.14257,5000,130,0,0,0,5,12,15,5000
DATA 38,.5,3,0,6,350000,1,0,0
DATA "","D,A","Passive IR","4","5","6","7","8","TUR"


DATA "T-72","MBT","SU",150,110,1000,350,"T6"
DATA 70,24,20,100,16,10
DATA 3
DATA "125 mm APFSDSDU","C",.3333,450,110,100,90,70,0,14,35,400
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA 40,.5,3,0,14,400000,1,0,0
DATA "Fair","D,A","A/P IR","4","5","6","7","8","TUR"

DATA "T-80","MBT","SU",150,110,1000,350,"T6"
DATA 90,24,20,120,16,10
DATA 3
DATA "125 mm APFSDSDU","C",.3333,450,110,100,90,70,0,14,35,400
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA "AT-8 Songster  ","R",.14257,5000,130,0,0,0,5,12,15,5000
DATA 40,.5,3,0,18,500000,1,0,0
DATA "Fair","G,AvG,A","A/P IR","Shielded","5","6","7","8","TUR"

DATA "T-90","MBT","SU",150,110,1000,350,"T6"
DATA 90,24,20,140,25,10
DATA 3
DATA "125 mm APFSDSDU","C",.3333,450,110,100,90,70,36,14,35,400
DATA "12.7 mm DShK","x",5,150,4.5,4.5,4.5,3,300,1,9,150
DATA "9M119 Reflecks ","R",.14257,5000,170,0,0,0,6,12,15,5000
DATA 45,.5,3,0,18,600000,2,0,0
DATA "Good","D,G,AvG,A","A/P IR, Spotlight","Shielded","5","6","7","R/R","TUR"

DATA "BMD - 1","LCV","SU",160,85,300,80,"T4"
DATA 5,05,03,3,3,2
DATA 3
DATA "73 mm AC HEAT","C",.5,200,70,70,70,70,40,6,12,200
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "AT-3 Sagger","R",1,3000,75,0,0,0,4,6,4,3000
DATA 9,.6,3,6,11,80000,1,0,0
DATA "","D,A","P/A IR","4","5","6","7","8","CIH"

DATA "BMD - 2","LCV","SU",160,85,300,80,"T4"
DATA 5,05,03,3,3,2
DATA 2
DATA "AGS-17","C",5,150,0,0,0,0,0,2,12,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 9.5,.6,2,8,11,110000,0,0,0
DATA "","D,A","P/A IR","4","5","6","7","8","VEH"

DATA "PT - 76","LCV","SU",85,65,250,169,"T2"
DATA 5,05,03,8,3,1
DATA 2
DATA "76.2 mm HEAT","C",.5,300,40,40,40,40,40,8,14,300
DATA "PK MG","x",5,125,2,2,1,0,1000,1,2,125
DATA 14,.3,3,0,5,110000,0,0,0
DATA "","D,A","Active IR/Headlights","4","5","6","7","R/S","TUR"

DATA "BMP - 2","IFV","SU",130,85,460,100,"T2"
DATA 5,03,02,4,3,3
DATA 3
DATA "30 mm AC API","C",5,250,5,1,-2,-2,200,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA "AT-5 Spandrel    ","R",1,3500,140,0,0,0,4,12,15,3500
DATA 12.5,1.5,3,8,12,150000,1,0,0
DATA "","D,G,AvG,A","Passive IR","4","5","6","7","8","CIH"

DATA "BMP - 3","APC","SU",130,85,460,100,"T3"
DATA 8,04,02,6,4,3
DATA 3
DATA "100 mm APDS-T    ","C",.5,350,70,60,50,30,40,6,15,300
DATA " 30 mm AC API    ","C",5,250,5,1,-2,-2,500,1,3,250
DATA "AT-10","R",.14257,3000,80,0,0,0,6,6,5,3000
DATA 18.7,1.5,3,7,12,175000,7,0,0
DATA "Good","D,G,A,AvG","Passive IR, ImageInt","Shielded","5","6","7","R/S","CIH"

DATA "BMP - 23 IFV","IFV","BU",130,85,540,221,"T3"
DATA 5,05,03,6,4,3
DATA 3
DATA "23 mm AC API    ","C",10,250,-2,-4,-6,-6,600,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA "AT-3 Sagger","R",.333,3000,70,0,0,0,4,6,5,3000
DATA 15.2,.7,3,7,5,150000,7,0,0
DATA "","D,A","Active/Passive IR, Headlights","Enclosed","5","6","7","R/S","CIH"

DATA "BMP - 30 IFV","IFV","BU",130,85,540,221,"T3"
DATA 5,05,03,6,4,3
DATA 3
DATA " 30 mm AC API    ","C",5,250,5,1,-2,-2,500,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA "AT-3 Sagger","R",.333,3000,70,0,0,0,4,6,5,3000
DATA 15.2,.7,3,7,5,150000,7,0,0
DATA "","D,A","Active/Passive IR, Headlights","Enclosed","5","6","7","R/S","CIH"
     
DATA "BTR - 70","APC","SU",160,65,290,80,"W4"
DATA 2,2,2,3,1,1
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 13.6,2.5,3,8,8,74000,0,0,0
DATA "","D,A","Active IR, Headlights","Shielded","5","6","7","8","CIH"

DATA "TAB - 72","APC","RO",195,85,290,220,"W2"
DATA 2,1,1,3,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA 11,.8,3,8,4,100000,0,0,0
DATA "","D,A","Active IR, Headlights","Enclosed","5","6","7","-/S","CIH"

DATA "TAB - 77","APC","RO",175,65,350,187,"W2"
DATA 2,1,1,3,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA 11.5,.9,3,9,4,110000,0,0,0
DATA "","D,A","Active IR, Headlights","Enclosed","5","6","7","-/S","CIH"

DATA "Type 531","APC","AL",130,110,480,250,"T2"
DATA 2,1,1,4,2,2
DATA 1
DATA "12.7 mm DShK","x",5,150,4.5,4.5,4.5,3,1120,1,9,150
DATA 12.6,1.3,3,13,4,50000,0,0,0
DATA "","D,A","Headlights","Enclosed","5","6","7","-/R","VEH"

DATA "BOV-M 4x4","IFV","YU",195,85,220,167,"W2"
DATA 2,2,2,2,2,2
DATA 1
DATA "M2HB","x",5,150,4,4,3,3,500,1,9,150
DATA 5.7,.8,2,8,2,100000,0,0,0
DATA "","D,A","Active IR, Headlights","Enclosed","5","6","7","R/S","VEH"

DATA "M-80","IFV","YU",130,85,460,100,"T2"
DATA 5,03,03,6,3,3
DATA 3
DATA "20 mm AC API    ","C",10,250,3,-2,-5,-5,400,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,2250,1,2,125
DATA "AT-3 Sagger","R",.333,3000,70,0,0,0,4,6,5,3000
DATA 13.7,.7,3,7,5,150000,0,0,0
DATA "Basic","D,A","Active/Passive IR, Headlights","Shielded","5","6","7","-/R","CIH"

DATA "BVP M80","IFV","YU",130,85,510,120,"T2"
DATA 5,03,03,6,3,3
DATA 3
DATA "20 mm AC API    ","C",10,250,3,-2,-5,-5,400,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA "AT-3 Sagger","R",.333,3000,70,0,0,0,4,6,5,3000
DATA 13.7,.7,3,7,5,150000,0,0,0
DATA "Basic","D,A","Active/Passive IR, Headlights","Shielded","5","6","7","-/R","CIH"

DATA "M-60P","APC","YU",85,65,150,68,"T2"
DATA 5,03,03,5,5,3
DATA 2
DATA "M2HB","x",5,150,4,4,3,3,500,1,9,150
DATA "MG-42","x",10,125,2,2,1,0,2000,1,2,125
DATA 11,1,4,10,4,75000,0,0,0
DATA "","D,A","Active IR, Headlights","Enclosed","5","6","7","R/S","VEH"

DATA "BTR - 80","APC","SU",150,65,290,80,"W4"
DATA 2,2,2,3,1,1
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 13.6,2.5,3,7,6,75000,0,0,0
DATA "","D,A","Headlights","Shielded","5","6","7","8","CIH"

DATA "OT-62B","LCV","CZ",130,85,417,212,"T2"
DATA 3,3,3,3,2,2
DATA 2
DATA "82 mm RR","C",1,100,4,4,4,4,12,3,8,100
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 15,1.8,3,18,5,90000,0,0,0
DATA "","D,A","IR searchlight","Encloesd","5","6","7","-/S","VEH"

DATA "OT-62C","LCV","CZ",130,85,520,219,"T2"
DATA 2,1,2,3,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 16.4,1.2,3,12,6,110000,0,0,0
DATA "","D,A","IR searchlight","Encloesd","5","6","7","-/R","CIH"

DATA "OT-64","APC","CZ",195,85,320,80,"W4"
DATA 3,3,3,4,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 14,3,2,15,6,80000,0,0,0
DATA "","D,A","Headlights","Shielded","5","6","7","8","CIH"

DATA "OT-65","LCV","HU",175,65,200,116,"W2"
DATA 3,3,3,2,1,1
DATA 1
DATA "PK MG","x",5,125,2,2,1,0,1250,1,2,125
DATA 7,.4,2,4,2,65000,0,0,0
DATA "","D,A","Active IR/Headlights","Open","5","6","7","R/S","VEH"

DATA "OT-66","LCV","HU",170,65,200,128,"W2"
DATA 3,2,2,3,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,2000,1,2,125
DATA 7.5,.3,3,6,3,95000,0,0,0
DATA "","D,A","IR Searchlights, Headlights","Enclosed","5","6","7","-/S","CIH"

DATA "BRDM-1","APC","SU",160,120,150,35,"W4"
DATA 0,0,0,2,1,1
DATA 2
DATA "AT-3 Sagger","R",.333,3000,75,75,75,75,6,6,4,3000
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 5.6,.5,3,0,6,25000,0,0,0
DATA "","G,A","Headlights","Shielded","5","6","7","8","VEH"


DATA "BRDM-2","APC","SU",195,85,290,80,"W2"
DATA 0,0,0,2,2,2
DATA 2
DATA "14.5 mm KPV MG","x",5,150,6,6,6,4,500,1,9,150
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 8,.6,4,0,4,50000,0,0,0
DATA "Basic","G, AvG, A","Headlights, ImInt","Shielded","5","6","7","8","VEH"


DATA "BRDM-3","APC","SU",195,85,290,80,"W2"
DATA 2,2,2,2,1,1
DATA 1
DATA "AT-5 Spandrel","R",.333,3500,155,155,155,155,10,12,12,3500
DATA 8,.6,3,0,4,50000,0,0,0
DATA "Basic","G, AvG, A","Headlights, ImInt","Shielded","5","6","7","8","CIH"



DATA "BRDM-4","APC","SU",195,85,290,80,"W2"
DATA 2,2,2,2,1,1
DATA 2
DATA "30 mm AC","C",5,250,5,1,-2,-2,250,1,3,250
DATA "PK MG","x",5,125,2,2,1,0,.4,1,2,125
DATA 8,.6,4,0,4,50000,0,0,0
DATA "Basic","G, AvG, A","Headlights, ImInt","Shielded","5","6","7","8","CIH"

DATA "OT-65 FUG","RCV","SU",175,65,200,60,"W2"
DATA 2,2,2,2,1,1
DATA 0
DATA 7,.7,2,4,4,45000,0,0,0
DATA "","D,A","Headlights, Passive IR","Enclosed","5","6","7","8","VEH"

DATA "M-77","MBT","RO",100,60,580,220,"T6"
DATA 41,26,12,40,18,12
DATA 1
DATA "100 mm HVAPDS-T","C",.5,350,70,60,50,30,43,6,15,300
DATA 36,.4,4,0,8,300000,1,0,0
DATA "","D,A","A/P IR","4","5","6","7","8","TUR"

DATA "M-81","MBT","RO",120,70,960,260,"T6"
DATA 41,26,12,40,16,12
DATA 1
DATA "120 mm APFSDSDU","C",.5,500,150,140,130,110,40,10,25,400
DATA 39,.5,4,0,8,450000,1,0,0
DATA "","D,A","A/P IR","4","5","6","7","8","TUR"

DATA "M-84","MBT","YU",130,85,1200,350,"T6"
DATA 70,24,20,100,16,10
DATA 3
DATA "125 mm APFSDSDU","C",.3333,450,110,100,90,70,42,14,35,400
DATA "PK MG","x",5,125,2,2,1,0,3000,1,2,125
DATA "M2HB","x",5,150,4,4,3,3,500,1,9,150
DATA 41,.5,3,0,13,400000,1,0,0
DATA "Basic","D,A","IR Searchlight, Headlights","Shielded","5","6","7","-/R","TUR"

DATA "TR-85","MBT","RO",85,65,965,420,"T6"
DATA 41,26,12,40,16,12
DATA 3
DATA "100 mm APDS-T","C",.5,350,70,60,50,30,43,6,15,300
DATA "PK MG","x",5,125,2,2,1,0,3000,1,2,125
DATA "DShK MG","x",5,150,4,4,1,0,500,1,9,150
DATA 36,.4,4,0,12,300000,1,0,0
DATA "Basic","D,A","Active/Passive IR, IR Searchlight","Shielded","5","6","7","-/R","TUR"

DATA "Dana (Vzor 77) 152 mm SPH","SPA","CZ",150,40,690,221,"W4"
DATA 4,3,3,4,3,2
DATA 2
DATA "152 mm","C",.333,350,80,80,80,80,28,75,45,300
DATA "DShK MG","x",5,150,4,4,1,0,300,1,9,150
DATA 23,.5,5,0,8,120000,0,0,0
DATA "","D,A,G,AvG","Active/Passive IR","Enclosed","5","6","7","-/R","TUR"

DATA "M53-59 SPAA","SPA","CZ",130,40,120,58,"W2"
DATA 4,3,3,3,2,2
DATA 1
DATA "30 mm","C",10,250,5,5,-1,-2,800,1,3,2500
DATA 10.3,.5,5,0,3,85000,1,0,0
DATA "","D,A","Headlights","Open","5","6","7","-/R","VEH"





DATA "XXX",",MBT","US",0,0,0,0,"T6"



8001 RESTORE 8001
DATA 0,20,40,80,120,160,200,250,300,400,500,750,1000,1250,1500,1750,2000,3000
DIM dam(17): FOR I = 0 TO 17: READ dam(I): NEXT
RETURN

9001 IF style = 2 THEN GOTO 9002
ttz = ttx
IF ttz > 100 THEN ttz = CINT(ttx / 10) * 10: RETURN
IF ttz > 50 THEN ttz = CINT(ttx / 5) * 5: RETURN
IF ttz < 1 THEN ttz = 1
RETURN


9002 'Striker Armor
FOR xi = 1 TO 120
    IF STRIKER(xi) > ttx THEN ttz = xi - 1: xi = 120
NEXT
RETURN




'ttx = ttx * DIV
FOR k = 0 TO 17: IF dam(k) > ttx THEN xxk = k - 1: sx0 = dam(k - 1) - .01: calc = dam(k) - dam(k - 1): k = 17
NEXT
calc2 = ttx - sx0
mult = calc2 / calc * 100 ': mult = 0
ttz = xxk * 10 + mult / 10
'ttz = xxk
RETURN


19999 ' Druckausgabe
s78 = 71
s782 = s78 - 2
PRINT #nnn, "з";
FOR I2 = 1 TO s78: PRINT #nnn, "д";: NEXT
PRINT #nnn, "©"

FOR I2 = 0 TO 10: text$(I2) = "д": NEXT

tabu0 = s782 + 1: tabu = tabu0: tx = 0:
text$(0) = text$: IF LEN(text$(0)) <= tabu THEN GOTO 10004

10001 IF tabu > 1 AND MID$(text$(tx), tabu, 1) <> " " THEN tabu = tabu - 1: GOTO 10001
leng = LEN(text$(tx)): l1 = leng - tabu
text$(tx + 1) = RIGHT$(text$(tx), l1)
text$(tx) = LEFT$(text$(tx), tabu)
tx = tx + 1
tabu = tabu0
IF LEN(text$(tx)) > tabu THEN GOTO 10001



10002 FOR I2 = 0 TO tx - 1: space0 = tabu0 - LEN(text$(I2)): work1$ = ""

    10003 work$ = text$(I2): work1$ = "":
    FOR zz = 1 TO LEN(work$): space0$ = MID$(work$, zz, 1)
        IF space0$ = " " AND space0 > 0 THEN space0$ = "  ": space0 = space0 - 1
        work1$ = work1$ + space0$
    NEXT
    text$(I2) = work1$
    IF space0 > 0 AND tx <> I2 THEN GOTO 10003

NEXT

10004 FOR I2 = 0 TO tx: 'IF I2 = 0 THEN PRINT #nnn, "Ё";
    IF nnn = 1 THEN PRINT #nnn, "Ё ";
    text$(I2) = LEFT$(text$(I2), LEN(text$(I2)) - 1)
    IF I2 = tx THEN text$(I2) = text$(I2) + SPC(s782 - LEN(text$(I2)))
    IF nnn = 1 THEN PRINT #nnn, text$(I2); " Ё":
    IF nnn = 0 THEN PRINT " "; text$(I2)
NEXT
'RETURN
'IF text$ = ammo$ THEN RETURN
PRINT #nnn, "ю";
FOR I2 = 1 TO s78: PRINT #nnn, "д";: NEXT
PRINT #nnn, "ы"


RETURN
19000
RESTORE 19000
FOR I = 1 TO 14: READ ARTL(I), ARTYPE$(I), ARMOR(I), ARWEIGHT(I), ARCOST(I): NEXT
DATA 1,"Loose dirt, Sand",.002,1,1
DATA 2,"Stone, Wood, packed dirt",.1,1,1
DATA 2,"Concrete and Bricks",.15,1,1
DATA 5,"Reinforced concrete",.2,1,1
DATA 4,"Iron",.6,8,1.2
DATA 5,"Sheet steel",.85,8,1.6
DATA 6,"Hard steel",1,8,2
DATA 6,"Aluminium",.5,2,3
DATA 7,"Composite laminates",2,7,7
DATA 8,"Chobham 2",2.5,8,10
DATA 9,"Chobham 3",3,9,20
DATA 10,"Crystaliron",4,10,9
DATA 12,"Superdense",7,15,14
DATA 14,"Bonded superdense",14,15,28
RETURN
19001: CLS
FOR I = 1 TO 14: PRINT USING "##. "; I;: PRINT ARTYPE$(I): NEXT
PRINT
INPUT " ", typ: IF typ = 0 THEN typ = 7
PRINT
INPUT " Thickness in mm ", thick
armor = ARMOR(typ)
PRINT
'INPUT " Armor angle ", angle0: angle = COS(angle0)


PRINT " Armor Slope (N)o = 0, (L)ow = <40, (M)edium = <60, (H)igh >=60"
GOSUB 1000: a$ = UCASE$(a$)
angle = 1
IF a$ = "L" THEN angle = 1.333: slope$ = ", light slope"
IF a$ = "M" THEN angle = 1.5: slope$ = ", medium slope"
IF a$ = "H" THEN angle = 2: slope$ = ", steep slope"
armor = thick * ARMOR(typ) * angle
CLS: PRINT " "; ARTYPE$(typ); slope$; thick; "mm"
PRINT: PRINT " Hard Steel EQ = "; armor; "mm"
PRINT: PRINT " Striker I     = ";: ttx = armor / 10: GOSUB 9002: PRINT ttz
PRINT: PRINT " T2K: 2.2      = "; CINT(armor / 10 * 2)
PRINT: PRINT " T2K: 1.0      = "; CINT(armor / 10 * 2 * 1000 / 160)
PRINT: PRINT " MgT2E         = "; CINT(armor / 10 * 2 / 2.166)
PRINT: PRINT " Cepheus       = "; CINT(armor / 10 * 2 / 5.4)

IF style = 1 THEN DIV = 1: Style$ = " T2K+TNE"
IF style = 2 THEN DIV = 2: HEX = 10: Style$ = " Striker I"
IF style = 3 THEN DIV = 2: Style$ = " Armor in cm"
IF style = 4 THEN DIV = 2.16666: Style$ = " MgT2E"
IF style = 5 THEN DIV = 5.4: Style$ = " Cepheus"


PRINT
GOSUB 1000
GOTO 19001



