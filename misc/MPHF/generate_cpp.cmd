xcopy /y/i Input\* .\

perfect -dm < NormalMap_keys.txt
make -f makekeys
output -dm < NormalMap_keys.txt
ren hash_keys.txt hash_keys_np.txt
ren phash.h npHash.h
ren phash.c npHash.c

perfect -dm < ShadowVolume_keys.txt
make -f makekeys
output -dm < ShadowVolume_keys.txt
ren hash_keys.txt hash_keys_sv.txt
ren phash.h svHash.h
ren phash.c svHash.c

cpp_edit
HashTableReparser

move /y npHash.h Output\
move /y npHash.c Output\
move /y svHash.h Output\
move /y svHash.c Output\
move /y np_cpp.txt Output\
move /y sv_cpp.txt Output\

clean

pause