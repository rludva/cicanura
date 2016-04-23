# collection

Modul collection obsahuje sadu datových struktur a funkcí, které umožňí dynamickou práci s objekty, přidávat je do kolekce ve které se s nimi dále manipuluje.
Motive pro vytvoření modulu collection byl micro framework pro vytváření testů k testy řízenému vývoji.
Bylo potřeba někam ukládat výsledky testů, registrovat testovací funkce, a pak pracovat rozumě s proběhnutými testy při procházení jejich výsledků.

Přehled funkcí pro collection:
* struct collection_item *collection_item_new();
* struct collection *collection_new();
* int collection_delete(struct collection *ptr);
* int collection_add(struct collection *ptr, void *object);
* void collection_object_delete(struct collection *ptr, void (*function)(void *object));
* int collection_foreach(struct collection *ptr, int (*function)(void *object));

Přehled datových struktur pro collection:
* Struktura collection
* Struktura collection_item

## Struktura collection

```C
//
struct collection
{
	//
	struct collection_item *first_item;
	struct collection_item *last_item;

	//
	int length;
};
```

Struktura kolekce obsahuje společné informace pro všechny položky kolekce.
Těmito informacemi je ukazatel na první a poslední položku kolekce a dále počet položek v kolekci.

## Struktura collection_item

```C
//
struct collection_item
{
	void *object;
	void *next;
};
```

Struktura pro položku kolekce obsahuje ukazatel na objekt, který je do kolekce vložen a ukazatel na další položku kolekce.

## struct collection_item *collection_item_new();
Pomocná funkce pro vytvoření nové položky do kolekce, tedy instanci struktury collection_item.

## struct collection *collection_new();
Pro vytvoření nové kolekce je třeba nejdříve připravit a rezervovat paměť a základní identifikátory kolekce, jako např. počet provků v kolekc (length).
To zabezpečí právě volání collection_new, které vrátí ukazatel na takto připravenou paměť.

Kolekci je poté nutné uvolnit z paměťi voláním funkce collection_delete.
Pokud jsou objekty v kolekci dynamické, tak je možné připravit funkci, která objekty z paměti uvolní během rušení samotných položek kolekce.
Tato funkce se pak nastaví pomocí collection_object_delete.

## Funkce int collection_delete(struct collection *ptr);
Odstranit kolekci z paměti je celkem náročná záležitost.
Je nutné projít všechny položky kolekce a odebrat je.

Samotných objektů vložených do kolekce se uvolňování z paměti netýká, není možné znát jejich strukturu a množství paměti, kterou je třeba uvolnit pro neznámou strukturu objektu vloženýh do kolekce.
Kolekci je totiž znám jen a pouze ukazazel na tento objekt a nic více.
Pokud je potřeba objekty z kolekce odstranit dynamicky, je dobré to udělat ještě před voláním funkce collection_delete a sice s použitím funkce collection_object_delete.


## Funkce int collection_add(struct collection *ptr, void *object);
Metoda přidá do kolekce novou položku a ukazatel na objekt této položky uloží do ní.
Nová položka je přidána na konec, tzn. že bude v pořadí poslední.

## Funkce void collection_object_delete(struct collection *ptr, void (*function)(void *object));
Pokud kolekce obsahuje dynamicky vytvořené objekty, které je třeba z paměti uvolnit, tak je toto možné zapsat do funkce a ukazatel na tuto funkci předat jako parametr funkci collection_object_delete.
Tato funkce je pak zodpovědná za uvolnění paměti pro objekt obsažený v kolekci.
Tento objekt může být libovolně strukturován např. (jméno, adresa, datum narození, atd.).
Následně po uvolnění nastaví do položky kolekce s ukazatelem na tento objekt hodnotu NULL, takže položky v kolekci neodkazuje na žádný regulérní objekt.

## Funkce int collection_foreach(struct collection *ptr, int (*function)(void *object));
Pokud je potřeba nad všemi objekty vloženými do kolekce vykonat nějaký kód, tak tento je možné zapsat do funkce a předat funkci collection_foreach ukazatel na tuto funkci.
Nejlépe se toto dělá např. pomocí vnořené funkce a je to použito v testovacím API C Test pro vypsání provedných assertů:

```C
///
int ctest_ls_fails()
{
	///
	int function(void *object_ptr)
	{
		//
		struct test_assert *ta_pointer = (struct test_assert *) object_ptr;

		//
		if(ta_pointer)
		{
			//
			if(ta_pointer -> result)
			{
				printf("Test %u has field: '%s'\n", ta_pointer -> count, ta_pointer -> message);
			}
		}
	}

	//
	collection_foreach(ta_collection, &function);

	//
	return 0;
}
```
