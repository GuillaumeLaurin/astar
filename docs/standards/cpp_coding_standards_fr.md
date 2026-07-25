# C++ Coding Standards and Style Guide (GMAT Project)

> Basé sur le document *"C++ Coding Standards and Style Guide"* (Mission Applications Branch — Code 583), modifié pour le General Mission Analysis Tool (GMAT).
> Ce document s'appuie sur le "C Style Guide" (SEL-94-003) et le complète/remplace pour le C++.

---

## 1. Introduction

### 1.1 Objectif
Décrire le style recommandé pour écrire des programmes C++, où un « bon style » signifie du code :
- Organisé
- Facile à lire
- Facile à comprendre
- Maintenable
- Efficace

### 1.2 Public visé
Développeurs C++ du projet, mais applicable plus largement.

### 1.3 Terminologie
- **Méthode** : fonction membre d'une classe.
- **Interface de classe** : déclaration de classe dans le fichier d'en-tête (header).
- **Implémentation de classe** : définition de classe dans le fichier source.

---

## 2. Noms

Principe général : choisir des noms **significatifs et lisibles**.

- Abréviation en majuscules OU première lettre majuscule + reste en minuscules — être cohérent.
- **Éviter les underscores** dans les noms (sauf exceptions ci-dessous).

### 2.1 Noms de classes
- Première lettre de chaque mot en majuscule (`PascalCase`).
- Un composant GUI doit être suffixé par le nom du composant parent : `class DisplayPanel : public Panel`.
- Les classes d'exception doivent être suffixées par `Exception` : `InvalidEulerSequenceException`.

### 2.2 Noms de bibliothèques de classes
- Utiliser des **namespaces** pour éviter les collisions de noms.
- Peu d'usages d'un namespace → utiliser l'opérateur de portée `::`.
- Usages nombreux → utiliser une clause `using` pour éviter d'encombrer le code.

### 2.3 Noms d'instances de classes
- Suivre les conventions des variables.

### 2.4 Noms de méthodes / fonctions
- Toujours des verbes, en mixed case commençant par une majuscule : `Normalize()`, `OutputCalibrationData()`.
- Préfixes utiles :
  - `Is/Has/Can` → question retournant un booléen
  - `Set/Get` → accesseurs
  - `Initialize` → initialisation d'un objet
  - `Compute` → calcul
- Ne pas dupliquer le nom de la classe dans le nom de méthode : `Vector::Normalize()`, PAS `Vector::NormalizeVector()`.
- Coder à partir d'une spec formelle → garder les noms de la spec, sans underscore.

### 2.5 Noms d'arguments de méthodes/fonctions
- Mêmes règles que pour les variables.
- Un argument de type classe peut porter le même nom que son type, sinon rester succinct :
  `void SetForceModel(ForceModel *forceModel)` ou `*fm`.

### 2.6 Noms de namespaces
- Mêmes règles que pour les classes.
- Préfixer par le nom du projet : `namespace GmatTimeUtil`.

### 2.7 Variables
- `camelCase` : première lettre minuscule, puis majuscule à chaque mot suivant.
  `double flatteningCoefficient;`
- Commenter la déclaration si le nom ne suffit pas à comprendre.
- Déclarer les variables au niveau où elles sont utilisées (variable locale à un bloc → déclarée dans ce bloc).
- Commenter les unités si elles ne sont pas dans le nom (ex : `initialPositionInKm`).
- Indice de boucle : déclaré dans le `for` ou au-dessus si réutilisé après la boucle.
- Préférer les types définis par le projet aux types natifs pour les indices (`Integer` plutôt que `int`).

#### 2.7.1 Variables pointeurs
- Placer le `*` avec le nom de variable, pas avec le type :
  `MAB::String *name = new MAB::String;`
- Faire attention aux conversions de pointeurs (base → dérivé) — *pour la portabilité*.
- Utiliser `NULL` pour un pointeur nul.

#### 2.7.2 Variables référence
- Placer le `&` avec le nom de variable :
  `MaString(const MaString &maString, unsigned int bufferLength = 0)`
- Pour les opérateurs surchargés et méthodes retournant une référence, placer le `&` avec le **type** :
  `const MaString& operator= (const char *string);`

#### 2.7.3 Variables globales
- À éviter. Utiliser des namespaces à la place.

