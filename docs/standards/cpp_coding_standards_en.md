# C++ Coding Standards and Style Guide (GMAT Project)

> Based on the *"C++ Coding Standards and Style Guide"* document (Mission Applications Branch — Code 583), modified for the General Mission Analysis Tool (GMAT).
> This document is based on the "C Style Guide" (SEL-94-003) and builds on/replaces it for C++.

---

## 1. Introduction

### 1.1 Purpose
Describe the recommended style for writing C++ programs, where "good style" means code that is:
- Organized
- Easy to read
- Easy to understand
- Maintainable
- Efficient

### 1.2 Audience
C++ developers on the project, though generally applicable more broadly.

### 1.3 Terminology
- **Method**: a function that is a member of a class.
- **Class Interface**: a class declaration in the header file.
- **Class Implementation**: a class definition in the source file.

---

## 2. Names

General principle: choose names that are **meaningful and readable**.

- All-uppercase abbreviation OR initial uppercase letter followed by lowercase — be consistent.
- **Avoid underscores** in names (except where noted below).

### 2.1 Class Names
- Capitalize the first letter of each word (`PascalCase`).
- A GUI component class should be suffixed by the parent component name: `class DisplayPanel : public Panel`.
- Exception classes should be suffixed with `Exception`: `InvalidEulerSequenceException`.

### 2.2 Class Library Names
- Use **namespaces** to prevent class name clashes.
- Few uses of a namespace's components → use the scope operator `::`.
- Many uses → use a `using` clause to avoid cluttering the code.

### 2.3 Class Instance Names
- Follow conventions for variables.

### 2.4 Method / Function Names
- Always verbs, written in mixed case starting with an uppercase letter: `Normalize()`, `OutputCalibrationData()`.
- Useful prefixes:
  - `Is/Has/Can` → to ask a question and return a bool
  - `Set/Get` → to set/get a value
  - `Initialize` → to initialize an object
  - `Compute` → to compute something
- The class name should not be duplicated in a method name: `Vector::Normalize()`, NOT `Vector::NormalizeVector()`.
- When coding from a formal spec, match names with the spec but use no underscores.

### 2.5 Method / Function Argument Names
- Use the same guideline as for variables.
- A class argument can share its type's name, or, if that's cumbersome, be succinct instead:
  `void SetForceModel(ForceModel *forceModel)` or `*fm`.

### 2.6 Namespace Names
- Same guideline as for class names.
- Prefix with the project name: `namespace GmatTimeUtil`.

### 2.7 Variables
- `camelCase`: starts with a lowercase letter, first letter of each subsequent word capitalized.
  `double flatteningCoefficient;`
- Add a comment to a variable declaration if the name alone doesn't make the meaning clear.
- Declare variables at the level where they're needed (a variable used only in a block is declared inside that block).
- Comment on units if not included in the variable name (e.g. `initialPositionInKm`).
- Loop index: may be declared inside the `for` loop or above it (declare above if needed after the loop).
- Prefer project-defined types over built-in types for loop indices (`Integer` instead of `int`).

#### 2.7.1 Pointer Variables
- Place the `*` with the variable name, not the type:
  `MAB::String *name = new MAB::String;`
- Take care with pointer conversions (base → derived) — *for portability*.
- Use `NULL` for a null pointer.

#### 2.7.2 Reference Variables
- Place the `&` with the variable name:
  `MaString(const MaString &maString, unsigned int bufferLength = 0)`
- For overloaded operators and methods returning a reference, place the `&` with the **type**:
  `const MaString& operator= (const char *string);`

#### 2.7.3 Global Variables
- Should be avoided. Use namespaces instead.

### 2.8 Type Names
- First letter of each word capitalized:
  `typedef unsigned int SystemType;`

### 2.9 Enum Type Names and Enum Names
- Enum types follow the class name policy.
- Enum values are declared in all caps with underscores:
  `enum Colors {RED = 3, BLUE, DARK_BLUE, GREEN, DARK_GREEN, YELLOW = 7};`

### 2.10 Constants / `#define`
- All CAPS with underscores: `const int MINIMUM_NUMBER_OF_BYTES = 4;`
- Avoid `#define` → prefer `const` or enumeration types instead of constant macros (exception: conditional debug compilation).

