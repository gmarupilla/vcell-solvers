      SUBROUTINEPCILU1(MODIFY,N,IJA,A,ISP,RSP,IJL,IJU,LD,U)
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
      INTEGERROW,IROW
      INTEGERANADR,ANFREE,AINADR,ALAST,AILAST,NZMAX,LEVL,IPT,
     *IUT,NZL,NZU,NSP1,IJU1,SPCN,SCRN
      SAVENZL,NZU
      INTEGERKNZL,KNZU,SPIUT,SPLEVL,SPIPT,SPIROW
      SPCN(KNZL,KNZU)=(KNZL+KNZU+RATIO-1)/RATIO+KNZL+KNZU-N-1
      SCRN(KNZL,KNZU,SPIUT,SPLEVL,SPIPT,SPIROW)=MAX((SPLEVL+SPIPT+(2+
     *SPIUT)*MAX(KNZL,KNZU)-(KNZU+KNZL)+RATIO-1)/RATIO-KNZL-KNZU+N
     *+1,N+(SPIROW+RATIO-1)/RATIO)
      IF(IFL.EQ.-1)THEN
      SPIUT=0
      SPLEVL=0
      SPIPT=0
      ELSEIF(IFL.GT.0)THEN
      SPIUT=1
      SPLEVL=N
      SPIPT=ISRT*N
      ELSE
      SPIPT=0
      SPIUT=1-ISRT
      SPLEVL=SPIUT*N
      ENDIF
      IF(MODIFY)THEN
      SPIROW=N
      ELSE
      SPIROW=0
      ENDIF
      IF(IJASGN.EQ.0)THEN
      CALLPCIABS(N,IJA)
      ENDIF
      IF(LUDONE.NE.0)THEN
      IROW=IJU+ISP(IJU+N)-1
      ROW=U+1
      ELSE
      ANADR=ISP(2)
      ANFREE=ISP(1)
      AINADR=(ANADR-1)*RATIO+1
      ALAST=ANADR+ANFREE
      AILAST=AINADR+ANFREE*RATIO
      IJL=AINADR
      LEVL=AILAST-SPLEVL
      IPT=LEVL-SPIPT
      NZMAX=(IPT-IJL)/(2+SPIUT)
      IUT=IJL+NZMAX*SPIUT
      IJU1=IUT+NZMAX
      IF(NZMAX.LE.N+1)THEN
      NZL=((IJA(N+1)-1-N)*(1+IFL)+N)/2
      NZU=NZL
      ISP(1)=ANFREE-SPCN(NZL,NZU)
      ISP(3)=ISP(1)-SCRN(NZL,NZU,SPIUT,SPLEVL,SPIPT,SPIROW)
      IERR=3
      RETURN
      ENDIF
      IF(ISRT.EQ.1)THEN
      CALLPCILUS(N,IJA,IFL,NZMAX,NZL,NZU,ISP(IJL),ISP(IJU1
     *),ISP(IUT),ISP(LEVL),ISP(IPT))
      ELSE
      CALLPCILUZ(N,IJA,IFL,NZMAX,NZL,NZU,ISP(IJL),ISP(IJU1
     *),ISP(IUT),ISP(LEVL))
      ENDIF
      IF(IERR.EQ.3)THEN
      ISP(1)=ANFREE-SPCN(NZL,NZU)
      ISP(3)=ISP(1)-SCRN(NZL,NZU,SPIUT,SPLEVL,SPIPT,SPIROW)
      ENDIF
      IF(IERR.NE.0)THEN
      RETURN
      ENDIF
      IJU=IJL+NZL
      CALLPCICPY(NZU,ISP(IJU1),ISP(IJU))
      IROW=IJU+NZU
      LD=ALAST-NZL
      U=LD-NZU
      ROW=U+1
      ENDIF
      ISP(2)=(IROW+RATIO-2)/RATIO+1
      ISP(1)=U+N+1-ISP(2)
      NSP1=ISP(1)-SCRN(NZL,NZU,SPIUT,SPLEVL,SPIPT,SPIROW)
      ISP(3)=NSP1
      IF(NSP1.LT.0)THEN
      IERR=3
      RETURN
      ENDIF
      CALLPCILUF(MODIFY,N,IJA,ISP(IJL),ISP(IJU),A,RSP(LD),RSP(U
     *),ISP(IROW),RSP(ROW))
      RETURN
      END
