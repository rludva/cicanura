# Bunkai Ichi
Bunkai Ichi je cvičná aplikace v jazyce C (dříve Bunkai C), která integruje testovací API C Test do aplikací vytvářených v jazyku C.
Samotná Bunkai Ichi obsahuje jen jednu jednou metodu hello a ve složce pro test její testovací funkci společně s registrační funkcí, která registruje testovací funkci do C Test API.

Pokud budeme chtít toto bunkai použít jako šablonu, tak je třeba příslušným způsobem upravit i Makefile, tak aby překládal zdrojový kód budoucí aplikace správně.

Přehled důležitých souborů:
* ./bunkai_ichi.c
* ./test/test_bunkai_ichi.c
* ./Makefile
