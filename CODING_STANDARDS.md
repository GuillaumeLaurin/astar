# Index des guides de style de codage

Ce fichier sert de point d'entrée vers les différents guides de style de codage transposés en Markdown.

| Guide | Langage(s) | Organisation | Fichier |
|---|---|---|---|
| **C++ Coding Standards and Style Guide** | C++ | NASA GSFC — Mission Applications Branch (GMAT Project) | [`cpp_coding_standards_en.md`](./docs/standards/cpp_coding_standards_en.md) *(EN)* / [`cpp_coding_standards_fr.md`](./docs/standards/cpp_coding_standards_fr.md) *(FR)* |
| **F´ / FPP Coding Standards and Style Guide** | C++, FPP | NASA JPL (F Prime framework) | [`fprime_fpp_coding_standards_en.md`](./docs/standards/fprime_fpp_coding_standards_en.md) *(EN)* / [`fprime_fpp_coding_standards_fr.md`](./docs/standards/fprime_fpp_coding_standards_fr.md) *(FR)* |

---

## Aperçu rapide

### GMAT (C++)
Guide de style pour le C++ développé par la Mission Applications Branch (Code 583) du Goddard Space Flight Center, adapté pour le General Mission Analysis Tool (GMAT). Couvre : conventions de nommage, formatage, documentation (prologs de fichier/méthode, Doxygen), structure des classes, templates, portabilité, efficacité, et usages divers (namespaces, STL, opérateur `new`).

### F´ / FPP (JPL)
Guide de style pour le framework de logiciel de vol **F´** et son langage de modélisation **FPP**, développés au Jet Propulsion Laboratory. Couvre : conventions de nommage (partagées entre FPP et C++), structure des répertoires de modules, règles C++ embarqué (Embedded C++), JPL Coding Standards (héritage *Power of 10 Rules*), gestion des asserts/événements, héritage multiple, et formatage (ClangFormat / black).

---

## Points communs entre les deux guides

- Conventions de nommage strictes et cohérentes (types vs variables vs constantes).
- Emphase sur la lisibilité et la maintenabilité plutôt que sur la concision à tout prix.
- Documentation intégrée au code via des outils automatisés (Doxygen dans les deux cas).
- Contraintes fortes héritées du contexte "logiciel spatial" : portabilité (GMAT), fiabilité et sûreté (F´ / JPL Power of 10 Rules).

## Différences notables

| Aspect | GMAT | F´ / FPP |
|---|---|---|
| Variables locales | `camelCase` | `lowerCamelCase` (équivalent) |
| Variables membres | Pas de préfixe imposé | Préfixe `m_` obligatoire |
| Constantes | `ALL_CAPS` | `ALL_CAPS` (identique) |
| Exceptions | Utilisées pour cas exceptionnels | **Interdites** (`-fno-exceptions`) |
| Templates / STL | Recommandés quand disponibles | **Interdits** (Embedded C++) |
| Récursion | Non mentionnée | **Interdite** |
| Allocation dynamique | `new` encouragé avec gestion `bad_alloc` | Interdite après l'initialisation |
| Formatage automatique | Non spécifié | ClangFormat (Chromium style) obligatoire |