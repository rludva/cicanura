# C Test Framework & API
C Test je jednoduchý aplikační framework pro psaní testů k programům v jazyce C.
Bylo jednodušší z důvodu obnovení znalostí s jazykem C si napsat tento framework, než-li se učit již nějaký existující.
Bylo to také mnohem dobrodružnější a zajímavější.

Todo:
* Najít způsob jak napsat ctest assert, který zjišťuje definici funkce.

Samotný frame work je použit v aplikaci, která spouští testy, tato aplikace tzv. test runner je umístěna ve zdrojovém souboru ./test_runner.c a jsou v ní obsaženy deklarace všech registračních funkcí, které registrují testovací funkce.
Samotné registrační funkce jsou obsaženy vždy ve zdrojovém kódu příslušné aplikace v níž je C Test Framework použit. Je nutné tedy ručně dopsát deklaraci této registrační funkce a napsat její volání a také dopsat do Makefile vzoru připojení objectového souboru s touto funkcí a všemi potřebnými dalšími zdroji.

Termín:
* Assert
* Test
* Testovací funkce
* Kolekce assertů
* Kolekce testovacích funkcí

Datové struktury:
* struct collection *ta_collection;
* struct collection *tf_collection;

* int asserts_count;
* int asserts_pass_count;
* int asserts_fail_count;


Přehled funkcí:
* int ctest_open()

* struct test_assert *ctest_test_assert_new(int count, int result, char *nazev);
* struct test_function *ctest_test_function_new(char *nazev, char *kategorie, int (*funkce)());
* void ctest_test_assert_delete(void *ptr);
* void ctest_test_function_delete(void *ptr);

* int ctest_close();

* void increment_asserts_count(int result);
* int ctest_test_assert_add(int result, char *message);
* int ctest_test_functions_add(char *nazev, char *kategorie, int (*function)());

* int ctest_ls_fails();
* int ctest_ls();

* int ctest_assert_fail(char *message)
* int ctest_assert_pass(char *message)

* int ctest_assert_true(int avalue, char *message);
* int ctest_assert_zero(int avalue, char *message);
* int ctest_assert_null(void *avalue, char *message);
* int ctest_assert_ptr(void *avalue, char *message);

* int ctest_run();

* int ctest_get_asserts_count();
* int ctest_get_asserts_pass_count();
* int ctest_get_asserts_fail_count();

* int ctest_print_asserts_count();

## int ctest_open();
Funkce pro otevření datových struktur aplikačního frameworku C Test a jejich inicializaci.
Je třeba vždy před použitím funkcí z tohoto API volat na začátku programu tuto funkci.
Obvykle je použita v běhovém procesoru, který spouští jednotlivé testy, tzv. test_runner.

V případě úspěchu a správné alokace paměti pro všechny datové struktury vrací 0.

## Funkce struct test_assert *ctest_test_assert_new(int result, char *nazev);
Funkce pro vytvoření nové instance objektu, který je ukazatelem na datovou strukturu test_asser.
Funkce je využita ve funkci pro přidání nového assertu, který bude součástí zpracovaných testů.

## Funkce struct test_function *ctest_test_function_new(char *nazev, char *kategorie, int (*funkce)());
Funkce pro vytvoření nové instnace objektu, který je ukazatelem na datovou strukturu test_function.
Funkce je využita ve funkci pro registraci testovacích funkcí.

## Funkce void ctest_test_assert_delete(void *ptr); a void ctest_test_function_delete(void *ptr);
Tyto funkce se postarají o uvolnění datové struktury pro ukazatele na strukturu test_assert a test_function.
Datová struktura test_assert obsahuje dynamicky alokovanou paměť pro zprávu o assertu a datový struktura test_function obsahuje dynamicky alokovanou paměť pro popis testovací funkce a název její kategorie.
Samotné funkce jednotlivé položky alokované přes malloc uvolní voláním funkce free a následně uvolní z paměti i obsah na který ukazuje samotný ukazatel na instanci objektu se strukturou (objektu v uvozovkách..).

## int ctest_close();
Funkce ctest_close uvolňuje z paměti veškeré datové struktury, které byly během procesu využívání C Test Framework alokovány.
Zejména volá uvolnění paměti pomocí funkce free pro ukazatele na struktury ta_collection a tf_collection.
Před uvolněním paměti však volá rušení všech objektů v těchto kolekcích pomocí funkce collection_object_delete, která uvolní všechny objekty test_assert a test_function.
Volání funkce ctest_close musí předcházet volání funkce ctest_open, která inicializuje data.
Po uvolnění paměti jsou ukazatele na kolekce ta_collection a tf_collection nastaveny NULL na.

