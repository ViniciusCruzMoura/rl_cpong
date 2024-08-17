#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#define MAX_ENTITY_MAP_ROW 4
#define MAX_ENTITY_MAP_COLUMNS 32 * MAX_ENTITY_MAP_ROW * 1000

typedef enum 
{
    ENTITY_TYPE_NOTHING = 0,
    ENTITY_TYPE_OBJECT,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
} EntityTypes;

typedef struct EntityManager {
    size_t m_total_entities;
    Entity *m_map[MAX_ENTITY_MAP_ROW][MAX_ENTITY_MAP_COLUMNS];
} EntityManager;

void update_entities(EntityManager *em);
Entity *add_entity(EntityManager *em, char * tag, EntityTypes type);

#endif //ENTITY_MANAGER_H
