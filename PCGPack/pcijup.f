      SUBROUTINEPCIJUP(N,IBLKN,IBTRM,IJUB,IJU,NZMAX)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IBLKN,IBTRM(*),IJUB(*),IJU(*),NZMAX
      INTEGERI,J,K,NZU,NI,JJ,I1,I2,IBLKSK,M1,M2,M
      IJU(1)=N+2
      NZU=N+1
      I2=IBTRM(1)
      DO1K=1,IBLKN
      I1=I2
      I2=IBTRM(K+1)
      IBLKSK=I2-I1
      IF(NZU+IBLKSK-1.GT.NZMAX)THEN
      NZMAX=-(NZU-N-1+(IBLKSK-1)*IBLKSK/2)*IBLKN/K-N-1
      RETURN
      ENDIF
      DO3I=I1+1,I2-1
      NZU=NZU+1
      IJU(NZU)=I
3     CONTINUE
      DO5J=IJUB(K),IJUB(K+1)-1
      JJ=IJUB(J)
      M1=IBTRM(JJ)
      M2=IBTRM(JJ+1)
      IF(M2-M1+NZU.GT.NZMAX)THEN
      NZMAX=-(NZU-N-1+(M2-M1)*IBLKSK)*IBLKN/K-N-1
      RETURN
      ENDIF
      DO7M=M1,M2-1
      NZU=NZU+1
      IJU(NZU)=M
7     CONTINUE
5     CONTINUE
      NI=NZU+1-IJU(I1)
      IJU(I1+1)=NZU+1
      IF((IBLKSK-1)*(NI-1)-IBLKSK*(IBLKSK-1)/2+NZU.GT.NZMAX)
     *THEN
      NZMAX=-(NZU-N-1+(IBLKSK-1)*(NI-1)-NI*(NI-1)/2)*IBLKN/K-N-
     *1
      RETURN
      ENDIF
      DO9I=I1+1,I2-1
      NI=NI-1
      CALLPCICPY(NI,IJU(IJU(I-1)+1),IJU(NZU+1))
      NZU=NZU+NI
      IJU(I+1)=NZU+1
9     CONTINUE
1     CONTINUE
      RETURN
      END
