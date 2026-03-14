if [ "$1" = "--wine" ]; then
    CC='wine ../cw/mwcceppc.exe'
else
    CC='../cw/mwcceppc.exe'
fi

$CC -i . -I- -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o kamekLoader.o kamekLoader.cpp
$CC -i . -I- -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o smg1_smg2.o -DSMG1 -DSMG2 smg1_smg2.cpp

../Kamek kamekLoader.o smg1_smg2.o -static=0x80004744 -output-code=loader.bin -output-riiv=loader.xml -valuefile=Code/loader.bin

# Or to inject directly into a DOL:
# ../Kamek kamekLoader.o smg1_smg2.o -static=0x80004744 -input-dol=smg.dol -output-dol=smg_kamek.dol
