Here is a detailed step-by-step plan for your **Pen and Paper Companion (PnPC)** project, based on your goal and your tech stack (QML/C++). The plan is structured to keep modularity, scalability, and maintainability in mind — especially as you you'll be implementing it solo, but with future extensibility in mind.

We’ll break it down into ** phases**, each focusing on a major feature area, and include **file/project structure**, **layering**, and **data flow** guidance.

---

## 🧭 Phase 0: Project Setup & Architecture

### ✅ Goals
- Set up a modular, scalable C++/QML project
- Define core abstractions for future extensibility (e.g., rules, units, UI components)
- Separate business logic (C++) from UI (QML)

### Steps

1. **Project Structure**
    ```
    pnpc/
    ├── main.cpp                    # QML entry point
    ├── qml/                        # QML UI files
    │   ├── main.qml
    │   ├── CharacterSheet/
    │   │   ├── Main.qml
    │   │   └── CharacterForm.qml
    │   ├── CombatTracker/
    │   │   ├── Main.qml
    │   │   └── CombatantCard.qml
    │   ├── Ruleset/
    │   │   ├── Main.qml
    │   │   ├── RuleEntryCard.qml
    │   │   └── RuleTree.qml
    │   ├── DiceRoller/
    │   │   ├── Main.qml
    │   │   └── DiceButton.qml
    │   └── Settings/
    │       └── UnitsSettings.qml
    ├── src/
    │   ├── core/
    │   │   ├── RuleEngine.hpp      # C++ rule evaluation (Rule-Language)
    │   │   ├── Units.hpp
    │   │   ├── DiceRoller.hpp
    │   │   └── Combatant.hpp
    │   ├── ui/
    │   │   ├── CharacterSheetModel.hpp
    │   │   └── CombatTrackerModel.hpp
    │   └── rules/
    │       ├── RuleParser.hpp      # Parse "Rule Code" (Python-like)
    │       └── RuleTemplate.hpp
    ├── assets/
    │   ├── images/
    │   └── units.json              # Default unit definitions (fallback)
    └── CMakeLists.txt              # Build config
    ```

2. **Define Core Data Models in C++**
   - `UnitType` → struct for unit metadata (`name`, `shortform`, `baseUnit`, `conversionFactor`)
   - `RuleEntry` → struct for rule metadata + rule code + children
   - `Combatant` → base class for Player/NPC with HP, initiative, etc.
   - `DiceRoller` → static utility or singleton

3. **Exposing to QML**
   - Use `Q_INVOCABLE`, `Q_PROPERTY`, `QML_REGISTER_TYPE`
   - Wrap models as `QAbstractItemModel` if needed (e.g., for tree views in Ruleset)

---

## 🧭 Phase 1: **Character Sheet (Core + Configurable)**

### ✅ Goals
- Static fields: name, race, inventory, weapons
- Configurable via Ruleset: class, skills, attitude
- Persistence (save/load)

### Steps

1. **Backend Model (`CharacterModel`)**
    - `name`, `race`, `class`, `skills`, `attitude`
    - Inventory list (struct: `Item {id, name, count, unit}`)

2. **UI Components**
    - `CharacterSheet.qml` → main view
    - `EditForm.qml` → for editable fields
    - `InventoryList.qml` → list + add/remove
    - `SkillsTree.qml` → if hierarchical

3. **Integration with Ruleset**
    - Class → select from RuleEntry of “Class”
    - Skills → list of RuleEntry of “Skill”
    - Attitude → enum from `RuleEntry` of `Attitude` category

---

## 🧭 Phase 2: **Combat Tracker**

### ✅ Goals
- Initiative ordering
- HP tracking (current + history toggle)
- NPC/Player toggle
- Add/remove combatants
- Auto-initiative for NPCs (optional toggle)

### Steps

1. **Backend**
    - `CombatSession` class:
        - ` QList<Combatant> combatants;`
        - `QList<int> initiativeOrder;`
        - `bool autoInitNPC;`
        - `bool showHistory;`

    - `Combatant` class:
        - `QString name`
        - `int initiative`
        - `int currentHp`, `int maxHp`
        - `QList<HpChange> history;` (if history enabled)
        - `bool isNPC`
        - `QString ruleEntryId` (→ link to Ruleset)

2. **UI**
    - `CombatTrackerMain.qml`
    - `CombatantCard.qml`:
        - HP: `Slider` or `Stepper`
        - `historyToggle` → shows history as `Text` or `List`
        - `addDamageButton`, `addHeedingButton`
    - `CombatantList.qml` with `ListView + Repeater + SortFilterProxyModel`