### 2.11 Structure Names
- Class name convention plus the word `Type`: `struct TimeType { ... };`
- Classes are preferred over structs, unless all data is public.
- Structs may be used to encapsulate global data (including exceptions).

### 2.12 C Function Names
- Lowercase with `_` as the word delimiter: `get_best_fit_model()`.
- Very few C functions should be used in a C++ program (only to interface between C++ and C code).

### 2.13 C++ File Names
- Header: `.hpp`
- Header compatible with both C and C++: `.h`
- Source: `.cpp`
- The file name should match the class name: `AnalyticalModel.hpp` / `AnalyticalModel.cpp`.

### 2.14 Generated Code File Names
- Don't change the naming convention for files generated by other programs (e.g. wxWidgets).

---

## 3. Formatting

General principles:
- Use blank lines to organize code into paragraphs.
- Limit the complexity of statements (break them up if needed).
- Indent to show the logical structure of the code.

### 3.1 Variables
- Declare only one variable per line.

### 3.2 Braces `{}`
- Used for all blocks. The opening brace appears on the following line, lined up with the keyword.

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

### 3.3 Parentheses `()`
- Always put `()` around a condition.
- Put a space between a keyword and parentheses.

### 3.4 Indentation
- Use 3 or 4 spaces (3 is strongly suggested).
- Use logical spacing when standard indentation isn't workable.
- Line up variables when several declarations are listed together.

### 3.5 Tab / Space
- **Do not use tabs** — use spaces only.
- One space after a comma and semicolons.
- One space around assignment operators.
- One space between a keyword and parentheses: `if ( )`, `while ( )`.
- Always a space around conditional operators: `z = (a > b) ? a : b;`
- No space before parentheses following a function name: `z = exp(2, x)`.
- No space between unary operators and their operands: `++i`, `-n`, `*p`, `&x`.
- No space around the primary operators: `->`, `.`, `[]`.

### 3.6 Blank Lines
- Use blank lines to create paragraphs in the code or comments to make it more understandable.

### 3.7 Method/Function Arguments
- When arguments don't fit on one line, try to line up the first argument on each line (or line up with the method name if still too long).

```cpp
void SomeFunction(unsigned int someCounter, double someScaleFactor,
                  int someOtherArgument,
                  const SolarSystemBody &solarSystemBody,
                  int theLastArgument);
```

### 3.8 If / If else
- Indent statements one level using braces. For a single statement, braces are optional.
- Use explicit comparisons:
  `if (theFile->EndOfData() != true)` rather than `if (!theFile->EndOfData())`.
- Always use braces for nested `if` statements.

### 3.9 Switch
- Every `switch` should have a `default` case, which may be simply a "fatal error" exit.
- `default` should be last and doesn't require a `break`, but it's a good idea to include one for consistency.
- Falling through into the next case is permitted as long as a comment explains it.
- If you need to create variables inside a case, put all its code in a block.

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
- Indent statements one level using braces; optional for a single statement.

### 3.11 Break
- Can be used to exit an inner loop (`for`, `while`, `do`, `switch`) at a logical breaking point.

### 3.12 Use of `goto`
- **Do not use `goto`.**

### 3.13 Use of `?:`
- Fine as long as they aren't too complex.
- Put the condition in parentheses to set it off from the rest of the code.

### 3.14 Return Statement
- Multiple return statements are allowed in a function if it makes the code more efficient *(for efficiency)*.
- Using an expression (including a constructor call) directly in a return statement is more efficient than declaring a local variable and returning it *(for efficiency — avoids a copy-constructor and destructor call)*.

### 3.15 Maximum Characters per Line
- Lines should be **no more than 80** characters long.

---

## 4. Documentation

Two main audiences: **Class Users** and **Class Implementors/Maintainers**.

- Program level: a **README** file (general description, organization).
- File level: a **file prolog** (purpose, information).
- Header: a **method prolog** for all pure virtual methods.
- Source: a **method prolog** for all other methods.
- Comment on data declarations/definitions to explain their purpose.

