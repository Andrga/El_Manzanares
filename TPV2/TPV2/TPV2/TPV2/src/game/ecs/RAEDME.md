# Entity-Component-System v3

This version implements only Entity-Component. Components inherit from the class Component, Entity maintains an array with a fixed number of (possible) components, and Manager maintains a list of entities. 

It also support groups of entities and handlers (assigning identifiers to entities for fast global access). Each entity belongs to a single group, resulting in a more efficient implementation. Entities keep no information on groups, everything is done in the manager.

The difference from v2 is in that we moved all methods from Entity to Manager, this way the user does not need to know anything about the Entity type, and will see it as entity_t. Later we can change the actual type of entity and it will still work with previous code.

