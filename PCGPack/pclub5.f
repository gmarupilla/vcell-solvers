      SUBROUTINEPCLUB5(MARK,I,K,N,IJA,S,V,A,ACC2)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERMARK(*),I,K,N,IJA(*)
      DOUBLEPRECISIONS,A(*),V(*),ACC2
      INTEGERJ
CDIR$ IVDEP
CVDIR IGNORE RECRDEPS
      DO1J=1,N
      IF(MARK(IJA(J)).EQ.K)THEN
      A(IJA(J))=A(IJA(J))+S*V(J)
      ELSE
      A(I)=A(I)+ACC2*S*V(J)
      ENDIF
1     CONTINUE
      RETURN
      END