### 2.8 Noms de types
- Première lettre de chaque mot en majuscule :
  `typedef unsigned int SystemType;`

### 2.9 Types énumérés et noms d'énumérations
- Les types enum suivent la règle des noms de classe.
- Les valeurs d'enum sont en MAJUSCULES avec underscores :
  `enum Colors {RED = 3, BLUE, DARK_BLUE, GREEN, DARK_GREEN, YELLOW = 7};`

### 2.10 Constantes / `#define`
- MAJUSCULES avec underscores : `const int MINIMUM_NUMBER_OF_BYTES = 4;`
- Éviter `#define` → préférer `const` ou des énumérations (exception : compilation conditionnelle de debug).

### 2.11 Noms de structures
- Convention des noms de classe + suffixe `Type` : `struct TimeType { ... };`
- Préférer les classes aux structs, sauf si toutes les données sont publiques.
- Les structs peuvent encapsuler des données globales (y compris des exceptions).

### 2.12 Noms de fonctions C
- Minuscules avec `_` comme séparateur : `get_best_fit_model()`.
- Très peu de fonctions C dans un programme C++ (interface C/C++ uniquement).

### 2.13 Noms de fichiers C++
- Header : `.hpp`
- Header compatible C et C++ : `.h`
- Source : `.cpp`
- Le nom de fichier doit correspondre au nom de la classe : `AnalyticalModel.hpp` / `AnalyticalModel.cpp`.

### 2.14 Noms de fichiers générés
- Ne pas modifier la convention de nommage des fichiers générés par d'autres outils (ex : wxWidgets).

---

## 3. Formatage

Principes généraux :
- Lignes blanches pour organiser le code en paragraphes.
- Limiter la complexité des instructions (les découper si besoin).
- Indenter pour montrer la structure logique.

### 3.1 Variables
- Une seule variable déclarée par ligne.

### 3.2 Accolades `{}`
- Utilisées pour tous les blocs. Accolade ouvrante sur la ligne suivante, alignée avec le mot-clé.

```cpp
for (j = 0; j < MAX_NUMBER_OF_ITERATIONS; j++)
{
    statement1;
    statement2;
    ...
}

class SolarSystemBody
{
    statement1;
    statement2;
    ...
};
```

### 3.3 Parenthèses `()`
- Toujours entourer une condition de parenthèses.
- Mettre un espace entre un mot-clé et les parenthèses.

### 3.4 Indentation
- 3 ou 4 espaces (3 fortement suggéré).
- Espacement logique si l'indentation standard n'est pas praticable.
- Aligner les variables lorsqu'il y a plusieurs déclarations groupées.

### 3.5 Tabulation / Espace
- **Ne pas utiliser de tabulations** — uniquement des espaces.
- Un espace après une virgule et un point-virgule.
- Un espace autour des opérateurs d'affectation.
- Un espace entre un mot-clé et une parenthèse : `if ( )`, `while ( )`.
- Un espace autour des opérateurs conditionnels : `z = (a > b) ? a : b;`
- Pas d'espace avant les parenthèses suivant un nom de fonction : `z = exp(2, x)`.
- Pas d'espace entre les opérateurs unaires et leurs opérandes : `++i`, `-n`, `*p`, `&x`.
- Pas d'espace autour des opérateurs primaires : `->`, `.`, `[]`.

### 3.6 Lignes blanches
- Utiliser des lignes blanches pour créer des paragraphes dans le code ou les commentaires.

### 3.7 Arguments de méthode/fonction
- Si les arguments ne tiennent pas sur une ligne, aligner le premier argument sur chaque ligne (ou aligner avec le nom de la méthode si nécessaire).

```cpp
void SomeFunction(unsigned int someCounter, double someScaleFactor,
                  int someOtherArgument,
                  const SolarSystemBody &solarSystemBody,
                  int theLastArgument);
```

### 3.8 If / If else
- Indenter d'un niveau avec accolades. Pour une seule instruction, les accolades sont optionnelles.
- Utiliser des comparaisons explicites :
  `if (theFile->EndOfData() != true)` plutôt que `if (!theFile->EndOfData())`.
- Toujours utiliser des accolades pour les `if` imbriqués.

### 3.9 Switch
- Toujours avoir un `default` (même si c'est juste une sortie d'erreur fatale).
- `default` en dernier, sans `break` obligatoire (mais recommandé pour la cohérence).
- Le fall-through entre `case` est permis si un commentaire l'indique.
- Si des variables sont nécessaires dans un `case`, les mettre dans un bloc `{ }`.

