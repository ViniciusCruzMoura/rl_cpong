#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

struct entity_manager {
    size_t m_total_entities;
    struct entity *m_list;
    struct entity *m_toadd;
};

void update_entities(struct entity_manager *em);
struct entity *add_entity(struct entity_manager *em, enum entity_types tag);
struct entity *get_entities(struct entity_manager *em, enum entity_types etype);

#endif //ENTITY_MANAGER_H
