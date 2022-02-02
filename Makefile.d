main.o: src/main.cpp src/Calculator/CApplication.h \
 src/Calculator/CCalculator.h src/Calculator/../Variable/CVariable.h \
 src/Calculator/../Variable/../MathObject/CMathObject.h \
 src/Calculator/../MathObject/CNumber.h src/Test/CTest.h
CApplication.o: src/Calculator/CApplication.cpp \
 src/Calculator/CApplication.h src/Calculator/CCalculator.h \
 src/Calculator/../Variable/CVariable.h \
 src/Calculator/../Variable/../MathObject/CMathObject.h \
 src/Calculator/../MathObject/CNumber.h
CCalculator.o: src/Calculator/CCalculator.cpp \
 src/Calculator/CCalculator.h src/Calculator/../Variable/CVariable.h \
 src/Calculator/../Variable/../MathObject/CMathObject.h \
 src/Calculator/../MathObject/CNumber.h \
 src/Calculator/../Expression/CExpression.h \
 src/Calculator/../Expression/../Operator/COperator.h
CExpression.o: src/Expression/CExpression.cpp \
 src/Expression/CExpression.h src/Expression/../MathObject/CMathObject.h \
 src/Expression/../Variable/CVariable.h \
 src/Expression/../Operator/COperator.h \
 src/Expression/../Operator/../MathObject/CNumber.h \
 src/Expression/../Operator/CAdd.h src/Expression/../Operator/CSubtract.h \
 src/Expression/../Operator/CMultiply.h \
 src/Expression/../Operator/CDivide.h src/Expression/../Operator/CMod.h \
 src/Expression/../Operator/CBracket.h
CMathObject.o: src/MathObject/CMathObject.cpp \
 src/MathObject/CMathObject.h
CNumber.o: src/MathObject/CNumber.cpp src/MathObject/CNumber.h \
 src/MathObject/CMathObject.h
CAdd.o: src/Operator/CAdd.cpp src/Operator/CAdd.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CBracket.o: src/Operator/CBracket.cpp src/Operator/CBracket.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CDivide.o: src/Operator/CDivide.cpp src/Operator/CDivide.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CMod.o: src/Operator/CMod.cpp src/Operator/CMod.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CMultiply.o: src/Operator/CMultiply.cpp src/Operator/CMultiply.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
COperator.o: src/Operator/COperator.cpp src/Operator/COperator.h \
 src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CSubtract.o: src/Operator/CSubtract.cpp src/Operator/CSubtract.h \
 src/Operator/COperator.h src/Operator/../MathObject/CMathObject.h \
 src/Operator/../MathObject/CNumber.h
CTest.o: src/Test/CTest.cpp src/Test/../Calculator/CApplication.h \
 src/Test/../Calculator/CCalculator.h \
 src/Test/../Calculator/../Variable/CVariable.h \
 src/Test/../Calculator/../Variable/../MathObject/CMathObject.h \
 src/Test/../Calculator/../MathObject/CNumber.h \
 src/Test/../Expression/CExpression.h \
 src/Test/../Expression/../Operator/COperator.h \
 src/Test/../Operator/CAdd.h src/Test/../Operator/CMultiply.h \
 src/Test/CTest.h
CVariable.o: src/Variable/CVariable.cpp src/Variable/CVariable.h \
 src/Variable/../MathObject/CMathObject.h \
 src/Variable/../Expression/CExpression.h \
 src/Variable/../Expression/../Operator/COperator.h \
 src/Variable/../Expression/../Operator/../MathObject/CNumber.h