3. **Initiative Logic**
    - Sort `combatants` by `initiative` (descending)
    - `nextTurn()`, `prevTurn()`, `setInitiative(int idx, int val)`

---

## 🧭 Phase 3: **Ruleset (Unit + Rule Entry)**

### ✅ Goals
- Define units (predefined + configurable)
- Define rule entries (title, description, image, sub-entries, templates)
- Support inheritance via templates (e.g., parent: `Creature`, child: `EnemyType`)

### Steps

1. **Units Model**
    - JSON or C++ `QMap<QString, UnitType>`
    - Predefined: `meters`, `kilograms`, `damagePoints`
    - Configurable: `customUnit {name, shortform, description}`

2. **Rule Entries**
    - Tree structure:
        ```cpp
        struct RuleEntry {
            QString id;
            QString title;
            QString description;
            QString parentId;  // for template inheritance
            QJsonObject templateValues; // e.g., {"hp": 10, "dmg": 5}
            QList<RuleEntry> children;
        };
        ```

    - Implement `QStandardItemModel` or `QAbstractTreeModel` for QML `TreeView`

3. **UI**
    - `RulesetTree.qml` (tree view)
    - `RuleEntryDetails.qml` (form for editing: title, desc, units, image)
    - `EditTemplateValues.qml` → grid for editing child override values

---

## 🧭 Phase 4: **Dice Roller**

### ✅ Goals
- Roll dice (N dS + M)
- Preset buttons (d6, d20, etc.)
- History (optional toggle)

### Steps

1. **Backend**
    ```cpp
    class DiceRoller {
        Q_INVOCABLE QVariant roll(int sides, int count, int modifier = 0);
        Q_INVOCABLE QStringList history();
    };
    ```

2. **UI**
    - `DiceButton.qml` → roll on press
    - `RollHistory.qml` → `ListView` of `rolls`
    - `CustomRollForm.qml` → N, S, M inputs

---

## 🧭 Phase 5: **Rule Language (Preview + Extensibility)**

### ✅ Goals
- Allow rule authors to write "Rule Code" (Python-like) in rule entries
- Expose units + buttons + context to rule engine
- Parse & evaluate at runtime (e.g., via PythonQt or custom parser)

### Steps

1. **Design the DSL**
    - Example:
      ```python
      if unit("damage") > 10:
          return "high"
      elif unit("range") < 5:
          return "close"
      else:
          return "default"
      ```

2. **Engine**
    - Option A: Embed Python via `PythonQt` or `QProcess`
    - Option B: Custom parser (simpler cases: arithmetic + conditionals)
    - Option C: QML/JS-based rule engine (if logic stays UI-side)

3. **Integration**
    - Add `Rule Code Editor` in `RuleEntryDetails.qml`
    - On save, serialize + store code
    - On evaluation → pass context (`units`, `combatants`, etc.)

---

## 🧭 Phase 6: **Nice-to-Have Features**

### AI DM Assistant
- Use QtMultimedia + SpeechRecognition (e.g., `QSound`, `QtSpeech`)
- On voice input: `Speech → Text → Command → Play Sound/FX`
- Example command: `play "ambient room music"`

### TCP Multiplayer
- Server: DM → sends `CombatUpdate`, `RulesetSync`, `CharSheetUpdate`
- Client: subscribe to updates
- Sync model: `CombatSession` + `CharacterModel` → JSON over TCP

### Rule Language (Expanded)
- Use `QScriptEngine` for lightweight JS rule logic (safe, embeddable)
- Expose `unit(name)`, `combatant(index)`, `roll(...)`, `print(...)`

---

## 🧭 Phase 7: **Data Persistence & Settings**

### Goals
- Save/load characters, combat sessions, ruleset to JSON or SQLite
- Settings for toggles (history, auto-init, etc.)

### Steps
- Use `QSettings` for app-level config
- `QJsonDocument` for complex data (character/combat)
- SQLite for large-scale ruleset if many entries

---

## 🧭 Phase 8: **UI Polish & UX**

- Tab navigation or drawer-based navigation (for mobile/Desktop)
- Dark/light theme toggle (QML `Theme` + `ColorGroup`)
- Responsive layout (desktop vs mobile)

---

## ✅ Optional Enhancements (Later)

- **Export to PDF** (e.g., character sheet)
- **Sync via cloud** (QtWebSockets / Firebase)
- **Plugin system** for ruleset extensions

---

Would you like me to help you **generate the initial CMakeLists.txt**, **create the model headers**, or **design the JSON schema for Ruleset** next?