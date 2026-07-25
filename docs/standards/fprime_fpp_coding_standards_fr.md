# F´ / FPP Coding Standards and Style Guide (NASA JPL)

> Transposition des guidelines officielles de **F´ (F Prime)**, le framework de logiciel de vol open-source développé au JPL (utilisé notamment sur l'hélicoptère martien *Ingenuity*), et de **FPP (F Prime Prime / F″)**, son langage de modélisation.
>
> Sources :
> - *F´ Style Guidelines* — [github.com/nasa/fprime/wiki](https://github.com/nasa/fprime/wiki/F%C2%B4-Style-Guidelines)
> - *Code and Style Guidelines* (C++) — [nasa.github.io/fprime](https://nasa.github.io/fprime/UsersGuide/dev/code-style.html)
> - *FPP User's Guide* — [nasa.github.io/fpp](https://nasa.github.io/fpp/fpp-users-guide.html)
>
> ⚠️ Ces recommandations s'appliquent au code du **framework F´ lui-même**. Les projets qui *utilisent* F´ sont encouragés à les suivre, mais n'y sont pas obligés — à adapter selon le contexte du projet.

---

## 1. Introduction

F´ est un framework de logiciel de vol (*flight software*) pour systèmes embarqués — satellites, sondes, instruments, etc. La **fiabilité** est l'objectif numéro un : ces systèmes tournent souvent très longtemps sans possibilité d'intervention humaine en cas de panne logicielle.

Principe directeur : le code doit être **facile à lire et facile à relire (review)**. La complexité et l'optimisation ont un coût en lisibilité/maintenabilité — une solution plus simple est souvent préférable.

FPP (F Prime Prime, aussi appelé F″) est le **langage de modélisation** de F´ : il sert à décrire les types, ports, composants, instances de composants et topologies, puis génère du C++ et du JSON. Les fichiers `.fpp` et le C++ généré/écrit à la main partagent les **mêmes conventions de nommage**.

---

## 2. Conventions de nommage

### 2.1 Constantes, valeurs d'énumération, directives de compilation
- **Toutes en majuscules**, tokens séparés par `_` (underscore).

```cpp
#define MY_DEFINITION 1234

const U32 MY_CONSTANT = 3;

enum EnumType {
    VALUE_SUCCESS = ...,
    VALUE_FAILURE = ...
};
```

### 2.2 Variables locales et variables globales
- **lowerCamelCase** : commence par une minuscule, majuscule au début de chaque mot suivant.

```cpp
U32 myVariable = 2;
```

### 2.3 Variables membres
- Mêmes règles que les variables locales, **préfixées par `m_`**.

```cpp
U32 m_myMemberVariable;
```

### 2.4 Fonctions et méthodes (fonctions membres)
- **lowerCamelCase**, comme les variables locales.

### 2.5 Types, Components, Ports, Classes, Packages, Namespaces, Modules
- **PascalCase** : lettre initiale majuscule, majuscule au début de chaque mot.

```
Svc.ComStub   // forme FPP
Svc::ComStub  // forme C++
```

> Le module FPP, le namespace C++ et le nom du composant sont tous définis en PascalCase — c'est cohérent d'un langage à l'autre.

---

## 3. Structure des répertoires de module

Les constructs F´ sont chacun définis dans un **module**, et se répartissent en plusieurs catégories : **Types**, **Ports**, **Components**, **Topologies**. Les modules sont eux-mêmes regroupés en **packages** : `Fw` (framework), `Drv` (drivers), `Svc` (composants de service), etc.

### 3.1 Ports et Types
- Placés dans des sous-dossiers de package nommés `Ports` et `Types` respectivement.

```
Fw/Ports/SuccessPort/     ← module de port Fw.SuccessPort
```

### 3.2 Components
- Le dossier du module est placé **directement** dans le dossier du package.

```
Svc/ComStub/              ← composant Svc.ComStub
```

### 3.3 Topologies
- Placées dans le dossier `Top` du package de déploiement.

```
Ref/Top                   ← topologie Ref
```

---

## 4. Référencer les membres de classe

### 4.1 Membres d'instance
- Préfixer par `this->`.

```cpp
this->m_myMemberVariable = 1;
this->myMemberFunction();
```

### 4.2 Membres statiques
- Préfixer par le nom de la classe englobante.

```cpp
ClassName::m_myStaticVariable = 1;
ClassName::myStaticFunction();
```

---

## 5. C++ dans F´

Le C++ de F´ suit principalement le style **Embedded C++**, avec quelques déviations notables, et respecte les **JPL Coding Standards** (adaptés du C — voir les *Power of 10 Rules*). Le code cible le standard **C++11**, mais certaines fonctionnalités C++11 sont évitées pour rester compatible avec des implémentations incomplètes. Le formatage suit le style **ClangFormat Chromium**.

### 5.1 Usage de l'Embedded C++
Points fondamentaux du style embarqué utilisés par F´ :
1. **Pas d'exceptions** — le code doit compiler avec `-fno-exceptions`.
2. **Pas de templates ni de STL** (Standard Template Library).
3. **Pas de `typeid` ni de RTTI** (run-time type information).

### 5.2 Déviations par rapport à l'Embedded C++ standard
Pour plus de sécurité, de lisibilité et un développement C++ moderne :
1. Utiliser des **namespaces** pour réduire les conflits de nommage.
2. Utiliser `std::numeric_limits` pour les valeurs min/max (les implémentations template de `std::numeric_limits` sont approuvées).
3. Utiliser `static_cast`, `reinterpret_cast` et `const_cast` plutôt que le cast C-style dangereux ou `dynamic_cast`.
4. Usage limité de l'héritage multiple et des classes de base virtuelles est autorisé (voir §7).

### 5.3 JPL Coding Standards (héritage NASA/JPL Flight Software)
Règles supplémentaires adaptées des guidelines C, héritées du logiciel de vol NASA/JPL :

1. Pas de récursion ; pas de `GOTO`.
2. Les boucles doivent avoir une **borne fixe**.
3. Pas d'allocation dynamique de mémoire après l'initialisation.
4. Utiliser `FW_ASSERT` pour valider les entrées de fonction et les calculs.
5. Restreindre la portée des données au strict nécessaire.
6. Vérifier les valeurs de retour de fonction, ou les rejeter explicitement avec `(void)`.
7. Éviter le préprocesseur, surtout les usages complexes.
8. Préférer les implémentations `Fw` et `Os` (ex : `FW_ASSERT` et `Os::Mutex` plutôt que `cassert` et `std::mutex`).
9. Compiler **sans warnings, sans erreurs, sans échec d'analyse statique** (passer l'intégration continue).
10. Ne pas utiliser `Os::Task::delay` pour synchroniser des threads.
11. Les valeurs explicites d'énumération doivent être spécifiées **pour toutes les valeurs, ou pour aucune**.

### 5.4 Usage de C++11
F´ supporte C++11, mais certaines implémentations sont incomplètes :
1. De nombreuses fonctionnalités C++11 utilisent des templates en interne → préférer les implémentations `Fw`/`Os` pour ces fonctionnalités.
2. `std::atomic` est connu pour ne pas fonctionner dans certains cas → à éviter.

### 5.5 ClangFormat
- F´ utilise **ClangFormat** basé sur le style Chromium (fichier `.clang-format` fourni à la racine du dépôt).
- L'outil `fprime-tools` (>v3.1.1) fournit une commande wrapper autour de `clang-format`, à privilégier car elle gère correctement les modificateurs d'accès `PRIVATE`, `PROTECTED`, `STATIC` utilisés pour les tests unitaires en boîte blanche.
- Voir `fprime-util format --help`.

---

## 6. Documentation

- Chaque composant doit être documenté via un **Software Description Document (SDD)**, placé dans un sous-dossier `docs`, couvrant :
  1. Requirements (exigences)
  2. Design (conception)
  3. Implementation and Usage Notes (implémentation et notes d'utilisation)
- La documentation C++ est générée avec **Doxygen** : annoter fonctions et variables avec des commentaires de style Doxygen.
- Les APIs et bibliothèques C++ doivent être documentées pour produire une documentation Doxygen exploitable.
- Les composants suivent la même logique, mais c'est le SDD qui reste la documentation primaire.

---

## 7. Asserts, événements WARNING et FATAL

Le logiciel doit continuer à fonctionner correctement en cas de comportement hors nominal.

- **`FW_ASSERT`** (assertion runtime) : garantit l'intégrité du logiciel et ses hypothèses internes (arguments dans les bornes attendues, valeurs de retour cohérentes, contrôles de confiance). **Ne jamais** utiliser une assertion runtime pour valider une entrée utilisateur ou le résultat d'une interaction matérielle — ces cas peuvent produire des erreurs hors du contrôle du logiciel.
- Dans ces cas (entrée utilisateur, matériel), il faut plutôt **émettre un événement** pour signaler l'erreur, et le logiciel doit continuer à s'exécuter de manière appropriée même en cas d'entrée erronée.

Sévérité des événements :
| Sévérité | Signification |
|---|---|
| `WARNING_LO` | Problème localisé à ce composant, récupération possible. |
| `WARNING_HI` | Problème affectant un système plus large, récupération possible. |
| `FATAL` | Problème non récupérable — le système est généralement redémarré. |

⚠️ Les événements `WARNING_HI` et `FATAL` doivent être documentés dans le SDD et approuvés lors de la revue de soumission (code review).

---

## 8. Héritage multiple et classes de base virtuelles

De nombreux constructs F´ doivent hériter d'une classe autogénérée (autocoded), elle-même héritant des classes de base du framework. Cela peut poser problème pour hériter d'autres structures — un héritage multiple limité est donc permis.

Règles de base (l'usage de l'héritage multiple sera probablement discuté en revue de soumission) :
1. N'utiliser l'héritage multiple que si c'est **absolument nécessaire**.
2. Éviter d'hériter de **plus d'une** classe écrite à la main.
3. Éviter d'hériter de descendants écrits à la main de classes autogénérées et de leurs parents (ex : `Fw::PortBase`, `Fw::PassiveComponentBase`) — c'est-à-dire éviter d'hériter d'autres Components, Ports, ou classes qui en héritent déjà.
4. Éviter les chemins d'héritage multiples menant à une base commune (le **problème du diamant**).

Usage normal de l'héritage multiple/virtuel dans F´ : mettre en place des **interfaces** (comme en Java) — une classe de base virtuelle C++ ne définissant que des fonctions. Une classe ou un composant F´ utilise alors l'héritage multiple pour hériter de ces définitions de fonction et les implémenter. Cela permet de faire le pont entre la fonctionnalité F´ autogénérée et la fonctionnalité C++ écrite à la main (ex : un composant peut exposer une fonctionnalité d'appel de port F´ à des classes support via ce type d'interface).

---

## 9. Python

- Le code Python est formaté avec **black**.
- Le code doit **passer un contrôle de formatage black**.
- Pour formater : installer `black` (voir le *Python Development Guide*) puis exécuter `black <chemin_du_code>`.

---

## Annexe — Tableau récapitulatif des conventions de nommage

| Élément | Convention | Exemple |
|---|---|---|
| Constantes / valeurs d'enum / directives préprocesseur | `ALL_CAPS_AVEC_UNDERSCORE` | `MY_CONSTANT`, `VALUE_SUCCESS` |
| Variables locales / globales | `lowerCamelCase` | `myVariable` |
| Variables membres | `m_` + `lowerCamelCase` | `m_myMemberVariable` |
| Fonctions / méthodes | `lowerCamelCase` | `myMemberFunction()` |
| Types, Components, Ports, Classes, Packages, Namespaces, Modules | `PascalCase` | `Svc.ComStub` / `Svc::ComStub` |

---

## Références

1. *F´ Style Guidelines*, NASA/JPL — https://github.com/nasa/fprime/wiki/F%C2%B4-Style-Guidelines
2. *Code and Style Guidelines*, F´ User's Guide — https://nasa.github.io/fprime/UsersGuide/dev/code-style.html
3. *The F Prime Prime (FPP) User's Guide* — https://nasa.github.io/fpp/fpp-users-guide.html
4. *The F Prime Prime (FPP) Language Specification* — https://nasa.github.io/fpp/fpp-spec.html
5. *Power of 10 Rules*, Gerard J. Holzmann, JPL Laboratory for Reliable Software.
6. Bocchino, R., *"FPP: A Modeling Language for F Prime"*, IEEE Aerospace Conference, 2022.