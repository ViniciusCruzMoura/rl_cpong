#ifndef ENTITY_H
#define ENTITY_H

typedef enum
{
    ENTITY_TYPE_NOTHING = 0,
    ENTITY_TYPE_OBJECT,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM,
} EntityTypes;

typedef struct Entity {
    struct Entity *next;
    bool m_active;
    size_t m_id;
    EntityTypes m_tag;
    CFlags flags;
    CInput input;
    CLifespan lifespan;
    CScore score;
    CAnimation animation;
    CCollision collision;
    CTransform transform;
    CShape shape;
} Entity;

uint32_t entity_size(Entity *head);
Entity *entity_create(Entity **head, EntityTypes tag, size_t id);
Entity *entity_search_by_tag(Entity *head, EntityTypes tag);
Entity *entity_search_by_id(Entity *head, size_t id);
void entity_remove_by_id(Entity **head, size_t id);
void entity_remove_by_tag(Entity **head, EntityTypes tag);
Entity *entity_append(Entity **head1, Entity *head2);
void entity_display(Entity *head);
void entity_free(Entity *head);

#endif //ENTITY_H
