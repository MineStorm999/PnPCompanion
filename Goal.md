# Overall
- Pen and Paper Companion
    - Important
        - Character Sheet
        - Combat Tracker
        - Ruleset
        - Dice Roller
    - Nice To have
        - AI DM assistant
        - TCP "Multiplayer"
        - "Rule Language"

# Detailed

## Important
### Character Sheet
- preconfigured
    - Name
    - Race
    - Inventory
    - Weapons
- configurable by ruleset
    - Class (or none at all)
    - Skills / SkillTree
    - Attitude

### Combat Tracker
- Initiative (NPC auto / on off)
- HP
    - history (on/off)
    - switch for damage taken/current hp
    - function to remove/add

- NPCs
    - Link to Ruleset entry
    - Function to add (and player)

### Ruleset
- Units
    - Predefined (as example)
        - Range (m)
        - Weight (kg)
        - Damage (dmg)
    - Configurable (can fork from examples (eg. different dmg forms, etc.))
        - Name
        - Shortform
        - Description
- Rule Entries
    - Title
    - Important Units
    - Image
    - Description
        - (hidden) rule code
    - Sub Entries (Treestructure of Rule Entries)
    - Template Entry
        - Defined in "Parent entry"
        - for example:
            - Creature (parent)
                - Template: hp, dmg, RK...
                - Child 1: hp: 10, dmg: 5, RK: 13...
                - Child 1: hp: 13, dmg: 4, RK: 11...
    













### Dice Roller
- Just dice rolling...
## Nice To have
### AI DM Assistant
- AI STT -> Plays FX and ambients

### TCP "Multiplayer"
- DM -> Server
    - Decides, what players can see at given time
        - Sends updates to clients
- Player -> Client
- Integration in Combat tracker



### Rule-Language
- every rule has a "Rule Code"
    - python like syntax
    - exposes
        - units defined in Units
        - Buttons