# PnPCompanion Code Review

## Project Overview
**PnPCompanion** is a Qt/QML application for tabletop RPGs featuring a hierarchical rules system with linked nodes, rich text formatting, and QML-based UI.

---

## Table of Contents
1. [Architecture & Design](#architecture--design)
2. [C++ Code Review](#cpp-code-review)
3. [QML Code Review](#qml-code-review)
4. [Build System](#build-system)
5. [Security & Safety](#security--safety)
6. [Performance Considerations](#performance-considerations)
7. [Recommendations Summary](#recommendations-summary)

---

## Architecture & Design

### ✅ Strengths
- **Clear separation of concerns**: C++ backend handles data logic, QML handles UI
- **Namespace organization**: `Rules::` namespace keeps code organized
- **Qt Meta-Object System**: Proper use of `Q_OBJECT`, signals/slots, and `QML_ELEMENT`
- **Hierarchical data model**: Parent-child relationships for rule nodes

### ⚠️ Concerns
- **Debug code in production**: `main.cpp` contains extensive debug logging and commented-out test code
- **Tight coupling**: `RuleNode` directly depends on `RuleNodeManager` for link resolution
- **Missing persistence**: No save/load mechanism despite being noted in roadmap

---

## C++ Code Review

### `main.cpp`

#### Issues Found:
1. **Unnecessary includes**: Many redundant includes (`qnamespace.h`, `qobject.h`, `qvariant.h`, `qquickview.h`)
2. **Debug code in production**:
   ```cpp
   // This should be removed or wrapped in #ifdef DEBUG
   auto c = engine.children();
   for (auto &ch : c) {
       QString s = ch->objectName();
       qDebug() << s;
       DumpChildren(ch, 1);
   }
   ```
3. **Unused variable**: `myModel` is retrieved but never used
4. **Hardcoded module name**: `"PnPCompanion"` should be configurable
5. **Memory leak risk**: `engine.findChild()` returns raw pointer without ownership clarity

#### Recommendations:
```cpp
// Wrap debug code
#ifdef DEBUG
    // ... debug logging ...
#endif

// Remove unused variables
// Use QScopedPointer for safety if needed
```

---

### `RuleNode.h`

#### Issues Found:
1. **Incomplete enum declaration**:
   ```cpp
   enum Type { eNormal, eUnit, eLocation, eClass, eSpezies };
   ```
   - Missing `Q_ENUM` macro for QML visibility
   - Inconsistent naming (German "Spezies" vs English others)

2. **Redundant member**: `m_this` appears unused and confusing
3. **Missing QML property for Type**: Cannot be accessed from QML without proper registration
4. **Private methods exposed**: `_setname`, `_setThis`, `_setformattedText` should be private slots

#### Recommendations:
```cpp
Q_ENUMS(Type)  // Or Q_ENUM(Type) in Qt 5.5+

// Remove m_this - unclear purpose
// Move private methods to private section properly
```

---

### `RuleNode.cpp`

#### Issues Found:
1. **String manipulation inefficiency**:
   ```cpp
   std::string rawUnformattedText = m_description.toStdString();
   // Multiple substr() calls create many temporary strings
   ```
   **Recommendation**: Use `QString` methods or `QRegularExpression`

2. **Link management complexity**:
   - Manual bracket parsing is error-prone
   - Signal connections not cleaned up properly on destruction
   - `m_links` map doesn't handle node removal gracefully

3. **Missing destructor**: No cleanup of signal connections or resources

4. **Inconsistent error handling**: Silent failures when links don't exist

5. **Thread safety**: No consideration for multi-threaded access

6. **Magic numbers**:
   ```cpp
   lastId = rawUnformattedText.find_first_of('}', id) + 1;
   ```

#### Recommendations:
```cpp
// Use QRegularExpression for link parsing
QRegularExpression linkPattern(R"(\{([^}]+)\})");
QRegularExpressionMatchIterator it = linkPattern.globalMatch(description);

// Add destructor
~RuleNode() {
    // Disconnect all signals
    for (auto link : m_links.keys()) {
        disconnect(link, &RuleNode::nameChanged, this, &RuleNode::LinkNameChanged);
    }
}
```

---

## QML Code Review

### `Main.qml`

#### Issues Found:
1. **No error handling**: No try-catch for component loading failures
2. **Hardcoded paths**: Resource paths should be configurable
3. **Missing accessibility**: No keyboard navigation support mentioned

### `RuleNodeDel.qml` & `RuleNodeHint.qml`

#### General Concerns:
1. **Component lifecycle**: Need to ensure proper cleanup when components are destroyed
2. **Memory management**: QML objects created dynamically need proper parent-child relationships

---

## Build System

### `CMakeLists.txt`

#### Issues Found:
1. **No version checking**: Should verify Qt version compatibility
2. **Missing install targets**: No installation configuration
3. **No testing framework**: No unit test integration

---

## Security & Safety

### Critical Issues:
1. **No input validation**: User-provided descriptions could contain malicious content
2. **SQL injection risk**: If/when database is added, no ORM or parameterized queries mentioned
3. **File path traversal**: Resource loading doesn't validate paths

### Recommendations:
- Add input sanitization for HTML/markdown content
- Implement path validation for resource loading
- Consider adding Content Security Policy for web views

---

## Performance Considerations

### Current Issues:
1. **String operations**: Heavy use of `std::string` conversions in hot paths
2. **Link resolution**: O(n) search through all nodes for each link
3. **No caching**: Formatted text regenerated on every change
4. **Memory leaks**: Signal connections not cleaned up

### Recommendations:
1. Implement caching for formatted text
2. Use hash maps for O(1) link resolution
3. Add memory profiling tools
4. Consider lazy loading for large rule sets

---

## Recommendations Summary

### 🔴 Critical (Fix Immediately)
1. Remove debug code from production builds
2. Add proper signal disconnection in destructors
3. Fix inconsistent naming (German/English mix)

### 🟡 High Priority
1. Implement save/load functionality
2. Add input validation for user content
3. Improve string handling performance
4. Add proper error handling

### 🟢 Medium Priority
1. Add unit tests
2. Implement caching for formatted text
3. Add accessibility features
4. Improve code documentation

### 🔵 Low Priority
1. Refactor to use modern C++ features (C++17/20)
2. Add CI/CD pipeline
3. Consider migrating to Qt 6
4. Add performance monitoring

---

## Code Quality Metrics

| Metric | Current | Target |
|--------|---------|--------|
| Test Coverage | 0% | >80% |
| Code Duplication | High | <5% |
| Cyclomatic Complexity | Medium | <10 |
| Documentation | Minimal | Complete |
| Build Time | Unknown | <30s |

---

## Final Thoughts

The project shows good architectural foundations with Qt's meta-object system and QML separation. However, several critical issues need addressing before production deployment:

1. **Debug code must be removed**
2. **Memory management needs attention**
3. **Input validation is essential**
4. **Persistence layer is missing**

The roadmap items (modules, chapters, templates) are ambitious and should be prioritized carefully. Consider implementing a minimal viable product first before adding complex features.

---

*Review generated: 2026*
*Reviewer: AI Code Assistant*