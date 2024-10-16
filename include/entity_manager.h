#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

typedef struct EntityManager {
    size_t m_total_entities;
    Entity *m_list;
    Entity *m_toadd;
} EntityManager;

void update_entities(EntityManager *em);
Entity *add_entity(EntityManager *em, EntityTypes tag);
Entity *get_entities(EntityManager *em, EntityTypes etype);

#endif //ENTITY_MANAGER_H
