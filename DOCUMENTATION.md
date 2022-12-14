# Grafické RPG

## Zadání z Progtestu

Naprogramujte engine pro grafické RPG

Váš engine:

* ze souboru nahraje definici světa (mapu, předměty, příšery, ...)
* umožní vytvořit herní postavu (její atributy a schopnosti) a následnou hru
* implementuje jednoduchý soubojový systém a inventář
* umožňuje ukládat a načítat rozehrané hry

Engine může fungovat jako real-time hra, či tahová hra.

Jak může vypadat mapa?

`# označuje zeď, T označuje truhlu s pokladem, > označuje pozici (směr otočení) hráče.`

```
###################
# T   #      #    #
#           ###   #
#     ##   #      #
#     #       # > #
###################
```

### Kde lze využít polymorfismus? (doporučené)

* Soubojové vlastnosti: postava, příšera, stroj (např. past, bomba,...)
* Efekty akcí: souboje, události (pád ze stromu,...), přechod do jiné místnosti
* Inventář: postava, batoh, toulec, kapsa
* Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

### Ukázky:

* https://en.wikipedia.org/wiki/Hack_(video_game)
* https://www.mobygames.com/game/heroes-of-might-and-magic
* http://www.drd2.cz/
* Dungeons & Dragons

## Upřesnění zadání

Pro RPG jsem se rozhodl použít knihovnu SDL. Při vytváření se snažím co nejvíce SDL zabalit do vlastních tříd, abych ho
nevolal napřímo tam, kde to není nutné. Bude pak jednodušší renderer vyměnit. Hra bude mít menu, kde půjde vytvořit
novou hru, načíst již uloženou, nebo hru opustit. Samotná hra pak bude „turn based“ plošinovka ovládaná klávesami
šipek. Mapa bude mít několik sekcí, mezi nimi bude moct hráč procházet. Na mapě se budou nacházet různá monstra,
která půjdou po hráči, avšak mezi sekcemi procházet nesmí. Pokud se s hráčem střetnou, bude se s nimi muset hráč
vypořádat.

Hráč bude mít implementován jednoduchý inventář (např. klíče do dveří), bude mít zbraň (bude existovat více typů zbraní)
a bude mít nějaké atributy. Atributy mu bude moci uživatel nastavit při vytváření nové hry. Tyto atributy budou
ovlivňovat
jeho sílu a výdrž.

Soubojový systém bude opravdu jednoduchý, hráč bude bojovat pomocí mezerníku a to vyvolá reakci monstra, které zaútočí
zpět.
Kdo bude první na tahu bude vybráno náhodně.

Hra se dá pozastavit stisknutím esc. Dostaneme se tak do menu, kde můžeme hru obnovit, odejít do hlavního menu a, pokud
nejsme v souboji, hru uložit.

Mapu lze načíst ze souboru. Lokace souboru mapy bude součástí save filu. Mapa specifikuje pozici hráče, monstra, sekce a
výchozí sekci po načtení.

Polymorfismus využívám hojně pro rendrování všech entit na obrazovku. Každá entita dědí ze třídy Entity, buď přímo a
nebo
přes jednoho až více sub-entit, které jim přidají různé možnosti (animace, entita, co může hráč zvednout, pohybující se
entita…).
Ve hře je využit polymorfismus i jinde, na graf tříd se lze podívat pomocí make doc, jelikož v projektu je nastaven
Doxygen.
Momentálně projekt neobsahuje moc dokumentace, ta ale ještě přibude.

## Zdroje assetů

Většinu textur jsem vytvořil sám.
Vyjímky:

* https://betterttv.com/emotes/5b1740221c5a6065a7bad4b5
* ikona hráče od Jovana Laníka, zdroj ze soukromé zprávy
* pozadí z: https://itch.io/game-assets/tag-pixel-art
* font: https://managore.itch.io/m5x7
