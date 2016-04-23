# Strings
Funkce pro práci s textovými řetězci jsou umístěny v modulu strings.

Tento modul obsahuje funkce:
* char *strings_new(char *src);
* int strings_free(char *src);

## Funkce char *strings_new(char *src);
Tato funkce alokuje paměť pro ukazatel na textový řetězec zakončený znakem '\0' a překopýruje obsah řetězce do alokované paměti.
Paměť je alokováná pomocí volání malloc a je nutné ji uvolnit voláním funkce strings_free. Funkce vrací ukazatel na takto nově alokovanou paměť se zkopírovaným texovým řetězcem.
Pokud paměť není možné alokovat je vrácen ukazatel NULL.

## Funkce int strings_free(char *src);
Tato funkce uvolní z paměti dříve alokovanou paměť pro text voláním funkce free.
Funkce vždy vrací 0.