### Doxygen
- Use [Doxygen](http://www.doxygen.org) to automatically extract documentation from the code.
- Follow the JavaDoc convention for comment blocks.
- Set `JAVADOC_AUTOBRIEF = YES` in the Doxygen configuration → the brief description ends at the first dot followed by a space or new line.

```cpp
/**
 * brief description.
 * detailed description.
 */
```

One-line brief description:
```cpp
/// one line brief description
```

⚠️ Comments starting with `//` will **NOT** show up in the generated documentation.

### 4.1 Header File Prolog
- All header files must begin with a header file prolog.
- PDL (Program Design Language) should not appear at the file level — replace it with well-documented code.
- Header file prolog sections (no "change history" section, since GMAT uses CVS to control source code):
  - `<CVS Keyword>` → `$Header$`
  - `<Class Name Banner>` (for a class header)
  - `<Project Name>` → `GMAT: General Mission Analysis Tool`
  - `<Legal Tag>` → `**Legal**`
  - `<Author>`
  - `<Created>` → `yyyy/mm/dd`
  - `<Class Description>` (JavaDoc block)
  - `<Note>` (optional)

Example:
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

### 4.2 Header File Pure Virtual Method/Function Prolog
- For pure virtual methods, include a method prolog (as in 4.4) focused on what's expected of derived classes' implementations.

### 4.3 Source File Prolog
- Same format as the header file prolog.
- Main audience: a maintainer → focus commentary on development/maintenance issues.

### 4.4 Source File Method/Function Prolog
- All methods and global functions (that aren't pure virtual) must have prologs in the source file, appearing just before their implementation.
- Describe the method/function clearly and concisely: purpose, inputs, return value (if any), and possible exceptions/abnormal conditions.
- Exception section can be omitted if no exceptions are thrown.
- Notes about ownership/deletion responsibilities for pointer arguments can be included.

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

### 4.5 Comments in General
- Use the `//` comment indicator exclusively, except where comments are intended for documentation (Doxygen style).
- **Do not include PDL** — clearly and succinctly comment the code (a block comment before each major section, document units, refer to specs where useful, etc.).
- Include units in comments for variable declarations if not included in the name:
  `Vector3 initialPosition(0.0, 0.0, 0.0); // initial position vector in km`
- Line up comments for declared variables.
- Reference a formal specification in the file prolog; reference the source of a specific algorithm in the function prolog.
- Step-by-step commentary is useful when coding from a spec, but comments shouldn't be too verbose or restate the obvious.

---

## 5. Class

### 5.1 Class Declaration (Header File)
- Public data should not be used without an overriding efficiency justification.
- Provide access methods (Get/Set).
- Declare the destructor `virtual` if the class could possibly be derived from.
- Declare a method `virtual` only if necessary (virtual functions are less efficient).
- Put the return type on the same line as the function name; if the return type is very long, put the method name on the next line, lined up with the list of methods.
- Use preprocessor commands to avoid multiple definitions in a header (include guards), capitalized the same way as the class name:

```cpp
#ifndef AnalyticalModel_hpp
#define AnalyticalModel_hpp
   ...
#endif // AnalyticalModel_hpp
```

#### 5.1.1 Required Methods for a Class
Always include (declare `private`, and possibly unimplemented, to limit or disable usage):
- default constructor
- copy constructor
- destructor
- assignment operator

#### 5.1.2 Class Method/Function Declaration Layout
- Order: `public`, `protected`, `private`.

#### 5.1.3 Include
- `#include` statements must be located at the top of a file only.
- Sorted and grouped by hierarchical position (low-level files included first).
- Prefer C++ libraries over C libraries (`<iostream>` instead of `<stdio.h>`) — unless the C routines prove more efficient.
- Comment why a particular system include file was included.
- Include headers only where needed, for clarity.
- Keep `extern` declarations of global data in source files, not headers.
- Use `extern "C"` when referencing C external variables/functions.
- *For portability*: avoid directory names in `#include` directives (relative paths with `/`, never absolute paths or other separators).

#### 5.1.4 Inlining
- Prefer the compiler's inlining switch over manually inlining implementations in the header.
- Define inline member functions **outside** the class definition (more compact/comprehensible):

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

#### 5.1.5 Class Header File Layout
Order:
1. CVS keyword
2. Class name banner
3. Header file prolog
4. Preprocessor `#ifndef` command
5. System include files
6. Application include files
7. Constant declarations
8. Class declaration
9. Non-member functions (global functions)
10. Preprocessor `#endif` command

### 5.2 Class Definition (Source File)

#### 5.2.1 Constructors
- Do not do any real work in the constructor — initialize variables and only perform actions that can't fail.
- Object instantiators must check an object for errors after construction.
- Avoid throwing exceptions from constructors.
- Initialize all member data in the constructor, not elsewhere, whenever possible.

#### 5.2.2 Exceptions
- Use exceptions for truly exceptional conditions, not for message passing.
- *For efficiency*: catch exceptions by reference.

#### 5.2.3 Class Method/Function Definition Layout
- Define methods/functions in the order they appear in the class declaration.
- Always initialize all variables.
- The function signature, its return type, and argument names must match the declaration exactly.
- A long return type may go on the line above the function name.

*For efficiency*:
- Minimize the number of constructor/destructor calls (minimize local objects constructed, construct on returning from a method rather than assigning-then-returning, pass large objects by const reference, etc.).
- Initialize member data in an **initialization list**, matching declaration order, initializing base class data first.

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

#### 5.2.4 Class Source File Layout
1. CVS keyword
2. Class name banner
3. Source file prolog
4. Source file method prolog followed by implementation (public, protected, private sections)
5. Include subunits, if any

---

## 6. Templates

- In one respect similar to an inline function: no code is generated until an instantiation occurs.
- The template specifier (`template<class T>`) sits alone on the line preceding the `class` keyword or the return type of a function.
- **Template parameters should be in uppercase.**

```cpp
// template declaration
template<class T>
class ListTemplate
{
public:
   T front();
};

// template definition
template<class T>
T ListTemplate<T>::front()
{
   ...
}
```

- Portability issue: not all compilers handle templates the same way.
- **Recommendation**: put the implementation of template functions in a separate file (a template definition file), included conditionally from the header via a compiler-dependent macro.

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

## 7. Program Files

- All files should begin with a file prolog.
- **Header File (.hpp)** should contain:
  - A class declaration
  - Any global type declarations
  - Any exceptions
  - Any typedefs
  - Any includes for template files
  - ENUM type definitions
- **Source File (.cpp)** should contain:
  - Method definitions (implementation)
  - Any global data definitions
  - Any constant data values
- Organize header files by class (one class declaration per header file) or by logical grouping of functions (e.g. `RealUtilities`).
- The main procedure should reside in its own file.
- For source files containing related functions (e.g. utilities), follow guidelines for ordering functions meaningfully.
- Do not use rows of asterisks to separate functions.
- **There should be only one class per .hpp/.cpp pair.**

---

## 8. Portability

- Use ANSI/ISO C++ whenever it's available.
- Give thought to portability from the start of optimization (much harder to redesign or recode later).
- Pass "large" arguments (class/struct instances) by **const reference** when they don't need to be modified, and by **reference** when they do.
- Place typedefs for all common types (e.g. `double`, `integer`) in a central header file, accessible by all code, for easier portability to other platforms and higher-precision types.

---

## 9. Efficiency

- Minimize the number of constructor/destructor calls.
- Use exceptions only for truly exceptional conditions, not for message passing.
- Use embedded assignments when they're proven to be more efficient:

```cpp
while ((c = getchar()) != EOF)
{
   ...
}
```

---

## 10. Miscellaneous

### 10.1 Extern Statements / External Variables
- Avoid `extern` statements in the header file — source files referencing the global data should `extern` the needed data themselves.
- Avoid declaring non-static external variables: variables needed by more than one file should appear in a `.cpp` file and be externed in a source file.

### 10.2 Preprocessor Directives
- Include the following in the main header file, accessed by all code:

```cpp
#ifndef GMAT_API
  #define GMAT_API
#endif
```

### 10.3 Mixing C and C++
- Header files containing code accepted by both C and C++ compilers should have the extension `.h`.
- Make the header files work correctly when included by both C and C++ files — don't just `extern "C" { }` an existing C header, fix it properly:

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

### 10.4 CVS Keywords
- If CVS is used for configuration management, the top of every file should contain: `//$Header$`

### 10.5 README file
Should explain what the program does and how it's organized, for example:
- All conditional compilation flags and their meanings
- Files that are machine dependent
- Paths to reused components
- History information about the current and previous releases
- Information about existing major bugs and fixes
- A brief description of new features added to the system

### 10.6 Makefiles
Should:
- List all files that are to be included as part of the program
- Contain comments documenting what files are part of libraries
- Demonstrate dependencies (source files and associated headers) using implicit and explicit rules

### 10.7 Standard Libraries
- A standard library is a collection of commonly used functions (e.g. `<iostream>`, `<math>`).
- Include only the libraries your program needs.
- Use C++ standard libraries instead of C libraries whenever possible.

### 10.8 Use of Namespaces
- Minimize potential name clashes and eliminate the need for global types/variables.
- Clashable names include: external variable names, external function names, top-level class names, type names in public headers, class member names in public headers, etc.
- **Do not place `using namespace` directives at global scope in a header file** — place them in a source file instead (to avoid magic invisible conflicts across all including files).
- Inside an implementation file, `using` declarations and directives are less risky, though too-frequent use of the scope operator is not recommended.

### 10.9 Standard Template Library (STL)
- Use STL components when available.

### 10.10 Using the new Operator
- The `new` operator throws a `std::bad_alloc` exception on failure (rather than returning `NULL`), so the code may catch this exception instead of checking for a NULL value:

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

## Appendix A — C++ Code Examples

### A.1 Example of a header file

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

### A.2 Example of a source file

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

## Appendix B — Common Doxygen Commands

| Command | Description |
|---|---|
| `@author {list}` | Starts a paragraph listing one or more authors |
| `@class <name> [<header-file>] [<header-name>]` | Documentation for a class |
| `@date {description}` | Paragraph with one or more dates |
| `@defgroup <name> (title)` | Documentation for a group of classes/files/namespaces |
| `@endlink` | Ends a link started with `@link` |
| `@enum <name>` | Documentation for an enumeration |
| `@example <file-name>` | Documentation for a source code example |
| `@exception <object> {description}` | Description of an exception |
| `@file [<name>]` | Documentation for a source/header file |
| `@fn (declaration)` | Documentation for a function |
| `@include <file-name>` | Includes a source file as a code block |
| `@interface <name>` | Documentation for an interface |
| `@link <object>` | Creates a link to an object (file, class, or member) |
| `@name (header)` | Turns a comment block into a header definition of a member group |
| `@namespace <name>` | Documentation for a namespace |
| `@package <name>` | Documentation for a Java package |
| `@param <name> {description}` | Description of a function parameter |
| `@return {description}` | Description of a return value |
| `@retval <value> {description}` | Description of a named return value |
| `@struct <name> [<header-file>] [<header-name>]` | Documentation for a struct |
| `@test {description}` | Description of a test case |
| `@union <name> [<header-file>] [<header-name>]` | Documentation for a union |
| `@var (declaration)` | Documentation for a variable or enum value |
| `@version {number}` | Paragraph with one or more version strings |
| `@warning {message}` | Paragraph with one or more warning messages |

Full list: [Doxygen — Special Commands](http://www.stack.nl/~dimitri/doxygen/download.html#latestman)

---

## References

1. *"C Style Guide"*, Doland, J. et al., SEL-94-003, Software Engineering Laboratory Series, Goddard Space Flight Center, August 1994.
2. *Effective C++*, Meyers, S., Addison-Wesley Professional Computing Series, 1992.
3. *C++ Primer*, 2nd Edition, Lippman, S., AT&T Bell Laboratories, 1991.
4. *"Programming in C++ Rules and Recommendations"*, Henricson, M. and Nyquist, E., Ellemtel Telecommunication Systems Laboratories, 1990-1992.
5. *C++ Style Guide*, Version 1.0, Software and Automation Systems Branch, Goddard Space Flight Center, July 1992.
6. *"C++ Programming Style Guides"*, Eckel, B., UNIX Review, March 1995.
7. *"C++ Coding Standard"*, http://www.chris-lott.org/resources/cstyle/CppCodingStandard.html