      SUBROUTINEPCVERS(N,IJA)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IJA(*)
      INTEGERIERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,LUDONE,IBLK,
     *MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,IFRMAT
      COMMON/PCCOM1/IERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,
     *LUDONE,IBLK,MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,
     *IFRMAT
      SAVE/PCCOM1/
      INTEGERISRT,IJASGN,ISX0,IFORM
      COMMON/PCVERI/ISRT,IJASGN,ISX0,IFORM
      SAVE/PCVERI/
      LOGICALLOWER,UPPER,FULL,HALF,SYMMAT
      COMMON/PCVERL/LOWER,UPPER,FULL,HALF,SYMMAT
      SAVE/PCVERL/
      INTEGERI,J
      SYMMAT=.TRUE.
      IF(NOVERF.NE.0)THEN
      IF(IFORM.EQ.-1)THEN
      LOWER=.TRUE.
      UPPER=.FALSE.
      HALF=.TRUE.
      FULL=.FALSE.
      ELSEIF(IFORM.EQ.1)THEN
      LOWER=.FALSE.
      UPPER=.TRUE.
      HALF=.TRUE.
      FULL=.FALSE.
      ELSE
      LOWER=.FALSE.
      UPPER=.FALSE.
      HALF=.FALSE.
      FULL=.TRUE.
      ENDIF
      RETURN
      ENDIF
      LOWER=.TRUE.
      UPPER=.TRUE.
      DO1I=1,N
CDIR$ IVDEP
CVDIR IGNORE RECRDEPS
      DO3J=ABS(IJA(I)),ABS(IJA(I+1))-1
      IF(LOWER)THEN
      IF(IJA(J).GT.I)THEN
      LOWER=.FALSE.
      ENDIF
      ENDIF
      IF(UPPER)THEN
      IF(IJA(J).LT.I)THEN
      UPPER=.FALSE.
      ENDIF
      ENDIF
      IF(.NOT.(LOWER.OR.UPPER))THEN
      GOTO2
      ENDIF
3     CONTINUE
1     CONTINUE
2     CONTINUE
      IF(UPPER)THEN
      IFORM=1
      ELSEIF(LOWER)THEN
      IFORM=-1
      ELSE
      IFORM=0
      ENDIF
      IF(UPPER)THEN
      LOWER=.FALSE.
      ENDIF
      HALF=(UPPER.OR.LOWER)
      FULL=.NOT.HALF
      RETURN
      END
