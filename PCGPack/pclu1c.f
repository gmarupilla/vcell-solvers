      SUBROUTINEPCLU1C(MODIFY,N,IJA,A,ISP,RSP,IJL,IJU,LD,U)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      LOGICALMODIFY
      INTEGERN,IJA(*),ISP(*),IJL,IJU,LD,U
      DOUBLEPRECISIONA(*),RSP(*)
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
      INTEGER
     *ROW,IROW,
     *KNZL,KNZU,ANADR,ANFREE,AINADR,ALAST,NZMAX,
     *LEVL,IPT,IUT,NZL,NZU,SPCN,SCRN0,SCRN2,
     *KNZ,NZ,IJAR,AR,IJLR,LDR,IJUR,UR,IJLR1,IJUR1,
     *SPIUT,SPLEVL,SPIPT
      SPCN(KNZL,KNZU)=(KNZL+KNZU+RATIO-1)/RATIO+
     +KNZL+KNZU-N-1
      SCRN0(KNZ,KNZL,KNZU,SPIUT,SPLEVL,SPIPT)=MAX(
     *(KNZ+SPLEVL+SPIPT+(2+SPIUT)*MAX(KNZU,KNZL)-
     -KNZL-KNZU+RATIO-1)/RATIO+KNZ-KNZL-KNZU+N+1,
     *(MAX(KNZ,MAX(KNZU,KNZL))+N+RATIO-1)/RATIO+
     +MAX(KNZ,MAX(KNZU,KNZL))+N+1)
      SCRN2(KNZ,KNZL,KNZU)=(KNZ+KNZL+KNZU+N+RATIO-1)/RATIO+
     +KNZ+KNZU+KNZL+N
      IF(IFL.EQ.-1)THEN
      SPIUT=0
      SPLEVL=0
      SPIPT=0
      ELSEIF(IFL.GT.0)THEN
      SPIUT=1
      SPLEVL=N
      SPIPT=ISRT*N
      ELSE
      SPIUT=1-ISRT
      SPLEVL=SPIUT*N
      SPIPT=0
      ENDIF
      IF(IJASGN.EQ.0)THEN
      CALLPCIABS(N,IJA)
      ENDIF
      IF(LUDONE.NE.0)THEN
      NZ=IJA(N+1)-1
      NZU=ISP(IJU+N)-1
      NZL=ISP(IJL+N)-1
      IJAR=IJU+NZU
      IJLR=IJAR+NZ
      IJUR=IJLR+NZL
      IROW=IJUR+NZU
      AR=U+1-NZ
      LDR=AR-NZL
      UR=LDR-NZU
      ROW=U+1
      IF((IROW+N+RATIO-1)/RATIO-UR.GT.0)THEN
      ISP(3)=ISP(1)-SCRN2(NZ,NZL,NZU)
      IERR=3
      RETURN
      ENDIF
      CALLPCTRAN(N,IJA,A,ISP(IJAR),RSP(AR))
      CALLPCSRIZ(N,ISP(IJL),ISP(IJLR))
      CALLPCSRIX(N,ISP(IJL),ISP(IJLR))
      CALLPCSRIZ(N,ISP(IJU),ISP(IJUR))
      CALLPCSRIX(N,ISP(IJU),ISP(IJUR))
      ELSE
      ANADR=ISP(2)
      ANFREE=ISP(1)
      AINADR=(ANADR-1)*RATIO+1
      ALAST=ANADR+ANFREE-1
      NZ=IJA(N+1)-1
      IJAR=AINADR
      IPT=IJAR+NZ
      LEVL=IPT+SPIPT
      IUT=LEVL+SPLEVL
      AR=ALAST-NZ+1
      NZMAX=((AR-1)*RATIO+1-IUT)/(2+SPIUT)
      IF(NZMAX.LE.N+1)THEN
      NZL=((IJA(N+1)-1-N)*(1+IFL)+N)/2
      NZU=NZL
      ISP(1)=ANFREE-SPCN(NZL,NZU)
      ISP(3)=ISP(1)-SCRN0(NZ,NZL,NZU,SPIUT,SPLEVL,SPIPT)
      IERR=3
      RETURN
      ENDIF
      IJLR1=IUT+NZMAX*SPIUT
      IJUR1=IJLR1+NZMAX
      CALLPCTRAN(N,IJA,A,ISP(IJAR),RSP(AR))
      IF(ISRT.EQ.1)THEN
      CALLPCILUS(N,ISP(IJAR),IFL,NZMAX,NZL,NZU,ISP(IJLR1),
     *ISP(IJUR1),ISP(IUT),ISP(LEVL),ISP(IPT))
      ELSE
      CALLPCILUZ(N,ISP(IJAR),IFL,NZMAX,NZL,NZU,ISP(IJLR1),
     *ISP(IJUR1),ISP(IUT),ISP(LEVL))
      ENDIF
      IF(IERR.EQ.3)THEN
      ISP(1)=ANFREE-SPCN(NZL,NZU)
      ISP(3)=ISP(1)-SCRN0(NZ,NZL,NZU,SPIUT,SPLEVL,SPIPT)
      ENDIF
      IF(IERR.NE.0)THEN
      RETURN
      ENDIF
      NZMAX=MAX(NZ,MAX(NZL,NZU))
      IJLR=IJAR+NZMAX
      IJUR=IJLR+NZL
      IROW=IJUR+NZU
      CALLPCICPY(NZL,ISP(IJLR1),ISP(IJLR))
      CALLPCICPY(NZU,ISP(IJUR1),ISP(IJUR))
      LDR=ALAST-NZMAX-NZL+1
      UR=LDR-NZU
      ROW=UR
      IF((IROW+N+RATIO-1)/RATIO-UR.GT.0)THEN
      ISP(1)=ANFREE-SPCN(NZL,NZU)
      ISP(3)=ISP(1)-SCRN0(NZ,NZL,NZU,SPIUT,SPLEVL,SPIPT)
      IERR=3
      RETURN
      ENDIF
      IJL=IJAR
      IJU=IJL+NZL
      LD=ALAST-NZL+1
      U=LD-NZU
      ENDIF
      ISP(2)=(IJU+NZU+RATIO-2)/RATIO+1
      ISP(1)=U+N+1-ISP(2)
      IF(LUDONE.NE.0)THEN
      ISP(3)=ISP(1)-SCRN2(NZ,NZL,NZU)
      ELSE
      ISP(3)=ISP(1)-SCRN0(NZ,NZL,NZU,SPIUT,SPLEVL,SPIPT)
      ENDIF
      CALLPCILUF(MODIFY,N,ISP(IJAR),ISP(IJLR),ISP(IJUR),
     *RSP(AR),RSP(LDR),RSP(UR),ISP(IROW),RSP(ROW))
      CALLPCTRAN(N,ISP(IJLR),RSP(LDR),ISP(IJL),RSP(LD))
      CALLPCTRAN(N,ISP(IJUR),RSP(UR),ISP(IJU),RSP(U))
      RETURN
      END
