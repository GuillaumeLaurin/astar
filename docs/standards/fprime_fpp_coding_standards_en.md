# F´ / FPP Coding Standards and Style Guide (NASA JPL)

> Transposition of the official guidelines for **F´ (F Prime)**, the open-source flight software framework developed at JPL (used notably on the Mars helicopter *Ingenuity*), and **FPP (F Prime Prime / F″)**, its modeling language.
>
> Sources:
> - *F´ Style Guidelines* — [github.com/nasa/fprime/wiki](https://github.com/nasa/fprime/wiki/F%C2%B4-Style-Guidelines)
> - *Code and Style Guidelines* (C++) — [nasa.github.io/fprime](https://nasa.github.io/fprime/UsersGuide/dev/code-style.html)
> - *FPP User's Guide* — [nasa.github.io/fpp](https://nasa.github.io/fpp/fpp-users-guide.html)
>
> ⚠️ These recommendations apply to the code of the **F´ framework itself**. Projects that *use* F´ are encouraged to follow them, but are not required to — adapt as needed for your project's context.

---

## 1. Introduction

F´ is a flight software framework for embedded systems — satellites, probes, instruments, etc. **Reliability** is the number-one goal: these systems often run for very long durations with no option to service failing software.

Guiding principle: code must be **easy to read and easy to review**. Complexity and optimization come at a cost in readability/maintainability — a simpler solution is often preferable.

FPP (F Prime Prime, also known as F″) is F´'s **modeling language**: it's used to describe types, ports, components, component instances, and topologies, then generates C++ and JSON. The `.fpp` files and the generated/hand-written C++ share the **same naming conventions**.

---

## 2. Naming Conventions

### 2.1 Constants, enumeration values, compiler directives
- **All uppercase**, tokens separated by `_` (underscore).

```cpp
#define MY_DEFINITION 1234

const U32 MY_CONSTANT = 3;

enum EnumType {
    VALUE_SUCCESS = ...,
    VALUE_FAILURE = ...
};
```

### 2.2 Local Variables and Global Variables
- **lower camel case**: starts with a lowercase letter, capital letter starting each subsequent word.

```cpp
U32 myVariable = 2;
```

### 2.3 Member Variables
- Same rules as local variables, **prefixed with `m_`**.

```cpp
U32 m_myMemberVariable;
```

### 2.4 Functions and Member Functions
- **lower camel case**, just like local variables.

### 2.5 Types, Components, Ports, Classes, Packages, Namespaces, Modules
- **Pascal case**: leading capital letter, additional capitals at the start of each word.

```
Svc.ComStub   // FPP form
Svc::ComStub  // C++ form
```

> Notice that the FPP module, C++ namespace, and component name are all defined in Pascal case — consistent across languages.

---

## 3. Module Directory Structure

F´ constructs are each defined in a **module**, and break down into several categories: **Types**, **Ports**, **Components**, **Topologies**. Modules are grouped into various **packages**: `Fw` (framework), `Drv` (drivers), `Svc` (service components), etc.

### 3.1 Ports and Types
- Placed in package sub-folders named `Ports` and `Types` respectively.

```
Fw/Ports/SuccessPort/     ← Fw.SuccessPort port module
```

### 3.2 Components
- The module directory is placed **directly** in the package directory.

```
Svc/ComStub/              ← Svc.ComStub component
```

### 3.3 Topologies
- Placed in the `Top` folder of a deployment's package.

```
Ref/Top                   ← Ref topology
```

---

## 4. Referring to Class Members

### 4.1 Instance Members
- Prefix the name with `this->`.

```cpp
this->m_myMemberVariable = 1;
this->myMemberFunction();
```

### 4.2 Static Members
- Prefix the name with the enclosing class name.

```cpp
ClassName::m_myStaticVariable = 1;
ClassName::myStaticFunction();
```

---

## 5. C++ in F´

C++ in F´ is written primarily following the **Embedded C++** style with some notable deviations, and follows the **JPL Coding Standards** (adapted from C — see the *Power of 10 Rules*). Code targets the **C++11** standard, though some C++11 features are avoided to support incomplete implementations. Code format is based on the **ClangFormat Chromium** style.

### 5.1 Embedded C++ Usage
Core points of the embedded C++ style used by F´:
1. **No exceptions** — code must compile with `-fno-exceptions`.
2. **No use of templates nor the Standard Template Library (STL)**.
3. **No `typeid` or run-time type information (RTTI)**.

### 5.2 Deviations from the Embedded C++ Standard
Done to increase safety, increase readability, and enable modern C++ development:
1. Use **namespaces** to reduce naming conflicts.
2. Use `std::numeric_limits` for min/max values (template implementations of `std::numeric_limits` have been approved).
3. Use `static_cast`, `reinterpret_cast`, and `const_cast` instead of dangerous C-style casting or `dynamic_cast`.
4. Limited use of multiple inheritance and virtual base classes is permitted (see §7).

### 5.3 JPL Coding Standards (NASA/JPL Flight Software heritage)
Additional rules adapted from C guidelines, inherited from NASA/JPL flight software heritage:

1. No recursion; no `GOTO`s.
2. Loops must have a **fixed bound**.
3. No dynamic memory allocation after initialization.
4. Use `FW_ASSERT` to validate function inputs and computation.
5. Restrict data to the smallest necessary scope.
6. Check function return values, or explicitly discard with `(void)`.
7. Avoid the preprocessor, and especially complex uses of it.
8. Prefer `Fw` and `Os` implementations (e.g. use `FW_ASSERT` and `Os::Mutex` over `cassert` and `std::mutex`).
9. Compile **without warnings, errors, or static analysis failures** (i.e. pass continuous integration).
10. Do not use `Os::Task::delay` to synchronize between threads.
11. Explicit enumeration values should be specified **for all values, or for none at all**.

### 5.4 C++11 Usage
F´ has been updated to support C++11, but some implementations are incomplete:
1. Many C++11 features use templates under the hood → prefer `Fw`/`Os` implementations for these features.
2. Use of `std::atomic` is known not to work in some cases → avoided.

### 5.5 ClangFormat
- F´ uses **ClangFormat** based on the Chromium style (a `.clang-format` file is supplied at the root of the repository).
- The `fprime-tools` command-line utility (>v3.1.1) provides a wrapper command around `clang-format`, and is the preferred way to format code, since it correctly handles the `PRIVATE`, `PROTECTED`, and `STATIC` access modifiers used to enable white-box unit testing in F´.
- See `fprime-util format --help`.

---

## 6. Documentation

- Each component must be documented through a **Software Description Document (SDD)**, placed in a `docs` subfolder, capturing:
  1. Requirements
  2. Design
  3. Implementation and Usage Notes
- C++ documentation is generated using **Doxygen**: use Doxygen-style comments to annotate functions and variables.
- C++ APIs and libraries must be documented to produce usable Doxygen documentation.
- Components should be documented in a similar fashion, but the SDD captures the primary documentation for components.

---

## 7. Asserts, WARNING Events, and FATAL Events

Software should operate correctly in the event of off-nominal behavior.

- **`FW_ASSERT`** (runtime assert): used to ensure software integrity and assumptions — arguments passed to functions are within bounds, return values make sense, and other confidence checks. Runtime assertions should **never** be used to validate user inputs nor the results of hardware interaction, as these may cause errors outside software control.
- In those cases (user input, hardware interaction), an **event** should be emitted to report the error, and the software should appropriately continue execution even in the case of erroneous input.

Event severity:
| Severity | Meaning |
|---|---|
| `WARNING_LO` | Issue localized to this component, recovery is possible. |
| `WARNING_HI` | Issue affecting the larger system, recovery is possible. |
| `FATAL` | Issue where recovery is not possible — the system is typically restarted. |

⚠️ `WARNING_HI` and `FATAL` events must be documented in the SDD and approved as part of the submission review.

---

## 8. Use of Multiple Inheritance and Virtual Base Classes

Many F´ constructs are required to inherit from an autocoded class that then inherits from framework base classes. This can present a problem, as it precludes inheritance from other structures — thus, limited multiple inheritance is permitted.

Basic guidelines (the use of multiple inheritance will likely be discussed during the submission review):
1. Only use multiple inheritance when **absolutely required**.
2. Avoid inheritance from more than **one** hand-coded class.
3. Avoid inheritance from hand-coded descendants of autocoded classes and their parents (e.g. `Fw::PortBase`, `Fw::PassiveComponentBase`) — i.e. avoid inheritance from other Components, Ports, or classes that do.
4. Avoid multiple inheritance paths that derive from a common base class (the **diamond problem**).

Normal usage of multiple/virtual inheritance in F´ is to set up **interfaces** (as is often done in Java) — a virtual C++ base class defining only functions. An F´ class or component then uses multiple inheritance to inherit those function definitions, with the intent of implementing them. This can be used to bridge autocoded F´ functionality and hand-written C++ functionality (e.g. a component can supply F´ port call functionality to supporting classes through this style of interface).

---

## 9. Python

- Python code is formatted with **black**.
- Code must **pass a black format check**.
- To format: install `black` (see the *Python Development Guide*) and run `black <path to code>`.

---

## Appendix — Naming Conventions Summary Table

| Element | Convention | Example |
|---|---|---|
| Constants / enum values / preprocessor directives | `ALL_CAPS_WITH_UNDERSCORES` | `MY_CONSTANT`, `VALUE_SUCCESS` |
| Local / global variables | `lowerCamelCase` | `myVariable` |
| Member variables | `m_` + `lowerCamelCase` | `m_myMemberVariable` |
| Functions / methods | `lowerCamelCase` | `myMemberFunction()` |
| Types, Components, Ports, Classes, Packages, Namespaces, Modules | `PascalCase` | `Svc.ComStub` / `Svc::ComStub` |

---

## References

1. *F´ Style Guidelines*, NASA/JPL — https://github.com/nasa/fprime/wiki/F%C2%B4-Style-Guidelines
2. *Code and Style Guidelines*, F´ User's Guide — https://nasa.github.io/fprime/UsersGuide/dev/code-style.html
3. *The F Prime Prime (FPP) User's Guide* — https://nasa.github.io/fpp/fpp-users-guide.html
4. *The F Prime Prime (FPP) Language Specification* — https://nasa.github.io/fpp/fpp-spec.html
5. *Power of 10 Rules*, Gerard J. Holzmann, JPL Laboratory for Reliable Software.
6. Bocchino, R., *"FPP: A Modeling Language for F Prime"*, IEEE Aerospace Conference, 2022.