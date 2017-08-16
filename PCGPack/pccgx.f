      SUBROUTINEPCCGX(N,IJA,A,RHS,X,RN,RP,P,ATP,ISP,RSP,
     *PRECON,PCSTOP,PCMV)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IJA(*),ISP(*)
      DOUBLEPRECISIONA(*),RHS(*),X(*),RN(*),RP(*),P(*),
     *ATP(*),RSP(*)
      EXTERNALPRECON,PCSTOP,PCMV
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
      INTEGERONE,MTHREE
      INTEGERLTEST
      DOUBLEPRECISIONALPHA,BETA,RRP,NRRP,PAP
      DOUBLEPRECISIONDDOT
      ONE=1
      MTHREE=-3
      IF(ISX0.NE.1)THEN
      CALLPCMV(N,IJA,A,X,RN)
      CALLPCVSUB(N,RN,RHS)
      ELSE
      CALLDCOPY(N,RHS,ONE,RN,ONE)
      ENDIF
      CALLPCSTOP(ONE,N,IJA,A,RHS,X,RN,ISP,RSP,PRECON)
      IF(IERR.GE.0)THEN
      RETURN
      ENDIF
      IF(IPRE.NE.3)THEN
      CALLDCOPY(N,RN,ONE,RP,ONE)
      CALLPRECON(MTHREE,N,IJA,A,RP,ISP,RSP)
      ENDIF
      CALLDCOPY(N,RP,ONE,P,ONE)
      RRP=DDOT(N,RP,ONE,RN,ONE)
      LTEST=ITEST
      DO1ITS=1,ITMAX-1
      LTEST=LTEST-1
      CALLPCMV(N,IJA,A,P,ATP)
      PAP=DDOT(N,P,ONE,ATP,ONE)
      IF(PAP.EQ.0.0D0)THEN
      IERR=13
      RETURN
      ENDIF
      ALPHA=RRP/PAP
      CALLDAXPY(N,ALPHA,P,ONE,X,ONE)
      CALLDAXPY(N,-ALPHA,ATP,ONE,RN,ONE)
      IF(LTEST.EQ.0)THEN
      LTEST=ITEST
      CALLPCSTOP(ONE,N,IJA,A,RHS,X,RN,ISP,RSP,PRECON)
      IF(IERR.GE.0)THEN
      RETURN
      ENDIF
      ENDIF
      IF(IPRE.NE.3)THEN
      CALLDCOPY(N,RN,ONE,RP,ONE)
      CALLPRECON(MTHREE,N,IJA,A,RP,ISP,RSP)
      ENDIF
      NRRP=DDOT(N,RN,ONE,RP,ONE)
      BETA=NRRP/RRP
      RRP=NRRP
      CALLPCVSMA(N,BETA,P,RP,P)
1     CONTINUE
      CALLPCMV(N,IJA,A,P,ATP)
      PAP=DDOT(N,P,ONE,ATP,ONE)
      IF(PAP.EQ.0.0D0)THEN
      IERR=13
      RETURN
      ENDIF
      ALPHA=RRP/PAP
      CALLDAXPY(N,ALPHA,P,ONE,X,ONE)
      CALLDAXPY(N,-ALPHA,ATP,ONE,RN,ONE)
      ITS=ITMAX
      CALLPCSTOP(ONE,N,IJA,A,RHS,X,RN,ISP,RSP,PRECON)
      RETURN
      END
