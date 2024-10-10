#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#define MAX_ENTITIES 128000

typedef struct EntityManager {
    size_t m_total_entities;
    Entity *m_vec[MAX_ENTITIES];
    Entity *m_to_add[MAX_ENTITIES];
} EntityManager;

void update_entities(EntityManager *em);
Entity *add_entity(EntityManager *em, EntityTypes tag);
Entity **get_entities(EntityManager *em, EntityTypes etype);

#endif //ENTITY_MANAGER_H