## Funkce pro asserty
Každá funkce, která něco testuje, musí následně zkontrolovat výsledek a skutečnost oproti tomu co očekává.
Za tímto účelem jsou vytvořeny sady assert funkcí, které jako parameter přijímají hodnotu a popis očekávaného výsledku.
Pokud hodnota není spolněna vůči očekávané hodnotě je test vyhodnocen jako neúspěšný, TEST_FAIL.
Pokud je hodnota stejná jako očekávaná hodnota, je test úspěšný, TEST_PASS.

Typické použití assert funkce v kódu může vypadat následovně:

```C
//
{
	char *assert_message = "Číslo je sudé..";
	int assert_result = (number % 2) ? TRUE : FALSE;
	ctest_assert_true(assert_result, assert_message);
}
```

Jedna testovací funkce může obsahovat teoreticky několik assertů, je otázkou zda to je správně, ale dle mého názoru se během procesu testování může testovat několik oarametrů v řadě tak jak je výpočet prováděn.

### int ctest_test_assert_print(struct test_assert *ptr);
Funkce ctest_test_assert_print jen zobrazuje assert na standardní výstup.

### void increment_asserts_count(int result); [vlastní funkce]
Přidání dalšího assert a incrementace počítadel dle výsledku uloženého do proměnné result.
Poukd je result TEST_PASS je incrementováno asserts_pass_count.
Pokud je result TEST_FAIL, tak je inkrementávno asserts_fail_count.
Dále je inkrementován celký počet assertů, který je uložen v proměnné asserts_count.

### int ctest_test_assert_add(int result, char *message);
Interní funkce, která přidá nový assert do kolekce všech spuštěný assertů..

### int ctest_assert_fail(char *message);
Funkce ctest_assert_fail je vždy selhávajícím assertem.
Možná je nelogické mít takovouto funkci vytvořenou, ale např. v sytuaci kdy test ještě není naprogramovaný nám nic jiného nezbývá.

### int ctest_assert_pass(char *message);
Funkce ctest_assert_pass je vždy úspěšný assert.
Také zde podobně jako u funkce ctest_test_assert_fail se může zdát být nelogické mít takovou funkci, ale v případě že program dál pokračuje a nedošlo k nějakému katastrofálnímu selhání může být toto tímto assertem zaznamenáno.

### Korektní assert funkce

#### int ctest_assert_true(int avalue, char *message);
Test je úspěšný pokud avalue je TRUE.
TRUE je přitom definováno v ctest.h jako 1 a hodnota FALSE jako 0.
Je třeba zde být opatrný, protože je většinou obecně přijímáno jako TRUE cokoliv co je nenulové, ale v samotném assert, který zkoumá avalue je přímo if(avalue == TRUE), takže pokud platí, že avalue > 1, tak se test vyhodnotí jako TEST_FAIL.

#### int ctest_assert_zero(int avalue, char *message);
Test je úspěšný pokud avalue je rovno nule.

#### int ctest_assert_null(void *avalue, char *message);
Test je úspěšný pokud avalue je NULL.

#### int ctest_assert_ptr(void *avalue, char *message);
Test je úspěšný pokut avalue ukazuje na ne NULL hodnotu.

## Postup registrace testovací funkce

Pokud máme funkci s testem, tak je třeba tuto funkci zaregistrovat.
V Konkrétním modulu např. když testujeme funkci pro přidání zákazníka test_customers_add(char *name) provedemi registraci této funkce pomocí ctest_test_customer_register:

```C
///
int test_customer_add()
{
	ctest_assert_fail("Test is not implemented!");
}

///
void ctest_test_customer_register()
{
	ctest_register_test_function("Testovací funkce popis..", "customer", &test_customer_add);
}
```

Jakmile máme registrační funkci v testovacím zdrojovém souboru zapsanou, tak ji musíme deklarovat a volat pro test_runner.c.
Dále je nezbytné dopsat kompilaci této funkce do Makefile celého projektu!

# Výsledný test runner musí mít k dispozici objektové soubory customer a test_customer!

```Makefile
test: ./customer.o ./test/test_customer.o ./cicanura/test/test_collection.o ./cicanura/test/test_strings.o ./cicanura/test/test_ctest.o ./cicanura/test_runner.o
	cc -o ./cicanura/test_runner ./customer.o ./test/test_customer.o ./cicanura/test/test_collection.o ./cicanura/test/test_strings.o ./cicanura/test/test_ctest.o ./cicanura/test_runner.o ./cicanura/ctest.o ./cicanura/collection.o ./cicanura/strings.o
```

# Přidání položky customer a test_customer do Makefile

```Makefile
customer.o: customer.c customer.h
test_customer.o: ./test/test_customer.c customer.o
```

