C      SUBROUTINEPCDSLV(N,A,RHS,X,IPARM)
      SUBROUTINEPCDSLV(N,A,RHS,X)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
C      INTEGERN,IPARM(*)
      INTEGERN
      DOUBLEPRECISIONA(*),RHS(*),X(*)
      INTEGERIERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,LUDONE,IBLK,
     *MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,IFRMAT
      COMMON/PCCOM1/IERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,
     *LUDONE,IBLK,MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,
     *IFRMAT
      SAVE/PCCOM1/
      INTEGERI
      ITS=0
      MNEED=0
      DO11I=1,N
      IF(A(I).EQ.0.0D0)THEN
      IF(RHS(I).EQ.0.0D0)THEN
      X(I)=0.0D0
      ELSE
      IERR2=I
      RETURN
      ENDIF
      ELSE
      X(I)=RHS(I)/A(I)
      ENDIF
11    CONTINUE
      IERR=0
      RETURN
      END
