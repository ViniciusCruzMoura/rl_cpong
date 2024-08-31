#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

//#define MAX_ENTITY_MAP_ROW 5
//#define MAX_ENTITY_MAP_COLUMNS 32 * MAX_ENTITY_MAP_ROW
#define MAX_ENTITIES 128000

typedef struct EntityManager {
    size_t m_total_entities;
    //Entity *m_map[MAX_ENTITY_MAP_ROW][MAX_ENTITY_MAP_COLUMNS];
    Entity *m_vec[MAX_ENTITIES];
    Entity *m_to_add[MAX_ENTITIES];
} EntityManager;

void update_entities(EntityManager *em);
Entity *add_entity(EntityManager *em, EntityTypes tag);
Entity **get_entities(EntityManager *em, EntityTypes etype);

#endif //ENTITY_MANAGER_H
