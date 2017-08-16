      SUBROUTINEPCREDB(N,IJA,A,RHS,X,ISP,RSP,METHOD,PRECON,
     *PCSTOP,PCMV)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IJA(*),ISP(*)
      DOUBLEPRECISIONA(*),RHS(*),X(*),RSP(*)
      EXTERNALMETHOD,PRECON,PCSTOP,PCMV
      INTEGERIERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,LUDONE,IBLK,
     *MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,IFRMAT
      COMMON/PCCOM1/IERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,
     *LUDONE,IBLK,MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,
     *IFRMAT
      SAVE/PCCOM1/
      INTEGERIPRE1,IPRE2,RATIO
      COMMON/PCCOM3/IPRE1,IPRE2,RATIO
      SAVE/PCCOM3/
      INTEGERISRT,IJASGN,ISX0,IFORM
      COMMON/PCVERI/ISRT,IJASGN,ISX0,IFORM
      SAVE/PCVERI/
      INTEGERIBLKN,IC,C,D2I,IPVT,ID2I,RSRHS,NZRS,IJRS,RS,Y,
     *RSNADR,NSP1,IBLKS,MAXBLK,IRTBM,IBTRM,IBTRMC,IMN,ISCR,
     *IJAB,CP,NBLACK,NBLCKB
      INTEGERNADR,INADR
      INTEGERONE,IRS1,IRS2,I
      INTEGERSISRT,SNVRFY,SIFORM
      INTEGERISAVE(31)
      EQUIVALENCE(IBLKN,ISAVE(8)),(IC,ISAVE(9)),(C,ISAVE(10)),(D2I,
     *ISAVE(11)),(IPVT,ISAVE(12)),(ID2I,ISAVE(13)),(RSRHS,ISAVE(14)),(
     *NZRS,ISAVE(15)),(IJRS,ISAVE(16)),(RS,ISAVE(17)),(Y,ISAVE(18)),(
     *RSNADR,ISAVE(19)),(NSP1,ISAVE(20)),(NBLCKB,ISAVE(21)),(IBLKS,
     *ISAVE(22)),(MAXBLK,ISAVE(23)),(IRTBM,ISAVE(24)),(IBTRM,ISAVE(25)
     *),(IBTRMC,ISAVE(26)),(NBLACK,ISAVE(27)),(IMN,ISAVE(28)),(ISCR,
     *ISAVE(29)),(IJAB,ISAVE(30)),(CP,ISAVE(31))
      ONE=1
      IRS1=8
      IRS2=31
      NADR=ISP(2)
      INADR=(NADR-1)*RATIO+1
      IF(RSDONE.EQ.1)THEN
      DO1I=IRS1,IRS2
      ISAVE(I)=ISP(I)
1     CONTINUE
      CALLDCOPY(N,RHS,ONE,RSP(Y),ONE)
      CALLPCD2I(IBLKN,ISP(IBLKS),ISP(IBTRM),ISP(IBTRMC),NBLCKB,
     *ISP(C),ISP(IPVT),RSP(D2I),RSP(Y))
      IF(IJASGN.EQ.0)THEN
      CALLPCIABS(N,IJA)
      ENDIF
      CALLPCRC1B(IBLKN,ISP(IBTRM),ISP(IRTBM),NBLCKB,ISP(C),ISP
     *(IC),IJA,A,RSP(Y),RSP(RSRHS))
      ELSE
      IBLKS=INADR
      IF(RSDONE.EQ.2)THEN
      DO3I=IRS1,IRS2
      ISAVE(I)=ISP(I)
3     CONTINUE
      ELSE
      LUDONE=0
      ENDIF
      CALLPCRSFB(N,IJA,A,RHS,ISP,RSP,IC,C,CP,NBLCKB,NBLACK
     *,IJAB,IBLKN,IBLKS,IBTRM,IRTBM,IBTRMC,IPVT,ID2I,D2I,
     *NZRS,IJRS,RS,RSRHS,Y,IMN,ISCR,RSNADR,NSP1)
      IF(IERR.NE.0)THEN
      RETURN
      ENDIF
      DO5I=IRS1,IRS2
      ISP(I)=ISAVE(I)
5     CONTINUE
      ENDIF
      IF(NBLACK.NE.0)THEN
      CALLPCPRMB(NBLCKB,ISP(IBTRM),ISP(C),X,RSP(Y))
      SISRT=ISRT
      SNVRFY=NOVERF
      SIFORM=IFORM
      ISRT=0
      NOVERF=2
      IFORM=0
      ISP(1)=NSP1
      ISP(2)=RSNADR
      CALLPCDRVX(NBLACK,ISP(IJRS),RSP(RS),RSP(RSRHS),RSP(Y),ISP,
     *RSP,METHOD,PRECON,PCSTOP,PCMV)
      ISRT=SISRT
      NOVERF=SNVRFY
      IFORM=SIFORM
      IF(IERR.LT.2.OR.IERR.GT.4)THEN
      MNEED=MAX(MNEED,ISCR)+IMN
      ENDIF
      ELSE
      MNEED=IMN+ISCR
      ENDIF
      CALLPCRDPT(N,IBLKN,ISP(IBLKS),ISP(IBTRM),ISP(IRTBM),ISP(
     *IBTRMC),NBLCKB,NBLACK,ISP(C),ISP(IC),ISP(IPVT),IJA,A,RHS,
     *RSP(D2I),RSP(Y),X)
      RETURN
      END
