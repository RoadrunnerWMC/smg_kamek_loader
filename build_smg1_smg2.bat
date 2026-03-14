..\cw\mwcceppc.exe -i . -I- -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o kamekLoader.o kamekLoader.cpp
..\cw\mwcceppc.exe -i . -I- -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o smg1_smg2.o smg1_smg2.cpp

..\Kamek kamekLoader.o smg1_smg2.o -static=0x80004744 -output-code=loader.bin -output-riiv=loader.xml -valuefile=Code/loader.bin

REM Or to inject directly into a DOL:
REM ..\Kamek kamekLoader.o smg1_smg2.o -static=0x80004744 -input-dol=smg.dol -output-dol=smg_kamek.dol

