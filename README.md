# 🛡️ RPG Projekt – Dokumentace

# O hře:

## 🎭 Třídy

- **Zloděj** – Nejlepší volba. Jeho staty jsou nic moc, ale má schopnost lifestealu - nejvíc OP schopnost třídy ve hře.
- **Mág** – Má silná kouzla, spoustu many, ale velice špatný útok. Nejlépe funguje proti osamělým monstrům s výsokým počtem životů.
- **Válečník** – Pevný tank, ale **nemůže používat manu**, což omezuje jeho schopnosti. Hodí se pro přímý boj, ale postrádá flexibilitu.
- **Paladin** – Vyvážený styl. Má nejlepší healovací schopnosti, ale není v ničem jiným extrémně silný.

---

## 👾 Monstra

- Každé **monstrum vybírá akce náhodně**.
- Typicky monstra mají schopnosti jako je direktní damage, heal, stun či imunitu.
- **Minibossové a hlavní boss** mají výhodu – **vždy začínají první**.
- Taktika a reakce hráče jsou klíčové. Ne vždy je nejlepší ihned vyplýtvat manu.

---

## 📈 Zkušenosti

- **XP jsou přidělovány náhodně.**
- Probíhá **na pozadí** – hráč nevidí přesný počet XP.
- Hráč zná pouze svůj **aktuální level**, nikoliv kolik chybí do dalšího.
- Za každý level up hráč podle náhody dostane + max životy, + manu nebo + útok.

---

## 🌸 Hlavní boss: *Bloomshade*

- **Na začátku nic nedělá.** Hráč musí zaútočit první.
- Po útoku se probudí a **začne růst květy** – každý tah je zdvojnásobí.
- **Květy se stackují rychle** – za 8 tahů může mít až **256 květů**.
- Má schopnost, kde za každý květ **udělí 1 dmg** – pokud nasbírá 16 384 květů, je dobré na chvíli přestat útočit, protože jestli hráč nenasbíral 17 000 životů, tuto schopnost nepřežije.
- Doporučuje se **občas neútočit**, aby se počet květů vynuloval.
- Některé jeho schopnosti můžou **snížit hráčův útok pod nulu**.
  - Jakmile se to stane, je **extrémně těžké dostat se zpět a začít dělat škodu** (prakticky jde to pouze s mágem, ale i to není vůbec lehké.).
  - Z toho vyplývá, že pokud na vás Bloomshade položí jeho květ, je dobré se ho **co nejrychleji zbavit**.
- Boj vyžaduje **opatrnost, pauzy a správné načasování útoku**.

---

# O kódu

## V kódu je použito pár advanced konceptů, viz níže
- Vectory -> Použito na pole, kde není jasné, jaká bude jeho velikost (a také v pár krajiních případech)
- Mapy -> Použito pro získávání hodnot, které itemy přidávají, aby se nemuselo neustále chodit do if statementů (např. player.health += items["Lékárna][1])

## V kódu je také napsáno několik funkcí usnadňující tvorbu kódu
- lower() -> převede string na malá písmena
- setColor() -> změní barvu textu v terminálu
- wait() -> zpozdí běh programu
- get_int() -> získá input od uživatele ve formě čísla, když uživatel zadá písmeno či slovo tak to tahle funkce chytí a donutí ho, aby zapsal číslo - jinak by se program začal chovat divně a musel by být restartován

## Pro správnou funkčnost tohoto programu je dobré ho spouštět na stejném setupu, jako byl vytvořen, a to tedy ve VSCode, se stejným nastavením jako je ve ./.vscode
    - Tato hra využívá diakritiku, takže pokud to daná sestava nepodporuje, stane se z toho enchant table language.

# To je vše
## Užijte si hraní hry :D