```cpp
switch (expression)
{
   case aaa:
      statement[s]
      break;

   case bbb:      // fall through
   case ccc:
   {
      int v;
      statement[s]
      break;
   }

   default:
      statement[s]
      break;
}
```

### 3.10 For / While
- Indenter d'un niveau avec accolades ; optionnel pour une seule instruction.

### 3.11 Break
- Peut être utilisé pour sortir d'une boucle interne (`for`, `while`, `do`, `switch`) à un point de rupture logique.

### 3.12 Utilisation de `goto`
- **Ne pas utiliser `goto`.**

### 3.13 Utilisation de `?:`
- Acceptable tant que ce n'est pas trop complexe.
- Mettre la condition entre parenthèses pour bien la distinguer du reste du code.

### 3.14 Instruction `return`
- Plusieurs `return` autorisés si cela rend le code plus efficace *(pour l'efficacité)*.
- Retourner directement une expression (y compris un appel de constructeur) est plus efficace que de déclarer une variable locale puis de la retourner *(pour l'efficacité — évite un appel copy-constructor/destructeur)*.

### 3.15 Nombre maximal de caractères par ligne
- **80 caractères maximum.**

---

## 4. Documentation

Deux publics principaux : les **utilisateurs de classe** et les **implémenteurs/mainteneurs**.

- Niveau programme : fichier **README** (description générale, organisation).
- Niveau fichier : **prolog de fichier** (purpose, informations).
- Header : **prolog de méthode** pour toutes les méthodes virtuelles pures.
- Source : **prolog de méthode** pour toutes les autres méthodes.
- Commenter les déclarations/définitions de données pour en expliquer le but.

### Doxygen
- Utiliser [Doxygen](http://www.doxygen.org) pour extraire automatiquement la documentation.
- Suivre la convention JavaDoc pour les blocs de commentaires.
- `JAVADOC_AUTOBRIEF = YES` dans la config Doxygen → la description brève se termine au premier point suivi d'un espace ou d'une nouvelle ligne.

```cpp
/**
 * brief description.
 * detailed description.
 */
```

Description brève sur une ligne :
```cpp
/// one line brief description
```

⚠️ Les commentaires commençant par `//` **n'apparaissent pas** dans la documentation générée.

### 4.1 Prolog de fichier header
- Tout header doit commencer par un prolog.
- Pas de PDL (Program Design Language) au niveau fichier — remplacer par du code bien documenté.
- Sections du prolog (pas de section "historique des changements" car géré par CVS) :
  - `<CVS Keyword>` → `$Header$`
  - `<Class Name Banner>` (pour un header de classe)
  - `<Project Name>` → `GMAT: General Mission Analysis Tool`
  - `<Legal Tag>` → `**Legal**`
  - `<Author>`
  - `<Created>` → `yyyy/mm/dd`
  - `<Class Description>` (bloc JavaDoc)
  - `<Note>` (optionnel)

Exemple :
```cpp
//$Header$
//------------------------------------------------------------------------------
//                                  MAB::String
//------------------------------------------------------------------------------
// GMAT: General Mission Analysis Tool.
//
// **Legal**
//
// Author: Your Name
// Created: 2003/08/05
//
/**
 * Provides a basic character string type operations.
 *
 * @note Any notes here.
 */
//------------------------------------------------------------------------------
```

### 4.2 Prolog de méthode virtuelle pure (header)
- Inclure un prolog de méthode (comme en 4.4) axé sur ce qui est attendu des implémentations dérivées.

### 4.3 Prolog de fichier source
- Même format que le prolog de header.
- Public cible : le mainteneur → commentaires orientés développement/maintenance.

### 4.4 Prolog de méthode/fonction (fichier source)
- Toutes les méthodes/fonctions globales non virtuelles pures doivent avoir un prolog juste avant leur implémentation.
- Décrire clairement : but, entrées, valeur de retour, exceptions/conditions anormales.
- Section exception omise si aucune exception n'est levée.
- Noter les responsabilités de possession/suppression pour les arguments pointeurs.

```cpp
//------------------------------------------------------------------------------
// function signature
//------------------------------------------------------------------------------
/**
 * brief description of this function.
 * detailed description of this function if any.
 *
 * @param   - if applicable
 * @return  - if applicable
 * @exception - if applicable
 * @see     - if applicable
 * @note    - if applicable
 */
//------------------------------------------------------------------------------
```

### 4.5 Commentaires en général
- Utiliser exclusivement `//`, sauf pour les commentaires destinés à la documentation (style Doxygen).
- **Pas de PDL** — commenter clairement et succinctement le code (bloc avant chaque section majeure, unités, références aux spécifications, etc.).
- Inclure les unités dans les commentaires si elles ne sont pas dans le nom de variable :
  `Vector3 initialPosition(0.0, 0.0, 0.0); // initial position vector in km`
- Aligner les commentaires des variables déclarées ensemble.
- Référencer la spécification formelle dans le prolog de fichier ; référencer la source d'un algorithme dans le prolog de fonction.
- Commentaires étape par étape utiles lors du codage à partir d'une spec, mais rester concis — ne pas être trop verbeux.

---

## 5. Classe

### 5.1 Déclaration de classe (Header)
- Ne pas utiliser de données publiques sans justification d'efficacité.
- Fournir des accesseurs (Get/Set).
- Déclarer le destructeur `virtual` si la classe peut être dérivée.
- Déclarer une méthode `virtual` seulement si nécessaire (moins efficace).
- Type de retour sur la même ligne que le nom de fonction ; si trop long, le nom de méthode peut passer à la ligne suivante, aligné avec la liste des méthodes.
- Utiliser des directives préprocesseur pour éviter les définitions multiples (include guards), en capitalisant comme le nom de la classe :

```cpp
#ifndef AnalyticalModel_hpp
#define AnalyticalModel_hpp
   ...
#endif // AnalyticalModel_hpp
```

#### 5.1.1 Méthodes requises pour une classe
Toujours inclure (déclarer en `private` si à désactiver) :
- constructeur par défaut
- constructeur de copie
- destructeur
- opérateur d'affectation

#### 5.1.2 Disposition des déclarations de méthode/fonction
- Ordre : `public`, `protected`, `private`.

#### 5.1.3 Include
- Les `#include` en haut du fichier uniquement.
- Triés et groupés par position hiérarchique (fichiers de bas niveau en premier).
- Préférer les bibliothèques C++ aux bibliothèques C (`<iostream>` plutôt que `<stdio.h>`) — sauf optimisation prouvée.
- Commenter le pourquoi d'un include système.
- Inclure les headers seulement où nécessaire, pour la clarté.
- Les déclarations `extern` de données globales dans les fichiers source, pas les headers.
- `extern "C"` pour référencer des variables/fonctions C externes.
- *Pour la portabilité* : éviter les noms de répertoires dans les directives `#include` (chemins relatifs avec `/`, jamais de chemins absolus ou avec d'autres séparateurs).

#### 5.1.4 Inlining
- Préférer le switch d'inlining du compilateur à l'inlining manuel dans le header.
- Définir les fonctions inline **en dehors** de la définition de classe (plus compact/lisible) :

```cpp
class X
{
public:
   bool outsideClass() const;
};

inline bool X::outsideClass() const
{
   return true;
}
```

#### 5.1.5 Disposition du fichier header de classe
Ordre :
1. Mot-clé CVS
2. Bannière du nom de classe
3. Prolog du fichier header
4. `#ifndef` préprocesseur
5. Includes système
6. Includes applicatifs
7. Déclarations de constantes
8. Déclaration de classe
9. Fonctions non-membres (globales)
10. `#endif` préprocesseur

### 5.2 Définition de classe (fichier source)

#### 5.2.1 Constructeurs
- Ne pas faire de « vrai travail » dans le constructeur — initialiser et ne faire que des actions qui ne peuvent pas échouer.
- Les instanciateurs doivent vérifier les erreurs après construction.
- Éviter de lever des exceptions depuis les constructeurs.
- Initialiser toutes les données membres dans le constructeur.

#### 5.2.2 Exceptions
- Utiliser les exceptions pour des conditions vraiment exceptionnelles, pas pour du passage de messages.
- *Pour l'efficacité* : capturer les exceptions par référence.

#### 5.2.3 Disposition de la définition des méthodes/fonctions
- Définir les méthodes dans l'ordre de la déclaration de classe.
- Toujours initialiser toutes les variables.
- Signature, type de retour et noms d'arguments doivent correspondre exactement à la déclaration.
- Type de retour long → peut être placé sur la ligne au-dessus du nom de fonction.

*Pour l'efficacité* :
- Minimiser le nombre d'appels constructeur/destructeur (minimiser les objets locaux construits, construire en retournant plutôt qu'assigner puis retourner, passer les gros objets par référence const, etc.).
- Initialiser les données membres dans une **liste d'initialisation**, dans l'ordre de déclaration, en initialisant d'abord les données de la classe de base.

```cpp
MaString::MaString(const char *string1, unsigned int len1,
                    const char *string2, unsigned int len2)
   :
   lengthD(len1 + len2),
   caseSensitiveD(true)
{
   ...
}
```

#### 5.2.4 Disposition du fichier source de classe
1. Mot-clé CVS
2. Bannière du nom de classe
3. Prolog du fichier source
4. Prolog de méthode source + implémentation (sections `public`, `protected`, `private`)
5. Inclusion des sous-unités le cas échéant

---

## 6. Templates

- Similaire à une fonction inline : aucun code généré tant qu'il n'y a pas d'instanciation.
- Le spécificateur de template (`template<class T>`) est seul sur la ligne précédant le mot-clé `class` ou le type de retour d'une fonction.
- Les **paramètres de template en majuscules**.

```cpp
// déclaration de template
template<class T>
class ListTemplate
{
public:
   T front();
};

// définition de template
template<class T>
T ListTemplate<T>::front()
{
   ...
}
```

- Problème de portabilité : tous les compilateurs ne gèrent pas les templates de la même manière.
- **Recommandation** : mettre l'implémentation des fonctions template dans un fichier séparé (fichier de définition de template), inclus conditionnellement depuis le header via une macro selon le compilateur.

```cpp
#ifndef QueueTemplate_hpp
#define QueueTemplate_hpp

template <class T>
class QueueTemplate
{
public:
   QueueTemplate();
   void insert(const T& t);
};

//---------------------------------
// Template Definition
//---------------------------------
#ifndef EXTERNAL_TEMPLATE_DEFINITION
#include "QueueTemplate.cpp"
#endif

#endif
```

---

## 7. Fichiers de programme

- Tout fichier doit commencer par un prolog.
- **Header (.hpp)** doit contenir :
  - Une déclaration de classe
  - Déclarations de types globaux
  - Exceptions
  - Typedefs
  - Includes pour fichiers template
  - Définitions de types ENUM
- **Source (.cpp)** doit contenir :
  - Définitions de méthodes (implémentation)
  - Définitions de données globales
  - Valeurs de données constantes
- Organiser les headers par classe (une déclaration de classe par header) ou par regroupement logique de fonctions (ex : `RealUtilities`).
- La procédure principale (`main`) doit résider dans son propre fichier.
- Ne pas utiliser de rangées d'astérisques pour séparer les fonctions.
- **Une seule classe par paire `.hpp`/`.cpp`.**

---

## 8. Portabilité

- Utiliser ANSI/ISO C++ dès que possible.
- Réfléchir à la portabilité dès le début de l'optimisation (plus difficile à refaire ensuite).
- Passer les « gros » arguments (instances de classes/structs) par **référence const** si non modifiés, par **référence** s'ils doivent être modifiés.
- Placer les typedefs des types communs (`double`, `integer`...) dans un header central, accessible à tout le code, pour la portabilité vers d'autres plateformes/précisions.

---

## 9. Efficacité

- Minimiser le nombre d'appels constructeur/destructeur.
- Utiliser les exceptions uniquement pour des conditions vraiment exceptionnelles.
- Utiliser des affectations embarquées (embedded assignments) quand il est prouvé qu'elles sont plus efficaces :

```cpp
while ((c = getchar()) != EOF)
{
   ...
}
```

---

## 10. Divers

### 10.1 Instructions `extern` / Variables externes
- Éviter les `extern` dans le header — les fichiers source référençant les données globales doivent faire l'`extern` eux-mêmes.
- Éviter de déclarer des variables externes non statiques : les variables partagées doivent être définies dans un `.cpp` et externées dans un fichier source.

### 10.2 Directives préprocesseur
- Inclure dans le header principal, accessible à tout le code :

```cpp
#ifndef GMAT_API
  #define GMAT_API
#endif
```

### 10.3 Mélange C et C++
- Les fichiers header compatibles C et C++ ont l'extension `.h`.
- Adapter un header C existant pour supporter le C++ correctement (ne pas juste faire un `extern "C" { }` autour) :

```c
#ifdef __cplusplus
extern "C"
{
#endif
int existingCfunction1(...);
int existingCfunction2(...);
#ifdef __cplusplus
}
#endif
```

### 10.4 Mots-clés CVS
- Si CVS est utilisé, chaque fichier doit commencer par : `//$Header$`

### 10.5 Fichier README
Doit expliquer ce que fait le programme et comment il est organisé, par exemple :
- Tous les flags de compilation conditionnelle et leur signification
- Fichiers dépendants de la machine
- Chemins vers les composants réutilisés
- Historique des versions actuelle/précédentes
- Bugs majeurs connus et corrections
- Brève description des nouvelles fonctionnalités

### 10.6 Makefiles
Doivent :
- Lister tous les fichiers faisant partie du programme
- Documenter quels fichiers font partie des bibliothèques
- Démontrer les dépendances (fichiers source / headers associés) via règles implicites et explicites

### 10.7 Bibliothèques standards
- Une bibliothèque standard regroupe des fonctions communes (ex : `<iostream>`, `<math>`).
- N'inclure que les bibliothèques nécessaires.
- Préférer les bibliothèques standards C++ aux bibliothèques C.

### 10.8 Utilisation des namespaces
- Minimisent les collisions de noms et éliminent le besoin de types/variables globaux.
- Noms pouvant entrer en collision : variables externes, fonctions externes, classes de premier niveau, noms de types dans les headers publics, noms de membres de classe dans les headers publics, etc.
- **Ne pas placer de directive `using namespace` à portée globale dans un header** — la placer dans un fichier source (sinon conflits invisibles difficiles à tracer).
- Dans un fichier d'implémentation, les déclarations/directives `using` sont moins risquées, mais un usage trop fréquent de l'opérateur de portée n'est pas recommandé.

### 10.9 Standard Template Library (STL)
- Utiliser les composants STL quand ils sont disponibles.

### 10.10 Utilisation de l'opérateur `new`
- `new` lève une exception `std::bad_alloc` en cas d'échec (plutôt que retourner `NULL`) — le code peut donc capturer cette exception :

```cpp
#include <stdexcept>

int someFunction()
{
   try
   {
      SomeClass *someClassList = new SomeClass[size];
   }
   catch (std::bad_alloc &ex)
   {
      ...
   }
}
```

---

## Annexe A — Exemples de code C++

### A.1 Exemple de fichier header

```cpp
//$Header$
//------------------------------------------------------------------------------
//                                  A1Date
//------------------------------------------------------------------------------
// GMAT: General Mission Analysis Tool
//
// **Legal**
//
// Author: Linda Jun
// Created: 2003/08/05
//
/**
 * This class provides conversions among various ways representing A1 calendar
 * dates and times.
 */
//------------------------------------------------------------------------------
#ifndef A1Date_hpp
#define A1Date_hpp

#include "IntType.h"
#include "RealType.h"
#include "TimeTypes.h"

#include "Date.hpp"
#include "UtcDate.hpp"
#include "String.hpp"

class A1Date : public MAB::Date
{
public:
   A1Date();
   A1Date(IntType year, IntType month, IntType day, IntType hour,
          IntType minute, RealType second);
   A1Date(IntType year, IntType doy, IntType hour, IntType minute,
          RealType second);
   A1Date(IntType year, IntType month, IntType day, RealType mSecondsOfDay);
   A1Date(const MaString &timeString);
   A1Date(const MaA1Date &date);
   ~A1Date();

   RealType operator-  (const A1Date &date) const;
   A1Date   operator=  (const A1Date &date);
   A1Date   operator+  (const RealType seconds) const;
   A1Date&  operator+= (const RealType seconds);
   A1Date   operator-  (const RealType seconds) const;
   A1Date&  operator-= (const RealType seconds);

   RealType ModifiedJulianDate(ElapsedDays JDBias =
                                TimeConstants::julianDateOf010541);

   Date ToUtcCDate();

protected:
private:
};
#endif // A1Date_hpp
```

### A.2 Exemple de fichier source

```cpp
//$Header$
//------------------------------------------------------------------------------
//                                  A1Date
//------------------------------------------------------------------------------
// GMAT: General Mission Analysis Tool
//
// **Legal**
//
// Author: Linda Jun
// Created: 2003/08/05
//
/**
 * This class provides conversions among various ways representing A1 calendar
 * dates and times.
 */
//------------------------------------------------------------------------------
#include "A1Date.hpp"
#include "Time.hpp"
#include "Date.hpp"

...

//---------------------------------
// public methods
//---------------------------------

//------------------------------------------------------------------------------
// A1Date()
//------------------------------------------------------------------------------
/**
 * Constructs A1Date objects with 0 second from reference (default constructor).
 *
 * @note Calls Time default constructor which creates an object with 0
 *       second from reference.
 */
//------------------------------------------------------------------------------
A1Date::A1Date()
   :
   MAB::Date()
{
   Time t;
   *this = t.A1Split();
}

//------------------------------------------------------------------------------
// RealType operator-(const A1Date &date) const
//------------------------------------------------------------------------------
/**
 * Computes the time offset between two A1Date objects.
 *
 * @param <date> date object to be subtracted from "this" A1Date object.
 */
//------------------------------------------------------------------------------
RealType A1Date::operator-(const A1Date &date) const
{
   RealType offset;

   Time t1(year, month, day, secondsOfDay);
   Time t2(date.year, date.month, date.day, date.secondsOfDay);

   offset = t1 - t2;
   return offset;
}
```

---

## Annexe B — Commandes Doxygen usuelles

| Commande | Description |
|---|---|
| `@author {liste}` | Paragraphe listant un ou plusieurs auteurs |
| `@class <name> [<header-file>] [<header-name>]` | Documentation d'une classe |
| `@date {description}` | Paragraphe de date(s) |
| `@defgroup <name> (titre)` | Documentation d'un groupe de classes/fichiers/namespaces |
| `@endlink` | Termine un lien commencé avec `@link` |
| `@enum <name>` | Documentation d'une énumération |
| `@example <file-name>` | Documentation d'un exemple de code source |
| `@exception <objet> {description}` | Description d'une exception |
| `@file [<name>]` | Documentation d'un fichier source/header |
| `@fn (déclaration)` | Documentation d'une fonction |
| `@include <file-name>` | Inclut un fichier source comme bloc de code |
| `@interface <name>` | Documentation d'une interface |
| `@link <objet>` | Crée un lien vers un objet (fichier, classe, membre) |
| `@name (header)` | Transforme un bloc de commentaire en en-tête de groupe de membres |
| `@namespace <name>` | Documentation d'un namespace |
| `@package <name>` | Documentation d'un package Java |
| `@param <nom> {description}` | Description d'un paramètre de fonction |
| `@return {description}` | Description de la valeur de retour |
| `@retval <valeur> {description}` | Description d'une valeur de retour nommée |
| `@struct <name> [<header-file>] [<header-name>]` | Documentation d'une struct |
| `@test {description}` | Description d'un cas de test |
| `@union <name> [<header-file>] [<header-name>]` | Documentation d'une union |
| `@var (déclaration)` | Documentation d'une variable ou valeur d'enum |
| `@version {numéro}` | Paragraphe de version(s) |
| `@warning {message}` | Paragraphe d'avertissement(s) |

Liste complète : [Doxygen — Special Commands](http://www.stack.nl/~dimitri/doxygen/download.html#latestman)

---

## Références

1. *"C Style Guide"*, Doland, J. et al., SEL-94-003, Software Engineering Laboratory Series, Goddard Space Flight Center, août 1994.
2. *Effective C++*, Meyers, S., Addison-Wesley Professional Computing Series, 1992.
3. *C++ Primer*, 2ᵉ édition, Lippman, S., AT&T Bell Laboratories, 1991.
4. *"Programming in C++ Rules and Recommendations"*, Henricson, M. et Nyquist, E., Ellemtel Telecommunication Systems Laboratories, 1990-1992.
5. *C++ Style Guide*, Version 1.0, Software and Automation Systems Branch, Goddard Space Flight Center, juillet 1992.
6. *"C++ Programming Style Guides"*, Eckel, B., UNIX Review, mars 1995.
7. *"C++ Coding Standard"*, http://www.chris-lott.org/resources/cstyle/CppCodingStandard.html